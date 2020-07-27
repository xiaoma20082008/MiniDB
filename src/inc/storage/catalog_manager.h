//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_CATALOG_MANAGER_H
#define MINIDB_CATALOG_MANAGER_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "common/StringUtils.h"

class Column;
class Index;
class Table;
class Database;

class Column {
 private:
  std::string name;
  int position;
  std::string fullType;
  std::string type;
  bool nullable;
  bool primary;

  int length;
  int scale;
  int precision;

  Table* table;
};
class Index {
 private:
  std::string name;
};
class Table {
 private:
  std::vector<Column*> columns;
};
class Database {};

class CatalogManager {
 public:
  explicit CatalogManager(std::string path_) : path(std::move(path_)) {}
  explicit CatalogManager(const char* path_) : path(path_) {}

  std::shared_ptr<Database> GetDb(const std::string& name);

  void DeleteDatabase(const std::string& name);
  void CreateDatabase(const std::string& name);

  void CreateTable(const Table& table);
  void DropTable(const std::string& name);
  void AlterTable();

  void CreateIndex(const Index& index);
  void DropIndex(const std::string& name);
  void AlterIndex();

 private:
  std::string path = "";
  std::unordered_map<std::string, std::shared_ptr<Database>> databases{};
};

#endif  // MINIDB_CATALOG_MANAGER_H
