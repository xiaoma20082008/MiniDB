//
// Created by machunxiao on 2020/5/9.
//
#include "sql/SqlExprParser.h"

#include <utility>

SqlExprParser::SqlExprParser(const std::string& s) : SqlParser(s) {}
SqlExprParser::SqlExprParser(std::shared_ptr<SqlLexer> lexer_)
    : SqlParser(std::move(lexer_)) {}

/**
 * expr
 *  : literal                                               #LiteralExpr
 *  | ident                                                 #IdentExpr
 *  | functionCall                                          #FunCallExpr
 *  | ('+' | '-' | '~') expr                                #UnaryExpr
 *  | expr operator expr                                    #BinaryExpr
 *  | 'not' expr                                            #NotExpr
 *  | expr 'is' 'not'? 'null'                               #IsNullExpr
 *  | 'between' expr 'and' expr                             #BetweenExpr
 *  | 'like' expr                                           #LikeExpr
 *  ;
 * operator
 *  : '+' | '-' | '*' | '/' | '%' |'^'                      #ArithmeticExpr
 *  | '<' | '<=' | '>' | '>=' | '!=' | '<>'                 #CompareExpr
 *  | 'and' | 'or'                                          #LogicalExpr
 *  ;
 * @return SqlExpr
 */
SqlExpr* SqlExprParser::ParseExpr() {
  SqlExpr* mainExpr{};
  switch (lexer->token().kind()) {
    case SqlToken::IDENTIFIER: {
      mainExpr = ParseIdent();
      break;
    }
    case SqlToken::LONG_V:
    case SqlToken::FLOAT_V:
    case SqlToken::STR_V: {
      mainExpr = ParseValue();
      break;
    }
    default: {
      break;
    }
  }
  return mainExpr;
}

SqlIdent* SqlExprParser::ParseIdent() {
  auto ident = new SqlIdent(lexer->stringValue());
  lexer->nextToken();
  return ident;
}

SqlValue* SqlExprParser::ParseValue() {
  SqlValue* value;
  if (lexer->token().kind() == SqlToken::LONG_V) {
    value = new SqlValue(lexer->longValue());
  } else if (lexer->token().kind() == SqlToken::FLOAT_V) {
    value = new SqlValue(lexer->doubleValue());
  } else {
    value = new SqlValue(lexer->stringValue());
  }
  lexer->nextToken();
  return value;
}

void SqlExprParser::ParseValueList(std::vector<SqlValue*>& valueList) {
  for (;;) {
    valueList.push_back(ParseValue());
    if (lexer->token().kind() == SqlToken::COMMA) {
      lexer->nextToken();
    } else {
      break;
    }
  }
}

void SqlExprParser::ParseIdentList(std::vector<SqlIdent*>& identList) {
  for (;;) {
    identList.push_back(ParseIdent());
    if (lexer->token().kind() == SqlToken::COMMA) {
      lexer->nextToken();
    } else {
      break;
    }
  }
}

void SqlExprParser::ParseExprList(std::vector<SqlExpr*>& out) {
  for (;;) {
    out.push_back(ParseExpr());
    if (lexer->token().kind() == SqlToken::COMMA) {
      lexer->nextToken();
    } else {
      break;
    }
  }
}
