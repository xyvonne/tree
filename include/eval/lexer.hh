#pragma once

#include <string>

#include "operator.hh"

class Lexer
{
  public:
    /// Constructor.
    Lexer(std::string expression);

    /// Read (consume) the next token, and return it as an operator.
    Operator next_token();

  private:
    /// Expression to be split into tokens.
    const std::string expression_;

    /// Position (index) of the character currently read in the expression.
    size_t pos_;

    /// If a number is currently read, consume it and return it as a number.
    std::string consume_number();

    /// If an true operator is currenty read, consume it and return its type.
    Operator::Type consume_operator();

    /// Tell if the '+/-' currently read is binary (true) or unary (false).
    bool is_binary() const;

    /// Tell if the expression consists only in digits or valid symbols.
    bool is_valid() const;
};
