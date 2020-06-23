//
// Created by machunxiao on 2020/5/8.
//

#ifndef MINIDB_INTERPRETER_H
#define MINIDB_INTERPRETER_H

#include <string>

#include "config/DbConfig.h"

class Interpreter {
 public:
  Interpreter(const DbConfig& cfg);
  ~Interpreter();

 public:
  void Exec(const std::string& sql);

 private:
  struct Impl;
  Impl* impl;
};
#endif  // MINIDB_INTERPRETER_H
