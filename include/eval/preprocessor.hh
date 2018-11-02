#pragma once

#include <string>

/* Do not mix this class with the C/C++ standard preprocessor! */
class Preprocessor
{
  public:
    /**
     * Class constructor.
     * Do some little preprocessing, i.e. calls in order
     * check_implementation(), parse_command_line() and remove_whitespaces()
     * (see below).
     */
    Preprocessor(int argc, char** argv, std::string default_expression = "");

    /// Return the preprocessed expression.
    inline std::string expression() const { return expression_; }

  private:
    /// Copy of the arguments passed in to the program.
    const int argc_;
    char** argv_;

    /// Expression to be processed if the user did not provide one.
    std::string default_expression_;

    /// Actual expression to be preprocessed.
    std::string expression_;

    /**
     * Check that the operator implementation is correct.
     * Throw a BadOperatorImplementation() exception if not.
     */
    void check_implementation() const;

    /**
     * Check that exactly 1 argument is passed in to the program;
     * if no argument is passed to the program but a default_expression
     * is passed in to the constructor, use this expression instead;
     * otherwise, throw an EmptyExpression() or a TooManyArguments()
     * exception.
     */
    std::string parse_command_line() const;

    /// Remove all whitespaces (e.g. ' ', '\n', '\r', '\t') from expression.
    void remove_whitespaces();
};
