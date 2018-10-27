#pragma once

#include <vector>

// Type aliases
using Id = std::vector<unsigned>;

// Forward declarations
template <typename T>
class AST;

template <typename T>
class BinaryAST;

// ASTNode interface
template <typename T>
class ASTNode
{
  friend AST<T>;
  friend BinaryAST<T>;

  public:

  private:
  T value_;
  Id id_;
};

// AST interface
template <typename T>
std::string default_print_leaf(T t);

template <typename T>
std::string default_print_node(T t);

template <typename T>
class AST
{
  public:
    AST();
    AST(T t, std::vector<AST<T>> sons = {});

    T root() const;

    unsigned root_arity() const;
    std::vector<AST<T>> sons() const;

    template <typename U>
      AST<U> map(U (*f)(T)) const;

    std::string to_string( \
        std::string (*print_node)(T) = default_print_node, \
        std::string (*print_leaf)(T) = default_print_leaf, \
        unsigned dashes = 2, \
        unsigned spaces = 1) const;

    std::vector<T> pre_order_search() const;
    std::vector<T> post_order_search() const;
    std::vector<T> breadth_first_search() const;
  protected:
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const AST<T>& ast);

// BinaryAST interface
template <typename T>
class BinaryAST : public AST<T>
{
  public:
    BinaryAST();
    BinaryAST(T t, std::vector<AST<T>> sons = {});
    std::vector<T> in_order_search() const;
};

#include "ast.hxx" // template class implementation
