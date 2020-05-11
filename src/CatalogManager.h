//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_CATALOGMANAGER_H
#define MINIDB_CATALOGMANAGER_H
#include "StringUtils.h"
class Index {};
class Table {};
class Database {};

class CatalogManager {
public:
  explicit CatalogManager(std::string path_) : path(std::move(path_)) {}
  explicit CatalogManager(const char* path_) : path(path_) {}

private:
  std::string path;
};

#endif // MINIDB_CATALOGMANAGER_H
