//
// Created by machunxiao on 2020/6/4.
//

#include "storage/page/Page.h"

FilHeader* FilHeader::FromSlice(Slice* slice) {
  //  auto fh = new FilHeader();
  //  fh->space_id = slice->ReadUnsignedInt();
  //  fh->offset = slice->ReadUnsignedInt();
  //  fh->prev = slice->ReadUnsignedInt();
  //  fh->next = slice->ReadUnsignedInt();
  //  fh->lsn = slice->ReadUnsignedInt();
  //  fh->type = slice->ReadUnsignedShort();
  //  fh->flush_lsn = slice->ReadUnsignedLong();
  //  fh->checksum = slice->ReadUnsignedInt();
  return nullptr;
}

FilTrailer* FilTrailer::FromSlice(Slice* slice) {
  //  auto ft = new FilTrailer();
  //  ft->checksum = slice->ReadUnsignedInt();
  //  ft->low32_lsn = slice->ReadUnsignedInt();
  return nullptr;
}

IndexHeader* IndexHeader::FromSlice(Slice* slice) {
  //  auto ih = new IndexHeader();
  //  ih->n_dir_slots = slice->ReadUnsignedShort();
  //  ih->heap_top = slice->ReadUnsignedShort();
  //  ih->n_heap_format = slice->ReadUnsignedShort();
  //  ih->garbage_offset = slice->ReadUnsignedShort();
  //  ih->garbage_size = slice->ReadUnsignedShort();
  //  ih->last_insert_offset = slice->ReadUnsignedShort();
  //  ih->direction = slice->ReadUnsignedShort();
  //  ih->n_direction = slice->ReadUnsignedShort();
  //  ih->n_recs = slice->ReadUnsignedShort();
  //  ih->max_trx_id = slice->ReadUnsignedLong();
  //  ih->level = slice->ReadUnsignedShort();
  //  ih->index_id = slice->ReadUnsignedLong();
  return nullptr;
}

Page::Page(uint32_t page_no_, Slice* slice_) {
  page_no = page_no_;
  slice = slice_;
  fil_header = FilHeader::FromSlice(slice);
  fil_trailer = FilTrailer::FromSlice(slice);
}