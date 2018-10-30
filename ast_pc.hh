#pragma once

#include <functional> // std::function
#include <vector>

/* ASTPrintCompanion interface */

// PrintFunction<T>: alias type for functions mapping T to std::string
template <typename T>
using PrintFunction = std::function<std::string(T)>;

/// Default printing functions for root, leaves and inner nodes
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
    /// Trivial constructor
    ASTPrintCompanion( \
        const PrintFunction<T>& print_node = default_print_node<T>, \
        const PrintFunction<T>& print_leaf = default_print_leaf<T>, \
        const PrintFunction<T>& print_root = default_print_root<T>, \
        unsigned dashes = 2, \
        unsigned spaces = 1);

    /// Trivial getters
    PrintFunction<T> print_leaf() const;
    PrintFunction<T> print_node() const;
    PrintFunction<T> print_root() const;
    unsigned dashes() const;
    unsigned spaces() const;

  private:
    //TODO: document this
    PrintFunction<T> print_leaf_;
    PrintFunction<T> print_node_;
    PrintFunction<T> print_root_;
    const unsigned dashes_;
    const unsigned spaces_;
};

#include "ast_pc.hxx" // template class implementation
