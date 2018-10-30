#pragma once

#include <functional> // std::function
#include <vector>

#include "tree_pc.hh"

/* Tree interface */

//TODO: document what this class does

/**
 * An Tree is implemented as follows. Its only attribute is the vector of its
 * nodes, sorted w.r.t. pre-order search. A node is a pair consisting in a
 * label (=value) and a vector of ids. The id of a node is its rank (starting
 * from 0) given by pre-order search. In the aforementioned vector of ids, the
 * parent id comes first (the parent of the root being the root itself); then
 * comes the id of the current node, and ltreely the ids of the node's children
 * (in ascending order).
 */

/// Type aliases
template <typename T>
using Node = std::pair<T, std::vector<size_t>>;

template <typename T>
using Nodes = std::vector<Node<T>>;

/// Interface of the class itself
template <typename T>
class Tree
{
  template <typename U>
    friend class Tree; // required for Tree mapping

  public:
  /// Contruct an empty Tree.
  Tree();

  /**
   * Bottom-to-top constructor: provide the label for the new root,
   * along with the children (as Trees) in a vector.
   */
  Tree(const T& root, const std::vector<Tree<T>>& children = {});

  /// Size of the Tree (i.e., its number of nodes).
  size_t size() const;

  /// Depth (=height) of the Tree. Equals -1 for an empty Tree.
  ssize_t depth() const;

  /**
   * Get the label of the root.
   * If the Tree is empty, an EmptyTree() exception is thrown.
   */
  T root() const;

  /**
   * Get the arity (i.e., the number of children) of the root.
   * If the Tree is empty, an EmptyTree() exception is thrown.
   */
  size_t root_arity() const;

  /**
   * Get the children of the root, as a vector of new Trees.
   * If the Tree is empty, an EmptyTree() exception is thrown.
   */
  std::vector<Tree<T>> children() const;

  /**
   * Tree mapping: apply a map f to all nodes of the Tree.
   * The result is a new Tree with same shape.
   */
  template <typename U>
    Tree<U> map(std::function<U(T)> f) const;

  /**
   * Developper-friendly representation of the Tree
   * (Python's equivalent of __repr__()).
   * Lists all the nodes w.r.t. pre-order search,
   * along with their values and ids.
   * The TreePrintCompanion specifies how the leaves and the inner nodes
   * must be represented;
   * please refer to the "tree_pc.hh" file for more details.
   */
  std::string represent(const TreePrintCompanion<T>& pc = {}) const;

  /**
   * User-friendly representation of the Tree
   * (Python's equivalent of __str__()).
   * The result is very similar to the UNIX/DOS 'tree' utility's
   * representation of a filesystem hierarchy.
   * The TreePrintCompanion specifies how the leaves and the inner nodes
   * must be represented, and how wide the columns must be spaced;
   * please refer to the "tree_pc.hh" file for more details.
   */
  std::string to_string(const TreePrintCompanion<T>& pc = {}) const;

  /// Perform the pre-order search on the Tree.
  std::vector<T> pre_order_search() const;

  /// Perform the post-order search on the Tree.
  std::vector<T> post_order_search() const;

  /// Perform the breadth-first search (BFS) on the Tree.
  std::vector<T> breadth_first_search() const;

  protected:
  /**
   * The nodes of the Tree, stored in a vector
   * (the full implementation of the nodes has been already discussed).
   */
  Nodes<T> nodes_;

  /**
   * Tell if a node given by its id is a leaf.
   * If the id is invalid (out of range), return false.
   */
  bool is_leaf(size_t id) const;

  /**
   * Perform the post-order search and breath-first search on the Tree,
   * but return the node ids instead of the node values.
   */
  std::vector<size_t> post_order_search_ids() const;
  std::vector<size_t> breadth_first_search_ids() const;

  /**
   * Return a vector telling whether each node (given by its id) is its
   * parent's ltree child, or not.
   * By convention, the root is its parent's ltree child.
   * There are as many ltree children as there are inner nodes.
   */
  std::vector<bool> ltree_children() const;

  /**
   * Return a vector containing the depth (or height) for each node
   * (given by its id) in the Tree. The root has depth 0.
   */
  std::vector<size_t> node_depths() const;
};

/**
 * Overload the << operator for pretty-printing purposes. Calls
 * Tree<T>::to_string() without parameter (i.e., use the default
 * TreePrintCompanion).
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree);

#include "tree.hxx" // template class implementation
