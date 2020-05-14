//
// Created by machunxiao on 2020/5/8.
//

#ifndef MINIDB_DBENGINE_H
#define MINIDB_DBENGINE_H
#include <memory>
#include <spdlog/spdlog.h>
#include <utility>

#include "BufferManager.h"
#include "CatalogManager.h"
#include "RelNode.h"
#include "StringUtils.h"

class DbEngine {
public:
  explicit DbEngine(std::string path_);
  explicit DbEngine(const char* path_);

  ~DbEngine() = default;

  /// region ddl

  void CreateDatabase(const std::string& db);
  void DropDatabase(const std::string& db);
  void DropTable(const std::string& tb);
  void DropIndex(const std::string& index);

  /// endregion ddl

  /// region dml

  void Execute(RelNode& node);

  /// endregion dml

private:
  std::shared_ptr<CatalogManager> cm;
  std::shared_ptr<BufferManager> bm;
};
#endif // MINIDB_DBENGINE_H
