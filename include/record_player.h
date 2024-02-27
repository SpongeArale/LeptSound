/***
 * @Author: spongearale
 * @Date: 2024-02-27 21:19:42
 * @LastEditors: spongearale
 * @LastEditTime: 2024-03-30 14:28:32
 * @FilePath: /LeptSound/include/record_player.h
 * @Description:
 * @
 * @Copyright (c) 2024 by spongearale, All Rights Reserved.
 */

#ifndef RECORDPLAYER_H
#define RECORDPLAYER_H
#include <cstdint>
#include <memory>
#include <mutex>
#include <thread>

#include "common.h"
#include "player_conf.h"
#include "record_manager.h"
#include "turntable.h"
namespace LeptSound {
class RecordPlayer : public Singleton<RecordPlayer> {
   public:
    friend class Singleton<RecordPlayer>;

    void Init(RecordPlayerOption);
    void Reset(RecordPlayerOption);
    void Start();
    void Destory();
    Record GetLoadedRecord() const;
    uint64_t Play(const Record);
    void Stop(const uint64_t);

   private:
    using TurntablePtr = std::unique_ptr<Turntable>;
    using ThreadPtr = std::unique_ptr<std::thread>;
    using RecordManagerPtr = std::unique_ptr<RecordManager>;

    void Run();
    void ProduceTurntable(EnumTurntable);

    bool running_{false};
    std::mutex record_mutex_;
    ThreadPtr thread_ptr_{nullptr};
    TurntablePtr turntable_ptr_{nullptr};
    RecordManagerPtr record_manager_ptr_{nullptr};
    RecordPlayerOptionPtr player_option_ptr_{nullptr};
};
}  // namespace LeptSound

#endif  // RECORDPLAYER_H
