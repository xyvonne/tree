#include <functional> // std::function
#include <iostream>

#include "bin_ast.hh"
#include "error.hh"

int main(void)
{
  ASTPrintCompanion<int> pc;
  std::cout << pc.print_leaf()(1) << std::endl;
  std::cout << pc.print_node()(1) << std::endl;

  auto ast = BinaryAST<int>();
  auto ast2 = BinaryAST<int>(0); (void) ast2;
  std::vector<int> v;

  try{ ast.root(); } catch(const EmptyTree& e) { std::cerr << e.what(); }
  ast.root_arity();
  ast.children();
  std::function<double(int)> f = [](int x){return 1/(x*x+1); };
  ast.map(f);

  std::cout << ast;

  ast.pre_order_search();
  ast.post_order_search();
  ast.in_order_search();

  v = ast.breadth_first_search();
  for (int e : v)
    std::cout << e << " ";
  std::cout << "\n";
  return 0;
}
