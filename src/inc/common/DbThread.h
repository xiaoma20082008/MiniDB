//
// Created by machunxiao on 2020/6/24.
//

#ifndef MINIDB_DBTHREAD_H
#define MINIDB_DBTHREAD_H

class DbThread {
 public:
  enum DbThreadState : short {
    NEW = 0,
    RUNNABLE,
    BLOCKED,
    WAITING,
    TIMED_WAITING,
    TERMINATED
  };

 private:
  DbThreadState state;
};

#endif  // MINIDB_DBTHREAD_H
