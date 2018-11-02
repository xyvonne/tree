#include <exception>

#include "../../include/eval/eval_error.hh"

//ArithmeticError
EvalException::Code ArithmeticError::code() const
{
  return EvalException::ARITHMETIC_ERROR;
}

//BadImplementation
EvalException::Code BadImplementation::code() const
{
  return EvalException::BAD_IMPLEMENTATION;
}

// BadOperatorImplementation
const char* BadOperatorImplementation::what() const throw()
{
  return ("[ERROR 5] Bad operator implementation.\n" \
      "Please read the \"error.hh\" documentation for more details.");
}

// DivisionByZero
const char* DivisionByZero::what() const throw()
{
  return "[ERROR 3] Division by zero";
}

// EmptyExpression
EvalException::Code EmptyExpression::code() const
{
  return EvalException::EMPTY_EXPRESSION;
}
const char* EmptyExpression::what() const throw()
{
  return "[ERROR 0] Empty expression. Usage: ./eval <expression to evaluate>";
}

// LexerError
EvalException::Code LexerError::code() const
{
  return EvalException::LEXER_ERROR;
}
const char* LexerError::what() const throw()
{
  return "[ERROR 1] Syntax error: lexer error";
}

// ParserError
EvalException::Code ParserError::code() const
{
  return EvalException::PARSER_ERROR;
}
const char* ParserError::what() const throw()
{
  return "[ERROR 2] Syntax error: parser error";
}

// TooManyArguments
EvalException::Code TooManyArguments::code() const
{
  return EvalException::BAD_ARGUMENT;
}
const char* TooManyArguments::what() const throw()
{
  return "[ERROR 4] Too many arguments. Usage: ./eval <expression to evaluate>";
}

// UnknownToken
const char* UnknownToken::what() const throw()
{
  return ("[ERROR 5] Unknown token.\n" \
      "Please read the \"error.hh\" documentation for more details.");
}
