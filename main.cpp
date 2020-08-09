#include <csignal>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "common/StringUtils.h"
#include "engine/db_interpreter.h"
#include "exception/Exception.h"

using namespace std;

void SignalHandler(int sig) {
  if ((sig == SIGINT || sig == SIGTERM)) {
    exit(sig);
  }
}

int RegisterSignalHandler() {
  struct sigaction sa {};
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
  MiniDb() = default;
  ~MiniDb() = default;

  void Run() const {
    do {
      std::string sql = ReadSQL();
      if (sql == "exit") {
        cout << "bye bye!" << endl;
        break;
      } else if (sql.empty()) {
        continue;
      }
      try {
        interpreter->Exec(sql);
      } catch (const MiniDbException& e) {
        std::cout << e.what() << std::endl;
        // break;
      }
    } while (true);
  }

  std::shared_ptr<Interpreter> interpreter;
};

int main(int argc, char* argv[]) {
  const auto r = RegisterSignalHandler();
  if (r != 0) {
    return r;
  }
  const char* basedir = "";
  const char* datadir = std::getenv("HOME");
  if (datadir == nullptr) {
    cout << "got an error datadir" << endl;
    exit(0);
    return 0;
  }
  uint32_t server_id = 1;
  DbConfig cfg{};
  cfg.SetBasedir(basedir).SetDatadir(datadir).SetServerId(server_id);
  auto db = std::make_unique<MiniDb>();
  db->interpreter = std::make_shared<Interpreter>(cfg);
  db->Run();
  return 0;
}
