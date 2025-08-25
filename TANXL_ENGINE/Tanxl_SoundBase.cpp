#pragma once

#include "Tanxl_SoundBase.h"

SoundBase& SoundBase::GetSoundBase()
{
	static SoundBase* SoundEngine{ new SoundBase() };
	return *SoundEngine;
}

void SoundBase::Play_Sound(std::string Wav_File_Location)
{
	this->_SoundEngine->play2D(Wav_File_Location.c_str());
}

void SoundBase::Play_Sound(ESound_WAV Sound_Name)
{
	this->_SoundEngine->play2D(this->_Sound_Names[Sound_Name].c_str());
}

void SoundBase::Stop_AllSound()
{
	this->_SoundEngine->stopAllSounds();
}

bool SoundBase::Sound_Playing(ESound_WAV Sound_Name)
{
	return this->_SoundEngine->isCurrentlyPlaying(this->_Sound_Names[Sound_Name].c_str());
}

ESound_WAV SoundBase::Sound_Playing_Id()
{
	for (int i{ 0 }; i < 8; ++i)
	{
		if (this->Sound_Playing(ESound_WAV(i)))
			return ESound_WAV(i);
	}
	return ESound_WAV::SOUND_NO_SOUND;
}

const std::string SoundBase::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

SoundBase::SoundBase() :_SoundEngine(irrklang::createIrrKlangDevice()), Tanxl_ClassBase("0.1") {}
SoundBase::~SoundBase() { this->_SoundEngine->drop(); }
SoundBase::SoundBase(const SoundBase&) :_SoundEngine(irrklang::createIrrKlangDevice()), Tanxl_ClassBase("0.1") {};
SoundBase& SoundBase::operator=(const SoundBase&) { return *this; };