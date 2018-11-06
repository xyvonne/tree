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
     * Throw an EvalException::BadOperatorImplementation exception if, for
     * some reason, the expression cannot be evaluated. Actually, this must
     * not happen here, because if the expression in invalid, then while
     * building the AST, pop_operator_and_add_node() (see below) must already
     * have thrown an exception.
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
     * Dijkstra's Shunting-yard Algorithm. For more details concerning this
     * algorithm, please refer to the class documentation.
     * If any step from this algorithm fails, meaning that the expression
     * is syntactically invalid, an EvalException::ParserError is thrown.
     * pop_operator_and_add_node() is the part of the algorithm that is run
     * when an operator is popped from the stack, and a new AST is built from
     * this operator and the children ASTs. If this method meets a
     * non-unary and non-binary operator (this must not happen, because the
     * Lexer instance has already checked this), an
     * EvalException::BadOperatorImplementation exception is thrown.
     */
    AST ast() const;
    void pop_operator_and_add_node(\
        std::stack<Operator>& O, std::stack<AST>& A) const;
};
