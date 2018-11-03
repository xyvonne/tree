#include <string>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/operator.hh"
#include "../../include/eval/preprocessor.hh"

Preprocessor::Preprocessor(int argc, char** argv)
  : argc_(argc), argv_(argv)
{
  check_implementation();
  expression_ = parse_command_line();
  remove_whitespaces();
}

void Preprocessor::check_implementation() const
{
  /* Check if all vectors implementing operator traits have the same size. */
  if (Operator::arities.size() != Operator::bindings.size() \
      or Operator::arities.size() != Operator::precedences.size() \
      or Operator::arities.size() != Operator::symbols.size())
    throw EvalException::BadOperatorImplementation();
}

std::string Preprocessor::parse_command_line() const
{
  if (argc_ == 1)
    throw EvalException::EmptyExpression();
  if (argc_ > 2)
    throw EvalException::TooManyArguments();
  return argv_[1];
}

void Preprocessor::remove_whitespaces()
{
  /* Naive implementation. */
  std::string old = expression_;
  expression_ .clear();
  for (const auto& c : old)
   if (c != ' ' and c != '\n' and c != '\r' and c != '\t')
     expression_ += c;

#if 0
  /** Less naive implementation:
   * https://www.gamedev.net/forums/topic/359650-remove-whitespace-from-string/
   */
#include<algorithm>
  expression_.erase(\
      remove_if(expression_.begin(), expression_.end(), ::isspace), \
      expression_.end());
#endif
}
