//
// Created by machunxiao on 2020/5/8.
//
#include "api/db_engine.h"

#include <spdlog/spdlog.h>

#include <memory>
#include <utility>

#include "exception/Exception.h"
#include "optimizer/rel_node.h"
#include "storage/buffer_manager.h"
#include "storage/catalog_manager.h"

struct DbEngine::Impl {
  explicit Impl(std::string path_) {
    cm = std::make_shared<CatalogManager>(path_);
    bm = std::make_shared<BufferManager>();
  }

  std::shared_ptr<CatalogManager> cm;
  std::shared_ptr<BufferManager> bm;
};

DbEngine::DbEngine(const char* path_) : DbEngine(std::string(path_)) {}

DbEngine::DbEngine(std::string path_) { impl = new Impl(std::move(path_)); }

DbEngine::~DbEngine() { delete impl; }

void DbEngine::CreateDatabase(const std::string& db) {
  auto database = impl->cm->GetDb(db);
  if (database != nullptr) {
    std::string error;
    error += "database: " + db + " ";
    error += "already exists";
    throw DbEngineException(error);
  }
  impl->cm->CreateDatabase(db);
}

void DbEngine::DropDatabase(const std::string& db) {
  auto database = impl->cm->GetDb(db);
  if (database == nullptr) {
    std::string error;
    error += "database: " + db + " ";
    error += "doesn't exists";
    throw DbEngineException(error);
  }
  impl->cm->DeleteDatabase(db);
}

void DbEngine::DropTable(const std::string& db, const std::string& tb) {}

void DbEngine::DropIndex(const std::string& db, const std::string& index) {}

void DbEngine::Execute(RelNode* node) {}