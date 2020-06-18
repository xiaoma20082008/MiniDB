//
// Created by machunxiao on 2020/6/18.
//
#include "exception/Exception.h"

#include <utility>

MiniDbException::MiniDbException(const char* msg) { error = std::string(msg); }
MiniDbException::MiniDbException(std::string msg) { error = std::move(msg); }
