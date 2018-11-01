#include <functional>
#include <iostream>
#include <system_error>

#include "../../include/read_dir/read_dir.hh"
#include "../../include/tree/bin_tree.hh"
#include "../../include/tree/tree_error.hh"

/* Type aliases. */
using String = std::string;
using Tre = Tree<int>;
using AST = BinaryTree<String>;

/*
 * Generic tree demo
 */

void generic_tree_demo()
{
  std::cout << "\n*** Generic tree demo ***\n\n";

  /* TreePrintCompanion setup. */
  std::function<String(int)> l = [](int x) { return std::to_string(x); };
  std::function<String(int)> n \
    = [](int x) { return "[" + std::to_string(x) + "]"; };
  std::function<String(int)> r \
    = [](int x) { return "[[" + std::to_string(x) + "]]"; };
  TreePrintCompanion<int> pc(r, n, l, 0, 1);

  /* Tree building. */
  Tre tree2(2);
  Tre tree3(3);
  Tre tree4(4);
  Tre tree6(6);
  Tre tree7(7);
  Tre tree8(8);
  Tre tree9(9);
  Tre tree1(1, {tree2, tree3, tree4});
  Tre tree5(5, {tree6, tree7});
  Tre tree0(0, {tree1, tree5, tree8, tree1, tree9});
  Tre tree(3, {tree0, tree3});

  /* Printing. */
  std::cout << "Tree representation:\n" << tree.represent(pc);
  std::cout << "\nTree pretty-printing:\n" << tree.to_string(pc);
  std::cout << "\nDefault pretty-printing:\n" << tree;

  /* Statistics. */
  std::cout << "\nStatistics:";
  std::cout << "\nSize: " << tree.size();
  std::cout << "\nDepth: " << tree.depth();
  try{ std:: cout << "\nRoot: " << tree.root(); }
  catch(const EmptyTree& e) { std::cerr << e.what(); }
  try{ std:: cout << "\nRoot arity: " << tree.root_arity(); }
  catch(const EmptyTree& e) { std::cerr << e.what(); }

  /* Mapping. */
  std::function<int(int)> g = [](int x){ return -x; };
  std::cout << "\n\nApplying x->-x to all nodes:\n";
  std::cout << tree.map(g).to_string(pc);

  /* Traversing. */
  std::cout << "\nTraversals of the original tree:";

  std::cout << "\nPre-order search: ";
  auto vi = tree.pre_order_search();
  for (auto e : vi)
    std::cout << e << " ";

  std::cout << "\nPost-order search: ";
  auto wi = tree.post_order_search();
  for (auto e : wi)
    std::cout << e << " ";

  std::cout << "\nBreadth-first search: ";
  auto xi = tree.breadth_first_search();
  for (auto e : xi)
    std::cout << e << " ";
}

/*
 * Binary tree demo
 */

void binary_tree_demo()
{
  std::cout << "\n\n*** Binary tree demo ***\n\n";

  /* TreePrintCompanion setup. */
  std::function<String(String)> l = [](String x) { return x; };
  std::function<String(String)> n = [](String x) { return "[" + x + "]"; };
  std::function<String(String)> r = [](String x) { return "[" + x + "]"; };
  TreePrintCompanion<String> pc(r, n, l, 0, 1);

  /* Binary tree building (here, an AST). */
  AST ast3("3");
  AST ast4("4");
  AST astm1("-", ast3, ast4);
  AST ast1("-", astm1);
  AST ast6("6");
  AST ast8("8");
  AST astp8("+", ast8);
  AST ast48("*", ast6, astp8);
  AST ast("+", ast1, ast48);

  /* Printing. */
  std::cout << "Tree representation:\n" << ast.represent(pc);
  std::cout << "\nTree pretty-printing:\n" << ast.to_string(pc);
  std::cout << "\nDefault pretty-printing:\n" << ast;

  /* Statistics. */
  std::cout << "\nStatistics:";
  std::cout << "\nSize: " << ast.size();
  std::cout << "\nDepth: " << ast.depth();
  try{ std:: cout << "\nRoot: " << ast.root(); }
  catch(const EmptyTree& e) { std::cerr << e.what(); }
  try{ std:: cout << "\nRoot arity: " << ast.root_arity(); }
  catch(const EmptyTree& e) { std::cerr << e.what(); }

  /* Mapping. */
  std::function<String(String)> g = [](String x){ return "{" + x + "}"; };
  std::cout << "\n\nApplying x-> \"{\" + x \"}\" to all nodes:\n";
  std::cout << ast.map(g).to_string(pc);

  /* Traversing. */
  std::cout << "\nTraversals of the original tree:";

  std::cout << "\nPre-order search: ";
  auto vs = ast.pre_order_search();
  for (auto e : vs)
    std::cout << e << " ";

  std::cout << "\nIn-order search: ";
  auto ws = ast.in_order_search();
  for (auto e : ws)
    std::cout << e << " ";

  std::cout << "\nPost-order search (RPN): ";
  auto xs = ast.post_order_search();
  for (auto e : xs)
    std::cout << e << " ";

  std::cout << "\nBreadth-first search: ";
  auto ys = ast.breadth_first_search();
  for (auto e : ys)
    std::cout << e << " ";

  std::cout << "\n";
}

/*
 * Directory reading demo
 */

void read_dir_demo()
{
  std::cout << "Enter path: ";
  String name;
  std::getline(std::cin, name);
  if (name.size() == 0)
    name += ".";

  /* TreePrintCompanion setup. */
  std::function<String(String)> l = [](String x) { return x; };
  std::function<String(String)> n = [](String x) { return x; };
  std::function<String(String)> r = [](String x) { return x; };
  TreePrintCompanion<String> pc(r, n, l);

  String s;
  try
  {
    auto table = DirectoryReader(name).table();

    /* Keep only the basename from a directory, e.g. replace a/b/c/d with d */
    std::function<String(String)> keep_basenames_only \
      = [](String s){ \
        size_t idx = s.rfind("/"); \
          return idx == std::string::npos ? s : s.substr(idx + 1); };

    auto tree = Tree(table).map(keep_basenames_only);

    s = tree.to_string(pc) + "\n";
    s += std::to_string(tree.size() - 1);
  }

  catch(const std::error_condition& econd) // Invalid path
  {
    s = name +" [error opening dir]\n\n0";
  }

  s +=" directories\n";
  std::cout << s;
}

int main(void)
{
  generic_tree_demo();
  binary_tree_demo();
  read_dir_demo();
  return 0;
}
