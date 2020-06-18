//
// Created by machunxiao on 2020/6/5.
//
#include "common/Slice.h"

Slice::Slice(char* data_, uint32_t offset_, uint32_t length_) {
  data = data_;
  offset = offset_;
  length = length_;
}