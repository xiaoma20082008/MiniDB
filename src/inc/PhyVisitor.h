//
// Created by machunxiao on 2020/5/18.
//

#ifndef MINIDB_PHYVISITOR_H
#define MINIDB_PHYVISITOR_H

#include "PhyNode.h"
#include "RelVisitor.h"

template <class R, class C> class PhyVisitor {
public:
  R Visit(const PhyNode& x, const C& ctx);
};

class RelToPhy : public RelVisitor<PhyNode, void*> {};

#endif // MINIDB_PHYVISITOR_H
