#include "../../include/eval/eval_error.hh"

namespace EvalException
{
  /* ArithmeticError */
  Code ArithmeticError::code() const
  {
    return ARITHMETIC_ERROR;
  }

  /* BadArgument */
  Code BadArgument::code() const
  {
    return BAD_ARGUMENT;
  }
  const char* BadArgument::what() const throw()
  {
    return "[ERROR 4] Bad number of arguments. Usage: ./eval <expression>";
  }

  /* BadImplementation */
  Code BadImplementation::code() const
  {
    return BAD_IMPLEMENTATION;
  }

  /* BadOperatorArguments */
  const char* BadOperatorArguments::what() const throw()
  {
    return ("[ERROR 5] Bad operator arguments.\n" \
        "Please read the \"eval_error.hh\" documentation for more details.");
  }

  /* BadOperatorImplementation */
  const char* BadOperatorImplementation::what() const throw()
  {
    return ("[ERROR 5] Bad operator implementation.\n" \
        "Please read the \"eval_error.hh\" documentation for more details.");
  }

  /* DivisionByZero */
  const char* DivisionByZero::what() const throw()
  {
    return "[ERROR 3] Division by zero";
  }

  /* LexerError */
  Code LexerError::code() const
  {
    return LEXER_ERROR;
  }
  const char* LexerError::what() const throw()
  {
    return "[ERROR 1] Syntax error: lexer error";
  }

  /* ParserError */
  Code ParserError::code() const
  {
    return PARSER_ERROR;
  }
  const char* ParserError::what() const throw()
  {
    return "[ERROR 2] Syntax error: parser error";
  }

  /* UnknownToken */
  const char* UnknownToken::what() const throw()
  {
    return ("[ERROR 5] Unknown token.\n" \
        "Please read the \"eval_error.hh\" documentation for more details.");
  }
}
