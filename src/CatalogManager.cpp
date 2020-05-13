//
// Created by machunxiao on 2020/5/9.
//
#include "CatalogManager.h"

std::shared_ptr<Database> CatalogManager::GetDb(const std::string& name) {
  auto db = databases[name];
  return db;
}

void CatalogManager::DeleteDatabase(const std::string& name) {}

void CatalogManager::CreateDatabase(const std::string& name) {}