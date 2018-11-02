#include <string>
#include <vector>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/lexer.hh"
#include "../../include/eval/operator.hh"

Lexer::Lexer(std::string expression)
  : expression_(expression), pos_(0)
{
  if (!is_valid())
    throw LexerError();
}

std::string Lexer::consume_number()
{
  /* end: first index such that expression_[end] is no longer a digit. */
  size_t end = pos_;
  for(; end < expression_.size(); end++)
  {
    char c = expression_[end];
    if (c < '0' or c > '9')
      break;
  }

  /* Consume all digits read, and return the number read as a sring. */
  pos_ = end;
  return expression_.substr(pos_, end - pos_);
}

Operator::Type Lexer::consume_operator()
{
  Operator::Type type = Operator::NUMBER;
  char c = expression_[pos_];

  /* Find the operator type corresponding to the character currently read. */
  for (size_t i = 0; \
      i < Operator::symbols.size() and type == Operator::NUMBER; \
      i++)
    if (c == Operator::symbols[i])
      type = static_cast<Operator::Type>(i);

  /* What if the operator type was not found? This should never happen!!! */
  if (type == Operator::NUMBER)
    throw UnknownToken();

  /* Distinguish between unary and binary plus. */
  if (type == Operator::BINARY_PLUS and !is_binary())
    type = Operator::UNARY_PLUS;

  /* Distinguish between unary and binary minus. */
  if (type == Operator::BINARY_MINUS and !is_binary())
    type = Operator::UNARY_MINUS;

  /* Consume the operator, and return its type. */
  pos_++;
  return type;
}

bool Lexer::is_binary() const
{
  if (pos_ == 0)
    return false;
  char c = expression_[pos_ - 1];
  return ('0' <= c and c <= '9') or c == ')';
}

bool Lexer::is_valid() const
{
  for (char c : expression_)
  {
    if (c == 'm' or c == 'p' or c == '$') // these are token symbols ...
      return false; // ... but not usual arithmetic operator symbols
    if ('0' <= c and c <= '9') // digits are valid
      continue;

    bool is_operator = false; // test if c is an operator symbol
    for (char s : Operator::symbols)
      if (c == s)
      {
        is_operator = true;
        break;
      }
    if (!is_operator)
      return false;
  }
  return true;
}

Operator Lexer::next_token()
{
  /* Case when there's nothing left to read. */
  if (pos_ >= expression_.size())
    return Operator(Operator::STOP);

  /* Consume the currently read number or operator, and return it as a token. */
  char c = expression_[pos_];
  if ('0' <= c and c <= '9')
    return Operator(Operator::NUMBER, consume_number());
  else
    return Operator(consume_operator());
}
