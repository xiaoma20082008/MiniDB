//
// Created by machunxiao on 2020/5/18.
//

#ifndef MINIDB_COMPILER_H
#define MINIDB_COMPILER_H

#include "RelNode.h"
#include "Tuple.h"
#include <memory>

class Compiler {
public:
  std::shared_ptr<Source> CreateSource(RelNode* rel, int original = 0);
  std::shared_ptr<Sinker> CreateSinker(RelNode* rel);
};

#endif // MINIDB_COMPILER_H
