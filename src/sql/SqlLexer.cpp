//
// Created by machunxiao on 2020/4/30.
//
#include "sql/SqlLexer.h"

static std::unordered_map<SqlToken::Kind, std::string> kinds{
    {SqlToken::Kind::INSERT, "insert"},
    {SqlToken::Kind::DELETE, "delete"},
    {SqlToken::Kind::UPDATE, "update"},
    {SqlToken::Kind::SELECT, "select"},

    {SqlToken::Kind::CREATE, "create"},
    {SqlToken::Kind::DROP, "drop"},
    {SqlToken::Kind::ALTER, "alter"},
    {SqlToken::Kind::SHOW, "show"},
    {SqlToken::Kind::DESC, "desc"},

    {SqlToken::Kind::INDEX, "index"},
    {SqlToken::Kind::TABLE, "table"},
    {SqlToken::Kind::DATABASE, "database"},
    {SqlToken::Kind::SCHEMA, "schema"},

    {SqlToken::Kind::INTO, "into"},
    {SqlToken::Kind::VALUES, "values"},
    {SqlToken::Kind::FROM, "from"},
    {SqlToken::Kind::WHERE, "where"},
    {SqlToken::Kind::AND, "and"},
    {SqlToken::Kind::OR, "or"},
    {SqlToken::Kind::NOT, "not"},
    {SqlToken::Kind::BETWEEN, "between"},
    {SqlToken::Kind::ON, "on"},
    {SqlToken::Kind::USING, "using"},

    {SqlToken::Kind::EQ, "="},
    {SqlToken::Kind::NEQ, "!="},
    {SqlToken::Kind::GT, ">"},
    {SqlToken::Kind::GE, ">="},
    {SqlToken::Kind::LT, "<"},
    {SqlToken::Kind::LE, "<="},

    {SqlToken::Kind::LP, "("},
    {SqlToken::Kind::RP, ")"},
    {SqlToken::Kind::DOT, "."},
    {SqlToken::Kind::COMMA, ","},
    {SqlToken::Kind::SEMI, ";"},
    {SqlToken::Kind::STAR, "*"},

};

static std::unordered_map<std::string, SqlToken::Kind> keywords{
    {"insert", SqlToken::Kind::INSERT},
    {"delete", SqlToken::Kind::DELETE},
    {"update", SqlToken::Kind::UPDATE},
    {"select", SqlToken::Kind::SELECT},

    {"create", SqlToken::Kind::CREATE},
    {"drop", SqlToken::Kind::DROP},
    {"alter", SqlToken::Kind::ALTER},
    {"show", SqlToken::Kind::SHOW},
    {"desc", SqlToken::Kind::DESC},

    {"index", SqlToken::Kind::INDEX},
    {"table", SqlToken::Kind::TABLE},
    {"database", SqlToken::Kind::DATABASE},
    {"schema", SqlToken::Kind::SCHEMA},

    {"into", SqlToken::Kind::INTO},
    {"values", SqlToken::Kind::VALUES},
    {"from", SqlToken::Kind::FROM},
    {"where", SqlToken::Kind::WHERE},
    {"and", SqlToken::Kind::AND},
    {"or", SqlToken::Kind::OR},
    {"not", SqlToken::Kind::NOT},
    {"between", SqlToken::Kind::BETWEEN},
    {"on", SqlToken::Kind::ON},
    {"using", SqlToken::Kind::USING},
    {"in", SqlToken::Kind::IN},
};

std::string SqlToken::name() { return kinds[kind_]; }

SqlLexer::SqlLexer(const char* _sql) : SqlLexer(std::string(_sql)) {}
SqlLexer::SqlLexer(std::string _sql) {
  sql = std::move(_sql);
  ch = sql[0];
}

