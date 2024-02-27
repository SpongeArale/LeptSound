/*
 * @Author: spongearale
 * @Date: 2024-03-30 00:32:51
 * @LastEditors: spongearale
 * @LastEditTime: 2024-03-30 18:47:00
 * @FilePath: /LeptSound/src/turntable.cc
 * @Description:
 *
 * Copyright (c) 2024 by spongearale, All Rights Reserved.
 */

#include "turntable.h"

#include <fstream>

namespace LeptSound {

IrrKlangTurntable::IrrKlangTurntable() {
    sound_engine_ptr_.reset(irrklang::createIrrKlangDevice());
}

IrrKlangTurntable::~IrrKlangTurntable() {
    if (sound_ptr_) {
        sound_ptr_->drop();
    }
    if (sound_engine_ptr_) {
        sound_engine_ptr_->drop();
    }
}

const Record& Turntable::GetLoadedRecord() {
    return *(loaded_record_extend_.first);
}

void IrrKlangTurntable::Play(const RecordExtendPair record_extend_pair) {
    if (!sound_engine_ptr_) return;
    auto record_ptr = record_extend_pair.first;
    auto extend_ptr = record_extend_pair.second;
    const std::string& sound_filename = record_extend_pair.first->path;
    if (sound_filename.empty() ||
        (loaded_record_extend_.first &&
         sound_filename == loaded_record_extend_.first->path) ||
        (loaded_record_extend_.second &&
         extend_ptr->uuid == loaded_record_extend_.second->uuid)) {
        return;
    }

    std::ifstream ifs(sound_filename.c_str());
    if (!ifs.good()) {
        return;
    }

    loaded_record_extend_ = record_extend_pair;

    if (sound_ptr_) {
        sound_ptr_->drop();
    }
    sound_ptr_.reset(
        sound_engine_ptr_->play2D(sound_filename.c_str(), false, false, true));

    if (sound_ptr_ && change_volume_enable_ && record_ptr->modify_volume) {
        sound_ptr_->setVolume(record_ptr->target_volume);
        modified_volume_ = record_ptr->target_volume;
    } else if (sound_ptr_ && change_volume_enable_ &&
               !record_ptr->modify_volume && is_change_volume_) {
        sound_ptr_->setVolume(current_volume_);
    }
}

void IrrKlangTurntable::Stop(const RecordExtendPair record_extend_pair) {
    if (loaded_record_extend_.second && (record_extend_pair.second->uuid ==
                                         loaded_record_extend_.second->uuid)) {
        if (sound_ptr_) {
            if (!(sound_ptr_->isFinished())) {
                sound_ptr_->stop();
            }
            sound_ptr_->drop();
        }
    }
}

}  // namespace LeptSound