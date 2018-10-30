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
BinaryAST<T>::BinaryAST(const T& t, const BinaryAST<T>& left)
: AST<T>(t, {left})
{}

template <typename T>
BinaryAST<T>::BinaryAST(const T& t, \
    const BinaryAST<T>& left, const BinaryAST<T>& right)
: AST<T>(t, {left, right})
{}

template <typename T>
template <typename U>
BinaryAST<U> BinaryAST<T>::map(std::function<U(T)> f) const
{
  BinaryAST<U> ast;
  for (const auto& node : AST<T>::nodes_)
    ast.AST<U>::nodes_.push_back({f(node.first), node.second});
  return ast;
}

template <typename T>
std::vector<T> BinaryAST<T>::in_order_search() const //TODO
{
  return {};
}
