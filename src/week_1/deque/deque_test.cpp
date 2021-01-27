#include "deque.h"
#include "test_runner.h"
#include <stdexcept>

void TestIndexOperator() {
  auto deque = Deque<int>();

  deque.PushFront(1);
  ASSERT_EQUAL(1, deque[0]);
  deque[0]--;
  ASSERT_EQUAL(0, deque[0]);

  deque.PushBack(2);
  ASSERT_EQUAL(2, deque[1]);
  deque[1]--;
  ASSERT_EQUAL(1, deque[1]);
}

void TestAt() {
  auto deque = Deque<int>();

  deque.PushFront(1);
  ASSERT_EQUAL(1, deque.At(0));
  deque.At(0)--;
  ASSERT_EQUAL(0, deque.At(0));

  deque.PushBack(2);
  ASSERT_EQUAL(2, deque.At(1));
  deque.At(1)--;
  ASSERT_EQUAL(1, deque.At(1));
}

void TestFront() {
  auto deque = Deque<int>();

  deque.PushFront(1);
  ASSERT_EQUAL(1, deque.Front());
  deque.Front()--;
  ASSERT_EQUAL(0, deque.Front());
}

void TestAtThrows() {
  auto deque = Deque<int>();
  try {

  } catch (const std::out_of_range &) {
    ASSERT(true);
  } catch (...) {
    ASSERT(false);
  }
}

void TestFrontBack() {
  {
    auto deque = Deque<int>();
    deque.PushFront(1);
    deque.PushFront(2);
    deque.PushFront(3);
    deque.PushFront(4);

    ASSERT_EQUAL(4, deque.Front());
    ASSERT_EQUAL(1, deque.Back());
  }
  {
    auto deque = Deque<int>();
    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);
    deque.PushBack(4);

    ASSERT_EQUAL(1, deque.Front());
    ASSERT_EQUAL(4, deque.Back());
  }
  {
    auto deque = Deque<int>();
    deque.PushBack(1);
    deque.PushFront(2);
    deque.PushBack(3);

    ASSERT_EQUAL(2, deque.Front());
    ASSERT_EQUAL(1, deque[1]);
    ASSERT_EQUAL(1, deque.At(1));
    ASSERT_EQUAL(3, deque.Back());
  }
}

int main() {
  TestRunner runner;
  RUN_TEST(runner, TestIndexOperator);
  RUN_TEST(runner, TestAt);
  RUN_TEST(runner, TestAtThrows);
  RUN_TEST(runner, TestFront);
  RUN_TEST(runner, TestFrontBack);

  return 0;
}
