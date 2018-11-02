#pragma once

#include <exception>
#include <stdexcept>
#include <string>

/*
 * A very simple exception handler for empty trees,
 * or trees constructed from invalid tables.
 */
namespace TreeException
{
  struct BaseException : public std::logic_error
  {
    BaseException(const std::string& message = "");
  };

  struct EmptyTree : public BaseException
  {
    EmptyTree(const std::string& message = "");
  };

  struct InvalidTable : public BaseException
  {
    InvalidTable(const std::string& message = "");
  };
}
