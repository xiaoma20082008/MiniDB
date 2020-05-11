//
// Created by machunxiao on 2020/5/8.
//

#ifndef MINIDB_INTERPRETER_H
#define MINIDB_INTERPRETER_H
#include "StringUtils.h"
class DBEngine;
class Interpreter {
public:
  Interpreter();
  ~Interpreter();

public:
  void Exec(const std::string& sql);

private:
  DBEngine* engine;
};
#endif // MINIDB_INTERPRETER_H
