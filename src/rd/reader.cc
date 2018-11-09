#include <cerrno>
#include <dirent.h>
#include <functional> // std::function
#include <stack>
#include <system_error>

#include "../../include/rd/reader.hh"
#include "../../include/tree/tree.hh"

DirectoryReader::DirectoryReader(const Path& path)
  : path_(path)
{}

DirectoryReader::DirectoryReader(const String& string)
  : path_(string.c_str()) // .c_str(): convert a std::string to a char*
{}

std::string DirectoryReader::read_directory() const
{
  /* Read the directory table, and generate a tree from it. */
  auto tree = Tree<String>(table());

  /* Keep only the basename from a directory, e.g. replace a/b/c/d with d */
  std::function<String(String)> keep_basenames_only = [](String s)
  {
    size_t idx = s.rfind("/");
    return (idx == std::string::npos) ? s : s.substr(idx + 1);
  };
  auto tree2 = tree.map(keep_basenames_only);

  /* TreePrintCompanion setup. */
  std::function<String(String)> print_leaf = [](String x) { return x; };
  std::function<String(String)> \
    print_root = [this](String x) { (void) x; return path_; };
  TreePrintCompanion<String> pc(print_leaf, print_leaf, print_root);

  /* Generate the string to be pretty-printed. */
  std::string s = tree2.to_string(pc) + "\n";
  s += std::to_string(tree2.size() - 1) + " directories\n";
  return s;
}

/*
 * Reference: http://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html
 *
 * We sticked to a POSIX implementation, because we were not able to install
 * the recent C++17 libraries (#include<filesystem> ...), which would have
 * yet simplified our life, and avoided the mix of both C and C++ styles.
 */
std::vector<Ptr<String>>
DirectoryReader::subdirectories(const String& current_dir)
{
  /* Try to open the directory. */
  DIR* dirp = opendir(current_dir.c_str());
  if (!dirp) // In case of failure, we assume that current_dir has no subdirs
    return {};

  /* If the directory was opened successfully, get its contents. */
  std::vector<Ptr<String>> out;
  dirent* dp = nullptr;
  while ((dp = readdir(dirp)) != nullptr)
  {
    String subdir = dp->d_name; // convert dp->d_name to a std::string
    if (subdir[0] != '.' and dp->d_type == DT_DIR) // keep only visible dirs
    {
      // and push them to the stack
      out.push_back(std::make_shared<String>(current_dir + "/" + subdir));
    }
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
  std::stack<Ptr<String>> s;
  Table<String> out;
  s.push(std::make_shared<String>(String(path_)));

  while (!s.empty())
  {
    const auto current_dir = s.top();
    s.pop();

    const auto subdirs = subdirectories(*current_dir);
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
