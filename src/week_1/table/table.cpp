#include "test_runner.h"

#include <array>
#include <cstddef>
#include <utility>
#include <vector>

template <typename T> class Table {
public:
  Table(size_t rows, size_t cols);

  std::pair<size_t, size_t> Size() const;

  void Resize(size_t rows, size_t cols);

  std::vector<T> &operator[](size_t index);
  const std::vector<T> &operator[](size_t index) const;

private:
  std::vector<std::vector<T>> table_;
};

template <typename T> Table<T>::Table(size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    cols = 0;
    rows = 0;
  }

  Resize(rows, cols);
}

template <typename T> std::pair<size_t, size_t> Table<T>::Size() const {
  auto cols = 0;
  if (table_.size() > 0) {
    cols = table_[0].size();
  }

  return std::make_pair(table_.size(), cols);
}

template <typename T> void Table<T>::Resize(size_t rows, size_t cols) {
  table_.resize(rows);
  for (auto &row : table_) {
    row.resize(cols);
  }
}

template <typename T> std::vector<T> &Table<T>::operator[](size_t index) {
  return table_[index];
}

template <typename T>
const std::vector<T> &Table<T>::operator[](size_t index) const {
  return table_[index];
}

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
