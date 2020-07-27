//
// Created by machunxiao on 2020/5/9.
//
#include "storage/catalog_manager.h"

#include "exception/Exception.h"

std::shared_ptr<Database> CatalogManager::GetDb(const std::string& name) {
  auto got = databases.find(name);
  if (got == databases.end()) {
    return nullptr;
  } else {
    return got->second;
  }
}

void CatalogManager::DeleteDatabase(const std::string& name) {
  databases.erase(name);
}

void CatalogManager::CreateDatabase(const std::string& name) {
  databases.insert(std::make_pair(name, std::make_shared<Database>()));
}