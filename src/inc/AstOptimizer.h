//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_ASTOPTIMIZER_H
#define MINIDB_ASTOPTIMIZER_H
#include "RelNode.h"
#include "SqlCall.h"
class Optimizer {
public:
  RelNode* Optimize(const SqlCall& call);
};
#endif // MINIDB_ASTOPTIMIZER_H
