//
// Created by machunxiao on 2020/5/18.
//

#ifndef MINIDB_PHY_VISITOR_H
#define MINIDB_PHY_VISITOR_H

#include "phy_node.h"
#include "rel_visitor.h"

template <class R, class C>
class PhyVisitor {
 public:
  R Visit(const PhyNode& x, const C& ctx);
};

class RelToPhy : public RelVisitor<PhyNode, void*> {};

#endif  // MINIDB_PHY_VISITOR_H
