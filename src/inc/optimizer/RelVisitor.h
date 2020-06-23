//
// Created by machunxiao on 2020/5/12.
//

#ifndef MINIDB_RELVISITOR_H
#define MINIDB_RELVISITOR_H
#include <string>

#include "RelNode.h"

template <class R, class C>
class RelVisitor {
 public:
  R Visit(const RelNode& x, const C& ctx);
};

class RelToStr : public RelVisitor<std::string, int> {};

#endif  // MINIDB_RELVISITOR_H
