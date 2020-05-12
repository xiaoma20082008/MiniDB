#include "Exception.h"
#include "Interpreter.h"
#include "StringUtils.h"
#include <iostream>

using namespace std;

static void HandleInterrupt(int sig) { exit(0); }

static string ReadSQL() {
  string sql;
  char ch = '0';
  cout << "MiniDB> ";
  cin >> std::noskipws;
  while ((!cin.eof()) && (cin >> ch)) {
    if (ch == ';') {
      break;
    }
    sql += ch;
  }
  if (cin.eof()) {
    sql = "exit";
  }
  return StringUtils::trim(sql);
}

int main(int argc, char* argv[]) {
  signal(SIGINT, HandleInterrupt);
  Interpreter interpreter;
  do {
    std::string sql = ReadSQL();
    if (sql == "exit") {
      cout << "bye bye!" << endl;
      break;
    } else if (sql.empty()) {
      continue;
    }
    try {
      interpreter.Exec(sql);
    } catch (const MiniDbException& e) {
      std::cout << e.what() << std::endl;
      break;
    }
  } while (true);
  return 0;
}
