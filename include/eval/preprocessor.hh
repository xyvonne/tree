#pragma once

#include <string>

/* Do not mix this class with the C/C++ standard preprocessor! */
class Preprocessor
{
  public:
    /**
     * Constructor.
     * Do some little preprocessing, i.e. call in order
     * check_implementation(), parse_command_line() and remove_whitespaces()
     * (see below).
     */
    Preprocessor(int argc, char** argv);

    /// Return the preprocessed expression.
    inline std::string expression() const { return expression_; }

  private:
    /// Copy of the arguments passed in to the program.
    const int argc_;
    char** argv_;

    /// Expression to be preprocessed.
    std::string expression_;

    /**
     * Check that the operator implementation is correct.
     * Throw an EvalException::BadOperatorImplementation exception if not.
     */
    void check_implementation() const;

    /**
     * Check that exactly 1 argument is passed in to the program; if not,
     * throw an EvalException::EmptyExpression or an
     * EvalException:TooManyArguments exception.
     */
    std::string parse_command_line() const;

    /// Remove all whitespaces (e.g. ' ', '\n', '\r', '\t') from expression_.
    void remove_whitespaces();
};
