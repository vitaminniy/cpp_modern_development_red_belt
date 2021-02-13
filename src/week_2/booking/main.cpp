#include <test_runner.h>

#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

constexpr const std::string_view kTestCommand = "test";
constexpr const int64_t kDayNightSeconds = 60 * 60 * 24;

using seconds = int64_t;
using client_id = uint32_t;
using hotel = std::string;

struct Booking {
  seconds time;
  hotel h;
  client_id client;
  int rooms;
};

class Registry {
public:
  void Book(const Booking &booking);

  size_t Clients(const hotel &hotel) const;

  size_t Rooms(const hotel &hotel) const;

private:
  void Recalculate(int64_t time);

  std::queue<Booking> bookings_;
  std::unordered_map<hotel, int> rooms_;
  std::unordered_map<hotel, std::unordered_map<client_id, int>> clients_;
};

void TestClientsEmpty();
void TestClientsUnknownHotel();
void TestRoomsEmpty();
void TestRoomsUnknownHotel();
void TestRoomsOK();
void TestRoomsSkip();
void TestSuite();

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  if (argc > 1) {
    if (argv[1] == kTestCommand) {
      TestRunner tr;

      RUN_TEST(tr, TestClientsEmpty);
      RUN_TEST(tr, TestClientsUnknownHotel);
      RUN_TEST(tr, TestRoomsEmpty);
      RUN_TEST(tr, TestRoomsUnknownHotel);
      RUN_TEST(tr, TestRoomsOK);
      RUN_TEST(tr, TestRoomsSkip);
      RUN_TEST(tr, TestSuite);

      return 0;
    }

    std::cout << "Unknown command: " << argv[1] << std::endl;
    return 1;
  }

  Registry registry;

  int query_count;
  std::cin >> query_count;
  for (int q = 0; q < query_count; q++) {
    std::string query;
    std::cin >> query;

    if (query == "BOOK") {
      Booking b;
      std::cin >> b.time >> b.h >> b.client >> b.rooms;
      registry.Book(b);
    } else if (query == "CLIENTS") {
      hotel h;
      std::cin >> h;
      std::cout << registry.Clients(h) << '\n';
    } else if (query == "ROOMS") {
      hotel h;
      std::cin >> h;
      std::cout << registry.Rooms(h) << '\n';
    }
  }

  return 0;
}

void Registry::Book(const Booking &booking) {
  bookings_.push(booking);
  rooms_[booking.h] += booking.rooms;
  clients_[booking.h][booking.client]++;

  Recalculate(booking.time);
}

void Registry::Recalculate(int64_t time) {
  while (!bookings_.empty() &&
         bookings_.front().time + kDayNightSeconds <= time) {
    const auto booking = bookings_.front();

    rooms_[booking.h] -= booking.rooms;
    clients_[booking.h][booking.client]--;
    if (clients_[booking.h][booking.client] <= 0) {
      clients_[booking.h].erase(booking.client);
    }

    bookings_.pop();
  }
}

size_t Registry::Rooms(const hotel &h) const {
  const auto it = rooms_.find(h);
  if (it == rooms_.end()) {
    return 0;
  }
  const auto result = it->second;
  return result < 0 ? 0 : static_cast<size_t>(result);
}

size_t Registry::Clients(const hotel &h) const {
  const auto it = clients_.find(h);
  if (it == clients_.end()) {
    return 0;
  }
  return it->second.size();
}

void TestClientsEmpty() {
  Registry registry;
  ASSERT_EQUAL(registry.Clients("test"), 0u);
}

void TestClientsUnknownHotel() {
  Registry registry;
  registry.Book({10, "yandex", 1, 1});
  ASSERT_EQUAL(registry.Clients("google"), 0u);
}

void TestRoomsEmpty() {
  Registry registry;
  ASSERT_EQUAL(registry.Rooms("test"), 0u);
}

void TestRoomsUnknownHotel() {
  Registry registry;
  registry.Book({10, "yandex", 1, 1});
  ASSERT_EQUAL(registry.Rooms("google"), 0u);
}

void TestRoomsOK() {
  Registry registry;

  registry.Book({10, "A", 1, 1});
  registry.Book({11, "A", 1, 2});
  registry.Book({12, "A", 1, 3});

  ASSERT_EQUAL(registry.Rooms("A"), 1u + 2u + 3u);
}

void TestRoomsSkip() {
  Registry registry;

  registry.Book({10, "A", 1, 1000});
  ASSERT_EQUAL(registry.Rooms("A"), 1000u);

  registry.Book({10 + kDayNightSeconds, "A", 1, 1});
  ASSERT_EQUAL(registry.Rooms("A"), 1u);
}

void TestSuite() {
  Registry registry;

  registry.Book({10, "Four Seasons", 1, 2});
  registry.Book({10, "Mariott", 1, 1});

  ASSERT_EQUAL(registry.Clients("Four Seasons"), 1u);
  ASSERT_EQUAL(registry.Clients("Mariott"), 1u);

  registry.Book({86409, "Four Seasons", 2, 1});

  ASSERT_EQUAL(registry.Clients("Four Seasons"), 2u);
  ASSERT_EQUAL(registry.Rooms("Four Seasons"), 3u);
  ASSERT_EQUAL(registry.Clients("Mariott"), 1u);

  registry.Book({86410, "Mariott", 2, 10});

  ASSERT_EQUAL(registry.Rooms("Four Seasons"), 1u);
  ASSERT_EQUAL(registry.Rooms("Mariott"), 10u);
}
