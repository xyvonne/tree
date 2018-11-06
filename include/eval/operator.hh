#pragma once

#include <string>
#include <vector>

class Lexer; // forward declaration
class Operator
{
  friend Lexer; // Operators are constructed by Lexer instances only.

  public:
  /**
   * Recall from the documentation class that this class is a kind of
   * union type between numbers, arithmetic operators, and other tokens
   * (parentheses and STOP).
   * The following methods tell if an Operator instance is respectively a left
   * parenthesis, number, true arithmetic operator, right parenthesis, or STOP
   * token.
   */
  inline bool is_left_parenthesis() const { return type_ == LEFT_PARENTHESIS; }
  inline bool is_number() const { return type_ == NUMBER; }
  inline bool is_operator() const { return type_ >= UNARY_PLUS; }
  inline bool is_right_parenthesis() const {return type_ == RIGHT_PARENTHESIS;}
  inline bool is_stop() const { return type_ == STOP; }

  /*
   * Getters for operator traits.
   * Recall from the documentation class that binding() returns true if the
   * operator binds from left to right, and false otherwise.
   */
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

  /**
   * Equality operator and its negation for Operator instances. We need this
   * operator== overloading to construct Tree<Operator> objects (a.k.a. ASTs).
   */
  bool operator==(const Operator& other) const;
  bool operator!=(const Operator& other) const;

  /**
   * Operator precedence in the sense of Shunting-yard Algorithm:
   * roughly speaking, o1 >= o2 if o1 has higher precedence
   * (in the usual sense) than o2, or if o1 and o2 have the same precedence
   * and o1 is right-associative.
   * (Actually, there is an extra condition for parentheses, please refer
   * to the implementation for full details.)
   */
  bool operator<=(const Operator& other) const;
  bool operator>=(const Operator& other) const;

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

  /**
   * Operator traits (these are class attributes).
   * Elements of the Type enumeration above can be directly used as indexes
   * for the following vectors to access to the corresponding operator traits.
   * Binding is stored as a Boolean, set to true if the operator binds from
   * left to right, and to false otherwise.
   */
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
