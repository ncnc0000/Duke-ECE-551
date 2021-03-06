#include <cstdlib>
#include <sstream>
#include <string>
class Expression
{
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
  long n;

 public:
  NumExpression(long v) : n(v) {}
  std::string toString() const {
    //std::string s = std::to_string(n);
    std::stringstream ss;
    ss << n;
    std::string str = ss.str();
    return str;
  }
  long evaluate() const { return n; }
  ~NumExpression() {}
};

class OpExpression : public Expression
{
 protected:
  std::string str1;
  std::string str2;
  long a;
  long b;

 public:
  OpExpression(Expression * lhs, Expression * rhs) {
    str1 = lhs->toString();
    str2 = rhs->toString();
    a = lhs->evaluate();
    b = rhs->evaluate();
    //delete lhs;
    //delete rhs;
  }
  virtual ~OpExpression() {}
};

class PlusExpression : public OpExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs) {}
  std::string toString() const {
    std::stringstream ss;
    ss << "(" << str1 << " + " << str2 << ")";
    std::string str = ss.str();
    return str;
  }
  long evaluate() const { return long(a + b); }
  ~PlusExpression() {}
};

class MinusExpression : public OpExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs) {}
  std::string toString() const {
    std::stringstream ss;
    ss << "(" << str1 << " - " << str2 << ")";
    std::string str = ss.str();
    return str;
  }
  long evaluate() const { return long(a - b); }
  ~MinusExpression() {}
};

class TimesExpression : public OpExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs) {}
  std::string toString() const {
    std::stringstream ss;
    ss << "(" << str1 << " * " << str2 << ")";
    std::string str = ss.str();
    return str;
  }
  long evaluate() const { return long(a * b); }
  ~TimesExpression() {}
};

class DivExpression : public OpExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs) {}
  std::string toString() const {
    std::stringstream ss;
    ss << "(" << str1 << " / " << str2 << ")";
    std::string str = ss.str();
    return str;
  }
  long evaluate() const { return long(a / b); }
  ~DivExpression() {}
};
