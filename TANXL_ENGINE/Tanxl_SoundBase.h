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
// 背景音乐使用独立的音源播放
// 多个接口增加音源选择参数
// 背景音乐音量降低到百分之三十
// 增加接口用于随机选择背景音乐
// 背景音乐播放接口增加默认参数
// 背景音乐音量初始化为百分之三十
// 修复停止声音接口任意选项都会影响背景音乐的问题
// 增加音量设置接口
// 所有用于选择音频引擎的整形变量改为枚举

#pragma once

#ifndef _TANXL_SOUNDBASE_
#define _TANXL_SOUNDBASE_

#include <string>
#include <vector>
#include <irrKlang/irrKlang.h>

#include "Tanxl_EngineBase.h"
#include "Tanxl_RandomBase.h"

enum ESoundEngine_ID
{
    SOUND_ENGINE_EVENT      = 0,
    SOUND_ENGINE_BACKGROUND = 1
};

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

    void Play_Sound(std::string Wav_File_Location, ESoundEngine_ID SoundEngine_Id = SOUND_ENGINE_EVENT);

    void Play_Sound(ESound_WAV Sound_Name, ESoundEngine_ID SoundEngine_Id = SOUND_ENGINE_EVENT);

    void Append_BackGround_Music(std::string Wav_File_Location);

    void Append_BackGround_Music(ESound_WAV Sound_Name);
    // 停止指定声音引擎的声音播放
    void Stop_AllSound(ESoundEngine_ID SoundEngine_Id = SOUND_ENGINE_EVENT);
    // 包含对背景音乐的顺序播放功能 顺序播放功能需要持续调用
    void Play_BackGround_Music(int Begin_Id = -1);

    void Random_BackGround_Music();

    void Set_SoundVolume(ESoundEngine_ID SoundEngine_Id, float Volume);

    bool Sound_Playing(std::string Wav_File_Location, ESoundEngine_ID SoundEngine_Id = SOUND_ENGINE_EVENT);

    bool Sound_Playing(ESound_WAV Sound_Name, ESoundEngine_ID SoundEngine_Id = SOUND_ENGINE_EVENT);

    bool BackGround_Playing() const;

    ESound_WAV Sound_Playing_Id(ESoundEngine_ID SoundEngine_Id = SOUND_ENGINE_EVENT);

    const std::string Get_Version();

private:
    irrklang::ISoundEngine* _SoundEngine[2];

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
