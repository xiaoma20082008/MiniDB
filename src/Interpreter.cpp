//
// Created by machunxiao on 2020/5/8.
//
#include "Interpreter.h"
#include "AstOptimizer.h"
#include "DBEngine.h"
#include "SqlStmtParser.h"

Interpreter::Interpreter() {
  char* home = getenv("HOME");
  std::string dbPath = std::string(home) + "/MiniDB";
  engine = new DBEngine(dbPath);
}

Interpreter::~Interpreter() { delete engine; }

/**
 * 1. sql -> ast
 * 2. ast -> logical
 * 3. logical -> phy
 * @param sql statement of user's input
 */
void Interpreter::Exec(const std::string& sql) {
  SqlStmtParser parser(sql);
  SqlCall* call = parser.ParseCall();
  switch (call->type) {
  case SqlKind::CREATE_DATABASE: {
    engine->CreateDatabase(((SqlCreateDatabase*)call)->database);
    break;
  }
  case SqlKind::CREATE_TABLE: {
    break;
  }
  case SqlKind::CREATE_INDEX: {
    break;
  }
  case SqlKind::DROP_DATABASE: {
    engine->DropDatabase(((SqlDropDatabase*)call)->database);
    break;
  }
  case SqlKind::DROP_TABLE: {
    engine->DropTable(((SqlDropTable*)call)->table);
    break;
  }
  case SqlKind::DROP_INDEX: {
    engine->DropIndex(((SqlDropIndex*)call)->index);
    break;
  }
  default: {
    Optimizer optimizer;
    RelNode* op = optimizer.Optimize(*call);
    engine->Execute(*op);
    delete op;
  }
  }
  delete call;
}
