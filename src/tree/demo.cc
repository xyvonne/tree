#include <functional> // std::function
#include <iostream>

#include "../../include/tree/bin_tree.hh"

/* Type aliases. Note that we choose 2 different types for the nodes. */
using AST = BinaryTree<std::string>;
using Tre = Tree<int>;

/*
 * Common part for both demos (Tre and AST).
 */
template <typename T>
void demo_core \
       (const std::string& header,
        const Tree<T>& tree,
        const TreePrintCompanion<T>& pc,
        const std::function<T(T)>& mapped_function,
        const std::string& mapping_msg)
{
  /* Header: "Tree demo" or "BinaryTree demo". */
  std::cout << header;

  /* Printing. */
  std::cout << "Tree representation:\n" << tree.represent(pc);
  std::cout << "\nDefault tree pretty-printing:\n" << tree;
  std::cout << "\nNice tree pretty-printing:\n" << tree.to_string(pc);

  /* Statistics. */
  std::cout << "\nStatistics:";
  std::cout << "\nSize: " << tree.size();
  std::cout << "\nDepth: " << tree.depth();
  std::cout << "\nNumber of leaves: " << tree.nb_leaves();
  std::cout << "\nNumber of inner nodes: " << tree.nb_inner_nodes();
  try{ std::cout << "\nRoot value: " << tree.root_value(); }
  catch(const TreeException::EmptyTree& e) { std::cerr << e.what(); }
  try{ std::cout << "\nRoot arity: " << tree.root_arity(); }
  catch(const TreeException::EmptyTree& e) { std::cerr << e.what(); }
  try{ tree.root_children(); }
  catch(const TreeException::EmptyTree& e) { std::cerr << e.what(); }

  /* Root children. */
  std::cout << "\nChild #0 of the original tree:\n";
  auto child = tree.root_children()[0];
  std::cout << child.to_string(pc);
  std::cout << "\nChildren of this new tree:\n";
  auto children = child.root_children();
  for (size_t i = 0; i < children.size(); i++)
    std::cout
      << "Child #" << i << ":\n"
      << children[i].to_string(pc) << "\n";

  /* Mapping. */
  std::cout << mapping_msg; // "Applying <such function> to the tree..."
  std::cout << tree.map(mapped_function).to_string(pc); // Show the mapped tree

  /* Traversing. */
  std::cout << "\nTraversals of the original tree:";

  std::cout << "\nBreadth-first search: ";
  for (const auto& x : tree.breadth_first_search())
    std::cout << x << " ";

  std::cout << "\nPre-order search: ";
  for (const auto& x : tree.pre_order_search())
    std::cout << x << " ";

  std::cout << "\nPost-order search (=RPN for an arithmetic AST evaluator): ";
  for (const auto& x : tree.post_order_search())
    std::cout << x << " ";
}

/*
 * Binary tree demo.
 */
void binary_tree_demo()
{
  std::string header = "\n\n*** Binary tree demo ***\n\n";

  /* TreePrintCompanion setup. */
  std::function<std::string(std::string)> l \
    = [](std::string x) { return x; };
  std::function<std::string(std::string)> n \
    = [](std::string x) { return "[" + x + "]"; };
  TreePrintCompanion<std::string> pc(l, n, n, 0, 1);

  /* Mapping setup. */
  std::function<std::string(std::string)> mapped_function \
    = [](std::string x){ return "{" + x + "}"; };
  std::string mapping_msg \
    = "Applying x-> \"{\" + x \"}\" to all nodes of the original tree:\n";

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

  /* Run the demo. */
  demo_core<std::string>(header, ast, pc, mapped_function, mapping_msg);

  /* Specific part for BinaryTree: in-order search. */
  std::cout << "\nIn-order search: ";
  for (const auto& x : ast.in_order_search())
    std::cout << x << " ";
  std::cout << "\n";
}

/*
 * Generic tree demo.
 */
void generic_tree_demo()
{
  std::string header = "\n*** Generic tree demo ***\n\n";

  /* TreePrintCompanion setup. */
  std::function<std::string(int)> l = [](int x) { return std::to_string(x); };
  std::function<std::string(int)> n \
    = [](int x) { return "[" + std::to_string(x) + "]"; };
  std::function<std::string(int)> r \
    = [](int x) { return "[[" + std::to_string(x) + "]]"; };
  TreePrintCompanion<int> pc(l, n, r, 0, 1);

  /* Mapping setup. */
  std::function<int(int)> mapped_function = [](int x){ return -x; };
  std::string mapping_msg \
    = "Applying x->-x to all nodes of the original tree:\n";

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

  /* Run the demo. */
  demo_core<int>(header, tree, pc, mapped_function, mapping_msg);
}

/*
 * Main function.
 */
int main(void)
{
  generic_tree_demo();
  binary_tree_demo();
  return 0;
}
