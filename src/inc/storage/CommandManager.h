//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_COMMANDMANAGER_H
#define MINIDB_COMMANDMANAGER_H
#include <unordered_map>

#include "optimizer/RelNode.h"

class CommandManager {
 public:
  bool Exec();

 private:
};
#endif  // MINIDB_COMMANDMANAGER_H