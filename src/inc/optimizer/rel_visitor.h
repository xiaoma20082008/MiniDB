//
// Created by machunxiao on 2020/5/12.
//

#ifndef MINIDB_REL_VISITOR_H
#define MINIDB_REL_VISITOR_H
#include <string>

#include "rel_node.h"

template <class R, class C>
class RelVisitor {
 public:
  R Visit(const RelNode& x, const C& ctx);
};

class RelToStr : public RelVisitor<std::string, int> {};

#endif  // MINIDB_REL_VISITOR_H
