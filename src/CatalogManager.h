//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_CATALOGMANAGER_H
#define MINIDB_CATALOGMANAGER_H
#include "StringUtils.h"

#include <memory>
#include <unordered_map>
#include <vector>

class Index {};
class Table {};
class Database {};

class CatalogManager {
public:
  explicit CatalogManager(std::string path_) : path(std::move(path_)) {}
  explicit CatalogManager(const char* path_) : path(path_) {}

  std::shared_ptr<Database> GetDb(const std::string& name);

  void DeleteDatabase(const std::string& name);
  void CreateDatabase(const std::string& name);

private:
  std::string path = "";
  std::unordered_map<std::string, std::shared_ptr<Database>> databases{};
};

#endif // MINIDB_CATALOGMANAGER_H
