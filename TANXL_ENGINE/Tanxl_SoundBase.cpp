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
	if (Sound_Name == ESound_WAV::SOUND_NO_SOUND)
		return;
	this->_SoundEngine->play2D(this->_Sound_Names[Sound_Name].c_str());
}

void SoundBase::Append_BackGround_Music(std::string Wav_File_Location)
{
	this->_BackGround_Music_List.push_back(Wav_File_Location);
}

void SoundBase::Append_BackGround_Music(ESound_WAV Sound_Name)
{
	if (Sound_Name == ESound_WAV::SOUND_NO_SOUND)
		return;
	this->_BackGround_Music_List.push_back(this->_Sound_Names[Sound_Name]);
}

void SoundBase::Stop_AllSound()
{
	this->_SoundEngine->stopAllSounds();

	this->_Current_BackGround_Id = 0;
	this->_BackGround_Music_Playing = false;
	this->_SoundEngine->setSoundVolume(1.0f);
}

void SoundBase::Play_BackGround_Music(int Begin_Id)
{
	if (this->_BackGround_Music_List.size() == 0)
		return;
	if (this->_BackGround_Music_Playing == false)
	{
		this->_BackGround_Music_Playing = true;
		this->_Current_BackGround_Id = Begin_Id + static_cast<int>(this->_BackGround_Music_List.size()) - 1;
		this->_Current_BackGround_Id = this->_Current_BackGround_Id % this->_BackGround_Music_List.size();
		this->Play_Sound(this->_BackGround_Music_List.at(this->_Current_BackGround_Id));
		this->_SoundEngine->setSoundVolume(0.5f);
	}

	if (!this->Sound_Playing(this->_BackGround_Music_List.at(this->_Current_BackGround_Id)))
	{
		this->_Current_BackGround_Id++;
		this->_Current_BackGround_Id = this->_Current_BackGround_Id % this->_BackGround_Music_List.size();
		this->Play_Sound(this->_BackGround_Music_List.at(this->_Current_BackGround_Id));
		this->_SoundEngine->setSoundVolume(0.5f);
	}
}

bool SoundBase::Sound_Playing(std::string Wav_File_Location)
{
	return this->_SoundEngine->isCurrentlyPlaying(Wav_File_Location.c_str());
}

bool SoundBase::Sound_Playing(ESound_WAV Sound_Name)
{
	if (Sound_Name == ESound_WAV::SOUND_NO_SOUND)
		return false;
	return this->_SoundEngine->isCurrentlyPlaying(this->_Sound_Names[Sound_Name].c_str());
}

bool SoundBase::BackGround_Playing()
{
	return this->_BackGround_Music_Playing;
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

SoundBase::SoundBase() :_SoundEngine(irrklang::createIrrKlangDevice()), Tanxl_ClassBase("0.1"), _BackGround_Music_List(),
_BackGround_Music_Playing(false), _Current_BackGround_Id(0) {}

SoundBase::~SoundBase() { this->_SoundEngine->drop(); }

SoundBase::SoundBase(const SoundBase&) :_SoundEngine(irrklang::createIrrKlangDevice()), Tanxl_ClassBase("0.1"), _BackGround_Music_List(),
_BackGround_Music_Playing(false), _Current_BackGround_Id(0) {}

SoundBase& SoundBase::operator=(const SoundBase&) { return *this; }