#include <sstream>
#include <string>
class Expression
{
 public:
  Expression() {}
  virtual std::string toString() const = 0;
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
  ~NumExpression() {}
};

class OpExpression : public Expression
{
 protected:
  std::string str1;
  std::string str2;

 public:
  OpExpression(Expression * lhs, Expression * rhs) {
    str1 = lhs->toString();
    str2 = rhs->toString();
    delete lhs;
    delete rhs;
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
  ~DivExpression() {}
};
