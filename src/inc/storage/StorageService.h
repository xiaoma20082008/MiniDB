//
// Created by machunxiao on 2020/6/5.
//

#ifndef MINIDB_STORAGESERVICE_H
#define MINIDB_STORAGESERVICE_H

#include <cstdint>

enum class LockMode {};
class ReadOptions {};
class Transaction {};
class TxnCtx {};

template <typename K, typename V> class EntityIndex {
public:
  virtual uint64_t Count() = 0;
  virtual uint64_t Count(uint64_t mem_limit) = 0;

  virtual V Get(const K& key) = 0;
  virtual V Get(const Transaction& txn, const K& key,
                const LockMode& lock_mode) = 0;
  virtual V Get(const Transaction& txn, const K& key, const LockMode& lock_mode,
                const ReadOptions& options) = 0;

  virtual bool Contains(const K& key) = 0;
  virtual bool Contains(const Transaction& txn, const K& key,
                        const LockMode& lock_mode) = 0;

  virtual bool Delete(const K& key) = 0;
  virtual bool Delete(const Transaction& txn, const K& key) = 0;

  virtual void Keys() = 0;
  virtual void Keys(const Transaction& txn) = 0;
};

template <typename PK, typename E> class SubIndex : public EntityIndex<PK, E> {
public:
};

template <typename K, typename E>
class BasicIndex : public EntityIndex<K, E> {};

class StorageService {
public:
  virtual ~StorageService() = 0;

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

#endif // MINIDB_STORAGESERVICE_H
