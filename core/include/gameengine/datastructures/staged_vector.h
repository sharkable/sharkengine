//
//  staged_vector.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_DATASTRUCTURES_STAGEDVECTOR_H_
#define GAMEENGINE_DATASTRUCTURES_STAGEDVECTOR_H_

#include <set>
#include <vector>

template <class T>
class StagedVector {
 typedef typename std::vector<T *>::iterator iterator;
 typedef typename std::vector<T *>::reverse_iterator reverse_iterator;

 public:
  StagedVector() : next_values_initialized_(false), has_staged_changes_(false) {}

  ~StagedVector() {
    ConsiderInitialization();
    for (auto i = next_values_.begin(); i != next_values_.end(); i++) {
      if (ManageMemoryForValue(*i)) {
        delete *i;
      }
    }
    for (iterator i = to_erase_.begin(); i != to_erase_.end(); i++) {
      delete *i;
    }
  }

  size_t Size() {
    return values_.size();
  }

  size_t StagedSize() {
    ConsiderInitialization();
    return next_values_.size();
  }

  T * Back() {
    return values_.back();
  }

  T * StagedBack() {
    ConsiderInitialization();
    return next_values_.back();
  }

  iterator Begin() {
    return values_.begin();
  }

  iterator End() {
    return values_.end();
  }

  reverse_iterator ReverseBegin() {
    return values_.rbegin();
  }

  reverse_iterator ReverseEnd() {
    return values_.rend();
  }

  void PushBack(T *value, bool manage_memory = false) {
    ConsiderInitialization();
    next_values_.push_back(value);
    if (manage_memory) {
      managed_memory_values_.insert(value);
    }
    has_staged_changes_ = true;
  }

  void InsertBefore(T *value, T *existing_value, bool manage_memory = false) {
    ConsiderInitialization();
    iterator i = std::find(next_values_.begin(), next_values_.end(), existing_value);
    assert(i != next_values_.end());
    next_values_.insert(i, value);
    if (manage_memory) {
      managed_memory_values_.insert(value);
    }
    has_staged_changes_ = true;
  }

  void InsertAfter(T *value, T *existing_value, bool manage_memory = false) {
    ConsiderInitialization();
    iterator i = std::find(next_values_.begin(), next_values_.end(), existing_value);
    assert(i != next_values_.end());
    next_values_.insert(i + 1, value);
    if (manage_memory) {
      managed_memory_values_.insert(value);
    }
    has_staged_changes_ = true;
  }

  void PopBack() {
    ConsiderInitialization();
    T *back = next_values_.back();
    if (ManageMemoryForValue(back)) {
      to_erase_.push_back(back);
    }
    next_values_.pop_back();
    has_staged_changes_ = true;
  }

  void Erase(T *value) {
    ConsiderInitialization();
    for (auto i = next_values_.begin(); i != next_values_.end();) {
      if (*i == value) {
        if (ManageMemoryForValue(value)) {
          to_erase_.push_back(value);
        }
        i = next_values_.erase(i);
      } else {
        i++;
      }
    }
    has_staged_changes_ = true;
  }

  void Clear() {
    ConsiderInitialization();
    for (auto i = next_values_.begin(); i != next_values_.end(); i++) {
      if (ManageMemoryForValue(*i)) {
        to_erase_.push_back(*i);
      }
    }
    next_values_.clear();
    has_staged_changes_ = true;
  }

  void Commit() {
    if (has_staged_changes_) {
      values_ = next_values_;
      for (auto i = to_erase_.begin(); i != to_erase_.end(); i++) {
        delete *i;
        managed_memory_values_.erase(*i);
      }
      to_erase_.clear();
      has_staged_changes_ = false;
    }
    if (next_values_initialized_) {
      next_values_.clear();
      next_values_initialized_ = false;
    }
  }

  bool HasStagedChanges() {
    return has_staged_changes_;
  }

 private:
  void ConsiderInitialization() {
    if (!next_values_initialized_) {
      next_values_ = values_;
      next_values_initialized_ = true;
    }
  }

  bool ManageMemoryForValue(T *value) {
    return managed_memory_values_.find(value) != managed_memory_values_.end();
  }

  std::vector<T *> values_;
  std::vector<T *> next_values_;
  std::vector<T *> to_erase_;
  std::set<T *> managed_memory_values_;
  bool next_values_initialized_;
  bool has_staged_changes_;
};

#endif
