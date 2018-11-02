#pragma once

#include <string>
#include <vector>

/**
 * Every token returned by the lexer is considered as an operator. Roughly
 * speaking, this class is a union type between numbers, arithmetic operators,
 * and other tokens (parentheses and STOP).
 * Of course, the operator traits (symbol, arity, precedence and binding)
 * only make sense for arithmetic operators, and they are defined here in the
 * usual way.
 * The unary plus (resp. minus) has symbol 'p' (resp. 'm') to distinguish
 * it from its binary counterpart.
 * Binding is stored as a Boolean, set to true if the operator binds from
 * left to right, and to false otherwise.
 * However, in this class, operator traits are also defined for numbers,
 * STOP token and parentheses. They are set to a placeholder value which is
 * never used: this merely makes the implementation more convenient.
 * Every operator has a type, given by the following enumeration, and a value,
 * which is a string. For a number, this value is obvious; for other operators,
 * by convention this value is the empty string, and is never used.
 */
class Operator
{
  public:
    /// Operator type enumeration.
    enum Type
    {
      STOP, // EOF token (EOF is a reserved macro)
      NUMBER, // any number
      LEFT_PARENTHESIS,
      RIGHT_PARENTHESIS,
      UNARY_PLUS,
      BINARY_PLUS,
      UNARY_MINUS,
      BINARY_MINUS,
      TIMES,
      DIVIDE,
      REMAINDER,
      POWER
    };

    /// Constructor.
    Operator(Type type = NUMBER, const std::string& value = "");

    /// Getters.
    inline unsigned arity() const { return arities[(size_t) type_]; }
    inline bool binding() const { return bindings[(size_t) type_]; }
    inline unsigned precedence() const { return precedences[(size_t) type_]; }
    inline char symbol() const { return symbols[(size_t) type_]; }

    inline Type type() const { return type_; }
    inline std::string value() const { return value_; }

    inline std::string name() const { return names[(size_t) type_]; }

    /*
     * Evaluation. Numbers are evaluated trivially as operators with arity 0.
     * An exception //FIXME: which one?
     * is thrown if the number of given arguments is different from
     * the operator arity.
     */
    long eval() const; // operators with arity 0
    long eval(long first) const; // unary operators
    long eval(long first, long second) const; // binary operators

    /// Represent the operator as a string.
    std::string to_string(bool verbose = false) const;

    /// Operator traits (note that they are class attributes).
    static const std::vector<unsigned> arities;
    static const std::vector<bool> bindings;
    static const std::vector<std::string> names;
    static const std::vector<unsigned> precedences;
    static const std::vector<char> symbols;

  private:
    /// Operator type.
    const Type type_;

    /// Operator value.
    const std::string value_;
};
