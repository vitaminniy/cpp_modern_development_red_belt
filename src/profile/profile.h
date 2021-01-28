#pragma once

#include <chrono>
#include <string>

class LogDuration {
public:
  explicit LogDuration(const std::string &message = "");
  ~LogDuration();

private:
  const std::chrono::steady_clock::time_point start;
  const std::string message_;
};

#define UNIQ_ID_IMPL(lineno) __log_duration__##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message)                                                  \
  const auto UNIQ_ID(__LINE__) = LogDuration(message);
