#pragma once

#include "ast.hh" // template class interface

#include <queue>
#include <stack>

#include "error.hh"

/* AST implementation */

  template <typename T>
AST<T>::AST()
{}

  template <typename T>
AST<T>::AST(const T& root, const std::vector<AST<T>>& children)
  : nodes_{{root, {0, 0}}} // parent's root is itself and has id = 0
{
  size_t offset = 1; // node reindexing counter
  for (auto child : children)
  {
    nodes_[0].second.push_back(offset); // child is a new root's child

    for (auto& node : child.nodes_)
    {
      for (auto& id : node.second)
        id += offset; // update id's grandchildren for all child's nodes
    }
    child.nodes_[0].second[0] = 0; // root is child's parent

    // add the whole child tree structure to root
    nodes_.insert(nodes_.end(), child.nodes_.begin(), child.nodes_.end());

    offset += child.size(); // update node reindexing counter
  }
}

template <typename T>
T AST<T>::root() const
{
  if (size() == 0)
    throw EmptyTree("[ERROR] Calling AST<T>::root() failed: Empty tree\n");
  return nodes_[0].first;
}

template <typename T>
size_t AST<T>::root_arity() const
{
  if (size() == 0)
    throw EmptyTree("[ERROR]" \
        " Calling AST<T>::root_arity() failed: Empty tree\n");
  return nodes_[0].second.size() - 2;
}

template <typename T>
template <typename U>
AST<U> AST<T>::map(std::function<U(T)> f) const
{
  AST<U> ast;
  for (const auto& node : nodes_)
    ast.AST<U>::nodes_.push_back({f(node.first), node.second});
  return ast;
}

template <typename T>
std::string AST<T>::represent(const ASTPrintCompanion<T>& pc) const
{
  std::string s;
  for (const auto& node : nodes_)
  {
    s += "Node #" + std::to_string(node.second[1]);
    s += ": value: ";
    T t = node.first;
    if (node.second[1] == 0) // node.second[1]: node's id; 0 = root's id
      s += pc.print_root()(t);
    else if (is_leaf(node.second[1]))
      s += pc.print_leaf()(t);
    else
      s += pc.print_node()(t);
    s += " | Ids: [";
    for (const auto& id : node.second)
      s += std::to_string(id) + ", ";
    s += "\b\b]\n";
  }
  return s;
}

template <typename T>
std::string AST<T>::to_string(const ASTPrintCompanion<T>& pc) const // TODO
{
  std::string s;
  (void) pc; //TODO
  return s;
}

template <typename T>
std::vector<T> AST<T>::pre_order_search() const
{
  /*
   * Recall that our implementation is such that all nodes are already stored
   * w.r.t. pre-order search, so we only have to fetch their labels (values).
   */
  std::vector<T> v;
  for (const auto& node : nodes_)
    v.push_back(node.first);
  return v;
}

template <typename T>
std::vector<size_t> AST<T>::post_order_search_ids() const
{
  /*
   * We make the search in an iterative way, using a stack.
   * Although it is much more natural to use recursion here, this would
   * probably require, due to our implementation, to get at each step the
   * children as a collection of *newly made AST* in order to apply the
   * recursion on them, which is far too expensive.
   */
  std::stack<size_t> stack;
  std::vector<size_t> out;

  // Push root's id onto the stack
  size_t id = 0;
  stack.push(id);

  while (!stack.empty())
  {
    // Pop one node id from the stack, and add it to the output
    id = stack.top();
    stack.pop();
    out.push_back(id);

    // Add the children ids to the stack
    const auto& v = nodes_[id].second;
    for (size_t i = 2; i < v.size(); i++)
      stack.push(v[i]);
  }

  // Reverse the output vector, so the root comes last
  std::reverse(out.begin(), out.end());
  return out;
}

template <typename T>
std::vector<T> AST<T>::post_order_search() const
{
  std::vector<size_t> sorted_ids = post_order_search_ids();
  std::vector<T> out;
  for (const auto& id : sorted_ids)
    out.push_back(nodes_[id].first);
  return out;
}

template <typename T>
std::vector<size_t> AST<T>::breadth_first_search_ids() const
{
  /*
   * We make the search in an iterative way, using a queue.
   * Although it is much more natural to use recursion here, this would
   * probably require, due to our implementation, to get at each step the
   * children as a collection of *newly made AST* in order to apply the
   * recursion on them, which is far too expensive.
   */
  std::queue<size_t> queue;
  std::vector<size_t> out;

  // Enqueue root's id
  size_t id = 0;
  queue.push(id);

  while (!queue.empty())
  {
    // Pop one node id from the queue, and add it to the output
    id = queue.front();
    queue.pop();
    out.push_back(id);

    // Add the children ids to the queue
    const auto& v = nodes_[id].second;
    for (size_t i = 2; i < v.size(); i++)
      queue.push(v[i]);
  }

  return out;
}

template <typename T>
std::vector<T> AST<T>::breadth_first_search() const
{
  std::vector<size_t> sorted_ids = breadth_first_search_ids();
  std::vector<T> out;
  for (const auto& id : sorted_ids)
    out.push_back(nodes_[id].first);
  return out;
}

template <typename T>
std::vector<bool> AST<T>::last_children_of_last_children() const
{
  if (size() == 0)
    return {};

  std::vector<bool> out(size(), false);
  out[0] = true;
  size_t i = 0;
  while (!is_leaf(i))
  {
    i = nodes_[i].second.back();
    out[i] = true;
  }
  return out;
}

template <typename T>
std::vector<bool> AST<T>::last_children() const
{
  if (size() == 0)
    return {};

  std::vector<bool> out(size(), false);
  out[0] = true;
  for (size_t i = 0; i < size(); i++)
    if (!is_leaf(i))
    {
      size_t j = nodes_[i].second.back(); // nodes_[i]'s last child id
      out[j] = true;
    }
  return out;
}

template <typename T>
std::vector<size_t> AST<T>::node_depths() const
{
  if (size() == 0)
    return {};

  std::vector<size_t> out(size(), 0); // vector of size size() filled with 0s
  std::vector<size_t> BFS = breadth_first_search_ids();
  size_t depth = 0;
  auto lclc = last_children_of_last_children();
  for (size_t i = 0; i < size(); i++)
  {
    size_t j = BFS[i];
    out[j] = depth;
    if (lclc[j])
      depth++;
  }

  return out;
}

template <typename T>
ssize_t AST<T>::depth() const
{
  if (size() == 0)
    return -1;

  /*
   * If the AST is not empty, we find the id of the deepest node by performing
   * a BFS and taking the id of the last node found.
   * Next, we follow the path from this node up to the root, and compute the
   * length of this path.
   */
  ssize_t depth = 0;
  for (size_t i = breadth_first_search_ids().back(); i != 0; \
      i = nodes_[i].second[0])
    depth++;

  return depth;
}

template <typename T>
size_t AST<T>::size() const
{
    return nodes_.size();
}

template <typename T>
bool AST<T>::is_leaf(size_t id) const
{
  return id < size() and nodes_[id].second.size() <= 2;
}

  template <typename T>
std::ostream& operator<<(std::ostream& os, const AST<T>& ast)
{
  return os << ast.to_string();
}
