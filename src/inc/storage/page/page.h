//
// Created by machunxiao on 2020/7/27.
//

#ifndef MINIDB_PAGE_HPP
#define MINIDB_PAGE_HPP

#include "common/Slice.h"

enum class PageType {
  ALLOCATED = 0,
  SYSTEM = 1,
  SYS_TRX = 2,
  INDEX = 3,
  UNDO = 4,
};

struct FilHeader {
  uint32_t space_id : 4;
  uint32_t offset : 4;
  uint32_t prev : 4;
  uint32_t next : 4;
  uint64_t lsn : 4;
  uint16_t type : 2;
  uint64_t flush_lsn : 8;
  uint32_t checksum : 4;

  static FilHeader* FromSlice(Slice* slice);
};
struct FilTrailer {
  uint32_t checksum : 4;
  uint32_t low32_lsn : 4;

  static FilTrailer* FromSlice(Slice* slice);
};

struct Page {
  Page(uint32_t page_no_, Slice* slice_);
  FilHeader* fil_header{};
  FilTrailer* fil_trailer{};
  uint32_t page_no{0};
  Slice* slice{};
};

class BasePage {
 public:
  explicit BasePage(Page* page_) : page(page_), slice(page_->slice) {}

 protected:
  Page* page;
  Slice* slice;
};

struct IndexHeader {
  uint16_t n_dir_slots : 2;
  uint16_t heap_top : 2;
  uint16_t n_heap_format : 2;
  uint16_t garbage_offset : 2;
  uint16_t garbage_size : 2;
  uint16_t last_insert_offset : 2;
  uint16_t direction : 2;
  uint16_t n_direction : 2;
  uint16_t n_recs : 2;
  uint64_t max_trx_id : 2;
  uint16_t level : 2;
  uint64_t index_id : 2;

  static IndexHeader* FromSlice(Slice* slice);
};

class SystemPage : public BasePage {
 public:
  explicit SystemPage(Page* page_) : BasePage(page_) {}
};
class IndexPage : public BasePage {
 public:
  explicit IndexPage(Page* page_) : BasePage(page_) {}

 private:
  IndexHeader* index_header{};
};
class AllocatedPage : public BasePage {
 public:
  explicit AllocatedPage(Page* page_) : BasePage(page_) {}
};

#endif  // MINIDB_PAGE_HPP