#pragma once

#include "Tanxl_SoundBase.h"

SoundBase& SoundBase::GetSoundBase()
{
	static SoundBase* SoundEngine{ new SoundBase() };
	return *SoundEngine;
}

void SoundBase::Play_Sound(std::string Wav_File_Location, int SoundEngine_Id)
{
	this->_SoundEngine[SoundEngine_Id]->play2D(Wav_File_Location.c_str());
}

void SoundBase::Play_Sound(ESound_WAV Sound_Name, int SoundEngine_Id)
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

void SoundBase::Stop_AllSound(int SoundEngine_Id)
{
	this->_SoundEngine[SoundEngine_Id]->stopAllSounds();

	//this->_Current_BackGround_Id = 0;
	this->_BackGround_Music_Playing = false;
	this->_SoundEngine[SoundEngine_Id]->setSoundVolume(1.0f);
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
		this->Play_Sound(this->_BackGround_Music_List.at(this->_Current_BackGround_Id), 1);
		this->_SoundEngine[1]->setSoundVolume(0.3f);
	}

	if (!this->Sound_Playing(this->_BackGround_Music_List.at(this->_Current_BackGround_Id), 1))
	{
		this->_Current_BackGround_Id++;
		this->_Current_BackGround_Id = this->_Current_BackGround_Id % this->_BackGround_Music_List.size();
		this->Play_Sound(this->_BackGround_Music_List.at(this->_Current_BackGround_Id), 1);
		this->_SoundEngine[1]->setSoundVolume(0.3f);
	}
}

void SoundBase::Random_BackGround_Music()
{
	RandomBase* RB{ &RandomBase::GetRandomBase() };
	this->_Current_BackGround_Id = RB->GenerateNum(static_cast<int>(time(0)));
	this->_Current_BackGround_Id = this->_Current_BackGround_Id % this->_BackGround_Music_List.size();
}

bool SoundBase::Sound_Playing(std::string Wav_File_Location, int SoundEngine_Id)
{
	return this->_SoundEngine[SoundEngine_Id]->isCurrentlyPlaying(Wav_File_Location.c_str());
}

bool SoundBase::Sound_Playing(ESound_WAV Sound_Name, int SoundEngine_Id)
{
	if (Sound_Name == ESound_WAV::SOUND_NO_SOUND)
		return false;
	return this->_SoundEngine[SoundEngine_Id]->isCurrentlyPlaying(this->_Sound_Names[Sound_Name].c_str());
}

bool SoundBase::BackGround_Playing() const
{
	return this->_BackGround_Music_Playing;
}

ESound_WAV SoundBase::Sound_Playing_Id(int SoundEngine_Id)
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
}

SoundBase& SoundBase::operator=(const SoundBase&) { return *this; }