#include <string>

#include "../../include/eval/lexer.hh"
#include "../../include/eval/operator.hh"
#include "../../include/eval/parser.hh"

Parser::Parser(std::string expression)
  : lexer_(Lexer(expression))
{}
