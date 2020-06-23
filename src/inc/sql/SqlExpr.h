//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_SQLEXPR_H
#define MINIDB_SQLEXPR_H
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "SqlNode.h"
#include "Types.h"

#define DEF_EXPR(name) struct Sql##name##Expr : public SqlExpr

struct SqlExpr : public SqlNode {
  virtual ~SqlExpr() = default;
};

struct SqlIdent : public SqlExpr {
  explicit SqlIdent(std::string name_) : name(std::move(name_)) {}
  std::string name;
};

enum class ValueType {
  T_LONG,
  T_DOUBLE,
  T_STRING,
};

struct SqlValueObj {
  ValueType type_; /**< tag appropriately (eg. ) */
  /**
   * value, as specified value type
   */
  union ValueUnion {
    int64_t l_val;     /**< A machine integer */
    double d_val;      /**< double */
    std::string s_val; /**< string */
  } value_;            /**< value */
};

struct SqlValue : public SqlExpr {
 public:
  SqlValue(int64_t s) {
    data = {};
    data->type_ = ValueType::T_LONG;
    data->value_.l_val = s;
  }
  SqlValue(double s) {
    data = {};
    data->type_ = ValueType::T_DOUBLE;
    data->value_.d_val = s;
  }
  SqlValue(std::string s) {
    data = {};
    data->type_ = ValueType::T_STRING;
    data->value_.s_val = s;
  }
  ~SqlValue(){};

 private:
  SqlValueObj* data{};
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

#endif  // MINIDB_SQLEXPR_H
