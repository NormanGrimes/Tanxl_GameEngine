//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-26 22:23

#pragma once

#ifndef _TANXL_SOUNDBASE_
#define _TANXL_SOUNDBASE_

#include <irrKlang/irrKlang.h>

enum ESound_WAV
{

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

private:
    irrklang::ISoundEngine* _SoundEngine;

    SoundBase() :_SoundEngine(irrklang::createIrrKlangDevice()) {}
    ~SoundBase() { this->_SoundEngine->drop(); }
    SoundBase(const SoundBase&) :_SoundEngine(irrklang::createIrrKlangDevice()) {};
    SoundBase& operator=(const SoundBase&) { return *this; };
};

#endif
