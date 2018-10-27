#include <iostream>

#include "ast.hh"

double f(int x){return 1/(x*x+1); }

int main(void)
{
  auto ast = BinaryAST<int>();
  auto ast2 = BinaryAST<int>(0); (void) ast2;
  std::vector<int> v;

  try{ ast.root(); } catch(...){}
  ast.root_arity();
  ast.sons();
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
