#pragma once

#include <functional> // std::function
#include <vector>

/* ASTPrintCompanion interface */

/// PrintFunction<T>: alias type for functions mapping T to std::string
template <typename T>
using PrintFunction = std::function<std::string(T)>;

/// Default printing functions for root, leaves and other nodes.
template <typename T>
std::string default_print_root(const T& t);
template <typename T>
std::string default_print_leaf(const T& t);
template <typename T>
std::string default_print_node(const T& t);

/// The class itself
template <typename T>
class ASTPrintCompanion
{
  public:
    /// Trivial constructor. TODO: describe the attributes
    ASTPrintCompanion( \
        const PrintFunction<T>& print_node = default_print_node<T>, \
        const PrintFunction<T>& print_leaf = default_print_leaf<T>, \
        const PrintFunction<T>& print_root = default_print_root<T>, \
        int dashes = 2, \
        int spaces = 1);

    /// Trivial getters.
    PrintFunction<T> print_leaf() const;
    PrintFunction<T> print_node() const;
    PrintFunction<T> print_root() const;
    int dashes() const;
    int spaces() const;

  private:
    /// Attributes, as already discussed with the constructor.
    PrintFunction<T> print_leaf_;
    PrintFunction<T> print_node_;
    PrintFunction<T> print_root_;
    const int dashes_;
    const int spaces_;
};

#include "ast_pc.hxx" // template class implementation
