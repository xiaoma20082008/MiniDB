//
// Created by machunxiao on 2020/6/5.
//

#ifndef MINIDB_SLICE_H
#define MINIDB_SLICE_H

#include <cstdint>

class Slice {
 public:
  Slice(char* data_, uint32_t offset_, uint32_t length_);
  int8_t ReadByte();
  uint8_t ReadUnsignedByte();
  int16_t ReadShort();
  uint16_t ReadUnsignedShort();
  int32_t ReadInt();
  uint32_t ReadUnsignedInt();
  int64_t ReadLong();
  uint64_t ReadUnsignedLong();

  void WriteByte(int8_t val);
  void WriteUnsignedByte(uint8_t val);

 private:
  uint32_t offset{0};
  uint32_t length{0};
  char* data{nullptr};
};

#endif  // MINIDB_SLICE_H
