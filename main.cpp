#include "Exception.h"
#include "Interpreter.h"
#include "StringUtils.h"
#include <csignal>
#include <iostream>

using namespace std;

void SignalHandler(int sig) {
  if ((sig == SIGINT || sig == SIGTERM)) {
    exit(sig);
  }
}

auto RegisterSignalHandler() {
  struct sigaction sa;
  sa.sa_handler = &SignalHandler;
  sa.sa_flags = SA_RESTART;

  sigfillset(&sa.sa_mask);

  // Terminal interrupt signal (usually from ^c, portable number is 2)
  if (sigaction(SIGINT, &sa, nullptr) == -1) {
    return errno;
  }

  // Terminate signal from administrator (portable number is 15)
  if (sigaction(SIGTERM, &sa, nullptr) == -1) {
    return errno;
  }

  return 0;
}

string ReadSQL() {
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

class MiniDb {
public:
  void Run() {
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
        // break;
      }
    } while (true);
  }

  class Builder {
  public:
    std::unique_ptr<MiniDb> Build() { return std::make_unique<MiniDb>(); }
  };
};

int main(int argc, char* argv[]) {
  const auto r = RegisterSignalHandler();
  if (r != 0) {
    return r;
  }
  auto db = MiniDb::Builder().Build();
  db->Run();
  return 0;
}
