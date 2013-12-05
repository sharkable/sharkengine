//
//  staged_vector.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_DATASTRUCTURES_STAGEDVECTOR_H_
#define GAMEENGINE_DATASTRUCTURES_STAGEDVECTOR_H_

#include <algorithm>
#include <set>
#include <vector>

template <class T>
class StagedVector {
 typedef typename std::vector<T *>::iterator iterator;
 typedef typename std::vector<T *>::reverse_iterator reverse_iterator;

 public:
  StagedVector() : staged_values_initialized_(false), has_staged_changes_(false) {}

  ~StagedVector() {
    ConsiderStageInitialization();
    for (T *i : staged_values_) {
      if (ManageMemoryForValue(i)) {
        delete i;
      }
    }
    for (T *i : to_erase_) {
      delete i;
    }
  }

  size_t Size() {
    return values_.size();
  }

  std::vector<T *> const & StagedValues() {
    ConsiderStageInitialization();
    return staged_values_;
  }

  T * operator[](size_t i) {
    return values_[i];
  }

  T * Back() {
    return values_.back();
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

  void StagePushBack(T *value, bool manage_memory = false) {
    ConsiderStageInitialization();
    staged_values_.push_back(value);
    if (manage_memory) {
      managed_memory_values_.insert(value);
    }
    has_staged_changes_ = true;
  }

  // Assumes all elements are already sorted.
  void StageOrderedInsert(T *value, bool (*compare)(T *, T *), bool manage_memory = false) {
    // Perform a binary search.
    int i_min = 0;
    int i_max = (int)staged_values_.size() - 1;

    while (true) {
      if (i_max < i_min) {
        StagePushBack(value, manage_memory);
        break;
      } else if (i_min == i_max) {
        if (compare(staged_values_[i_min], value)) {
          StageInsertAfter(value, staged_values_[i_min], manage_memory);
        } else {
          StageInsertBefore(value, staged_values_[i_min], manage_memory);
        }
        break;
      }

      int i_mid = (i_min + i_max) / 2;

      if (compare(staged_values_[i_mid], value) && !compare(staged_values_[i_mid + 1], value)) {
        StageInsertAfter(value, staged_values_[i_mid], manage_memory);
        break;
      } else if (compare(staged_values_[i_mid], value)) {
        if (i_min < i_mid) {
          i_min = i_mid;
        } else {
          i_min++;
        }
      } else {
        if (i_max > i_mid) {
          i_max = i_mid;
        } else {
          i_max--;
        }
      }
    }
  }

  void StageInsertBefore(T *value, T *existing_value, bool manage_memory = false) {
    ConsiderStageInitialization();
    iterator i = std::find(staged_values_.begin(), staged_values_.end(), existing_value);
    shark_assert(i != staged_values_.end(),
                 "StagedVector::StagedInsertBefore - Existing value not found.");
    staged_values_.insert(i, value);
    if (manage_memory) {
      managed_memory_values_.insert(value);
    }
    has_staged_changes_ = true;
  }

  void StageInsertAfter(T *value, T *existing_value, bool manage_memory = false) {
    ConsiderStageInitialization();
    iterator i = std::find(staged_values_.begin(), staged_values_.end(), existing_value);
    shark_assert(i != staged_values_.end(),
                 "StagedVector::StagedInsertAfter - Existing value not found.");
    staged_values_.insert(i + 1, value);
    if (manage_memory) {
      managed_memory_values_.insert(value);
    }
    has_staged_changes_ = true;
  }

  T * StagePopBack() {
    ConsiderStageInitialization();
    T *back = staged_values_.back();
    if (ManageMemoryForValue(back)) {
      to_erase_.push_back(back);
    }
    staged_values_.pop_back();
    has_staged_changes_ = true;
    return back;
  }

  void StageErase(T *value) {
    ConsiderStageInitialization();
    for (auto i = staged_values_.begin(); i != staged_values_.end();) {
      if (*i == value) {
        if (ManageMemoryForValue(value)) {
          to_erase_.push_back(value);
        }
        i = staged_values_.erase(i);
      } else {
        i++;
      }
    }
    has_staged_changes_ = true;
  }

  void StageClear() {
    ConsiderStageInitialization();
    for (T *i : staged_values_) {
      if (ManageMemoryForValue(i)) {
        to_erase_.push_back(i);
      }
    }
    staged_values_.clear();
    has_staged_changes_ = true;
  }

  void CommitStaging() {
    if (has_staged_changes_) {
      values_ = staged_values_;
      for (T *i : to_erase_) {
        delete i;
        managed_memory_values_.erase(i);
      }
      to_erase_.clear();
      has_staged_changes_ = false;
    }
    if (staged_values_initialized_) {
      staged_values_.clear();
      staged_values_initialized_ = false;
    }
  }

  bool HasStagedChanges() {
    return has_staged_changes_;
  }

 private:
  void ConsiderStageInitialization() {
    if (!staged_values_initialized_) {
      staged_values_ = values_;
      staged_values_initialized_ = true;
    }
  }

  bool ManageMemoryForValue(T *value) {
    return managed_memory_values_.find(value) != managed_memory_values_.end();
  }

  std::vector<T *> values_;
  std::vector<T *> staged_values_;
  std::vector<T *> to_erase_;
  std::set<T *> managed_memory_values_;
  bool staged_values_initialized_;
  bool has_staged_changes_;
};

#endif
