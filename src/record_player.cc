/*
 * @Author: spongearale
 * @Date: 2024-03-30 00:08:34
 * @LastEditors: spongearale
 * @LastEditTime: 2024-03-30 19:01:02
 * @FilePath: /LeptSound/src/record_player.cc
 * @Description:
 *
 * Copyright (c) 2024 by spongearale, All Rights Reserved.
 */

#include "record_player.h"

namespace LeptSound {

void RecordPlayer::Init(RecordPlayerOption player_option) {
    player_option_ptr_ = std::make_shared<RecordPlayerOption>(player_option);
    running_ = false;
    record_manager_ptr_.reset(new RecordManager());
    record_manager_ptr_->Init(player_option.priority_enable,
                              player_option.same_priority_interrupt_enable);
    ProduceTurntable(player_option.turntable);
}

void RecordPlayer::Reset(RecordPlayerOption player_option) {
    Init(player_option);
    Destory();
}

void RecordPlayer::Destory() {
    running_ = false;
    record_manager_ptr_.reset();
    turntable_ptr_.reset();
    player_option_ptr_.reset();
    thread_ptr_->join();
    thread_ptr_.reset();
}

uint64_t RecordPlayer::Play(const Record record) {
    uint64_t uuid = 0;
    {
        std::lock_guard<std::mutex> lock(record_mutex_);
        uuid = record_manager_ptr_->Push(std::make_shared<Record>(record));
    }
    return uuid;
}

void RecordPlayer::Stop(uint64_t uuid) {
    {
        std::lock_guard<std::mutex> lock(record_mutex_);
        record_manager_ptr_->Pop(uuid);
    }
}

void RecordPlayer::Start() {
    if (running_) {
        return;
    }
    running_ = true;
    thread_ptr_.reset(new std::thread(&RecordPlayer::Run, this));
}

void RecordPlayer::ProduceTurntable(EnumTurntable turntable) {
    if (turntable == EnumTurntable::IrrKlang) {
        turntable_ptr_.reset(new IrrKlangTurntable());
    } else {  // todo
        turntable_ptr_.reset(new IrrKlangTurntable());
    }
}

void RecordPlayer::Run() {
    while (running_) {
        const RecordExtendPair record_extend_pair =
            record_manager_ptr_->Select();
        turntable_ptr_->Play(record_extend_pair);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
}  // namespace LeptSound
