#include "error.hh"

EmptyTree::EmptyTree(const std::string& message)
  : std::logic_error(message)
{}
