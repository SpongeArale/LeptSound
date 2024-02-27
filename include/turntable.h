/***
 * @Author: spongearale
 * @Date: 2024-03-29 23:46:30
 * @LastEditors: spongearale
 * @LastEditTime: 2024-03-30 15:32:14
 * @FilePath: /LeptSound/include/turntable.h
 * @Description:
 * @
 * @Copyright (c) 2024 by spongearale, All Rights Reserved.
 */
#include <irrKlang/irrKlang.h>

#include <memory>
#include <string>

#include "player_conf.h"
namespace LeptSound {
class Turntable {
   public:
    Turntable();
    virtual ~Turntable();
    virtual void Play(const RecordExtendPair) = 0;
    virtual void Stop(const RecordExtendPair) = 0;
    const Record& GetLoadedRecord();

   protected:
    bool is_playing_{false};
    int max_volume_{1};
    int min_volume_{0};
    int current_volume_{50};
    int modified_volume_{50};
    bool is_change_volume_{false};
    bool change_volume_enable_{false};
    RecordExtendPair loaded_record_extend_{nullptr, nullptr};
};

class IrrKlangTurntable : public Turntable {
   public:
    IrrKlangTurntable();
    ~IrrKlangTurntable();
    void Play(const RecordExtendPair) override;
    void Stop(const RecordExtendPair) override;

   private:
    using SoundPtr = std::unique_ptr<irrklang::ISound>;
    using SoundEnginePtr = std::unique_ptr<irrklang::ISoundEngine>;

    SoundPtr sound_ptr_{nullptr};
    SoundEnginePtr sound_engine_ptr_{nullptr};
};

}  // namespace LeptSound
