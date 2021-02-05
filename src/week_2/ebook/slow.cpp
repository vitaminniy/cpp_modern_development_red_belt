#include <array>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

class ReadingManager {
public:
  ReadingManager() { user_pages.reserve(MAX_USER_COUNT_); }

  void Read(int user_id, int page_count) {
    if (user_pages.count(user_id) != 0) {
      page_users_[user_pages.at(user_id)]--;
    }

    user_pages[user_id] = page_count;
    page_users_[page_count]++;
  }

  double Cheer(int user_id) const {
    if (user_pages.count(user_id) == 0) {
      return 0;
    }

    if (user_pages.size() == 1) {
      return 1;
    }

    return CalculateRating(user_pages.at(user_id));
  }

private:
  constexpr static const size_t MAX_USER_COUNT_ = 100'000;
  constexpr static const size_t MAX_PAGE_COUNT_ = 1000;

  double CalculateRating(size_t page) const {
    int users = 0;
    for (size_t i = 0; i < page; i++) {
      users += page_users_[i];
    }
    return (1.0 * users) / (user_pages.size() - 1);
  }

  std::array<int, MAX_PAGE_COUNT_ + 1> page_users_{};
  std::unordered_map<int, size_t> user_pages;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  std::cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    std::string query_type;
    std::cin >> query_type;
    int user_id;
    std::cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      std::cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
