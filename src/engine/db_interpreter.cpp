//
// Created by machunxiao on 2020/5/8.
//
#include "engine/db_interpreter.h"

#include <memory>

#include "engine/db_engine.h"
#include "optimizer/Optimizer.h"
#include "sql/SqlStmtParser.h"

struct Interpreter::Impl {
  explicit Impl(const char* path) { engine = std::make_unique<DbEngine>(path); }
  explicit Impl(const std::string& path) {
    engine = std::make_unique<DbEngine>(path);
  }
  ~Impl() = default;
  std::unique_ptr<DbEngine> engine;
};

Interpreter::Interpreter(const DbConfig& cfg) { impl = new Impl(cfg.datadir); }
Interpreter::~Interpreter() { delete impl; }

/**
 * 1. sql -> ast(SqlNode:nothing)
 * 2. ast -> logical(RelNode:with annotation and attribute)
 * 3. logical -> physical(PhyNode:physical)
 *
 * @param sql statement of user's input
 */
void Interpreter::Exec(const std::string& sql) {
  SqlStmtParser parser(sql);
  SqlCall* call = parser.ParseCall();
  switch (call->type) {
    case SqlKind::CREATE_DATABASE: {
      impl->engine->CreateDatabase(((SqlCreateDatabase*)call)->database);
      break;
    }
    case SqlKind::CREATE_TABLE: {
      break;
    }
    case SqlKind::CREATE_INDEX: {
      break;
    }
    case SqlKind::DROP_DATABASE: {
      impl->engine->DropDatabase(((SqlDropDatabase*)call)->database);
      break;
    }
    case SqlKind::DROP_TABLE: {
      auto dropTable = ((SqlDropTable*)call);
      impl->engine->DropTable("", dropTable->table);
      break;
    }
    case SqlKind::DROP_INDEX: {
      auto dropIndex = ((SqlDropIndex*)call);
      impl->engine->DropIndex("", dropIndex->index);
      break;
    }
    default: {
      Optimizer optimizer;
      RelNode* op = optimizer.Optimize(*call);
      impl->engine->Execute(op);
      delete op;
    }
  }
  delete call;
}
