//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_OPTIMIZER_H
#define MINIDB_OPTIMIZER_H
#include "RelNode.h"
#include "sql/SqlCall.h"
class Optimizer {
 public:
  RelNode* Optimize(const SqlCall& call);
};
#endif  // MINIDB_OPTIMIZER_H
