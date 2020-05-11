//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_RELNODE_H
#define MINIDB_RELNODE_H

#include <cstdint>
#include <string>
#include <vector>

/**
 * <pre>
 * 1. select
 * select a,b,c from d where c = ? order by e desc limit 5,10
 * ==>>
 *  Project(a,b,c)
 *      Limit(offset=5,limit=10)
 *          Sort(e desc)
 *              Filter(c=?)
 *                  TableScan(table = c)
 *
 * 2. update
 * update t set a = ?,b = ? where c = ?
 * ==>>
 *  Update(table=t,col=[a,b])
 *      Project(a,b)
 *          Filter(c=?)
 *              TableScan(table = c)
 *
 * 3. delete
 * delete from t where a = ?
 * ==>>
 *  Delete(table=t)
 *      Filter(a=?)
 *          TableScan(table = t)
 * 4. insert
 * insert into t(a,b,c,d) values(?,?,?,?)
 * ==>>
 *  Insert(table)
 *      Values(?,?,?,?)
 * </pre>
 */

class RelNode {
public:
  virtual ~RelNode() = 0;
  enum PhyOpType {
    PHY_INVALID = 0,
    PHY_PROJECT = 1,
    PHY_LIMIT = 2,
    PHY_FILTER = 3,
    PHY_TABLE_SCAN = 4,
    PHY_SORT = 5,
    PHY_INSERT,
    PHY_UPDATE,
    PHY_DELETE,
  };
  bool virtual Open() = 0;
  bool virtual GetNext() = 0;
  bool virtual HasNext() = 0;
  bool virtual Close() = 0;

protected:
  RelNode* childOp{};

private:
  PhyOpType opType = PHY_INVALID;
};

class RelProject : public RelNode {
private:
  std::vector<std::string> columns{};
};
class RelLimit : public RelNode {
private:
  int64_t limit;
  int64_t offset;
};
class RelFilter : public RelNode {
private:
  void* condition{};
};
class RelTableScan : public RelNode {
private:
  std::string table;
};
class RelIndexScan : public RelNode {
private:
  std::string index;
};
class RelClusterScan : public RelNode {
private:
  std::string index;
};
class RelSort : public RelNode {};
class RelValues : public RelNode {};

class RelInsert : public RelNode {};
class RelDelete : public RelNode {};
class RelUpdate : public RelNode {};

#endif // MINIDB_RELNODE_H
