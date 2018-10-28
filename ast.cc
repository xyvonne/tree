#include <functional> // std::function
#include <iostream>

#include "bin_ast.hh"
#include "error.hh"

int main(void)
{
  std::function<std::string(double)> print_node \
    = [](double x) { return std::to_string(x); };
  ASTPrintCompanion<double> pc(print_node);

std::function<double(double)> f = [](double x){ return -x; };

#if 0
auto ast2 = AST<double>(2);
auto ast3 = AST<double>(3);
auto ast4 = AST<double>(4);
auto ast6 = AST<double>(6);
auto ast7 = AST<double>(7);
auto ast8 = AST<double>(8);
auto ast9 = AST<double>(9);
auto ast1 = AST<double>(1, {ast2, ast3, ast4});
auto ast5 = AST<double>(5, {ast6, ast7});
auto ast0 = AST<double>(0, {ast1, ast5, ast8, ast1, ast9});

auto ast = ast0.map(f);

std::cout << "ast:\n" << ast.to_string(pc);
#endif

#if 1
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

  auto v = ast.breadth_first_search();
  for (int e : v)
    std::cout << e << " ";
  std::cout << "\n";
#endif
  return 0;
}
