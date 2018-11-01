#include "../../include/tree/tree_error.hh"

EmptyTree::EmptyTree(const std::string& message)
  : TreeException(message)
{}

InvalidTable::InvalidTable(const std::string& message)
  : TreeException(message)
{}

TreeException::TreeException(const std::string& message)
  : std::logic_error(message)
{}


