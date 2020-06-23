//
// Created by machunxiao on 2020/5/8.
//

#ifndef MINIDB_DBENGINE_H
#define MINIDB_DBENGINE_H

#include <string>
class RelNode;

class DbEngine {
 public:
  explicit DbEngine(std::string path_);
  explicit DbEngine(const char* path_);

  ~DbEngine();

  /// region ddl

  void CreateDatabase(const std::string& db);
  void DropDatabase(const std::string& db);
  void DropTable(const std::string& db, const std::string& tb);
  void DropIndex(const std::string& db, const std::string& index);

  /// endregion ddl

  /// region dml

  void Execute(RelNode* node);

  /// endregion dml

 private:
  // PImpl
  struct Impl;
  Impl* impl;
};
#endif  // MINIDB_DBENGINE_H
