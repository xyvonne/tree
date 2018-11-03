#include <algorithm> // std::reverse
#include <stack>
#include <string>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/lexer.hh"
#include "../../include/eval/operator.hh"
#include "../../include/eval/parser.hh"
#include "../../include/tree/tree.hh"

Parser::Parser(std::string expression)
  : lexer_(Lexer(expression))
{}

AST Parser::ast() const
{
  std::stack<Operator> O;
  std::stack<AST> A;

  /* Read the whole expression. */
  while (true)
  {
    /*
     * Tricky!
     * The snippet Operator o1; o1 = lexer_.next_token(); does not compile.
     * The value returned by a method can only be used as a rhs in a
     * definition, but not in a later assignment, so this o1 cannot be
     * modified either. And so, I could see no other way to write this loop.
     */
    const auto o1 = lexer_.next_token();
    if (o1.type() == Operator::STOP)
      break;

    /* Two easy cases. */
    if (o1.type() == Operator::NUMBER)
    {
      A.push({o1}); // Numbers are pushed onto the AST stack.
      continue;
    }
    if (o1.type() == Operator::LEFT_PARENTHESIS)
    {
      O.push(o1); // '(' are pushed onto the operator stack.
      continue;
    }

    /*
     * The core of the Shunting-yard algorithm roughly runs as follows.
     * If o1 is a right parenthesis, then we pop from the operator stack until
     * we met a left parenthesis (there must be at least one), and update
     * the AST stack accordingly.
     * If o1 has greater precedence than the operator o2 on the top of the
     * stack, then we push o1 to the operator stack.
     * If o1 has lesser precedence than o2, we pop o2 from the operator stack,
     * update the AST stack accordingly, and repeat this until the former
     * condition is false.
     */
    bool missing_left_parenthesis = (o1.type() == Operator::RIGHT_PARENTHESIS);

    while (!O.empty())
    {
      Operator o2 = O.top();
      if (o2.type() == Operator::LEFT_PARENTHESIS)
      {
        missing_left_parenthesis = false;
        if (o1.type() == Operator::RIGHT_PARENTHESIS)
          O.pop();
        break;
      }
      if (o1.type() != Operator::RIGHT_PARENTHESIS and o1 > o2)
        break;
      pop_operator_and_add_node(O, A);
    }

    if (missing_left_parenthesis)
      throw EvalException::ParserError();
    if (o1.type() != Operator::RIGHT_PARENTHESIS)
      O.push(o1);
  }

  /* Pop from the operator stack all the remaining operators. */
  while (!O.empty())
    pop_operator_and_add_node(O, A);

  /* Get the result. */
  if (A.empty())
    return {};
  if (A.size() != 1)
    throw EvalException::ParserError();
  return A.top();
}

void Parser::pop_operator_and_add_node(\
    std::stack<Operator>& O, std::stack<AST>& A) const
{
  /* Pop an operator from the operator stack. */
  if (O.empty())
    throw EvalException::ParserError();
  Operator o = O.top();
  O.pop();

  /* This operator must be neither a parenthesis, nor a number, nor STOP. */
  if (o.type() < Operator::UNARY_PLUS)
    throw EvalException::ParserError();

  /* Collect the children ASTs from the AST stack, and combine them with the
   * operator to push a new AST to the AST stack. */
  std::vector<AST> children;

  unsigned r =  o.arity();
  while (r--) // repeat r times
  {
    if (A.empty())
      throw EvalException::ParserError();
    const auto a = A.top();
    A.pop();
    children.push_back(a);
  }
  std::reverse(children.begin(), children.end()); // reverse the children order
  A.push(AST(o, children));
}

long Parser::eval() const
{
  const auto RPN = ast().post_order_search();

  /* Trivial case. */
  if (RPN.empty())
    return 0;

  /**
   * Read the RPN vector from left to right, and evluate on-the-fly
   * using a stack to store temporary results.
   */
  std::stack<long> numbers;
  for (const auto& o : RPN)
  {
    if (o.type() == Operator::NUMBER)
      numbers.push(o.eval());

    unsigned r = o.arity();
    if (numbers.size() < r)
      throw EvalException::ParserError();

    if (o.arity() == 1)
    {
      long first = numbers.top();
      numbers.pop();
      numbers.push(o.eval(first));
    }

    if (o.arity() == 2)
    {
      long second = numbers.top();
      numbers.pop();
      long first = numbers.top();
      numbers.pop();
      numbers.push(o.eval(first, second));
    }
  }

  /* Get the result. */
  if (numbers.size() != 1) // should not occur, since our AST is valid
    throw EvalException::ParserError();
  return numbers.top();
}
