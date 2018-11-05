#pragma once

#include <stack>
#include <string>

#include "lexer.hh"
#include "operator.hh"
#include "../tree/bin_tree.hh"

/* Type alias for ASTs. */
using AST = BinaryTree<Operator>;

/* Class interface. */

class Parser
{
  public:
    /// Constructor. The lexer used by the parser is set automatically.
    Parser(std::string expression);

    /**
     * Evaluate the expression, using an AST which is a BinaryTree (see the
     * documentation of this class).
     * An expression yielding a valid but empty AST is evaluated as 0.
     * Throw an EvalException::BadOperatorImplementation exception if the
     * expression cannot be evaluated. Actually, this must not happen here,
     * because if the expression in invalid, then while building the AST,
     * pop_operator_and_add_node() (see below) must throw the same exception
     * before.
     */
    long eval() const;

  private:
    /**
     * Lexer needed by the parser.
     * It can be made const, because we only use the next_token() method from
     * it, which is also made const (see the Lexer class for details).
     */
    const Lexer lexer_;

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
     * If pop_operator_and_add_node() meets a non-unary and
     * non-binary operator (this must not happen, because the Lexer instance
     * has already checked this), it thrown an
     * EvalException::BadOperatorImplementation exception.
     */
    AST ast() const;
    void pop_operator_and_add_node(\
        std::stack<Operator>& O, std::stack<AST>& A) const;
};
