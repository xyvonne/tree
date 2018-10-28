#pragma once

#include <functional> // std::function
#include <vector>

#include "ast_pc.hh"

/* AST interface */

template <typename T>
using Node = std::pair<T, std::vector<size_t>>;

template <typename T>
using Nodes = std::vector<Node<T>>;

template <typename T>
class AST
{
  template <typename U>
    friend class AST; // required for AST mapping

public:
    AST();
    AST(const T& t, const std::vector<AST<T>>& children = {});

    T root() const;

    size_t root_arity() const;
    std::vector<AST<T>> children() const;

    template <typename U>
      AST<U> map(std::function<U(T)> f) const;

    std::string to_string(const ASTPrintCompanion<T>& pc = {}) const;

    std::vector<T> pre_order_search() const;
    std::vector<T> post_order_search() const;
    std::vector<T> breadth_first_search() const;

  protected:
    Nodes<T> nodes_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const AST<T>& ast);

#include "ast.hxx" // template class implementation
