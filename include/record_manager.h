/***
 * @Author: spongearale
 * @Date: 2024-02-27 21:19:42
 * @LastEditors: spongearale
 * @LastEditTime: 2024-03-30 15:27:47
 * @FilePath: /LeptSound/include/record_manager.h
 * @Description:
 * @
 * @Copyright (c) 2024 by spongearale, All Rights Reserved.
 */

#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H
#include <cstdint>
#include <deque>
#include <map>
#include <memory>
#include <unordered_map>

#include "player_conf.h"
namespace LeptSound {
class RecordManager {
   public:
    using RecordPtr = std::shared_ptr<Record>;
    void Init(bool priority_enable, bool same_priority_interrupt_enable);
    uint64_t Push(const RecordPtr&);
    void Pop(uint64_t);
    const RecordExtendPair Select();
    void Clear();
    void Destory();

   private:
    using RecordExtendDeque = std::deque<RecordExtendPair>;

    static uint64_t count_;
    bool priority_enable_{false};
    static const uint32_t default_priority;
    bool same_priority_interrupt_enable_{false};
    RecordExtendPair loaded_record_extend_pair_{nullptr, nullptr};
    std::unordered_map<uint64_t, RecordExtendPair> uuid_record_map_;
    std::map<uint32_t, RecordExtendDeque> priority_record_deque_map_;
};
}  // namespace LeptSound

#endif  // RECORDMANAGER_H