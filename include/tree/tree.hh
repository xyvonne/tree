#pragma once

#include <functional> // std::function
#include <iostream> // operator<< overloading
#include <memory> // std::shared_ptr
#include <string>
#include <vector>

#include "tree_pc.hh"

/**
 * Type aliases.
 * Ptr<T>: shared pointers to T objects.
 * Node<T>: node in the tree.
 * Nodes<T>: vector of the nodes forming the tree.
 * Table<T>: table used for tree building:
 * see Tree<T>::Tree(const Table<T>& table) below.
 */
template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T>
using Node = std::pair<Ptr<T>, std::vector<size_t>>;

template <typename T>
using Nodes = std::vector<Node<T>>;

template <typename T>
using Table = std::vector<std::pair<Ptr<T>, std::vector<Ptr<T>>>>;

/* Tree interface. */

template <typename T>
class Tree
{
  template <typename U>
    friend class Tree; // required for tree mapping

  public:
  /**
   * Bottom-to-top constructor: provide a reference to the label for the new
   * root, along with the children (as Trees) in a vector.
   */
  Tree(const T& root, const std::vector<Tree<T>>& children = {});

  /**
   * Top-to-bottom constructor: construct a tree from a table.
   * An empty table (default case) can be used to construct an empty tree.
   * Otherwise, a table is a vector of (key, value) pairs, where each key is a
   * pointer to an object of type T corresponding to a node value, and each
   * value in the table is a vector of pointers to objects of type T
   * corresponding to the children of the node given by the key.
   * All the keys must be pointers to distinct objects, and all pointers
   * corresponding to values in the table must point to distinct objects too.
   * To check equality between pointed values, the type T must be endowed with
   * an overloaded == operator.
   * The first pair in the table corresponds to the root and its children.
   * All leaves must appear in the table as (key, value) pairs, with value
   * being the empty vector.
   * It falls to the caller's duty to provide a valid table, as the constructor
   * does not check it. Failing to comply with this may result in an undefined
   * behavior. In the special case though where the table contains values
   * which do not match with keys, a TreeException::InvalidTable is thrown
   * and an empty tree is constructed.
   * If you want to construct a tree with some nodes having the same value,
   * you must give them distinct ids first; then, you can use this constructor
   * to construct a temporary tree with node ids instead of true node values,
   * and finally use tree mapping (with a custom map node id->node value) to
   * construct the tree you want.
   **/
  Tree(const Table<T>& table = {});

  /// Depth (=height) of the tree. Equals -1 for an empty tree.
  ssize_t depth() const;

  /// Number of inner nodes.
  size_t nb_inner_nodes() const;

  /// Number of leaves.
  size_t nb_leaves() const;

  /// Size of the tree (i.e., its number of nodes).
  size_t size() const;

  /**
   * Get the arity (i.e., the number of children) of the root.
   * If the tree is empty, throw a TreeException::EmptyTree exception.
   */
  size_t root_arity() const;

  /**
   * Get the children of the root, as a vector of new trees.
   * If the tree is empty, throw a TreeException::EmptyTree exception.
   */
  std::vector<Tree<T>> root_children() const;

  /**
   * Get a shared pointer to the value (label) of the root.
   * If the tree is empty, throw a TreeException::EmptyTree exception.
   */
  Ptr<T> root_value() const;

  /**
   * Tree mapping: apply a map f to all nodes of the tree.
   * The result is a new tree with same shape.
   */
  template <typename U>
    Tree<U> map(std::function<U(T)> f) const;

  /**
   * Breadth-first search (BFS).
   * Return a vector of shared pointers.
   */
  std::vector<Ptr<T>> breadth_first_search() const;

  /**
   * Post-order search.
   * Return a vector of shared pointers.
   */
   std::vector<Ptr<T>> post_order_search() const;

  /**
   * Pre-order search.
   * Return a vector of shared pointers.
   */
 std::vector<Ptr<T>> pre_order_search() const;

  /**
   * Developper-friendly representation of the tree
   * (equivalent of Python's __repr__()).
   * List all the nodes w.r.t. pre-order search,
   * along with their values and ids.
   * The TreePrintCompanion specifies how the leaves, inner
   * nodes and root must be represented;
   * please refer to the documentation of that class for more details.
   */
  std::string represent(const TreePrintCompanion<T>& pc = {}) const;

  /**
   * User-friendly representation of the tree
   * (equivalent of Python's __str__()).
   * The result is very similar to the UNIX/MS-DOS 'tree' utility's
   * representation of a filesystem hierarchy.
   * The TreePrintCompanion specifies how the leaves, inner nodes
   * nodes and root must be represented, and how wide the columns must
   * be spaced;
   * please refer to the documentation of that class for more details.
   */
  std::string to_string(const TreePrintCompanion<T>& pc = {}) const;

  protected:
  /**
   * The nodes of the tree, stored in a vector.
   * The full implementation of the nodes has been already discussed
   * in the Tree documentation class.
   */
  Nodes<T> nodes_;

  /**
   * Perform a breath-first search on the tree,
   * but return the node ids instead of the node values.
   */
  std::vector<size_t> breadth_first_search_ids() const;

  /**
   * Tell if a node given by its id is a leaf.
   * If the id is invalid (out of range), return false.
   */
  bool is_leaf(size_t id) const;

  /**
   * Return a vector telling whether each node (given by its id) is its
   * parent's last child, or not.
   * By convention, the root is its parent's last child.
   * There are as many last children as there are inner nodes.
   */
  std::vector<bool> last_children() const;

  /**
   * Return a vector containing the depth for each node
   * (given by its id) in the tree. The root has depth 0.
   */
  std::vector<size_t> node_depths() const;

  /**
   * Perform a post-order search on the tree,
   * but return the node ids instead of the node values.
   */
  std::vector<size_t> post_order_search_ids() const;
};

/**
 * Overload the << operator for pretty-printing. This calls
 * Tree<T>::to_string() without parameter (i.e., use the default
 * TreePrintCompanion).
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree);

#include "tree.hxx" /* template class implementation */
