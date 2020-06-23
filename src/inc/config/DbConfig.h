//
// Created by machunxiao on 2020/6/23.
//

#ifndef MINIDB_DBCONFIG_H
#define MINIDB_DBCONFIG_H

#include <cstdint>

struct DbConfig {
 public:
  DbConfig& SetBasedir(const char*& basedir_) {
    basedir = basedir_;
    return *this;
  }

  DbConfig& SetDatadir(const char*& datadir_) {
    datadir = datadir_;
    return *this;
  }

  DbConfig& SetServerId(const uint64_t& server_id_) {
    server_id = server_id_;
    return *this;
  }

  const char* basedir;
  const char* datadir;
  uint64_t server_id;
};

#endif  // MINIDB_DBCONFIG_H
