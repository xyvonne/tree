#include <math.h> // pow
#include <string>
#include <vector>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/operator.hh"

const std::vector<unsigned> Operator::arities \
        = {0, 0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 2};

// Bindings: true=left binding; false=right binding
const std::vector<bool> Operator::bindings \
        = {true, true, true, true, false, true, \
          false, true, true, true, true, false};

const std::vector<unsigned> Operator::precedences \
        = {0, 0, 0, 0, 4, 1, 4, 1, 2, 2, 2, 3};

const std::vector<char> Operator::symbols \
        = {'$', '0', '(', ')', 'p', '+', 'm', '-', '*', '/', '%', '^'};

Operator::Operator(Type type, const std::string& value)
  : type_(type), value_(value)
{}

long Operator::eval() const
{
  if (type() == NUMBER)
    return std::stol(value());
  else // invalid operator
    throw EvalException::BadOperatorArguments();
}

long Operator::eval(long first) const
{
  switch (type())
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
  switch (type())
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

bool Operator::operator==(const Operator& other) const
{
  return (type() == other.type() and !value().compare(other.value()));
}

bool Operator::operator>(const Operator& other) const
{
 if (other.type_ < UNARY_PLUS) // other is not a real operator
   return false;
 return (precedence() > other.precedence()) \
   or (precedence() == other.precedence() and !binding());
}

std::string Operator::to_string() const
{
  /* std::string(1, c) explicitly converts a character c to a string. */
  return (type_ == NUMBER) ? value() : std::string(1, symbol());
}
