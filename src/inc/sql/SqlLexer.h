//
// Created by machunxiao on 2020/4/30.
//

#ifndef MINIDB_SQLLEXER_H
#define MINIDB_SQLLEXER_H
#include "exception/Exception.h"
#include <string>
#include <unordered_map>
#include <utility>

class SqlToken {
public:
  enum Kind {
    INVALID = 0,
    INSERT = 1,
    UPDATE = 2,
    DELETE = 3,
    SELECT = 4,
    CREATE = 5,
    DROP = 6,
    ALTER = 7,
    SHOW = 8,
    DESC = 9,
    INTO = 10,
    VALUES = 11,
    INDEX,
    TABLE,
    DATABASE,
    SCHEMA,
    FROM,
    WHERE,
    // logical
    AND,
    OR,
    NOT,
    BETWEEN,

    ON,
    USING,
    IN,

    STAR,

    LONG_V,
    FLOAT_V,
    STR_V,
    IDENTIFIER,
    // compare
    EQ,
    NEQ,
    GT,
    GE,
    LT,
    LE,
    // binary
    // arithmetic
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,     // 求模
    POW,     // 乘方
    EXC,     // 感叹号
    AMP,     // &
    AMP_AMP, // &&
    BAR,     // |
    BAR_BAR, // ||
    // (
    LP,
    // )
    RP,
    // .
    DOT,
    // ;
    SEMI,
    // ,
    COMMA,
  };

  SqlToken() : kind_(INVALID) {}
  SqlToken(Kind k) : kind_(k) {}

public:
  std::string name();
  Kind kind() { return kind_; }

private:
  Kind kind_;
};

class SqlLexer {
public:
  explicit SqlLexer(std::string _sql);
  explicit SqlLexer(const char* _sql);
  SqlLexer(const SqlLexer& rhs) = delete;
  SqlLexer& operator=(const SqlLexer& rhs) = delete;
  ~SqlLexer() = default;

public:
  void nextToken();

  void scanNumber();

  void scanString();

  void scanIdentifier();

  SqlToken token() { return token_; }

  std::string identifier();

  int64_t longValue() { return long_value; }
  double doubleValue() { return double_value; }
  std::string stringValue() { return str_value; }

private:
  void scanChar();
  char charAt(int index);
  static bool isWhitespace(char c);
  static bool isIdentChar(char c);
  static bool isNumberChar(char c);

private:
  std::string sql;

private:
  int pos = 0;
  int mark = 0;
  char ch;

  int64_t long_value = 0;
  double double_value = 0.0;
  std::string str_value = "";

  SqlToken token_;
};

#endif // MINIDB_SQLLEXER_H
