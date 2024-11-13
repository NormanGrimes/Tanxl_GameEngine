//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-26 22:23
// 增加枚举重载版本的音频播放功能
// 整理进入引擎层
// 新增触发地图事件的音频

#pragma once

#ifndef _TANXL_SOUNDBASE_
#define _TANXL_SOUNDBASE_

#include <string>
#include <irrKlang/irrKlang.h>

enum ESound_WAV
{
    SOUND_GAME_START  = 0,
    SOUND_GAME_OVER   = 1,
    SOUND_EVENT_START = 2
};

class SoundBase
{
public:
    static SoundBase& GetSoundBase();

    void Play_Sound(std::string Wav_File_Location);

    void Play_Sound(ESound_WAV Sound_Name);

private:
    irrklang::ISoundEngine* _SoundEngine;
    std::string Sound_Names[3]{ "music/Game_Start.wav", "music/Game_Over.wav","music/Game_Event_Start.wav" };

    SoundBase();
    ~SoundBase();
    SoundBase(const SoundBase&);
    SoundBase& operator=(const SoundBase&);
};

#endif
