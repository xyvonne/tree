#include <vector>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/lexer.hh"
#include "../../include/eval/operator.hh"

Lexer::Lexer(std::string expression)
  : expression_(expression), pos_(0)
{
  if (!is_valid_operator_implementation())
    throw EvalException::BadOperatorImplementation();

  remove_whitespaces();

  if (!is_valid_expression())
    throw EvalException::LexerError();
}

std::string Lexer::consume_number() const
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
  const auto out = expression_.substr(pos_, end - pos_);
  pos_ = end;
  return out;
}

Operator::Type Lexer::consume_operator() const
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
    throw EvalException::UnknownToken();

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

bool Lexer::is_valid_expression() const
{
  for (const auto& c : expression_)
  {
    if (c == 'm' or c == 'p' or c == '$') // these are token symbols ...
      return false; // ... but not usual arithmetic operator symbols
    if ('0' <= c and c <= '9') // digits are valid
      continue;

    bool is_operator = false; // test if c is an operator symbol
    for (const auto& s : Operator::symbols)
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

bool Lexer::is_valid_operator_implementation()
{
  return \
    Operator::arities.size() == Operator::bindings.size()
    and Operator::arities.size() == Operator::precedences.size()
    and Operator::arities.size() == Operator::symbols.size();
}

Operator Lexer::next_token() const
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

void Lexer::remove_whitespaces()
{
  /* Naive implementation. */
  std::string old = expression_;
  expression_ .clear();
  for (const auto& c : old)
   if (c != ' ' and c != '\n' and c != '\r' and c != '\t')
     expression_ += c;

#if 0
  /* Less naive implementation:
   * https://www.gamedev.net/forums/topic/359650-remove-whitespace-from-string/
   */
#include<algorithm>
  expression_.erase(\
      remove_if(expression_.begin(), expression_.end(), ::isspace), \
      expression_.end());
#endif
}
