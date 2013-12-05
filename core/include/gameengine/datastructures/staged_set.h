//
//  staged_set.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-12-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_DATASTRUCTURES_STAGEDSET_H_
#define GAMEENGINE_DATASTRUCTURES_STAGEDSET_H_

#include <algorithm>
#include <set>
#include <vector>

template <class T, class Compare>
class StagedSet {
  typedef typename std::set<T *>::iterator iterator;
  typedef typename std::set<T *>::reverse_iterator reverse_iterator;

 public:
  StagedSet() : staged_values_initialized_(false), has_staged_changes_(false) {}

  ~StagedSet() {
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

  std::set<T *> const & StagedValues() {
    ConsiderStageInitialization();
    return staged_values_;
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

  void StageInsert(T *value, bool manage_memory = false) {
    ConsiderStageInitialization();
    staged_values_.insert(value);
    if (manage_memory) {
      managed_memory_values_.insert(value);
    }
    has_staged_changes_ = true;
  }

  void StageErase(T *value) {
    ConsiderStageInitialization();
    if (ManageMemoryForValue(value)) {
      to_erase_.push_back(value);
    }
    staged_values_.erase(value);
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

  std::set<T *, Compare> values_;
  std::set<T *, Compare> staged_values_;
  std::vector<T *> to_erase_;
  std::set<T *> managed_memory_values_;
  bool staged_values_initialized_;
  bool has_staged_changes_;
};

#endif
