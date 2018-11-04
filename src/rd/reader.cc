#include <cerrno>
#include <dirent.h>
#include <stack>
#include <system_error>

#include "../../include/rd/reader.hh"

DirectoryReader::DirectoryReader(const Path& path)
  : path_(path)
{}

DirectoryReader::DirectoryReader(const String& string)
  : path_(string.c_str()) // .c_str(): convert a std::string to a char*
{}

/*
 * Reference: http://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html
 *
 * We sticked to a POSIX implementation, because we were not able to install
 * the recent C++17 libraries (#include<filesystem> ...), which would have
 * yet simplified our life, and avoided the mix of both C and C++ styles.
 */
std::vector<String> DirectoryReader::subdirectories(const String& current_dir)
{
  /* Try to open the directory. */
  DIR* dirp = opendir(current_dir.c_str());
  if (!dirp) // In case of failure, we assume that current_dir has no subdirs
    return {};

  /* If the directory was opened successfully, get its contents. */
  std::vector<String> out;
  dirent* dp = nullptr;
  while ((dp = readdir(dirp)) != nullptr)
  {
    String subdir = dp->d_name; // convert dp->d_name to a std::string
    if (subdir[0] != '.' and dp->d_type == DT_DIR) // keep only visible dirs
      out.push_back(current_dir + "/" + subdir); // and push them to the stack
  }
  closedir(dirp);

  return out;
}

Table<String> DirectoryReader::table() const
{
  /* Try to open 'path_' as a directory, and quit prematurely if it fails. */
  DIR* dirp = opendir(path_);
  if (!dirp) // 'path_' cannot be opened as a directory
  {
    std::error_condition econd \
      = std::generic_category().default_error_condition(errno);
    throw econd;
  }
  closedir(dirp);

  /*
   * Now that we know that 'path_' is a directory, we read recursively
   * its subdirectories using a stack, and store the results in the table.
   */
  std::stack<String> s;
  Table<String> out;
  s.push(String(path_));

  while (!s.empty())
  {
    String current_dir = s.top();
    s.pop();

    auto subdirs = subdirectories(current_dir);
    out.push_back({current_dir, subdirs});

    /*
     * rit is a reverse iterator; we use it to push the subdirs onto
     * the stack in the right order.
     */
    for (auto rit = subdirs.rbegin(); rit != subdirs.rend(); rit++)
      s.push(*rit);
  }
  return out;
}
