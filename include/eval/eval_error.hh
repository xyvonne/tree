#pragma once

#include <exception>

/**
 * This is the interface for all our Eval exception classes,
 * ordered w.r.t. breadth-first search in the hierarchy class tree.
 */

namespace EvalException
{
  /**
   * Exit program codes.
   */
  enum Code
  {
    EMPTY_EXPRESSION = 0,
    LEXER_ERROR = 1,
    PARSER_ERROR = 2,
    ARITHMETIC_ERROR = 3,
    BAD_ARGUMENT = 4,
    BAD_IMPLEMENTATION = 5
  };

  /**
   * BaseException
   * Base exception class.
   * Not to be instantiated.
   */
  struct BaseException : public std::exception
  {
    /**
     * Getter for exit program code.
     * The error message itself is handled by the STL's method what().
     */
    virtual Code code() const = 0;
  };

  /**
   * BaseException/ArithmeticError
   * Thrown if the evaluation leads to a arithmetic error (e.g., division by 0).
   * Not to be instantiated.
   */
  struct ArithmeticError : public BaseException
  {
    virtual Code code() const override;
  };

  /**
   * BaseException/BadArgument
   * Thrown if the user does not provide exactly 1 expression.
   * Not to be instantiated.
   */
  struct BadArgument : public BaseException
  {};

  /**
   * BaseException/BadImplementation
   * Thrown if the program logic is broken.
   * Probably reveals a unknown bug in the code.
   * Not to be instantiated.
   */
  struct BadImplementation : public BaseException
  {
    virtual Code code() const override;
  };

  /**
   * BaseException/SyntaxError
   * Thrown if the lexer finds an invalid symbol, or the parsing
   * fails because the expression is not well-formed.
   * Not to be instantiated.
   */
  struct SyntaxError : public BaseException
  {};

  /**
   * BaseException/ArithmeticError/DivisionbyZero
   * Thrown if the second operand of '/' (division) or '%' (remainder) is 0.
   */
  struct DivisionByZero : public ArithmeticError
  {
    virtual const char* what() const throw() override;
  };

  /**
   * BaseException/BadArgument/EmptyExpression
   * Thrown if no argument is passed in to the program.
   */
  struct EmptyExpression : public BadArgument
  {
    virtual Code code() const override;
    virtual const char* what() const throw() override;
  };

  /**
   * BaseException/BadArgument/TooManyArguments
   * Thrown if too many arguments are passed in to the program.
   */
  struct TooManyArguments : public BadArgument
  {
    virtual Code code() const override;
    virtual const char* what() const throw() override;
  };

  /**
   * BaseException/BadImplementation/BadOperatorArguments
   * Thrown if during operator evaluation, the wrong number of operands
   * (=arguments) are passed in: for example, if only 1 number (instead of 2)
   * is passed in for a BINARY_PLUS operatation.
   */
  struct BadOperatorArguments : public BadImplementation
  {
    virtual const char* what() const throw() override;
  };

  /**
   * BaseException/BadImplementation/BadOperatorImplementation
   * Thrown if the operators are not well-defined in "operator.cc",
   * for example if the sizes of the vectors referring to arities,
   * bindings, operator names, precedences and symbols do not match.
   */
  struct BadOperatorImplementation : public BadImplementation
  {
    virtual const char* what() const throw() override;
  };

  /**
   * BaseException/BadImplementation/UnknownToken
   * Thrown if the lexer meets an unknown operator token.
   * Probably reveals an unknown bug in the implementation of the Lexer class.
   */
  struct UnknownToken : public BadImplementation
  {
    virtual const char* what() const throw() override;
  };

  /**
   * BaseException/BadArgument/LexerError
   * Thrown if the lexer finds an invalid symbol.
   */
  struct LexerError : public SyntaxError
  {
    virtual Code code() const override;
    virtual const char* what() const throw() override;
  };

  /**
   * BaseException/BadArgument/ParserError
   * Thrown if a syntax error is detected by the parser.
   */
  struct ParserError : public SyntaxError
  {
    virtual Code code() const override;
    virtual const char* what() const throw() override;
  };
}
