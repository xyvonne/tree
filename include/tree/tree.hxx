#pragma once

#include "tree.hh" // template class interface

#include <algorithm> // std::reverse
#include <queue>
#include <stack>
#include <string>

#include "tree_error.hh"

/* Tree implementation */

template <typename T>
Tree<T>::Tree(const T& root, const std::vector<Tree<T>>& children)
  : nodes_{{root, {0, 0}}} // parent's root is itself and has id == 0
{
  size_t offset = 1; // counter used for updating all node ids
  for (auto child : children)
  {
    nodes_[0].second.push_back(offset); // child is a new root's child

    for (auto& node : child.nodes_)
    {

      for (auto& id : node.second)
        id += offset; // update id's grandchildren for all child's nodes
    }

    child.nodes_[0].second[0] = 0; // root is child's parent

    /* Add the whole child tree structure to root. */
    std::copy (child.nodes_.begin(), child.nodes_.end(), \
        std::back_inserter(nodes_));
    /*
     * CAUTION: the more common following implemenation produces a TERRIBLE
     * ERROR LOG from the compiler when applied which T = Operator, a custom
     * class.
     * The former implementation works. Do not ask me why!!!
     *
     * nodes_.insert(nodes_.end(), child.nodes_.begin(), child.nodes_.end());
     */

    offset += child.size(); // update offset for the next child
  }
}

template <typename T>
Tree<T>::Tree(const Table<T>& table)
{
  size_t n = table.size();
  if (n > 0)
  {
    /* Store all different values in an array, for lookup purposes. */
    std::vector<T> symbols;
    for (size_t i = 0; i < n; i++)
      symbols.push_back(table[i].first);

    /* Construct every node. */
    for (size_t i = 0; i < n; i++)
    {
      /* Add to the node its value and own id. */
      nodes_.push_back({symbols[i], {0, i}}); // parent id is not correct yet

      /* Add to the node the children ids. */
      for (const T& symbol : table[i].second)
      {
        /* Find the id corresponding to each child. */
        size_t j = 0;
        while (j < n and not (symbols[j] == symbol))
          j++;
        if (j == n) // Symbol not found
        {
          nodes_.clear(); // Leave an empty tree as a zombie
          throw TreeException::InvalidTable(
              "[ERROR] Calling Tree<T>::Tree(const Table<T>&) failed: "
              "Invalid table.\nConstructing an empty tree instead.");
        }

        /* Add the child id to the node data. */
        nodes_[i].second.push_back(j);
      }
    }

    /* Fix all parent ids, as for now they are set to 0. */
    for (size_t i = 1; i < n; i++)
    {
      for (size_t j = 2; j < nodes_[i].second.size(); j++)
      {
        /* nodes_[i].second[j] is j-th child of i */
        nodes_[nodes_[i].second[j]].second[0] = i;
      }
    }
  }
}

template <typename T>
T Tree<T>::root_value() const
{
  if (size() == 0)
    throw TreeException::EmptyTree("[ERROR]" \
        " Calling Tree<T>::root_value() failed: Empty tree\n");
  return nodes_[0].first;
}

template <typename T>
size_t Tree<T>::root_arity() const
{
  if (size() == 0)
    throw TreeException::EmptyTree("[ERROR]" \
        " Calling Tree<T>::root_arity() failed: Empty tree\n");
  return nodes_[0].second.size() - 2;
}

