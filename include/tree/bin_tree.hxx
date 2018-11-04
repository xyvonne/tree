#pragma once

#include "bin_tree.hh" /* template class interface */

template <typename T>
BinaryTree<T>::BinaryTree(const Table<T>& table)
  : Tree<T>(table)
{}

template <typename T>
BinaryTree<T>::BinaryTree(const T& t)
  : Tree<T>(t, {})
{}

template <typename T>
BinaryTree<T>::BinaryTree(const T& t, const BinaryTree<T>& right)
  : Tree<T>(t, {right})
{}

template <typename T>
BinaryTree<T>::BinaryTree(const T& t, \
    const BinaryTree<T>& left, const BinaryTree<T>& right)
: Tree<T>(t, {left, right})
{}

template <typename T>
std::vector<T> BinaryTree<T>::in_order_search() const
{
  std::vector<size_t> sorted_ids = in_order_search_ids();
  std::vector<T> out;
  for (const auto& id : sorted_ids)
    out.push_back(Tree<T>::nodes_[id].first);
  return out;
}

template <typename T>
std::vector<size_t> BinaryTree<T>::in_order_search_ids() const
{
  /*
   * We make the search in an iterative way, using a stack.
   * Although it is much more natural to use recursion here, this would
   * probably require, due to our implementation, to get at each step the
   * children as a collection of *newly made BinaryTree* in order to apply
   * the recursion on them, which is too expensive.
   *
   * We handle leaves and nodes with only 1 child as follows.
   * First, every node has a modified id, equals to 1 + its true id.
   * Next, we consider that all nodes have arity 2: if this is not the case,
   * we pretend their missing children have a modified id equal to 0
   * (NB: this shift by 1 makes all modified ids non-negative, so they may
   * still be stored with an unsigned type).
   * Of course, the output consists in true ids only, not modified ids.
   */
  if (Tree<T>::size() == 0)
    return {};

  std::stack<size_t> stack;
  std::vector<size_t> out;

  /* Start with the root. */
  size_t id = 1; // modified id

  while (true)
  {
    /*
     * Push the current node id onto the stack, and replace it by its left
     * child until we get a null id.
     */
    while (id)
    {
      stack.push(id);
      if (Tree<T>::nodes_[id - 1].second.size() >= 4)
        id = Tree<T>::nodes_[id - 1].second[2] + 1;
      else
        id = 0;
    }

    if (stack.empty())
      break;

    /*
     * Pop one (modified id) node from the stack, add the true id to the
     * output, and replace this node with its right child if it exists
     * (or with a null id otherwise).
     */
    id = stack.top();
    stack.pop();
    out.push_back(id - 1);
    if (Tree<T>::nodes_[id - 1].second.size() >= 3)
      id = Tree<T>::nodes_[id - 1].second.back() + 1;
    else
      id = 0;
  }

  return out;
}

template <typename T>
template <typename U>
BinaryTree<U> BinaryTree<T>::map(std::function<U(T)> f) const
{
  BinaryTree<U> tree;
  for (const auto& node : Tree<T>::nodes_)
    tree.Tree<U>::nodes_.push_back({f(node.first), node.second});
  return tree;
}
