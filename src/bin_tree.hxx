#pragma once

#include "bin_tree.hh" // template class interface

/* BinaryTree implementation */

template <typename T>
BinaryTree<T>::BinaryTree()
  : Tree<T>()
{}

template <typename T>
BinaryTree<T>::BinaryTree(const T& t)
  : Tree<T>(t, {})
{}

template <typename T>
BinaryTree<T>::BinaryTree(const T& t, const BinaryTree<T>& left)
: Tree<T>(t, {left})
{}

template <typename T>
BinaryTree<T>::BinaryTree(const T& t, \
    const BinaryTree<T>& left, const BinaryTree<T>& right)
: Tree<T>(t, {left, right})
{}

template <typename T>
template <typename U>
BinaryTree<U> BinaryTree<T>::map(std::function<U(T)> f) const
{
  BinaryTree<U> tree;
  for (const auto& node : Tree<T>::nodes_)
    tree.Tree<U>::nodes_.push_back({f(node.first), node.second});
  return tree;
}

template <typename T>
std::vector<T> BinaryTree<T>::in_order_search() const //TODO
{
  return {};
}