template <typename T>
std::vector<Tree<T>> Tree<T>::root_children() const
{
  if (size() == 0)
    throw TreeException::EmptyTree("[ERROR]" \
        " Calling Tree<T>::root_children() failed: Empty tree\n");

  if (root_arity() == 0)
    return {};

  /* Get root's children ids, and add size() at the end for convenience. */
  std::vector<size_t> children_ids;
  for (size_t i = 2; i < nodes_[0].second.size(); i++)
    children_ids.push_back(nodes_[0].second[i]);
  children_ids.push_back(size());

  /* Initialize the output vector. */
  std::vector<Tree<T>> out((children_ids.size() - 1), Tree<T>{});

  /*
   * Update all ids in children trees.
   * Recall that all nodes in the given tree are stored w.r.t. pre-order
   * search; in other words, their indexes for a same given child tree form a
   * sequence of consecutive integers; index 0 corresponds to the current root
   * and has to be dropped, then child #0's sequence comes first, then
   * child #1's, and so on. So, thanks to children_ids constructed above, the
   * nodes for every child are retrieved easily, whence the double loop
   * below.
   * Actually, the tedious part of the job consists in updating correctly
   * all node ids (references) inside all children trees. If 'offset' is the
   * integer in the given tree indexing a new root, then we have to substract
   * this offset to all the ids inside the corresponding child tree,
   * but this new root must have its vector ids starting with 0,0, because
   * it does become a new root and thus its own parent.
   */
  for (size_t j = 0; j < out.size(); j++)
    // By construction, children_ids[j + 1] == size() if j == out.size() -1
    for (size_t i = children_ids[j]; i < children_ids[j + 1]; i++)
    {
      Node<T> child_node = nodes_[i];
      size_t offset = children_ids[j];
      for (auto& child_id : child_node.second)
        child_id -= offset; // substract offset to all ids in the child
      if (i == children_ids[j])
        child_node.second[0] = 0; // let the child root ids start with 0,0
      out[j].nodes_.push_back(child_node); // commit the updates in the result
    }

  return out;
}

template <typename T>
template <typename U>
Tree<U> Tree<T>::map(std::function<U(T)> f) const
{
  Tree<U> tree;
  for (const auto& node : nodes_)
    tree.Tree<U>::nodes_.push_back({f(node.first), node.second});
  return tree;
}

template <typename T>
std::string Tree<T>::represent(const TreePrintCompanion<T>& pc) const
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
    s += " | ids: [";
    for (const auto& id : node.second)
      s += std::to_string(id) + ", ";
    s += "\b\b]\n";
  }
  return s;
}

template <typename T>
std::string Tree<T>::to_string(const TreePrintCompanion<T>& pc) const
{
  if (size() == 0)
    return {};

  std::string s;
  auto depths = node_depths();
  /*
   * Vector flags for the columns: we shall print
   * "|" if the flag is true, and " " otherwise
   */
  std::vector<bool> printable_columns(depth() + 1, false);

  /* Print the root. */
  s += pc.print_root()(nodes_[0].first) + "\n";
  printable_columns[0] = true;

  /* Give self-explicit names for all characters and Unicode strings used. */
  int dashes = pc.dashes();
  std::string hline;
  for (int i = 0; i < dashes; i++)
    hline += "\u2500"; // "\u250":  ─
  std::string spaces(pc.spaces(), ' '); // spaces just before a node
  auto tab = std::string(dashes, ' ') + spaces; // spaces between 2 columns
  std::string vline = "\u2502"; // │
  std::string hook = "\u2514"; // └
  std::string tee = "\u251c"; // ├

  /* Print the other nodes. */
  auto lc = last_children();
  for (size_t i = 1; i < size(); i++)
  {
    /* Print the vertical lines and the horizontal lines/spaces. */
    size_t j = 0;
    if (depths[i] > 1)
      for (; j < depths[i] - 1; j++)
        s += (printable_columns[j] ? vline : " ") + tab;

    /* Print the tees and the hooks. */
    if (lc[i]) // lc = last_children()
    {
      s += hook;
      printable_columns[j++] = false;
    }
    else
      s += tee;

    /* Print the leaves and the inner nodes. */
    T t = nodes_[i].first;
    s += hline + spaces;
    if (is_leaf(i))
      s += pc.print_leaf()(t);
    else
      s += pc.print_node()(t);
    printable_columns[j] = true;
    s += '\n';
  }

  return s;
}

template <typename T>
std::vector<T> Tree<T>::pre_order_search() const
{
  /*
   * Recall that our implementation is such that all nodes are already stored
   * w.r.t. pre-order search, so we only have to fetch their labels (values).
   */
  std::vector<T> out;
  for (const auto& node : nodes_)
    out.push_back(node.first);
  return out;
}

