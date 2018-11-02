#pragma once

#include <string>

#include "lexer.hh"

class Parser
{
  public:
    /// Constructor.
    Parser(std::string expression);

  private:
    /// Lexer needed by the parser.
    Lexer lexer_;
};
