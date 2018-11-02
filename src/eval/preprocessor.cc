#include <algorithm> // remove whitespaces //FIXME
#include <iostream> // parse_command_line() may raise a warning //FIXME
#include <string>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/operator.hh"
#include "../../include/eval/preprocessor.hh"

Preprocessor::Preprocessor(int argc, char** argv, \
    std::string default_expression)
: argc_(argc), argv_(argv), \
    default_expression_(default_expression)
{
  check_implementation();
  expression_ = parse_command_line();
  remove_whitespaces();
}

void Preprocessor::check_implementation() const
{
  // Check if all vectors implementing operator traits have the same size.
  if (Operator::names.size() != Operator::arities.size() \
      or Operator::names.size() != Operator::symbols.size() \
      or Operator::names.size() != Operator::precedences.size() \
      or Operator::names.size() != Operator::bindings.size())
    throw EvalException::BadOperatorImplementation();
}

std::string Preprocessor::parse_command_line() const
{
  if (argc_ == 1)
  {
    if (default_expression_ == "")
      throw EvalException::EmptyExpression();
    else
    {
      std::cerr << "[WARNING] No expression provided: evaluating ";
      std::cerr << default_expression_ << " instead." << std::endl;
      return default_expression_;
    }
  }

  if (argc_ > 2)
    throw EvalException::TooManyArguments();

  return argv_[1];
}

void Preprocessor::remove_whitespaces()
{
  expression_.erase(\
      remove_if(expression_.begin(), expression_.end(), ::isspace), \
      expression_.end());
}
