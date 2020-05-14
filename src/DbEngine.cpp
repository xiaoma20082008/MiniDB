//
// Created by machunxiao on 2020/5/8.
//
#include "DbEngine.h"
#include "Exception.h"

DbEngine::DbEngine(const char* path_) : DbEngine(std::string(path_)) {}

DbEngine::DbEngine(std::string path_) {
  cm = std::make_shared<CatalogManager>(path_);
  bm = std::make_shared<BufferManager>();
}

void DbEngine::CreateDatabase(const std::string& db) {
  auto database = cm->GetDb(db);
  if (database != nullptr) {
    std::string error;
    error += "database: " + db + " ";
    error += "already exists";
    throw DbEngineException(error);
  }
  cm->CreateDatabase(db);
}

void DbEngine::DropDatabase(const std::string& db) {
  auto database = cm->GetDb(db);
  if (database == nullptr) {
    std::string error;
    error += "database: " + db + " ";
    error += "doesn't exists";
    throw DbEngineException(error);
  }
  cm->DeleteDatabase(db);
}

void DbEngine::DropTable(const std::string& tb) {}

void DbEngine::DropIndex(const std::string& index) {}

void DbEngine::Execute(RelNode& node) {
  if (!node.Open()) {
    return;
  }
}