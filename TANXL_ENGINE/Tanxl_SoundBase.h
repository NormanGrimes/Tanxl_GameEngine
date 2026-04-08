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
// 增加停止所有音频的接口
// 修复停止后重新播放的背景音乐重复的问题
// 增加音频事件观察者类
// 增加音频观察者成员变量
// 音频宏与名称调整
// 新增鼠标右键点击的音频
// 增加错误调试模式
// 停止音频接口不再调整音量
// 禁用存在问题的波形文件
// 移除音频枚举以及所有枚举涉及的接口
// 移除内部记录音频路径的成员
// 增加音频事件通知接口

#pragma once

#ifndef _TANXL_SOUNDBASE_
#define _TANXL_SOUNDBASE_

#include <string>
#include <vector>
#include <irrKlang/irrKlang.h>

#include "Tanxl_EngineBase.h"
#include "Tanxl_RandomBase.h"
#include "Tanxl_GameEvent.h"

#define _ENABLE_SOUNDBASE_DEBUG_MODE_ 0

enum ESoundEngine_ID
{
    SOUND_ENGINE_EVENT      = 0,
    SOUND_ENGINE_BACKGROUND = 1
};

enum ESound_WAV
{
    SOUND_GAME_START        = 0,
    SOUND_GAME_OVER         = 1,
    SOUND_TAKE_DAMAGE       = 2,
    SOUND_RESTORE_HEALTH    = 3,
    SOUND_MOUSE_CLICK       = 4,
    SOUND_MOUSE_CLICK_RIGHT = 5,
    SOUND_TAKE_COIN         = 6,
    SOUND_ACHIEVEMENT       = 7,
    SOUND_SECRET_CORE       = 8,

    SOUND_BACKGROUND_01     = 9,
    SOUND_BACKGROUND_02     = 10,
    SOUND_BACKGROUND_03     = 11,
    SOUND_BACKGROUND_04     = 12,
    SOUND_BACKGROUND_05     = 13,

    SOUND_NO_SOUND          = 0xFF
};

class SoundBase : public Tanxl_ClassBase
{
public:
    static SoundBase& GetSoundBase();

    void Play_Sound(std::string Wav_File_Location, ESoundEngine_ID SoundEngine_Id = SOUND_ENGINE_EVENT);

    void Append_BackGround_Music(std::string Wav_File_Location);
    // 停止指定声音引擎的声音播放
    void Stop_Sound(ESoundEngine_ID SoundEngine_Id);
    // 停止所有声音引擎的播放
    void Stop_AllSound();
    // 包含对背景音乐的顺序播放功能 顺序播放功能需要持续调用
    void Play_BackGround_Music(int Begin_Id = -1);

    void Random_BackGround_Music();

    void Set_SoundVolume(ESoundEngine_ID SoundEngine_Id, float Volume);

    void Notify(int SoundEvent);

    bool Sound_Playing(std::string Wav_File_Location, ESoundEngine_ID SoundEngine_Id = SOUND_ENGINE_EVENT);

    bool BackGround_Playing() const;

    const std::string Get_Version();

private:
    irrklang::ISoundEngine* _SoundEngine[2];

    std::vector<std::string> _BackGround_Music_List;

    int _Current_BackGround_Id;
    bool _BackGround_Music_Playing;

    EventSubject<int> _SoundCheck;

    SoundBase();
    ~SoundBase();
    SoundBase(const SoundBase&);
    SoundBase& operator=(const SoundBase&);
};

class Sound_Observer : public Event_Observer<int>
{
public:
    Sound_Observer(int Event_Id, std::string Sound_Name, SoundBase* Sound_Engine) :
        _Event_Id(Event_Id), _Sound_Name(Sound_Name), _Sound_Engine(Sound_Engine) {}

    virtual void EventCheck(int& Event_Id)
    {
        if (this->_Event_Id == Event_Id)
            _Sound_Engine->Play_Sound(this->_Sound_Name);
    }

private:
    int _Event_Id;
    std::string _Sound_Name;
    SoundBase* _Sound_Engine;
};

#endif
