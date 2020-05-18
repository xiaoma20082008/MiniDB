//
// Created by machunxiao on 2020/5/18.
//

#include "PhyNode.h"
#include "Compiler.h"

bool RelFilter::Open() { return false; }
bool RelFilter::Close() { return false; }
bool RelFilter::Run() {
  Tuple* tuple;
  while ((tuple = &(source->Receive())) != nullptr) {
    bool flag = condition->Execute<bool>(tuple);
    if (flag) {
      sinker->Accept(*tuple);
    }
  }
  return true;
}
