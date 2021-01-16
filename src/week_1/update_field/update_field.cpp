#include "airline_ticket.h"
#include "test_runner.h"

#include <istream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>

#define UPDATE_FIELD(ticket, field, values)                                    \
  {                                                                            \
    auto it = values.find(#field);                                             \
    if (it != values.end()) {                                                  \
      std::stringstream ss(it->second);                                        \
      ss >> ticket.field;                                                      \
    }                                                                          \
  }

std::ostream &operator<<(std::ostream &dst, const Date &date) {
  dst << date.year << '-' << date.month << '-' << date.day;
  return dst;
}

std::istream &operator>>(std::istream &src, Date &date) {
  src >> date.year;
  src.ignore(1);

  src >> date.month;
  src.ignore(1);

  src >> date.day;

  return src;
}

bool operator==(const Date &lhs, const Date &rhs) {
  return std::tie(lhs.year, lhs.month, lhs.day) ==
         std::tie(rhs.year, rhs.month, rhs.day);
}

std::ostream &operator<<(std::ostream &dst, const Time &time) {
  dst << time.minutes << ':' << time.minutes;
  return dst;
}

std::istream &operator>>(std::istream &src, Time &time) {
  src >> time.hours;
  src.ignore(1);
  src >> time.minutes;

  return src;
}

bool operator==(const Time &lhs, const Time &rhs) {
  return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const std::map<std::string, std::string> updates1 = {
      {"departure_date", "2018-2-28"},
      {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const std::map<std::string, std::string> updates2 = {
      {"price", "12550"},
      {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
