//
// Created by machunxiao on 2020/6/5.
//

#ifndef MINIDB_STORAGE_MANAGER_H
#define MINIDB_STORAGE_MANAGER_H

class StorageManager {
 public:
  virtual ~StorageManager() = 0;

 public:
  virtual void Start() = 0;
  virtual void Close() = 0;

  virtual void Put() = 0;
  virtual void Del() = 0;

  // region ddl

  // endregion ddl

  // region trx

  virtual void BeginTrx() = 0;
  virtual void PrepareTrx() = 0;
  virtual void CommitTrx() = 0;
  virtual void RollbackTrx() = 0;

  // endregion trx
};

#endif  // MINIDB_STORAGE_MANAGER_H
