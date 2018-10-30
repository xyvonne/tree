#pragma once

#include "ast_pc.hh" // template class interface

/* ASTPrintCompanion implementation */

template <typename T>
std::string default_print_leaf(const T& t)
{
  (void) t; // intended, as the signature cannot be changed
  return "o";
}

template <typename T>
std::string default_print_node(const T& t)
{
  (void) t; // intended, as the signature cannot be changed
  return "[*]";
}

template <typename T>
std::string default_print_root(const T& t)
{
  (void) t; // intended, as the signature cannot be changed
  return "[[ROOT]]";
}

template <typename T>
ASTPrintCompanion<T>::ASTPrintCompanion( \
    const PrintFunction<T>& print_node, \
    const PrintFunction<T>& print_leaf, \
    const PrintFunction<T>& print_root, \
    int dashes, \
    int spaces)
: print_leaf_(print_leaf), print_node_(print_node), print_root_(print_root), \
    dashes_(dashes), spaces_(spaces)
{}

template <typename T>
PrintFunction<T> ASTPrintCompanion<T>::print_leaf() const
{
  return print_leaf_;
}

template <typename T>
PrintFunction<T> ASTPrintCompanion<T>::print_node() const
{
  return print_node_;
}

template <typename T>
PrintFunction<T> ASTPrintCompanion<T>::print_root() const
{
  return print_root_;
}

template <typename T>
int ASTPrintCompanion<T>::dashes() const
{
  return dashes_;
}

template <typename T>
int ASTPrintCompanion<T>::spaces() const
{
  return spaces_;
}