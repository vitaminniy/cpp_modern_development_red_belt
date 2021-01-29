#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

class Learner {
private:
  std::unordered_set<std::string> words_;

public:
  int Learn(const std::vector<std::string> &words) {
    int newWords = 0;
    for (const auto &word : words) {
      if (const auto i = words_.insert(word); i.second) {
        ++newWords;
      }
    }
    return newWords;
  }

  std::vector<std::string> KnownWords() {
    auto result = std::vector(words_.cbegin(), words_.cend());
    std::sort(result.begin(), result.end());
    return result;
  }
};
