#include <functional> // std::function
#include <iostream>

#include "bin_tree.hh"
#include "error.hh"

int main(void)
{
 /* Setup the TreePrintCompanion. */
  std::function<std::string(int)> print_leaf_int \
    = [](int x) { return std::to_string(x); };
  std::function<std::string(int)> print_node_int \
    = [](int x) { return "[" + std::to_string(x) + "]"; };
  std::function<std::string(int)> print_root_int \
    = [](int x) { return "[[" + std::to_string(x) + "]]"; };
  TreePrintCompanion<int> pc(print_node_int, print_leaf_int, print_root_int, \
      0, 1);

  /* Build a tree. */
  auto tree2 = Tree<int>(2);
  auto tree3 = Tree<int>(3);
  auto tree4 = Tree<int>(4);
  auto tree6 = Tree<int>(6);
  auto tree7 = Tree<int>(7);
  auto tree8 = Tree<int>(8);
  auto tree9 = Tree<int>(9);
  auto tree1 = Tree<int>(1, {tree2, tree3, tree4});
  auto tree5 = Tree<int>(5, {tree6, tree7});
  auto tree0 = Tree<int>(0, {tree1, tree5, tree8, tree1, tree9});
  auto tree  = Tree<int>(3, {tree0, tree3});

  /* Printing. */
  std::cout << "Tree representation:\n" << tree.represent(pc);
  std::cout << "\nTree pretty-printing:\n" << tree.to_string(pc);

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
  std::cout << "\n\nApply x->-x on all nodes:\n" << tree.map(g).to_string(pc);

  /* Traversals. */
  std::cout << "\nTraversals of the original tree:";

  std::cout << "\nPre-order search: ";
  auto v = tree.pre_order_search();
  for (auto e : v)
    std::cout << e << " ";

  std::cout << "\nPost-order search: ";
  auto w = tree.post_order_search();
  for (auto e : w)
    std::cout << e << " ";

  std::cout << "\nBreadth-first search: ";
  auto x = tree.breadth_first_search();
  for (auto e : x)
    std::cout << e << " ";

  std::cout << "\n";
  return 0;
}
