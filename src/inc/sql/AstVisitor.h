//
// Created by machunxiao on 2020/5/12.
//

#ifndef MINIDB_ASTVISITOR_H
#define MINIDB_ASTVISITOR_H

#include "SqlCall.h"

class RelNode;

template <class R, class C>
class AstVisitor {
 public:
  R Visit(const SqlNode& x, const C& ctx);

  // region SqlExpr

  R Visit(const SqlExpr& x, const C& ctx);
  R Visit(const SqlBetweenExpr& x, const C& ctx);
  R Visit(const SqlBinaryExpr& x, const C& ctx);
  R Visit(const SqlColDefExpr& x, const C& ctx);
  R Visit(const SqlFuncCallExpr& x, const C& ctx);
  R Visit(const SqlIdent& x, const C& ctx);
  R Visit(const SqlInListExpr& x, const C& ctx);
  R Visit(const SqlLikeExpr& x, const C& ctx);
  R Visit(const SqlSubQueryExpr& x, const C& ctx);
  R Visit(const SqlExistsSubQueryExpr& x, const C& ctx);
  R Visit(const SqlInSubQueryExpr& x, const C& ctx);
  R Visit(const SqlScalarSubQueryExpr& x, const C& ctx);
  R Visit(const SqlValue& x, const C& ctx);

  // endregion SqlExpr

  // region SqlCall

  R Visit(const SqlCall& x, const C& ctx);
  R Visit(const SqlCreateDatabase& x, const C& ctx);
  R Visit(const SqlCreateIndex& x, const C& ctx);
  R Visit(const SqlCreateTable& x, const C& ctx);
  R Visit(const SqlDropDatabase& x, const C& ctx);
  R Visit(const SqlDropIndex& x, const C& ctx);
  R Visit(const SqlDropTable& x, const C& ctx);
  R Visit(const SqlInsert& x, const C& ctx);
  R Visit(const SqlDelete& x, const C& ctx);
  R Visit(const SqlUpdate& x, const C& ctx);
  R Visit(const SqlSelect& x, const C& ctx);

  // endregion SqlCall
};

class AstToStr : public AstVisitor<std::string, int> {};

class AstToRel : public AstVisitor<RelNode, void*> {};

#endif  // MINIDB_ASTVISITOR_H
