#pragma once

#include "ast.hh" // template class interface

#include "error.hh"

/* AST implementation */

template <typename T>
AST<T>::AST()
{}

template <typename T>
AST<T>::AST(const T& t, const std::vector<AST<T>>& children) //TODO
{
  (void) t; (void) children;//TODO
}

template <typename T>
T AST<T>::root() const //TODO
{
  throw EmptyTree("[ERROR] Calling AST<T>::root() failed: Empty tree");
}

template <typename T>
unsigned AST<T>::root_arity() const //TODO
{
  return 0;
}

template <typename T>
std::vector<AST<T>> AST<T>::children() const //TODO
{
  return {};
}

template <typename T>
template <typename U>
AST<U> AST<T>::map(std::function<U(T)> f) const //TODO
{
  (void) f; //TODO
  return {};
}

template <typename T>
std::string AST<T>::to_string(const ASTPrintCompanion<T>& pc) const //TODO
{
  (void) pc; //TODO
  return {};
}

template <typename T>
std::vector<T> AST<T>::pre_order_search() const //TODO
{
  return {};
}

template <typename T>
std::vector<T> AST<T>::post_order_search() const //TODO
{
  return {};
}

template <typename T>
std::vector<T> AST<T>::breadth_first_search() const //TODO
{
  return {};
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const AST<T>& ast)
{
  return os << ast.to_string();
}
