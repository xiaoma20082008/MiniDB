//
// Created by machunxiao on 2020/5/8.
//
#include "DBEngine.h"
#include "Exception.h"

void DBEngine::CreateDatabase(const std::string& db) {
  auto database = cm->GetDb(db);
  if (database != nullptr) {
    std::string error;
    error += "database: " + db + " ";
    error += "already exists";
    throw DbEngineException(error);
  }
  cm->CreateDatabase(db);
}
void DBEngine::DropDatabase(const std::string& db) {
  auto database = cm->GetDb(db);
  if (database == nullptr) {
    std::string error;
    error += "database: " + db + " ";
    error += "doesn't exists";
    throw DbEngineException(error);
  }
  cm->DeleteDatabase(db);
}
void DBEngine::DropTable(const std::string& tb) {}
void DBEngine::DropIndex(const std::string& index) {}
void DBEngine::Execute(RelNode& node) {
  if (!node.Open()) {
    return;
  }
}