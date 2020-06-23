//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_TYPES_H
#define MINIDB_TYPES_H

class SqlKind {
 public:
  enum SqlType {
    // DML 1~20
    INSERT = 1,
    DELETE = 2,
    UPDATE = 3,
    SELECT = 4,
    REPLACE = 5,
    // DDL 21~50
    CREATE_DATABASE = 21,
    DROP_DATABASE = 22,
    DROP_SCHEMA = 23,  // eq: drop database
    CREATE_TABLE = 24,
    ALTER_TABLE = 25,
    DROP_TABLE = 26,
    DESC_TABLE = 27,
    CREATE_INDEX = 28,
    ALTER_INDEX = 29,
    DROP_INDEX = 20,
    // DCL 51 ~
    USE_DATABASE = 51,
  };
  inline static bool IsDML(SqlType t) { return t >= INSERT && t <= REPLACE; }
  inline static bool IsDDL(SqlType t) {
    return CREATE_DATABASE <= t && t <= DROP_INDEX;
  }
};

#endif  // MINIDB_TYPES_H
