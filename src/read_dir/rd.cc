#include <functional>
#include <iostream>
#include <system_error>

#include "../../include/read_dir/read_dir.hh"
#include "../../include/tree/tree.hh"
#include "../../include/tree/tree_error.hh"

/* Check command-line arguments. */
std::string check_args(int argc, char* argv[])
{
  if (argc == 1)
    return ".";

  if (argc != 2)
  {
    std::cerr << "Usage: rd <path>\n";
    exit(2);
  }

  return std::string(argv[1]);
}

/* Read the directory tree, and generate a string from it. */
std::string read_directory(const std::string& path)
{
  /* Read the directory table, and generate a tree from it. */
  auto table = DirectoryReader(path).table();
  auto tree = Tree(table);

  /* Keep only the basename from a directory, e.g. replace a/b/c/d with d */
  std::function<std::string(std::string)> basenames_only = [](std::string s)
  {
    size_t idx = s.rfind("/");
    return (idx == std::string::npos) ? s : s.substr(idx + 1);
  };
  auto tree2 = tree.map(basenames_only);

  /* TreePrintCompanion setup. */
  std::function<std::string(std::string)> \
    print_node = [](std::string x) { return x; };
  TreePrintCompanion<std::string> pc(print_node, print_node, print_node);

  /* Generate the string to be pretty-printed. */
  std::string s = tree2.to_string(pc) + "\n";
  s += std::to_string(tree2.size() - 1) + " directories\n";
  return s;
}

/* Main function. */
int main(int argc, char* argv[])
{
  const std::string path = check_args(argc, argv);
  try
  {
    std::cout << read_directory(path);
  }
  catch(const std::error_condition& econd)
  {
    std::cerr << path + " [error opening dir]\n\n0 directories\n";
    return 1;
  }

  return 0;
}
