//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_SQLSTMTPARSER_H
#define MINIDB_SQLSTMTPARSER_H
#include "SqlCall.h"
#include "SqlExprParser.h"
#include "SqlLexer.h"

class SqlStmtParser : public SqlParser {
public:
  explicit SqlStmtParser(const std::string& s);
  explicit SqlStmtParser(SqlExprParser* parser_);
  ~SqlStmtParser() override { delete exprParser; };
  SqlCall* ParseCall();

protected:
  // region parse dml

  SqlInsert* ParseInsert();
  SqlDelete* ParseDelete();
  SqlUpdate* ParseUpdate();
  SqlSelect* ParseSelect();

  // endregion parse dml

  // region parse ddl

  SqlCreateDatabase* ParseCreateDb();
  SqlCreateTable* ParseCreateTb();
  SqlCreateIndex* ParseCreateIndex();
  SqlDropDatabase* ParseDropDb();
  SqlDropTable* ParseDropTb();
  SqlDropIndex* ParseDropIndex();

  // endregion parse ddl
protected:
  SqlExprParser* exprParser;
};

#endif // MINIDB_SQLSTMTPARSER_H
