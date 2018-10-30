#include <functional> // std::function
#include <iostream>

#include "bin_ast.hh"
#include "error.hh"

int main(void)
{
 /* Setup the ASTPrintCompanion. */
  std::function<std::string(int)> print_leaf_int \
    = [](int x) { return std::to_string(x); };
  std::function<std::string(int)> print_node_int \
    = [](int x) { return "[" + std::to_string(x) + "]"; };
  std::function<std::string(int)> print_root_int \
    = [](int x) { return "[[" + std::to_string(x) + "]]"; };
  ASTPrintCompanion<int> pc(print_node_int, print_leaf_int, print_root_int, \
      0, 1);

  /* Build a tree. */
  auto ast2 = AST<int>(2);
  auto ast3 = AST<int>(3);
  auto ast4 = AST<int>(4);
  auto ast6 = AST<int>(6);
  auto ast7 = AST<int>(7);
  auto ast8 = AST<int>(8);
  auto ast9 = AST<int>(9);
  auto ast1 = AST<int>(1, {ast2, ast3, ast4});
  auto ast5 = AST<int>(5, {ast6, ast7});
  auto ast0 = AST<int>(0, {ast1, ast5, ast8, ast1, ast9});
  auto ast  = AST<int>(3, {ast0, ast3});

  /* Printing. */
  std::cout << "Tree representation:\n" << ast.represent(pc);
  std::cout << "\nTree pretty-printing:\n" << ast.to_string(pc);

  /* Statistics. */
  std::cout << "\nStatistics:";
  std::cout << "\nSize: " << ast.size();
  std::cout << "\nDepth: " << ast.depth();
  try{ std:: cout << "\nRoot: " << ast.root(); }
  catch(const EmptyTree& e) { std::cerr << e.what(); }
  try{ std:: cout << "\nRoot arity: " << ast.root_arity(); }
  catch(const EmptyTree& e) { std::cerr << e.what(); }

  /* Mapping. */
  std::function<int(int)> g = [](int x){ return -x; };
  std::cout << "\n\nApply x->-x on all nodes:\n" << ast.map(g).to_string(pc);

  /* Traversals. */
  std::cout << "\nTraversals of the original tree:";

  std::cout << "\nPre-order: ";
  auto v = ast.pre_order_search();
  for (auto e : v)
    std::cout << e << " ";

  std::cout << "\nPost-order: ";
  auto w = ast.post_order_search();
  for (auto e : w)
    std::cout << e << " ";

  std::cout << "\nBFS: ";
  auto x = ast.breadth_first_search();
  for (auto e : x)
    std::cout << e << " ";

  std::cout << "\n";
  return 0;
}
