#pragma once

#include <exception>
#include <stdexcept>
#include <string>

struct EmptyTree : public std::logic_error
{
  EmptyTree(const std::string& message = "");
};
