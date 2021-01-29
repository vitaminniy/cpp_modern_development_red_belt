#include <algorithm>
#include <string>
#include <set>
#include <vector>

class Learner {
private:
  std::set<std::string> words_;

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
    return {words_.begin(), words_.end()};
  }
};
