#pragma once

#include "ast.hh" // template class interface

// AST implementation
template <typename T>
std::string default_print_leaf(T t)
{
  (void) t; // intented, as the signature cannot be changed
  return " o";
}

template <typename T>
std::string default_print_node(T t)
{
  (void) t; // intented, as the signature cannot be changed
  return "[*]";
}

template <typename T>
AST<T>::AST()
{}

template <typename T>
AST<T>::AST(T t, std::vector<AST<T>> sons) //TODO
{
  (void) t; (void) sons;//TODO
}

template <typename T>
T AST<T>::root() const //TODO
{
  throw "Empty tree";
}

template <typename T>
unsigned AST<T>::root_arity() const //TODO
{
  return 0;
}

template <typename T>
std::vector<AST<T>> AST<T>::sons() const //TODO
{
  return {};
}

template <typename T>
template <typename U>
AST<U> AST<T>::map(U (*f)(T)) const //TODO
{
  (void) f; //TODO
  return {};
}

template <typename T>
std::string AST<T>::to_string( \
        std::string (*print_node)(T), std::string (*print_leaf)(T), \
        unsigned dashes, unsigned spaces) const //TODO
{
  (void) print_node; (void) print_leaf; (void) dashes; (void) spaces; //TODO
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

// BinaryAST implementation
template <typename T>
BinaryAST<T>::BinaryAST()
  : AST<T>()
{}

template <typename T>
BinaryAST<T>::BinaryAST(T t, std::vector<AST<T>> sons)
  : AST<T>(t, sons)
{}

template <typename T>
std::vector<T> BinaryAST<T>::in_order_search() const //TODO
{
  return {};
}
