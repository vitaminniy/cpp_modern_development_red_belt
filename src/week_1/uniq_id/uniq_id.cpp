#include <string>
#include <vector>

#define UNIQ_VAR(number) __variable__##number
#define NAME(number) UNIQ_VAR(number)
#define UNIQ_ID NAME(__LINE__)

int main() {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

  int UNIQ_ID = 0;
  std::string UNIQ_ID = "hello";
  std::vector<std::string> UNIQ_ID = {"hello", "world"};
  std::vector<int> UNIQ_ID = {1, 2, 3, 4};

#pragma GCC diagnostic pop
}
