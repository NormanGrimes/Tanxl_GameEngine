//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-26 22:23
// 增加枚举重载版本的音频播放功能

#pragma once

#ifndef _TANXL_SOUNDBASE_
#define _TANXL_SOUNDBASE_

#include <irrKlang/irrKlang.h>

enum ESound_WAV
{
    SOUND_GAME_START  = 0,
    SOUND_GAME_OVER   = 1
};

class SoundBase
{
public:
    static SoundBase& GetSoundBase()
    {
        static SoundBase* SoundEngine{ new SoundBase() };
        return *SoundEngine;
    }

    void Play_Sound(std::string Wav_File_Location)
    {
        this->_SoundEngine->play2D(Wav_File_Location.c_str());
    }

    void Play_Sound(ESound_WAV Sound_Name)
    {
        this->_SoundEngine->play2D(this->Sound_Names[Sound_Name].c_str());
    }

private:
    irrklang::ISoundEngine* _SoundEngine;
    std::string Sound_Names[2]{ "music/Game_Start.wav", "music/Game_Over.wav" };

    SoundBase() :_SoundEngine(irrklang::createIrrKlangDevice()) {}
    ~SoundBase() { this->_SoundEngine->drop(); }
    SoundBase(const SoundBase&) :_SoundEngine(irrklang::createIrrKlangDevice()) {};
    SoundBase& operator=(const SoundBase&) { return *this; };
};

#endif
