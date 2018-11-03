#pragma once

#include <functional> // std::function
#include <vector>

/* TreePrintCompanion interface */

// TODO: documentation

/// PrintFunction<T>: type alias for functions mapping T to std::string
template <typename T>
using PrintFunction = std::function<std::string(T)>;

/// Default printing functions for root, leaves and other nodes.
template <typename T>
std::string default_print_root(const T& t);
template <typename T>
std::string default_print_node(const T& t);
template <typename T>
std::string default_print_leaf(const T& t);

/// The class itself
template <typename T>
class TreePrintCompanion
{
  public:
    /// Trivial constructor.
    TreePrintCompanion( \
        const PrintFunction<T>& print_root = default_print_root<T>, \
        const PrintFunction<T>& print_node = default_print_node<T>, \
        const PrintFunction<T>& print_leaf = default_print_leaf<T>, \
        int dashes = 2, \
        int spaces = 1);

    /// Trivial getters.
    PrintFunction<T> print_root() const;
    PrintFunction<T> print_node() const;
    PrintFunction<T> print_leaf() const;
    int dashes() const;
    int spaces() const;

  private:
    /// Attributes, as already discussed with the constructor.
    PrintFunction<T> print_root_;
    PrintFunction<T> print_node_;
    PrintFunction<T> print_leaf_;
    const int dashes_;
    const int spaces_;
};

#include "tree_pc.hxx" // template class implementation
