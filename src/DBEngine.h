//
// Created by machunxiao on 2020/5/8.
//

#ifndef MINIDB_DBENGINE_H
#define MINIDB_DBENGINE_H
#include <utility>

#include "CatalogManager.h"
#include "RelNode.h"
#include "StringUtils.h"

class DBEngine {
public:
  explicit DBEngine(std::string path_) {
    cm = new CatalogManager(std::move(path_));
  }
  explicit DBEngine(const char* path_) { cm = new CatalogManager(path_); }

  ~DBEngine() { delete cm; }

  // region ddl
  void CreateDatabase(const std::string& db);
  void DropDatabase(const std::string& db);
  void DropTable(const std::string& tb);
  void DropIndex(const std::string& index);
  // endregion ddl

  // region dml
  void Execute(const RelNode& node);
  // endregion dml

private:
  CatalogManager* cm;
};
#endif // MINIDB_DBENGINE_H
