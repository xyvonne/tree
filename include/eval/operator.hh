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
 * Lexer, and only this class, needs to construct Operators instances, and
 * handle operator types directly. The other classes only need the provided
 * interface (public part).
 */
class Lexer; // forward declaration
class Operator
{
  friend Lexer; // Operators are constructed by Lexer instances only.

  public:
  /**
   * Tell if an Operator instance is respectively a left parenthesis,
   * number, true arithmetic operator, right parenthesis, or STOP token.
   */
  inline bool is_left_parenthesis() const { return type_ == LEFT_PARENTHESIS; }
  inline bool is_number() const { return type_ == NUMBER; }
  inline bool is_operator() const { return type_ >= UNARY_PLUS; }
  inline bool is_right_parenthesis() const {return type_ == RIGHT_PARENTHESIS;}
  inline bool is_stop() const { return type_ == STOP; }

  /// Getters for operator traits.
  inline unsigned arity() const { return arities[(size_t) type_]; }
  inline bool binding() const { return bindings[(size_t) type_]; }
  inline unsigned precedence() const { return precedences[(size_t) type_]; }
  inline char symbol() const { return symbols[(size_t) type_]; }

  /*
   * Evaluation.
   * Numbers are treated as operators with arity 0: just eval() a number to
   * get its value as a long integer.
   * Throw an EvalException::BadOperatorArguments exception if the number
   * of given arguments is different from the operator arity.
   * Throw an EvalException::DivisionByZero exception if one attempts
   * to divide by 0 (i.e., to pass in "0" as second argument during a
   * DIVIDE or REMAINDER operation, or to raise 0 to a negative power).
   */
  long eval() const; // operators with arity 0
  long eval(long first) const; // unary operators
  long eval(long first, long second) const; // binary operators

  /// Represent an Operator instance as a string.
  std::string to_string() const;

  /**
   * Operator equality. We need this operator== overloading to construct
   * Tree<Operator> objects (a.k.a. ASTs).
   */
  bool operator==(const Operator& other) const;

  /**
   * Operator precedence in the sense of Shunting-yard Algorithm:
   * roughly speaking, o1 > o2 if o1 has higher precedence
   * (in the usual sense) than o2, or if o1 and o2 have the same precedence
   * and o1 is right associative.
   * (Actually, there is an extra condition for parentheses, please refer
   * to the implementation for full details.)
   */
  bool operator>(const Operator& other) const;

  private:
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

  /// Operator traits (note that they are class attributes).
  static const std::vector<unsigned> arities;
  static const std::vector<bool> bindings;
  static const std::vector<unsigned> precedences;
  static const std::vector<char> symbols;

  /// Operator type.
  const Type type_;

  /// Operator value.
  const std::string value_;

  /// Constructor.
  Operator(Type type = NUMBER, const std::string& value = "");
};
