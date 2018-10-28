#pragma once

#include "bin_ast.hh" // template class interface

/* BinaryAST implementation */

template <typename T>
BinaryAST<T>::BinaryAST()
  : AST<T>()
{}

template <typename T>
BinaryAST<T>::BinaryAST(const T& t)
  : AST<T>(t, {})
{}

template <typename T>
BinaryAST<T>::BinaryAST(const T& t, \
    const BinaryAST<T>& left, const BinaryAST<T>& right)
: AST<T>(t, {left, right})
{}

template <typename T>
std::vector<T> BinaryAST<T>::in_order_search() const //TODO
{
  return {};
}
