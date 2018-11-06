#pragma once

#include <functional> // std::function

/**
 * This class is a wrapper containing all the objects needed for
 * pretty-printing Trees. It has no other methods than trivial getters.
 * The attributes are:
 * - print_leaf: a function mapping T to std::string describing how to print
 *   the leaves,
 *  - print_node: object of the same type, for printing inner nodes,
 *  - print_root: object of the same type, for printing the root,
 *  - dashes: number of dashes to print on each line,
 *  - spaces: number of spaces to print before each node.
 *  All these attributes can be assigned default values to, see the
 *  constructor below.
 */

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
    /// Attributes, as already discussed with the documentation class.
    PrintFunction<T> print_leaf_;
    PrintFunction<T> print_node_;
    PrintFunction<T> print_root_;
    const unsigned dashes_;
    const unsigned spaces_;
};

#include "tree_pc.hxx" /* template class implementation */
