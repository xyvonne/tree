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

const std::vector<std::string> Operator::names \
        = { \
          "STOP", "NUMBER", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", \
            "UNARY_PLUS", "BINARY_PLUS", "UNARY_MINUS", "BINARY_MINUS", \
            "TIMES", "DIVIDE", "REMAINDER", "POWER" \
        };

const std::vector<unsigned> Operator::precedences \
        = {0, 0, 0, 0, 3, 1, 3, 1, 2, 2, 2, 4};

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
      return static_cast<long>(pow(first, second));
    default: // invalid operator
      throw EvalException::BadOperatorArguments();
  }
}

std::string Operator::to_string(bool verbose) const
{
  std::string str;

  if (verbose)
  {
    if (type_ == NUMBER)
      str = ", " + value();
    if (type_ >= UNARY_PLUS)
    {
      str += ", " + std::to_string(arity());
      str += ", " + std::to_string(precedence());
      str += ", ";
      str += (binding() ? "=>" : "<=");
    }
    str = "(" + name() + str + ")";
  }
  else
    /* std::string(1, c) explicitly converts a character c to a string. */
    str = (type_ == NUMBER) ? value() : std::string(1, symbol());

  return str + " ";
}
