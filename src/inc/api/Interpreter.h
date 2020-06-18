//
// Created by machunxiao on 2020/5/8.
//

#ifndef MINIDB_INTERPRETER_H
#define MINIDB_INTERPRETER_H
#include "common/StringUtils.h"
#include <memory>

class DbEngine;

class Interpreter {
public:
  Interpreter();
  ~Interpreter() = default;

public:
  void Exec(const std::string& sql);

private:
  std::shared_ptr<DbEngine> engine;
};
#endif // MINIDB_INTERPRETER_H
