//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-26 22:23
// 增加枚举重载版本的音频播放功能
// 整理进入引擎层
// 新增触发地图事件的音频
// 新增恢复生命值和鼠标点击的音频
// 新增系统调用音频
// 增加版本信息功能
// 增加停止所有音频功能
// 改为继承自引擎基础类
// 新增成就解锁音频
// 增加捡起神秘核心的音频

#pragma once

#ifndef _TANXL_SOUNDBASE_
#define _TANXL_SOUNDBASE_

#include <string>
#include <irrKlang/irrKlang.h>

#include "Tanxl_EngineBase.h"

enum ESound_WAV
{
    SOUND_GAME_START        = 0,
    SOUND_GAME_OVER         = 1,
    SOUND_EVENT_START       = 2,
    SOUND_RESTORE_HEALTH    = 3,
    SOUND_MOUSE_CLICK       = 4,
    SOUND_SYSTEM_CALL       = 5,
    SOUND_ACHIEVEMENT       = 6,
    SOUND_SECRET_CORE       = 7
};

class SoundBase : public Tanxl_ClassBase
{
public:
    static SoundBase& GetSoundBase();

    void Play_Sound(std::string Wav_File_Location);

    void Play_Sound(ESound_WAV Sound_Name);

    void Stop_AllSound();

    const std::string Get_Version();

private:
    irrklang::ISoundEngine* _SoundEngine;

    std::string Sound_Names[8]
    { 
        "music/Game_Start.wav", 
        "music/Game_Over.wav",
        "music/Game_Event_Start.wav",
        "music/Game_Event_Restore_Health.wav" ,
        "music/Game_Mouse_Click.wav",
        "music/Game_System_Call.wav",
        "music/Achievement_Unlock.wav",
        "music/Game_Event_Secret_Core.wav"
    };

    SoundBase();
    ~SoundBase();
    SoundBase(const SoundBase&);
    SoundBase& operator=(const SoundBase&);
};

#endif
