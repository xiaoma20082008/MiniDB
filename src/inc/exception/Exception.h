//
// Created by machunxiao on 2020/4/30.
//

#ifndef MINIDB_EXCEPTION_H
#define MINIDB_EXCEPTION_H
#include <exception>
#include <string>
#include <utility>

class MiniDbException : public std::exception {
 public:
  explicit MiniDbException(std::string msg);
  explicit MiniDbException(const char* msg);
  ~MiniDbException() override = default;

 public:
  [[nodiscard]] const char* what() const noexcept override {
    return error.c_str();
  }

 private:
  std::string error;
};

class ParserException : public MiniDbException {
 public:
  explicit ParserException(std::string msg_)
      : MiniDbException(std::move(msg_)) {}
};

class LexerException : public MiniDbException {
 public:
  explicit LexerException(std::string msg_)
      : MiniDbException(std::move(msg_)) {}
};

class DbEngineException : public MiniDbException {
 public:
  explicit DbEngineException(std::string msg_)
      : MiniDbException(std::move(msg_)) {}
};

#endif  // MINIDB_EXCEPTION_H
