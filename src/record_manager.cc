/*
 * @Author: spongearale
 * @Date: 2024-02-24 23:22:16
 * @LastEditors: spongearale
 * @LastEditTime: 2024-03-30 19:01:24
 * @FilePath: /LeptSound/src/record_manager.cc
 * @Description:
 *
 * Copyright (c) 2024 by spongearale, All Rights Reserved.
 */

#include "record_manager.h"

#include <assert.h>
namespace LeptSound {

uint64_t RecordManager::count_ = 0;
const uint32_t RecordManager::default_priority = 0;

void RecordManager::Init(bool priority_enable,
                         bool same_priority_interrupt_enable) {
    priority_enable_ = priority_enable;
    same_priority_interrupt_enable_ = same_priority_interrupt_enable;
}

uint64_t RecordManager::Push(const RecordPtr& record_ptr) {
    count_++;

    auto extend_ptr = std::make_shared<Extend>();
    extend_ptr->uuid = count_;

    uuid_record_map_[count_] = {record_ptr, extend_ptr};
    uint32_t priority = default_priority;
    if (priority_enable_) {
        priority = record_ptr->priority;
    }
    priority_record_deque_map_[priority].push_back({record_ptr, extend_ptr});

    return count_;
}

void RecordManager::Pop(uint64_t uuid) {
    if (uuid_record_map_.find(uuid) == uuid_record_map_.end()) {
        return;
    }
    uint32_t priority = default_priority;
    if (priority_enable_) {
        priority = uuid_record_map_[uuid].first->priority = priority;
    }

    assert(priority_record_deque_map_.find(priority) !=
           priority_record_deque_map_.end());

    assert(priority_record_deque_map_.find(priority) !=
           priority_record_deque_map_.end());

    auto record_extend_deque = priority_record_deque_map_[priority];
    for (auto iter = record_extend_deque.begin();
         iter != record_extend_deque.end(); ++iter) {
        if (iter->second->uuid == uuid) {
            record_extend_deque.erase(iter);
            break;
        }
    }
}

const RecordExtendPair RecordManager::Select() {
    RecordExtendPair record_extend_pair{nullptr, nullptr};
    auto loaded_record_ptr = loaded_record_extend_pair_.first;
    auto loaded_extend_ptr = loaded_record_extend_pair_.second;

    for (auto& [priority, record_deque] : priority_record_deque_map_) {
        if (!record_deque.empty()) {
            for (auto iter = record_deque.begin(); iter != record_deque.end();
                 ++iter) {
                if (!loaded_record_ptr) {
                    record_extend_pair = *iter;
                    break;
                } else {
                    if (priority_enable_) {
                        if (iter->first->priority <
                            loaded_record_ptr->priority) {
                            record_extend_pair = *iter;
                            break;
                        } else if (iter->first->priority ==
                                   loaded_record_ptr->priority) {
                            if (same_priority_interrupt_enable_) {
                                record_extend_pair = *iter;
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                }
            }

            if (record_extend_pair.first) {
                break;
            }
        }
    }

    return record_extend_pair;
}

void RecordManager::Clear() {
    count_ = 0;
    uuid_record_map_.clear();
    priority_record_deque_map_.clear();
    loaded_record_extend_pair_ = {nullptr, nullptr};
}

}  // namespace LeptSound