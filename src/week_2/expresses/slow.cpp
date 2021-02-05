#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class RouteManager {
public:
  void AddRoute(int start, int finish);
  int FindNearestFinish(int start, int finish) const;

private:
  std::map<int, std::set<int>> reachable_lists_;
};

void RouteManager::AddRoute(int start, int finish) {
  reachable_lists_[start].insert(finish);
  reachable_lists_[finish].insert(start);
}

int RouteManager::FindNearestFinish(int start, int finish) const {
  int result = std::abs(start - finish);
  if (reachable_lists_.count(start) == 0) {
    return result;
  }

  const std::set<int> &reachable_stations = reachable_lists_.at(start);
  if (reachable_stations.count(finish) != 0) {
    return 0;
  }

  const auto it = reachable_stations.lower_bound(finish);
  if (it != reachable_stations.cend()) {
    result = std::min(result, std::abs(finish - *it));
  }

  if (it != reachable_stations.cbegin()) {
    result = std::min(result, std::abs(finish - *std::prev(it)));
  }

  return result;
}

int main() {
  RouteManager routes;

  int query_count;
  std::cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    std::string query_type;
    std::cin >> query_type;
    int start, finish;
    std::cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      std::cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
