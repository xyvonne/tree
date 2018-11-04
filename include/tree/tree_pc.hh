#pragma once

#include <functional> // std::function

/// Type alias for functions mapping T to std::string
template <typename T>
using PrintFunction = std::function<std::string(T)>;

/// Default printing functions for leaves, inner nodes and root.
template <typename T>
std::string default_print_leaf(const T& t);
template <typename T>
std::string default_print_node(const T& t);
template <typename T>
std::string default_print_root(const T& t);

/* TreePrintCompanion interface. */

template <typename T>
class TreePrintCompanion
{
  public:
    /// Trivial constructor.
    TreePrintCompanion( \
        const PrintFunction<T>& print_leaf = default_print_leaf<T>, \
        const PrintFunction<T>& print_node = default_print_node<T>, \
        const PrintFunction<T>& print_root = default_print_root<T>, \
        unsigned dashes = 2, \
        unsigned spaces = 1);

    /// Trivial getters.
    PrintFunction<T> print_leaf() const;
    PrintFunction<T> print_node() const;
    PrintFunction<T> print_root() const;
    unsigned dashes() const;
    unsigned spaces() const;

  private:
    /// Attributes, as already discussed with the constructor.
    PrintFunction<T> print_leaf_;
    PrintFunction<T> print_node_;
    PrintFunction<T> print_root_;
    const unsigned dashes_;
    const unsigned spaces_;
};

#include "tree_pc.hxx" /* template class implementation */
