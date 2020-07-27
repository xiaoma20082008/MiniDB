//
// Created by machunxiao on 2020/5/18.
//

#ifndef MINIDB_PHY_NODE_H
#define MINIDB_PHY_NODE_H

#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "storage/Tuple.h"

class PhyNode {
 public:
  enum PhyOpType {
    PHY_INVALID = 0,
    PHY_PROJECT = 1,
    PHY_LIMIT = 2,
    PHY_FILTER = 3,
    PHY_SEQ_SCAN = 4,
    PHY_SORT = 5,
    PHY_INSERT,
    PHY_UPDATE,
    PHY_DELETE,
  };
  PhyNode(PhyOpType type = PHY_INVALID) : opType(type) {}
  virtual ~PhyNode() = default;

  virtual bool Open() = 0;
  virtual bool Run() = 0;
  virtual bool Close() = 0;

 public:
  std::shared_ptr<PhyNode> childOp{};

 private:
  PhyOpType opType;
};

#define DEF_PHY(name) class Phy##name : public PhyNode

/// region PhyNode

DEF_PHY(Limit) {
 private:
  int64_t offset = 0;
  int64_t limit = -1;
};
DEF_PHY(SeqScan) {
 private:
  std::string table;
};
DEF_PHY(IndexScan) {
 private:
  std::string index;
};
DEF_PHY(RowIdScan) {
 private:
  std::string index;
};
DEF_PHY(Values){};
DEF_PHY(Join){};
DEF_PHY(Union){};

/// endregion PhyNode

/// region SingleNode

class SingleNode : public PhyNode {
 protected:
  std::shared_ptr<Source> source;
  std::shared_ptr<Sinker> sinker;
};

class RelProject : public SingleNode {
 public:
  bool Open() override;
  bool Run() override;
  bool Close() override;

 private:
  std::vector<std::string> columns{};
};
class RelSort : public SingleNode {
 public:
  bool Open() override;
  bool Run() override;
  bool Close() override;

 private:
};
class RelFilter : public SingleNode {
 public:
  bool Open() override;
  bool Run() override;
  bool Close() override;

 private:
  std::shared_ptr<Scalar> condition;
};

/// endregion SingleNode

#endif  // MINIDB_PHY_NODE_H
