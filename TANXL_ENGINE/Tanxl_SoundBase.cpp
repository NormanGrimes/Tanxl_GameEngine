#pragma once

#include "Tanxl_SoundBase.h"

SoundBase& SoundBase::GetSoundBase()
{
	static SoundBase* SoundEngine{ new SoundBase() };
	return *SoundEngine;
}

void SoundBase::Play_Sound(std::string Wav_File_Location, ESoundEngine_ID SoundEngine_Id)
{
	this->_SoundEngine[SoundEngine_Id]->play2D(Wav_File_Location.c_str());
}

void SoundBase::Play_Sound(ESound_WAV Sound_Name, ESoundEngine_ID SoundEngine_Id)
{
	if (Sound_Name == ESound_WAV::SOUND_NO_SOUND)
		return;
	this->_SoundEngine[SoundEngine_Id]->play2D(this->_Sound_Names[Sound_Name].c_str());
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

void SoundBase::Stop_Sound(ESoundEngine_ID SoundEngine_Id)
{
	this->_SoundEngine[SoundEngine_Id]->stopAllSounds();
	
	if (SoundEngine_Id == 1)
	{
		//this->_Current_BackGround_Id = 0;
		this->_BackGround_Music_Playing = false;
		this->_SoundEngine[SoundEngine_Id]->setSoundVolume(0.3f);
	}
	else
	{
		this->_SoundEngine[SoundEngine_Id]->setSoundVolume(1.0f);
	}
}

void SoundBase::Stop_AllSound()
{
	this->_SoundEngine[SOUND_ENGINE_EVENT]->stopAllSounds();
	this->_SoundEngine[SOUND_ENGINE_BACKGROUND]->stopAllSounds();

	//this->_Current_BackGround_Id = 0;
	this->_BackGround_Music_Playing = false;

	this->_SoundEngine[SOUND_ENGINE_EVENT]->setSoundVolume(1.0f);
	this->_SoundEngine[SOUND_ENGINE_BACKGROUND]->setSoundVolume(0.3f);
}

void SoundBase::Play_BackGround_Music(int Begin_Id)
{
	if (this->_BackGround_Music_List.size() == 0)
		return;
	if (Begin_Id == -1)
		Begin_Id = this->_Current_BackGround_Id;
	if (this->_BackGround_Music_Playing == false)
	{
		this->_BackGround_Music_Playing = true;
		this->_Current_BackGround_Id = Begin_Id + static_cast<int>(this->_BackGround_Music_List.size()) - 1;
		this->_Current_BackGround_Id = this->_Current_BackGround_Id % this->_BackGround_Music_List.size();
		this->Play_Sound(this->_BackGround_Music_List.at(this->_Current_BackGround_Id), SOUND_ENGINE_BACKGROUND);
	}

	if (!this->Sound_Playing(this->_BackGround_Music_List.at(this->_Current_BackGround_Id), SOUND_ENGINE_BACKGROUND))
	{
		this->_Current_BackGround_Id++;
		this->_Current_BackGround_Id = this->_Current_BackGround_Id % this->_BackGround_Music_List.size();
		this->Play_Sound(this->_BackGround_Music_List.at(this->_Current_BackGround_Id), SOUND_ENGINE_BACKGROUND);
	}
}

void SoundBase::Random_BackGround_Music()
{
	this->_Current_BackGround_Id = RandomBase::GenerateNum(static_cast<int>(time(0)));
	this->_Current_BackGround_Id = this->_Current_BackGround_Id % this->_BackGround_Music_List.size();
}

void SoundBase::Set_SoundVolume(ESoundEngine_ID SoundEngine_Id, float Volume)
{
	this->_SoundEngine[SoundEngine_Id]->setSoundVolume(Volume);
}

bool SoundBase::Sound_Playing(std::string Wav_File_Location, ESoundEngine_ID SoundEngine_Id)
{
	return this->_SoundEngine[SoundEngine_Id]->isCurrentlyPlaying(Wav_File_Location.c_str());
}

bool SoundBase::Sound_Playing(ESound_WAV Sound_Name, ESoundEngine_ID SoundEngine_Id)
{
	if (Sound_Name == ESound_WAV::SOUND_NO_SOUND)
		return false;
	return this->_SoundEngine[SoundEngine_Id]->isCurrentlyPlaying(this->_Sound_Names[Sound_Name].c_str());
}

bool SoundBase::BackGround_Playing() const
{
	return this->_BackGround_Music_Playing;
}

ESound_WAV SoundBase::Sound_Playing_Id(ESoundEngine_ID SoundEngine_Id)
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

SoundBase::SoundBase() : Tanxl_ClassBase("0.1"), _BackGround_Music_List(),
_BackGround_Music_Playing(false), _Current_BackGround_Id(0)
{
	_SoundEngine[0] = irrklang::createIrrKlangDevice();
	_SoundEngine[1] = irrklang::createIrrKlangDevice();
	this->_SoundEngine[1]->setSoundVolume(0.3f);
}

SoundBase::~SoundBase() 
{
	this->_SoundEngine[0]->drop();
	this->_SoundEngine[1]->drop();
}

SoundBase::SoundBase(const SoundBase&) : Tanxl_ClassBase("0.1"), _BackGround_Music_List(),
_BackGround_Music_Playing(false), _Current_BackGround_Id(0) 
{
	_SoundEngine[0] = irrklang::createIrrKlangDevice();
	_SoundEngine[1] = irrklang::createIrrKlangDevice();
	this->_SoundEngine[1]->setSoundVolume(0.3f);
}

SoundBase& SoundBase::operator=(const SoundBase&) { return *this; }