//
// Created by machunxiao on 2020/5/18.
//

#ifndef MINIDB_TUPLE_H
#define MINIDB_TUPLE_H

class Tuple {};

class Sinker {
 public:
  void Begin(long size){};
  virtual void Accept(Tuple& tuple) = 0;
  void End(){};
};

class Source {
 public:
  Tuple* Receive();
};

class Scalar {
 public:
  template <typename T, typename C>
  T Execute(C ctx) {
    return nullptr;
  }
};

#endif  // MINIDB_TUPLE_H
