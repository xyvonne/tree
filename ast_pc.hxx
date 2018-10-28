#pragma once

#include "ast_pc.hh" // template class interface

/* ASTPrinterCompanion implementation */

template <typename T>
std::string default_print_leaf(const T& t)
{
  (void) t; // intented, as the signature cannot be changed
  return " o";
}

template <typename T>
std::string default_print_node(const T& t)
{
  (void) t; // intented, as the signature cannot be changed
  return "[*]";
}

template <typename T>
ASTPrintCompanion<T>::ASTPrintCompanion( \
    PrintFunction<T> print_node, PrintFunction<T> print_leaf,
    unsigned dashes, unsigned spaces)
: print_leaf_(print_leaf), print_node_(print_node), \
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
unsigned ASTPrintCompanion<T>::dashes() const
{
  return dashes_;
}

template <typename T>
unsigned ASTPrintCompanion<T>::spaces() const
{
  return spaces_;
}
