//
// Created by machunxiao on 2020/4/30.
//

#ifndef MINIDB_SQLPARSER_H
#define MINIDB_SQLPARSER_H
#include "SqlLexer.h"
#include <memory>

/**
 * <pre>
 *  SqlExprParser : SqlParser
 *  SqlStmtParser : SqlParser
 * </pre>
 */

class SqlParser {
public:
  explicit SqlParser(const std::string& s);
  explicit SqlParser(std::shared_ptr<SqlLexer> lexer_);
  SqlParser(const SqlParser& rhs) = delete;
  SqlParser& operator=(const SqlParser& rhs) = delete;
  virtual ~SqlParser() = default;

  void accept(SqlToken expect);
  void accept(SqlToken::Kind kind);

  std::shared_ptr<SqlLexer> GetLexer();

protected:
  std::shared_ptr<SqlLexer> lexer;
};

#endif // MINIDB_SQLPARSER_H