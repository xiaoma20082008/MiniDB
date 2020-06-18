//
// Created by machunxiao on 2020/4/30.
//

#ifndef MINIDB_STRINGUTILS_H
#define MINIDB_STRINGUTILS_H
#include <string>

class StringUtils {
public:
  StringUtils() = delete;
  StringUtils(const StringUtils& rhs) = delete;
  StringUtils& operator=(const StringUtils& rhs) = delete;
  ~StringUtils() = delete;

public:
  static std::string& ltrim(std::string& str,
                            const std::string& chars = "\t\n\v\f\r ");

  static std::string& rtrim(std::string& str,
                            const std::string& chars = "\t\n\v\f\r ");

  static std::string& trim(std::string& str,
                           const std::string& chars = "\t\n\v\f\r ");
};

#endif // MINIDB_STRINGUTILS_H