template <typename T>
std::vector<size_t> Tree<T>::post_order_search_ids() const
{
  /*
   * We make the search in an iterative way, using a stack.
   * Although it is much more natural to use recursion here, this would
   * probably require, due to our implementation, to get at each step the
   * children as a collection of *newly made Tree* in order to apply the
   * recursion on them, which is far too expensive.
   */
  if (size() == 0)
    return {};

  std::stack<size_t> stack;
  std::vector<size_t> out;

  /* Push root's id onto the stack. */
  size_t id = 0;
  stack.push(id);

  while (!stack.empty())
  {
    /* Pop one node id from the stack, and add it to the output. */
    id = stack.top();
    stack.pop();
    out.push_back(id);

    /* Add the children ids to the stack. */
    const auto& v = nodes_[id].second;
    for (size_t i = 2; i < v.size(); i++)
      stack.push(v[i]);
  }

  /* Reverse the output vector, so the root comes last. */
  std::reverse(out.begin(), out.end());
  return out;
}

template <typename T>
std::vector<T> Tree<T>::post_order_search() const
{
  std::vector<size_t> sorted_ids = post_order_search_ids();
  std::vector<T> out;
  for (const auto& id : sorted_ids)
    out.push_back(nodes_[id].first);
  return out;
}

template <typename T>
std::vector<size_t> Tree<T>::breadth_first_search_ids() const
{
  /*
   * We make the search in an iterative way, using a queue.
   * Although it is much more natural to use recursion here, this would
   * probably require, due to our implementation, to get at each step the
   * children as a collection of *newly made Tree* in order to apply the
   * recursion on them, which is far too expensive.
   */
  if (size() == 0)
    return {};

  std::queue<size_t> queue;
  std::vector<size_t> out;

  /* Enqueue root's id. */
  size_t id = 0;
  queue.push(id);

  while (!queue.empty())
  {
    /* Pop one node id from the queue, and add it to the output. */
    id = queue.front();
    queue.pop();
    out.push_back(id);

    /* Add the children ids to the queue. */
    const auto& v = nodes_[id].second;
    for (size_t i = 2; i < v.size(); i++)
      queue.push(v[i]);
  }

  return out;
}

template <typename T>
std::vector<T> Tree<T>::breadth_first_search() const
{
  std::vector<size_t> sorted_ids = breadth_first_search_ids();
  std::vector<T> out;
  for (const auto& id : sorted_ids)
    out.push_back(nodes_[id].first);
  return out;
}

template <typename T>
std::vector<bool> Tree<T>::last_children() const
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
std::vector<size_t> Tree<T>::node_depths() const
{
  /**
   * To compute the depth of a node, we just we follow the path from this node
   * up to the root, and compute the length of this path.
   */
  std::vector<size_t> out;

  for (size_t i = 0; i < size(); i++)
  {
    size_t depth = 0;
    for (size_t j = i; j != 0; j = nodes_[j].second[0])
      depth++;
    out.push_back(depth);
  }

  return out;
}

template <typename T>
ssize_t Tree<T>::depth() const
{
  if (size() == 0)
    return -1;

  /* Return the max of all node depths. */
  size_t depth = 0;
  for (size_t i = 0; i < size(); i++)
    if (node_depths()[i] > depth)
      depth = node_depths()[i];
  return static_cast<ssize_t>(depth);
}

template <typename T>
size_t Tree<T>::size() const
{
  return nodes_.size();
}

template <typename T>
bool Tree<T>::is_leaf(size_t id) const
{
  return id < size() and nodes_[id].second.size() <= 2;
}

template <typename T>
size_t Tree<T>::nb_leaves() const
{
  size_t count = 0;
  for (size_t i = 0; i < size(); i++)
    if (is_leaf(i))
      count++;
  return count;
}

template <typename T>
size_t Tree<T>::nb_inner_nodes() const
{
  return size() - nb_leaves();
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree)
{
  return os << tree.to_string();
}
