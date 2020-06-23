//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_SQLCALL_H
#define MINIDB_SQLCALL_H

#include "SqlExpr.h"

struct SqlCall : public SqlNode {
  SqlKind::SqlType type;
};

#define DEF_CALL(name) \
  struct Sql##name : public SqlCall, public Visitable<Sql##name>

DEF_CALL(Insert) {
  SqlInsert() : SqlCall() { type = SqlKind::INSERT; }
  ~SqlInsert() {
    delete table;
    insertColumns.clear();
    insertValues.clear();
  }
  SqlIdent* table{};
  std::vector<SqlIdent*> insertColumns{};
  std::vector<SqlValue*> insertValues{};
};
DEF_CALL(Delete) {
  SqlDelete() : SqlCall() { type = SqlKind::DELETE; }

  SqlIdent* table{};
  SqlExpr* where{};
};
DEF_CALL(Update) {
  SqlUpdate() : SqlCall() { type = SqlKind::UPDATE; }
  SqlIdent* table{};
  std::vector<SqlIdent*> updateColumns;
  SqlExpr* where{};
};
DEF_CALL(Select) {
  SqlSelect() : SqlCall() { type = SqlKind::SELECT; }
  SqlIdent* table{};
  SqlExpr* where{};
};

/// region trx

DEF_CALL(Begin){};
DEF_CALL(Commit){};
DEF_CALL(Rollback){};

/// endregion trx

/**
 * create database database_name;
 */
DEF_CALL(CreateDatabase) {
  explicit SqlCreateDatabase(std::string db)
      : database(std::move(db)), SqlCall() {
    type = SqlKind::CREATE_DATABASE;
  }
  std::string database;
};
/**
 * <pre>
 * create table table_name (
 *  col_def (',' col_def)*
 * )
 * col_def
 *  : col_name col_type (num)
 *  ;
 * </pre>
 */
DEF_CALL(CreateTable) {
  SqlCreateTable() : SqlCall() { type = SqlKind::CREATE_TABLE; }
  ~SqlCreateTable() {
    delete table;
    for (auto def : columnDef) {
      delete def;
    }
    columnDef.clear();
  }
  SqlIdent* table{};
  std::vector<SqlColDefExpr*> columnDef{};
};
/**
 * <pre>
 * create index
 *  index_name
 * on
 *  table_name (field (',' field)*)
 * </pre>
 */
DEF_CALL(CreateIndex) {
  SqlCreateIndex() : SqlCall() { type = SqlKind::CREATE_INDEX; }
  ~SqlCreateIndex() {
    delete index;
    delete table;
    for (auto field : fields) {
      delete field;
    }
    fields.clear();
  }
  SqlIdent* index{};
  SqlIdent* table{};
  std::vector<SqlIdent*> fields{};
};
/**
 * drop database database_name;
 */
DEF_CALL(DropDatabase) {
  explicit SqlDropDatabase(const char* database_) : SqlCall() {
    database = std::string(database_);
    type = SqlKind::DROP_DATABASE;
  }
  explicit SqlDropDatabase(const std::string& database_) : SqlCall() {
    database = database_;
    type = SqlKind::DROP_DATABASE;
  }
  std::string database;
};
/**
 * drop table table_name;
 */
DEF_CALL(DropTable) {
  explicit SqlDropTable(const char* table_) : SqlCall() {
    table = std::string(table_);
    type = SqlKind::DROP_TABLE;
  }
  explicit SqlDropTable(const std::string& table_) : SqlCall() {
    table = table_;
    type = SqlKind::DROP_TABLE;
  }
  std::string table;
};
/**
 * drop index index_name;
 */
DEF_CALL(DropIndex) {
  explicit SqlDropIndex(const char* index_) : SqlCall() {
    index = std::string(index_);
    type = SqlKind::DROP_INDEX;
  }
  explicit SqlDropIndex(const std::string& index_) : SqlCall() {
    index = index_;
    type = SqlKind::DROP_INDEX;
  }
  std::string database;
  std::string index;
};

// region subQuery
struct SqlSubQueryExpr : public SqlExpr {};

/// a in (select xxx)
struct SqlInSubQueryExpr : public SqlSubQueryExpr {
  SqlIdent* name{};
  bool negated{false};
  SqlSelect* subSelect{};
};

/// a exists (select xxx)
struct SqlExistsSubQueryExpr : public SqlSubQueryExpr {
  SqlIdent* name{};
  bool negated{false};
  SqlSelect* subSelect{};
};

///
struct SqlScalarSubQueryExpr : public SqlSubQueryExpr {};

// endregion subQuery

#endif  // MINIDB_SQLCALL_H
