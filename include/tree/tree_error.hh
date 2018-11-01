#pragma once

#include <exception>
#include <stdexcept>
#include <string>

/*
 * A very simple exception handler for empty trees, or trees constructed from
 * invalid tables.
 */

struct TreeException : public std::logic_error
{
  TreeException(const std::string& message = "");
};

struct EmptyTree : public TreeException
{
  EmptyTree(const std::string& message = "");
};

struct InvalidTable : public TreeException
{
  InvalidTable(const std::string& message = "");
};
