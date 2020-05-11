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
  [[nodiscard]] const char* what() const noexcept override = 0;
};

class ParserException : public MiniDbException {
public:
  explicit ParserException(std::string msg_) : msg(std::move(msg_)) {}
  [[nodiscard]] const char* what() const noexcept override {
    return msg.c_str();
  }

private:
  const std::string msg;
};

class LexerException : public MiniDbException {
public:
  explicit LexerException(const std::string& msg_) : msg(msg_) {}
  [[nodiscard]] const char* what() const noexcept override {
    return msg.c_str();
  }

private:
  const std::string msg;
};

#endif // MINIDB_EXCEPTION_H
