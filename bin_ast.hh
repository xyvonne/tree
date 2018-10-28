#pragma once

#include <vector>

#include "ast.hh"

/* BinaryAST interface */

template <typename T>
class BinaryAST : public AST<T>
{
  template <typename U>
    friend class BinaryAST; // required for BinaryAST mapping

  public:
  BinaryAST();
  BinaryAST(const T& t);
  BinaryAST(const T& t, const BinaryAST<T>& left, const BinaryAST<T>& right);

  template <typename U>
    BinaryAST<U> map(std::function<U(T)> f) const;

  std::vector<T> in_order_search() const;
};

#include "bin_ast.hxx" // template class implementation
