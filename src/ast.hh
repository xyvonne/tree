#pragma once

#include <functional> // std::function
#include <vector>

#include "ast_pc.hh"

/* AST interface */

//TODO: document whis class does

/**
 * An AST is implemented as follows. Its only attribute is the vector of its
 * nodes, sorted w.r.t. pre-order search. A node is a pair consisting in a
 * label (=value) and a vector of ids. The id of a node is its rank (starting
 * from 0) given by pre-order search. In the aforementioned vector of ids, the
 * parent id comes first (the parent of the root being the root itself); then
 * comes the id of the current node, and lastly the ids of the node's children
 * (in ascending order).
 */

/// Type aliases
template <typename T>
using Node = std::pair<T, std::vector<size_t>>;

template <typename T>
using Nodes = std::vector<Node<T>>;

/// Interface of the class itself
template <typename T>
class AST
{
  template <typename U>
    friend class AST; // required for AST mapping

  public:
  /// Contruct an empty AST.
  AST();

  /**
   * Bottom-to-top constructor: provide the label for the new root,
   * along with the children (as ASTs) in a vector.
   */
  AST(const T& root, const std::vector<AST<T>>& children = {});

  /// Size of the AST (i.e., its number of nodes).
  size_t size() const;

  /// Depth (=height) of the AST. Equals -1 for an empty AST.
  ssize_t depth() const;

  /**
   * Get the label of the root.
   * If the AST is empty, an EmptyTree() exception is thrown.
   */
  T root() const;

  /**
   * Get the arity (i.e., the number of children) of the root.
   * If the AST is empty, an EmptyTree() exception is thrown.
   */
  size_t root_arity() const;

  /**
   * Get the children of the root, as a vector of new ASTs.
   * If the AST is empty, an EmptyTree() exception is thrown.
   */
  std::vector<AST<T>> children() const;

  /**
   * AST mapping: apply a map f to all nodes of the AST.
   * The result is a new AST with same shape.
   */
  template <typename U>
    AST<U> map(std::function<U(T)> f) const;

  /**
   * Developper-friendly representation of the AST
   * (Python's equivalent of __repr__()).
   * Lists all the nodes w.r.t. pre-order search,
   * along with their values and ids.
   * The ASTPrintCompanion specifies how the leaves and the inner nodes
   * must be represented;
   * please refer to the "ast_pc.hh" file for more details.
   */
  std::string represent(const ASTPrintCompanion<T>& pc = {}) const;

  /**
   * User-friendly representation of the AST
   * (Python's equivalent of __str__()).
   * The result is very similar to the UNIX/DOS 'tree' utility's
   * representation of a filesystem hierarchy.
   * The ASTPrintCompanion specifies how the leaves and the inner nodes
   * must be represented, and how wide the columns must be spaced;
   * please refer to the "ast_pc.hh" file for more details.
   */
  std::string to_string(const ASTPrintCompanion<T>& pc = {}) const;

  /// Perform the pre-order search on the AST.
  std::vector<T> pre_order_search() const;

  /// Perform the post-order search on the AST.
  std::vector<T> post_order_search() const;

  /// Perform the breadth-first search (BFS) on the AST.
  std::vector<T> breadth_first_search() const;

  protected:
  /**
   * The nodes of the AST, stored in a vector
   * (the full implementation of the nodes has been already discussed).
   */
  Nodes<T> nodes_;

  /**
   * Tell if a node given by its id is a leaf.
   * If the id is invalid (out of range), return false.
   */
  bool is_leaf(size_t id) const;

  /**
   * Perform the post-order search and breath-first search on the AST,
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
   * Return a vector containing the depth (or height) for each node
   * (given by its id) in the AST. The root has depth 0.
   */
  std::vector<size_t> node_depths() const;
};

/**
 * Overload the << operator for pretty-printing purposes. Calls
 * AST<T>::to_string() without parameter (i.e., use the default
 * ASTPrintCompanion).
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const AST<T>& ast);

#include "ast.hxx" // template class implementation
