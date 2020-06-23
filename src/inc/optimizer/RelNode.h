//
// Created by machunxiao on 2020/5/9.
//

#ifndef MINIDB_RELNODE_H
#define MINIDB_RELNODE_H
/**
 * A RelNode is a relational expression in a planner.
 *
 * Relational expressions process data, so their names are typically verbs:
 * Sort, Join, Project, Filter, Scan, Sample.
 */
class RelNode {
 public:
  virtual int GetId() = 0;
};

#endif  // MINIDB_RELNODE_H
