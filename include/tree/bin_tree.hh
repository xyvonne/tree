#pragma once

#include "tree.hh"

/* BinaryTree interface */

template <typename T>
class BinaryTree : public Tree<T>
{
  template <typename U>
    friend class BinaryTree; // required for BinaryTree mapping

  /**
   * Constructors.
   * These are variations of the constructors of the parent Tree class, in
   * order to restrict ourselves to at most 2 children per node, as the class
   * standards require it.
   * If a node has only one child, it must be considered as the *right* child,
   * the left child being "null". This convention is important for
   * in-order search. We preferred it to the oppsite one, because of the
   * important example of ASTs storing arithmetic expressions, where nodes are
   * operators -- and many (if not all) unary operators are *right*-associative.
   * For the constructor from a table, it agains falls to the caller's duty
   * to provide a valid table. In particular, this table must consist in
   * (key, value) pairs where each value contains at most 2 keys (otherwise,
   * the resulting tree would not be binary). Failure to complying with this
   * results in an undefined behavior.
   */
  public:
  BinaryTree(const T& root);
  BinaryTree(const T& root, const BinaryTree<T>& right);
  BinaryTree(const T& root, const BinaryTree<T>& left, \
      const BinaryTree<T>& right);
  BinaryTree(const Table<T>& table = {});

  /**
   * BinaryTree mapping.
   * Override but act in the same way as the Tree<T>::map() method.
   */
  template <typename U>
    BinaryTree<U> map(std::function<U(T)> f) const;

  /*
   * In-order search.
   * Return a vector of shared pointers.
   * Recall that nodes without siblings are treated as right children.
   */
  std::vector<Ptr<T>> in_order_search() const;

  private:
  /**
   * Perform the in-order search on the BinaryTree,
   * but return the node ids instead of the node values.
   */
  std::vector<size_t> in_order_search_ids() const;
};

#include "bin_tree.hxx" /* template class implementation */
