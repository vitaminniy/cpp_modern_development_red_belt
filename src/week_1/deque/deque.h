#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

#define BY_INDEX(front_, back_, index)                                         \
  {                                                                            \
    if (front_.size() > index) {                                               \
      return front_[front_.size() - index - 1];                                \
    }                                                                          \
    return back_[index - front_.size()];                                       \
  }

#define FRONT(front_, back_)                                                   \
  (front_.empty()) ? (back_.front()) : (front_.back())

#define BACK(front_, back_) (back_.empty()) ? (front_.front()) : (back_.back())

template <typename T> class Deque {
public:
  Deque() = default;

  inline bool Empty() const { return front_.empty() && back_.empty(); }
  inline size_t Size() const { return front_.size() + back_.size(); }

  inline T &operator[](size_t index) { BY_INDEX(front_, back_, index) }
  inline const T &operator[](size_t index) const {
    BY_INDEX(front_, back_, index)
  }

  inline T &At(size_t index) {
    check_index(index);
    BY_INDEX(front_, back_, index);
  }

  inline const T &At(size_t index) const {
    check_index(index);
    BY_INDEX(front_, back_, index);
  }

  inline T &Front() { return FRONT(front_, back_); }
  inline const T &Front() const { return FRONT(front_, back_); }

  inline T &Back() { return BACK(front_, back_); }
  inline const T &Back() const { return BACK(front_, back_); }

  inline void PushFront(const T &t) { front_.push_back(t); }
  inline void PushBack(const T &t) { back_.push_back(t); }

private:
  void check_index(size_t index) const;

  std::vector<T> front_, back_;
};

template <typename T> void Deque<T>::check_index(size_t index) const {
  if (const auto size = Size(); index >= size) {
    throw std::out_of_range("index " + std::to_string(index) +
                            " is out of range " + std::to_string(size));
  }
}
