//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_TYPES_H
#define MINIDB_TYPES_H

class SqlKind {
public:
  enum SqlType {
    // DML
    INSERT = 1,
    DELETE = 2,
    UPDATE = 3,
    SELECT = 4,
    // DDL
    CREATE_DATABASE = 5,
    DROP_DATABASE = 6,
    DROP_SCHEMA = 7, // eq: drop database
    CREATE_TABLE = 8,
    ALTER_TABLE = 9,
    DROP_TABLE = 10,
    DESC_TABLE = 11,
    CREATE_INDEX = 12,
    ALTER_INDEX = 13,
    DROP_INDEX = 14,
    // DCL
    USE_DATABASE = 15,
  };
  inline static bool IsDML(SqlType t) { return t >= INSERT && t <= SELECT; }
  inline static bool IsDDL(SqlType t) {
    return t >= CREATE_DATABASE && t <= DROP_INDEX;
  }
};

#endif // MINIDB_TYPES_H
