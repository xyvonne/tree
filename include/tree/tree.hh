#pragma once

#include <functional> // std::function
#include <vector>

#include "tree_pc.hh"

/* Tree interface */

/**
 * We are working with trees of any size and nodes having any possible arity
 * (=number of children). The leaves are viewed as nodes with arity 0. All
 * nodes (more precisely, node values or labels) must be of the same type.
 * For technical reasons, this type must be endowed with an overloaded ==
 * operator.
 *
 * The supported (=public) methods include:
 * - the construction from the new root and the children trees, or from a
 *   table giving the children of each node;
 * - general information about the tree: size (=total number of nodes),
 *   depth (=height), number of leaves, number of inner nodes;
 * - information about the root: label, arity, and children (as whole trees);
 * - tree mapping;
 * - developer-friendly representation and pretty-printing;
 * - traversals: pre-, post-, and breadth-first searches. We chose to implement
 *   them without using recursion, in order to practice with common STL
 *   structures (vectors, stacks, queues).
 * Methods concerning a specific node other than the root are not part of
 * the interface. In particular, it is not possible to extract a node (other
 * than the root) nor a subtree (unless it is attached to the root), nor to
 * add a node (anywhere else than on the top of the tree).
 *
 *  As a special category of trees, binary trees are implemented through the
 *  derived class BinaryTree<T>. Please refer to "bin_tree.hh" for more
 *  details.
 *
 * A (generic) tree is implemented as follows. Its only attribute is the
 * vector of its nodes, sorted w.r.t. pre-order search. A node is a pair
 * consisting of a label (=value) and a vector of ids. The id of a node is its
 * rank (starting from 0) given by pre-order search. In the aforementioned
 * vector of ids, the parent id comes first (the parent of the root being the
 * root itself); then comes the id of the current node, and lastly the ids of
 * the node's children (in ascending order).
 * For access to children, we rejected the common implementation with pointers,
 * because for tree mapping in particular, we want this accessing type be
 * independent from T (the type labelling nodes), and we did not want to use
 * the void* type in C++ either.
 */

/**
 * Type aliases.
 * Node<T>: node in the tree.
 * Nodes<T>: vector of the nodes forming the tree.
 * Table<T>: table used for tree building:
 * see Tree<T>::Tree(const Table<T>& table) below.
 */
template <typename T>
using Node = std::pair<T, std::vector<size_t>>;

template <typename T>
using Nodes = std::vector<Node<T>>;

template <typename T>
using Table = std::vector<std::pair<T, std::vector<T>>>;

/**
 * Interface of the class itself.
 */
template <typename T>
class Tree
{
  template <typename U>
    friend class Tree; // required for tree mapping

  public:
  /**
   * Bottom-to-top constructor: provide the label for the new root,
   * along with the children (as Trees) in a vector.
   */
  Tree(const T& root, const std::vector<Tree<T>>& children = {});

  /**
   * Top-to-bottom constructor: construct a tree from a table.
   * If the table in invalid, throw a TreeException::InvalidTable exception.
   * An empty table (default case) can also be used to construct an empty tree.
   */
  Tree(const Table<T>& table = {});

  /// Size of the tree (i.e., its number of nodes).
  size_t size() const;

  /// Depth (=height) of the tree. Equals -1 for an empty tree.
  ssize_t depth() const;

  /// Number of leaves.
  size_t nb_leaves() const;

  /// Number of inner nodes.
  size_t nb_inner_nodes() const;

  /**
   * Get the value (label) of the root.
   * If the tree is empty, throw a TreeException::EmptyTree exception.
   */
  T root_value() const;

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
   * Tree mapping: apply a map f to all nodes of the tree.
   * The result is a new tree with same shape.
   */
  template <typename U>
    Tree<U> map(std::function<U(T)> f) const;

  /**
   * Developper-friendly representation of the tree
   * (Python's equivalent of __repr__()).
   * List all the nodes w.r.t. pre-order search,
   * along with their values and ids.
   * The TreePrintCompanion specifies how the root, leaves and other inner
   * nodes must be represented;
   * please refer to the "tree_pc.hh" file for more details.
   */
  std::string represent(const TreePrintCompanion<T>& pc = {}) const;

  /**
   * User-friendly representation of the tree
   * (Python's equivalent of __str__()).
   * The result is very similar to the UNIX/DOS 'tree' utility's
   * representation of a filesystem hierarchy.
   * The TreePrintCompanion specifies how the leaves and the inner nodes
   * must be represented, and how wide the columns must be spaced;
   * please refer to the "tree_pc.hh" file for more details.
   */
  std::string to_string(const TreePrintCompanion<T>& pc = {}) const;

  /// Perform the pre-order search on the tree.
  std::vector<T> pre_order_search() const;

  /// Perform the post-order search on the tree.
  std::vector<T> post_order_search() const;

  /// Perform the breadth-first search (BFS) on the tree.
  std::vector<T> breadth_first_search() const;

  protected:
  /**
   * The nodes of the tree, stored in a vector
   * (the full implementation of the nodes has been already discussed above).
   */
  Nodes<T> nodes_;

  /**
   * Tell if a node given by its id is a leaf.
   * If the id is invalid (out of range), return false.
   */
  bool is_leaf(size_t id) const;

  /**
   * Perform a post-order / breath-first search on the tree,
   * but return the node ids instead of the node values.
   */
  std::vector<size_t> post_order_search_ids() const;
  std::vector<size_t> breadth_first_search_ids() const;

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
};

/**
 * Overload the << operator for pretty-printing. Calls Tree<T>::to_string()
 * without parameter (i.e., use the default TreePrintCompanion).
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree);

#include "tree.hxx" // template class implementation
