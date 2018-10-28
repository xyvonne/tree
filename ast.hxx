#pragma once

#include "ast.hh" // template class interface

#include <algorithm> // std::reverse
#include <queue>
#include <stack>

#include "error.hh"

/* AST implementation */

template <typename T>
AST<T>::AST()
{}

template <typename T>
AST<T>::AST(const T& t, const std::vector<AST<T>>& children)
  : nodes_{{t, {0, 0}}} // root is itself's parent and has id = 0
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

    // add all child tree structure to root
    nodes_.insert(nodes_.end(), child.nodes_.begin(), child.nodes_.end());

    offset += child.nodes_.size(); // update node reindexing counter
  }
}

template <typename T>
T AST<T>::root() const
{
  if (nodes_.size() == 0)
    throw EmptyTree("[ERROR] Calling AST<T>::root() failed: Empty tree\n");
  return nodes_[0].first;
}

template <typename T>
size_t AST<T>::root_arity() const
{
  if (nodes_.size() == 0)
    throw EmptyTree("[ERROR]"\
        " Calling AST<T>::root_arity() failed: Empty tree\n");
  return nodes_[0].second.size() - 2;
}

template <typename T>
std::vector<AST<T>> AST<T>::children() const //TODO
{
  return {};
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
std::string AST<T>::to_string(const ASTPrintCompanion<T>& pc) const
{
  // This is a basic pretty-printing. TODO: pretty-pretting v2
  std::string s;
  for (const auto& node : nodes_)
  {
    s += "Node #" + std::to_string(node.second[1]);
    s += ": value: " + pc.print_node()(node.first);
    s += " | Ids: [";
    for (const auto& id : node.second)
      s += std::to_string(id) + ", ";
    s += "\b\b]\n";
  }
  return s;
}

template <typename T>
std::vector<T> AST<T>::pre_order_search() const
{
  /*
   * Our implementation is such that all nodes are always already stored
   * w.r.t pre-order search, so we only have to fetch their labels (values).
   */
  std::vector<T> v;
  for (const auto& node : nodes_)
    v.push_back(node.first);
  return v;
}

template <typename T>
std::vector<T> AST<T>::post_order_search() const
{
  /*
   * We make the search in an iterative way, using a stack.
   * Although it is much more natural to use recursion here, this would
   * probably require, due to our implementation, to get at each step the
   * children as a collection of *newly made AST* in order to apply the
   * recursion on them, which is far too expensive.
   */
  std::stack<size_t> stack;
  std::vector<T> out;

  // Push root's id onto the stack
  size_t id = 0;
  stack.push(id);

  while (!stack.empty())
  {
    // Pop one node (id) from the stack, and add its value to the output
    id = stack.top();
    stack.pop();
    out.push_back(nodes_[id].first);

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
std::vector<T> AST<T>::breadth_first_search() const
{
  /*
   * We make the search in an iterative way, using a queue.
   * Although it is much more natural to use recursion here, this would
   * probably require, due to our implementation, to get at each step the
   * children as a collection of *newly made AST* in order to apply the
   * recursion on them, which is far too expensive.
   */
  std::queue<size_t> queue;
  std::vector<T> out;

  // Enqueue root's id
  size_t id = 0;
  queue.push(id);

  while (!queue.empty())
  {
    // Pop one node (id) from the queue, and add its value to the output
    id = queue.front();
    queue.pop();
    out.push_back(nodes_[id].first);

    // Add the children ids to the stack
    const auto& v = nodes_[id].second;

    for (size_t i = 2; i < v.size(); i++)
      queue.push(v[i]);
  }

  return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const AST<T>& ast)
{
  return os << ast.to_string();
}
