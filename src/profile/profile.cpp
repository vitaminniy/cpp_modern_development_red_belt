#include "profile.h"

#include <iostream>

LogDuration::LogDuration(const std::string &message)
    : start(std::chrono::steady_clock::now()), message_(message + ": ") {}

LogDuration::~LogDuration() {
  const auto duration = std::chrono::steady_clock::now() - start;
  const auto ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  std::cerr << message_ << ms << " ms\n";
}
