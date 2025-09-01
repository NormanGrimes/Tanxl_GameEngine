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
// 增加检测指定音频是否在播放的接口
// 增加检测当前播放音频编号的接口
// 增加背景音乐容器与添加接口
// 增加音乐枚举重载为文件路径的函数版本
// 新增背景音乐播放接口
// 增加无声枚举的检查
// 增加获取背景音乐是否播放的接口

#pragma once

#ifndef _TANXL_SOUNDBASE_
#define _TANXL_SOUNDBASE_

#include <string>
#include <vector>
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
    SOUND_SECRET_CORE       = 7,
    SOUND_BACKGROUND_01     = 8,
    SOUND_BACKGROUND_02     = 9,
    SOUND_BACKGROUND_03     = 10,
    SOUND_BACKGROUND_04     = 11,
    SOUND_BACKGROUND_05     = 12,

    SOUND_NO_SOUND          = 0xFF
};

class SoundBase : public Tanxl_ClassBase
{
public:
    static SoundBase& GetSoundBase();

    void Play_Sound(std::string Wav_File_Location);

    void Play_Sound(ESound_WAV Sound_Name);

    void Append_BackGround_Music(std::string Wav_File_Location);

    void Append_BackGround_Music(ESound_WAV Sound_Name);

    void Stop_AllSound();
    // 包含对背景音乐的顺序播放功能 顺序播放功能需要持续调用
    void Play_BackGround_Music(int Begin_Id);

    bool Sound_Playing(std::string Wav_File_Location);

    bool Sound_Playing(ESound_WAV Sound_Name);

    bool BackGround_Playing();

    ESound_WAV Sound_Playing_Id();

    const std::string Get_Version();

private:
    irrklang::ISoundEngine* _SoundEngine;

    std::string _Sound_Names[13]
    { 
        "music/Game_Start.wav", 
        "music/Game_Over.wav",
        "music/Game_Event_Start.wav",
        "music/Game_Event_Restore_Health.wav" ,
        "music/Game_Mouse_Click.wav",
        "music/Game_System_Call.wav",
        "music/Achievement_Unlock.wav",
        "music/Game_Event_Secret_Core.wav",
        "music/Game_BackGround_01.mp3",
        "music/Game_BackGround_02.mp3",
        "music/Game_BackGround_03.mp3",
        "music/Game_BackGround_04.mp3",
        "music/Game_BackGround_05.mp3"
    };

    std::vector<std::string> _BackGround_Music_List;

    int _Current_BackGround_Id;
    bool _BackGround_Music_Playing;

    SoundBase();
    ~SoundBase();
    SoundBase(const SoundBase&);
    SoundBase& operator=(const SoundBase&);
};

#endif
