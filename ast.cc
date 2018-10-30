#include <functional> // std::function
#include <iostream>

#include "bin_ast.hh"
#include "error.hh"

int main(void)
{
#if 1
  std::function<std::string(int)> print_leaf_int \
    = [](int x) { return std::to_string(x); };
  std::function<std::string(int)> print_node_int \
    = [](int x) { return "[" + std::to_string(x) + "]"; };
  std::function<std::string(int)> print_root_int \
    = [](int x) { return "[[" + std::to_string(x) + "]]"; };
  ASTPrintCompanion<int> pc(print_node_int, print_leaf_int, print_root_int);

  //std::function<double(int)> f = [](int x){ return x+1; };
#endif

#if 0
  std::function<std::string(std::string)> print_node_str \
    = [](std::string x) { return x; };
  ASTPrintCompanion<std::string> pc(print_node_str);

  auto ast1 = AST<std::string>("1");
  auto ast2 = AST<std::string>("2");
  auto ast4 = AST<std::string>("+", {ast1, ast2});
  auto ast3 = AST<std::string>("3");
  auto ast  = AST<std::string>("-", {ast4, ast3});
#endif

#if 1
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

  auto ast = ast0; //.map(f);

  std::cout << "ast:\n" << ast.represent(pc);
#endif

#if 0
  auto ast1 = BinaryAST<double>(2.5);
  std::function<double(double)> sqr = [](double x){ return x * x; };
  auto ast2(ast1);
  auto ast3 = ast2.map(sqr);
  auto ast4 = BinaryAST<double>(5.1, ast1, ast2);

  std::cout << "ast 4:\n " << ast4.to_string(pc);
  std::cout << " -(ast 4)\n: " << ast4.map(f).to_string(pc);

  auto ast(ast1);
  try{ std:: cout << "Root: " << ast1.root() << std::endl; }
  catch(const EmptyTree& e) { std::cerr << e.what(); }
  try{ std:: cout << "Arity: " << ast1.root_arity() << std::endl; }
  catch(const EmptyTree& e) { std::cerr << e.what(); }
  ast.children();

  ast.pre_order_search();
  ast.post_order_search();
  ast.in_order_search();
#endif

  auto v = ast.pre_order_search();
  std::cout << "\nPre-order: ";
  for (auto e : v)
    std::cout << e << " ";

  auto w = ast.post_order_search();
  std::cout << "\nPost-order: ";
  for (auto e : w)
    std::cout << e << " ";

  auto x = ast.breadth_first_search();
  std::cout << "\nBFS: ";
  for (auto e : x)
    std::cout << e << " ";

  std::cout << "\nTree depth: " << ast.depth();

  std::cout << "\n";
  return 0;
}
