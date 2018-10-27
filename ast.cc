#include <iostream>

#include "ast.hh"

int main(void)
{
  auto ast = AST<int>();
  std::cout << ast.zero() << std::endl;
  return 0;
}

