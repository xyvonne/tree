#pragma once

#include <string>

#include "operator.hh"

class Lexer
{
  public:
    /**
     * Constructor.
     * Store the expression to be read, and set the position (=index in this
     * string) of the character being read to 0.
     * Call is_valid() (see below) to check the lexical validity of the given
     * expression. If this fails, throw an EvalException::LexerError
     * exception.
     */
    Lexer(std::string expression);

    /**
     * Read (consume) the next token, and return it as an operator.
     * This method can be made const because the only member attribute it
     * modifies, namely pos_, is mutable.
     */
    Operator next_token() const;

  private:
    /// Expression to be split into tokens.
    const std::string expression_;

    /*
     * Position (index) of the character currently read in the expression.
     * Mutability is required here to make several methods of this class
     * const, and hence allow definitions like "auto o1 = lexer._next_token()"
     * in the parser.
     */
    mutable size_t pos_;

    /**
     * If a number is currently read, consume it and return it as a number.
     * This method can be made const because the only member attribute it
     * modifies, namely pos_, is mutable.
     */
   std::string consume_number() const;

    /**
     * If an arithmetic operator or a parenthesis is currently being read,
     * consume it and return its operator type.
     * Throw an EvalException::UnknownToken exception if this type could not
     * be determined.
     * This method can be made const because the only member attribute it
     * modifies, namely pos_, is mutable.
     */
    Operator::Type consume_operator() const;

    /// Tell if the '+/-' currently read is binary (true) or unary (false).
    bool is_binary() const;

    /// Tell if the expression consists only in digits or valid symbols.
    bool is_valid() const;
};
