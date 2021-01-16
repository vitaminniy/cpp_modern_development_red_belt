#include "test_runner.h"

#include <sstream>
#include <string>

class Logger {
public:
  explicit Logger(std::ostream &output_stream) : os(output_stream) {}
  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file = value; }
  bool LogLine() { return log_line; }
  bool LogFile() { return log_file; }
  void Log(const std::string &message) { os << message; }

private:
  std::ostream &os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message)                                                   \
  {                                                                            \
    std::ostringstream ss;                                                     \
    if (logger.LogFile()) {                                                    \
      ss << __FILE__;                                                          \
      if (logger.LogLine()) {                                                  \
        ss << ':' << __LINE__;                                                 \
      }                                                                        \
      ss << ' ';                                                               \
    } else if (logger.LogLine()) {                                             \
      ss << "Line " << __LINE__ << ' ';                                        \
    }                                                                          \
    ss << message << '\n';                                                     \
    logger.Log(ss.str());                                                      \
  }

void TestLog() {
#line 1 "logger.cpp"

  std::ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  std::string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