void SqlLexer::nextToken() {
  for (;;) {
    if (isWhitespace(ch)) {
      scanChar();
      continue;
    }
    switch (ch) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      scanNumber();
      return;
    }
    case '\'': {
      scanString();
      return;
    }
    case '(': {
      token_ = SqlToken::LP;
      scanChar();
      return;
    }
    case ')': {
      token_ = SqlToken::RP;
      scanChar();
      return;
    }
    case ',': {
      token_ = SqlToken::COMMA;
      scanChar();
      return;
    }
    case '+': {
      token_ = SqlToken::ADD;
      scanChar();
      return;
    }
    case '-': {
      token_ = SqlToken::SUB;
      scanChar();
      return;
    }
    case '*': {
      token_ = SqlToken::STAR;
      scanChar();
      return;
    }
    case '/': {
      token_ = SqlToken::DIV;
      scanChar();
      return;
    }
    case '%': {
      token_ = SqlToken::MOD;
      scanChar();
      return;
    }
    case '&': {
      scanChar();
      if (ch == '&') {
        scanChar();
        token_ = SqlToken::AMP_AMP;
      } else {
        token_ = SqlToken::AMP;
      }
      return;
    }
    case '|': {
      scanChar();
      if (ch == '|') {
        scanChar();
        token_ = SqlToken::BAR_BAR;
      } else {
        token_ = SqlToken::BAR;
      }
    }
    case '!': {
      scanChar();
      if (ch == '=') {
        scanChar();
        token_ = SqlToken::NEQ;
      } else {
        token_ = SqlToken::EXC;
      }
    }
    case '>': {
      scanChar();
      if (ch == '=') {
        scanChar();
        token_ = SqlToken::GE;
      } else {
        token_ = SqlToken::GT;
      }
      return;
    }
    case '<': {
      scanChar();
      if (ch == '=') {
        scanChar();
        token_ = SqlToken::LE;
      } else if (ch == '>') {
        scanChar();
        token_ = SqlToken::NEQ;
      } else {
        token_ = SqlToken::LT;
      }
      return;
    }
    default: {
      scanIdentifier();
      return;
    }
    }
  }
}
void SqlLexer::scanIdentifier() {
  std::string s;
  if (isIdentChar(ch) && isNumberChar(ch)) {
    throw LexerException(std::string("illegal identifier:") + ch);
  }
  mark = pos;
  s += ch;
  for (;;) {
    scanChar();
    if (isIdentChar(ch)) {
      s += ch;
    } else {
      break;
    }
  }
  SqlToken tk = keywords[s];
  if (tk.kind() != SqlToken::Kind::INVALID) {
    token_ = tk;
    str_value = s;
  } else {
    str_value = s;
    token_ = SqlToken::IDENTIFIER;
  }
}
void SqlLexer::scanNumber() {
  mark = pos;
  bool isFloat = false;
  if (ch == '-') {
    scanChar();
  }
  for (;;) {
    if (isNumberChar(ch)) {
      scanChar();
    } else {
      break;
    }
  }
  if (ch == '.') {
    if (isNumberChar(charAt(pos + 1))) {
      scanChar();
      isFloat = true;
      for (;;) {
        if (isNumberChar(ch)) {
          scanChar();
        } else {
          break;
        }
      }
    }
  }
  str_value = identifier();
  if (isFloat) {
    double_value = std::stod(str_value);
    token_ = SqlToken::FLOAT_V;
  } else {
    long_value = std::stol(str_value);
    token_ = SqlToken::LONG_V;
  }
}
void SqlLexer::scanString() {
  scanChar();
  mark = pos;
  std::string ss;
  while (ch != '\'') {
    ss += ch;
    scanChar();
  }
  scanChar();
  str_value = std::move(ss);
  token_ = SqlToken::STR_V;
}

std::string SqlLexer::identifier() { return sql.substr(mark, pos - mark); }

void SqlLexer::scanChar() {
  if (pos >= sql.size()) {
    ch = EOF;
  } else {
    ++pos;
    ch = charAt(pos);
  }
}
char SqlLexer::charAt(int index) {
  if (index >= sql.size()) {
    return EOF;
  } else {
    return sql[index];
  }
}

bool SqlLexer::isWhitespace(char c) {
  return c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == '\f';
}

bool SqlLexer::isIdentChar(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
         (c >= '0' && c <= '9') || (c == '_') || (c == '$');
}
bool SqlLexer::isNumberChar(char c) { return (c >= '0' && c <= '9'); }