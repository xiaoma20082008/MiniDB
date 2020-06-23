//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_SQLEXPRPARSER_H
#define MINIDB_SQLEXPRPARSER_H

#include <vector>

#include "SqlExpr.h"
#include "SqlParser.h"

class SqlExprParser : public SqlParser {
 public:
  explicit SqlExprParser(const std::string& s);
  explicit SqlExprParser(std::shared_ptr<SqlLexer> lexer_);

  SqlExpr* ParseExpr();

  SqlIdent* ParseIdent();

  SqlValue* ParseValue();

  void ParseExprList(std::vector<SqlExpr*>& exprList);

  void ParseIdentList(std::vector<SqlIdent*>& identList);
  void ParseValueList(std::vector<SqlValue*>& valueList);
};

#endif  // MINIDB_SQLEXPRPARSER_H
