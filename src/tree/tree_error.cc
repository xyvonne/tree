#include "../../include/tree/tree_error.hh"

namespace TreeException
{
  BaseException::BaseException(const std::string& message)
    : std::logic_error(message)
  {}

  EmptyTree::EmptyTree(const std::string& message)
    : BaseException(message)
  {}

  InvalidTable::InvalidTable(const std::string& message)
    : BaseException(message)
  {}
}
