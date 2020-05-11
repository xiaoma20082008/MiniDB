//
// Created by machunxiao on 2020/5/9.
//
#include "SqlStmtParser.h"

SqlStmtParser::SqlStmtParser(const std::string& s)
    : SqlStmtParser(new SqlExprParser(s)) {}

SqlStmtParser::SqlStmtParser(SqlExprParser* parser_)
    : SqlParser(parser_->GetLexer()) {
  exprParser = parser_;
}

SqlCall* SqlStmtParser::ParseCall() {
  switch (lexer->token().kind()) {
  case SqlToken::INSERT:
    return ParseInsert();
  case SqlToken::DELETE:
    return ParseDelete();
  case SqlToken::UPDATE:
    return ParseUpdate();
  case SqlToken::SELECT:
    return ParseSelect();
  case SqlToken::CREATE: {
    lexer->nextToken();
    if (lexer->token().kind() == SqlToken::TABLE) {
      lexer->nextToken();
      return ParseCreateTb();
    } else if (lexer->token().kind() == SqlToken::DATABASE ||
               lexer->token().kind() == SqlToken::SCHEMA) {
      lexer->nextToken();
      return ParseCreateDb();
    } else if (lexer->token().kind() == SqlToken::INDEX) {
      lexer->nextToken();
      return ParseCreateIndex();
    }
  }
  case SqlToken::DROP: {
    lexer->nextToken();
    if (lexer->token().kind() == SqlToken::TABLE) {
      lexer->nextToken();
      return ParseDropTb();
    } else if (lexer->token().kind() == SqlToken::DATABASE ||
               lexer->token().kind() == SqlToken::SCHEMA) {
      lexer->nextToken();
      return ParseDropDb();
    } else if (lexer->token().kind() == SqlToken::INDEX) {
      lexer->nextToken();
      return ParseDropIndex();
    }
  }
  default:
    std::string error;
    error += std::string("unknown sql kind: ");
    error += lexer->stringValue();
    throw ParserException(error);
  }
}

// region parse dml

SqlInsert* SqlStmtParser::ParseInsert() {
  auto insert = new SqlInsert();
  lexer->nextToken();
  if (lexer->token().kind() == SqlToken::INTO) {
    lexer->nextToken();
    insert->table = new SqlIdent(lexer->stringValue());
    lexer->nextToken();
  } else {
    insert->table = exprParser->ParseIdent();
  }
  if (lexer->token().kind() == SqlToken::LP) {
    lexer->nextToken();
    exprParser->ParseIdentList(insert->insertColumns);
    accept(SqlToken::RP);
  }
  accept(SqlToken::VALUES);
  accept(SqlToken::LP);
  exprParser->ParseValueList(insert->insertValues);
  accept(SqlToken::RP);
  return insert;
}
SqlDelete* SqlStmtParser::ParseDelete() { return nullptr; }
SqlUpdate* SqlStmtParser::ParseUpdate() { return nullptr; }
SqlSelect* SqlStmtParser::ParseSelect() { return nullptr; }

// endregion parse dml

// region parse ddl

SqlCreateDatabase* SqlStmtParser::ParseCreateDb() {
  auto cmd = new SqlCreateDatabase(lexer->stringValue());
  return cmd;
}
SqlCreateTable* SqlStmtParser::ParseCreateTb() {
  auto cmd = new SqlCreateTable();
  cmd->table = exprParser->ParseIdent();
  accept(SqlToken::LP);
  // todo
  // exprParser->ParseColumnDefs(cmd->columnDef);
  accept(SqlToken::RP);
  return cmd;
}
SqlCreateIndex* SqlStmtParser::ParseCreateIndex() {
  auto cmd = new SqlCreateIndex();
  cmd->index = exprParser->ParseIdent();
  accept(SqlToken::ON);
  cmd->table = exprParser->ParseIdent();
  accept(SqlToken::LP);
  exprParser->ParseIdentList(cmd->fields);
  accept(SqlToken::RP);
  return cmd;
}
SqlDropDatabase* SqlStmtParser::ParseDropDb() {
  return new SqlDropDatabase(lexer->stringValue());
}
SqlDropTable* SqlStmtParser::ParseDropTb() {
  return new SqlDropTable(lexer->stringValue());
}
SqlDropIndex* SqlStmtParser::ParseDropIndex() {
  return new SqlDropIndex(lexer->stringValue());
}

// endregion parse ddl
