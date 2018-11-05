#include <math.h> // pow

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/operator.hh"

/* Operator trait implementation. */

const std::vector<unsigned> Operator::arities \
        = {0, 0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 2};
const std::vector<bool> Operator::bindings \
        = {true, true, true, true, false, true, \
          false, true, true, true, true, false};
const std::vector<unsigned> Operator::precedences \
        = {0, 0, 0, 0, 4, 1, 4, 1, 2, 2, 2, 3};
const std::vector<char> Operator::symbols \
        = {'$', '0', '(', ')', 'p', '+', 'm', '-', '*', '/', '%', '^'};

/* Methods. */

Operator::Operator(Type type, const std::string& value)
  : type_(type), value_(value)
{}

long Operator::eval() const
{
  if (!is_number()) // invalid operator
    throw EvalException::BadOperatorArguments();
  return std::stol(value_);
}

long Operator::eval(long first) const
{
  switch (type_)
  {
    case (UNARY_PLUS):
      return first;

    case (UNARY_MINUS):
      return -first;

    default: // invalid operator
      throw EvalException::BadOperatorArguments();
  }
}

long Operator::eval(long first, long second) const
{
  switch (type_)
  {
    case (BINARY_PLUS):
      return first + second;

    case (BINARY_MINUS):
      return first - second;

    case (TIMES):
      return first * second;

    case (DIVIDE):
      {
        if (second == 0)
          throw EvalException::DivisionByZero();
        else
          return first / second;
      }

    case (REMAINDER):
      {
        if (second == 0)
          throw EvalException::DivisionByZero();
        else
          return first % second;
      }

    case (POWER):
      {
        if (first == 0 and second < 0)
          throw EvalException::DivisionByZero();
        else
          return static_cast<long>(pow(first, second));
      }

    default: // invalid operator
      throw EvalException::BadOperatorArguments();
  }
}

/* Operator overloading. */

bool Operator::operator==(const Operator& other) const
{
  return (type_ == other.type_ and !value_.compare(other.value_));
}

bool Operator::operator!=(const Operator& other) const
{
  return not(*this == other);
}

bool Operator::operator<=(const Operator& other) const
{
  return other >= *this;
}

bool Operator::operator>=(const Operator& other) const
{
  return \
    (other.is_operator()) \
    and (!is_right_parenthesis()) \
    and (precedence() > other.precedence() \
        or (precedence() == other.precedence() and !binding()));
}
