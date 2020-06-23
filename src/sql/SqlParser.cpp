//
// Created by machunxiao on 2020/4/30.
//
#include "sql/SqlParser.h"

#include <utility>

#include "exception/Exception.h"

// region SqlParser

SqlParser::SqlParser(const std::string& s)
    : SqlParser(std::make_shared<SqlLexer>(s)) {
  lexer->nextToken();
}

SqlParser::SqlParser(std::shared_ptr<SqlLexer> lexer_) {
  lexer = std::move(lexer_);
}

void SqlParser::accept(SqlToken::Kind kind) { accept(SqlToken(kind)); }

void SqlParser::accept(SqlToken expect) {
  if (lexer->token().kind() == expect.kind()) {
    lexer->nextToken();
  } else {
    std::string error;
    error += "expect:" + expect.name() + ",";
    error += "actual:" + lexer->token().name();
    throw ParserException(error);
  }
}

std::shared_ptr<SqlLexer> SqlParser::GetLexer() { return lexer; }

// endregion SqlParser
