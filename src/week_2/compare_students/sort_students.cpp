#include "profile.h"
#include "student.h"
#include "test_runner.h"

#include <algorithm>
#include <random>
#include <string>
#include <vector>

bool Compare(const Student &first, const Student &second) {
  return first.Less(second);
}

void TestComparison() {
  Student newbie{"Ivan", "Ivanov", {{"c++", 1.0}, {"algorithms", 3.0}}, 2.0};

  Student cpp_expert{
      "Petr", "Petrov", {{"c++", 9.5}, {"algorithms", 6.0}}, 7.75};

  Student guru{"Sidor", "Sidorov", {{"c++", 10.0}, {"algorithms", 10.0}}, 10.0};
  ASSERT(Compare(guru, newbie));
  ASSERT(Compare(guru, cpp_expert));
  ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting() {
  std::vector<Student> students{
      {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
      {"Semen", "Semenov", {{"maths", 4.}}, 4.},
      {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
      {"Petr", "Petrov", {{"maths", 3.}}, 3.},
      {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}};
  std::sort(students.begin(), students.end(), Compare);
  ASSERT(std::is_sorted(
      students.begin(), students.end(),
      [](Student first, Student second) { return first.Less(second); }));
}

void BenchSort(size_t size) {
  auto students = std::vector<Student>(size);
  int id = 1;
  for (auto &s : students) {
    s.first_name = std::to_string(id);
    s.last_name = std::to_string(id);
    s.rating = static_cast<double>(id);
    id++;
  }

  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(students), std::end(students), rng);

  LOG_DURATION("BenchSort " + std::to_string(size) + " students")
  std::sort(students.begin(), students.end(), Compare);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestComparison);
  RUN_TEST(tr, TestSorting);

  BenchSort(10);
  BenchSort(100);
  BenchSort(1'000);
  BenchSort(10'000);
  BenchSort(100'000);

  return 0;
}
