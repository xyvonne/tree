#pragma once

#include <vector>

#include "tree.hh"

/* BinaryTree interface */

template <typename T>
class BinaryTree : public Tree<T>
{
  template <typename U>
    friend class BinaryTree; // required for BinaryTree mapping

  public:
  BinaryTree();
  BinaryTree(const T& t);
  BinaryTree(const T& t, const BinaryTree<T>& left);
  BinaryTree(const T& t, const BinaryTree<T>& left, const BinaryTree<T>& right);

  template <typename U>
    BinaryTree<U> map(std::function<U(T)> f) const;

  std::vector<T> in_order_search() const;
};

#include "bin_tree.hxx" // template class implementation
