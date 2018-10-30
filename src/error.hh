#pragma once

#include <exception>
#include <stdexcept>
#include <string>

/// A very simple exception hadler for empty trees.
struct EmptyTree : public std::logic_error
{
  EmptyTree(const std::string& message = "");
};
