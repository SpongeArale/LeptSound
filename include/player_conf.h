/***
 * @Author: spongearale
 * @Date: 2024-03-29 22:08:46
 * @LastEditors: spongearale
 * @LastEditTime: 2024-03-30 15:30:39
 * @FilePath: /LeptSound/include/player_conf.h
 * @Description:
 * @
 * @Copyright (c) 2024 by spongearale, All Rights Reserved.
 */

#ifndef PLAYERCONF_H
#define PLAYERCONF_H

#include <string>
namespace LeptSound {

enum EnumTurntable {
    IrrKlang = 0,
};

enum EnumLoopMode {
    None = 0,
    IntervalLoop = 1,
    CountLoop = 2,
};

struct Record {
    std::string id;
    std::string name;
    std::string path;
    std::string desc;
    uint32_t priority;       // 0 > 1 > 2 > 3 ......

    uint32_t loop_count;
    uint32_t loop_interval;  // sec

    uint32_t target_volume;
    bool modify_volume;
    bool recovery_volume;

    Record() {
        id = "";
        name = "";
        path = "";
        desc = "";
        priority = 0;
        modify_volume = false;
        recovery_volume = true;
        target_volume = 0;
        loop_count = 0;
    }
};

struct Extend {
    uint64_t uuid;
    uint32_t current_count;
    uint32_t last_time;
    Extend() : uuid(0), current_count(0), last_time(0) {}
};

struct RecordPlayerOption {
    bool priority_enable;
    bool same_priority_interrupt_enable;
    bool change_volume_enable;
    EnumLoopMode loop_mode;
    EnumTurntable turntable;

    RecordPlayerOption() {
        priority_enable = true;
        same_priority_interrupt_enable = false;
        change_volume_enable = false;
        loop_mode = EnumLoopMode::None;
        turntable = EnumTurntable::IrrKlang;
    }
};

using RecordPtr = std::shared_ptr<Record>;
using ExtendPtr = std::shared_ptr<Extend>;
using RecordExtendPair = std::pair<RecordPtr, ExtendPtr>;
using RecordPlayerOptionPtr = std::shared_ptr<RecordPlayerOption>;

}  // namespace LeptSound

#endif  // PLAYERCONF_H
