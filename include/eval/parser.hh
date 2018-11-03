#pragma once

#include <stack>
#include <string>

#include "lexer.hh"
#include "operator.hh"
#include "../../include/tree/tree.hh"

/* Type alias for ASTs. */
using AST = Tree<Operator>;

/* Class interface. */

class Parser
{
  public:
    /// Constructor. The lexer used by the parser is declared implicitly.
    Parser(std::string expression);

    /**
     * Evaluate the expression.
     * An expression yielding a valid but empty AST is evaluated as 0.
     */
    long eval() const;

  private:
    /// Lexer needed by the parser.
    Lexer lexer_;

    /**
     * Build the AST corresponding to the expression, using
     * Dijkstra's Shunting-yard Algorithm:
     *
     * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
     *
     * The difference with the classical algorithm presented there, is that we
     * work with a stack of ASTs instead of a queue of numbers. The execution
     * flow is the same, except that:
     * - instead of pushing a number to the number queue, we push onto the AST
     *   stack the AST reduced to the node storing this number;
     * - when we pop from the operator stack an operator with arity r,
     *   we also pop from the AST stack the last r ASTs, add the operator
     *   as a node on the top of them, and push the new AST to the stack;
     *   all of this is made by the pop_operator_and_add_node() method below.
     * Finally, there must be at most one AST left in the stack, which is the
     * AST we want (if the stack is empty, just return an empty AST too).
     * If any step from this algorithm fails, an EvalException::ParserError is
     * thrown.
     */
    AST ast() const;
    void pop_operator_and_add_node(\
        std::stack<Operator>& O, std::stack<AST>& A) const;
};
