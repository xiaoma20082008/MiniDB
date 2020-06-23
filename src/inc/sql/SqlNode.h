//
// Created by machunxiao on 2020/4/30.
//

#ifndef MINIDB_SQLNODE_H
#define MINIDB_SQLNODE_H

struct SqlNode {};

template <typename T>
struct Visitable {
  //  void Accept(AstVisitor2* visitor) { visitor->Visit(static_cast<T*>(this));
  //  }
};
#endif  // MINIDB_SQLNODE_H
