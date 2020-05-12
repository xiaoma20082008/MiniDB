//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_SQLEXPR_H
#define MINIDB_SQLEXPR_H
#include "SqlNode.h"
#include "Types.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

#define DEF_EXPR(name) struct Sql##name##Expr : public SqlExpr

struct SqlExpr : public SqlNode {
  virtual ~SqlExpr() = default;
};

struct SqlIdent : public SqlExpr {
  explicit SqlIdent(std::string name_) : name(std::move(name_)) {}
  std::string name;
};

class Holder {
public:
  virtual ~Holder() = default;
};

template <typename ValueType> class SqlValueObj : public Holder {
public:
  explicit SqlValueObj(ValueType v) : value(std::move(v)) {}

public:
  ValueType getValue() { return value; }

private:
  ValueType value;
};

struct SqlValue : public SqlExpr {
public:
  template <typename ValueType>
  explicit SqlValue(ValueType value)
      : data(new SqlValueObj<ValueType>(value)) {}
  ~SqlValue() { delete data; };
  template <typename ValueType> ValueType getData() {
    return ((SqlValueObj<ValueType>)data).getValue();
  }

private:
  Holder* data{};
};

DEF_EXPR(Binary) {
  enum BinaryOp {
    // logical
    AND,
    OR,
    // arithmetic
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    POW,
    // Compare
    GT,
    GE,
    LT,
    LE,
    NEQ,
    EQ,
  };
  SqlExpr* lhs;
  SqlExpr* rhs;
  BinaryOp opt;
};

/// a like '%xxx%'
DEF_EXPR(Like) {
  std::string name;
  bool negated;
  SqlExpr* expr;
};

/// a in (x,x,x)
DEF_EXPR(InList) {
  SqlIdent* name;
  bool negated;
  std::vector<SqlExpr*> values;
};

/// a between xx and xx
DEF_EXPR(Between) {
  SqlIdent* name;
  bool negated;
  SqlExpr* lower;
  SqlExpr* upper;
};

/// max(a),min(a),...
DEF_EXPR(FuncCall){};

DEF_EXPR(ColDef) {

  ~SqlColDefExpr() {
    delete colName;
    delete colType;
    delete colDesc;
  }

  SqlIdent* colName;
  SqlIdent* colType;
  SqlIdent* colDesc;
};

#endif // MINIDB_SQLEXPR_H
