#pragma once

#include "Tanxl_SoundBase.h"

SoundBase& SoundBase::GetSoundBase()
{
	static SoundBase* SoundEngine{ new SoundBase() };
	return *SoundEngine;
}

void SoundBase::Play_Sound(std::string Wav_File_Location, ESoundEngine_ID SoundEngine_Id)
{
#if _ENABLE_SOUNDBASE_DEBUG_MODE_
	std::cout << "Play Sound : " << Wav_File_Location << std::endl;
#endif
	this->_SoundEngine[SoundEngine_Id]->play2D(Wav_File_Location.c_str());
}

void SoundBase::Append_BackGround_Music(std::string Wav_File_Location)
{
#if _ENABLE_SOUNDBASE_DEBUG_MODE_
	std::cout << "Append BGM : " << Wav_File_Location << std::endl;
#endif
	this->_BackGround_Music_List.push_back(Wav_File_Location);
}

void SoundBase::Stop_Sound(ESoundEngine_ID SoundEngine_Id)
{
#if _ENABLE_SOUNDBASE_DEBUG_MODE_
	std::cout << "Stop Sound : " << SoundEngine_Id << std::endl;
#endif
	this->_SoundEngine[SoundEngine_Id]->stopAllSounds();

	if (SoundEngine_Id == ESoundEngine_ID::SOUND_ENGINE_BACKGROUND)
		this->_BackGround_Music_Playing = false;
}

void SoundBase::Stop_AllSound()
{
#if _ENABLE_SOUNDBASE_DEBUG_MODE_
	std::cout << "Stop All Sound" << std::endl;
#endif
	this->_SoundEngine[SOUND_ENGINE_EVENT]->stopAllSounds();
	this->_SoundEngine[SOUND_ENGINE_BACKGROUND]->stopAllSounds();

	this->_BackGround_Music_Playing = false;
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
#if _ENABLE_SOUNDBASE_DEBUG_MODE_
	std::cout << "Random BGM Id : " << this->_Current_BackGround_Id << std::endl;
#endif
}

void SoundBase::Set_SoundVolume(ESoundEngine_ID SoundEngine_Id, float Volume)
{
#if _ENABLE_SOUNDBASE_DEBUG_MODE_
	std::cout << "Set SoundEngine " << SoundEngine_Id << " Volume :" << Volume << std::endl;
#endif
	this->_SoundEngine[SoundEngine_Id]->setSoundVolume(Volume);
}

void SoundBase::Notify(int SoundEvent)
{
	this->_SoundCheck.Notify(SoundEvent);
}

bool SoundBase::Sound_Playing(std::string Wav_File_Location, ESoundEngine_ID SoundEngine_Id)
{
#if _ENABLE_SOUNDBASE_DEBUG_MODE_
	std::cout << "Check Sound " << Wav_File_Location << " " << this->_SoundEngine[SoundEngine_Id]->isCurrentlyPlaying(Wav_File_Location.c_str()) << std::endl;
#endif
	return this->_SoundEngine[SoundEngine_Id]->isCurrentlyPlaying(Wav_File_Location.c_str());
}

bool SoundBase::BackGround_Playing() const
{
	return this->_BackGround_Music_Playing;
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

	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_GAME_START, "music/Game_Start.wav", this));
	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_GAME_OVER, "music/Game_Over.wav", this));
	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_TAKE_DAMAGE, "music/Game_Take_Damage.wav", this));
	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_RESTORE_HEALTH, "music/Game_Event_Restore_Health.wav", this));
	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_MOUSE_CLICK, "music/Game_Mouse_Click_Right.wav", this));
	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_MOUSE_CLICK_RIGHT, "music/Game_Mouse_Click_Right.wav", this));
	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_TAKE_COIN, "music/Game_Take_Coin.wav", this));
	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_ACHIEVEMENT, "music/Game_Achievement_Unlock.wav", this));
	_SoundCheck.Add_Observer(new Sound_Observer(SOUND_SECRET_CORE, "music/Game_Event_Secret_Core.wav", this));
}

SoundBase::~SoundBase() 
{
	this->_SoundEngine[0]->drop();
	this->_SoundEngine[1]->drop();
}

SoundBase::SoundBase(const SoundBase&) : Tanxl_ClassBase("0.1"), _BackGround_Music_List(),
_BackGround_Music_Playing(false), _Current_BackGround_Id(0) {}

SoundBase& SoundBase::operator=(const SoundBase&) { return *this; }