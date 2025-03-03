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
	this->_SoundEngine->play2D(this->Sound_Names[Sound_Name].c_str());
}

const std::string SoundBase::Get_Version()
{
	return this->_Version;
}

SoundBase::SoundBase() :_SoundEngine(irrklang::createIrrKlangDevice()) {}
SoundBase::~SoundBase() { this->_SoundEngine->drop(); }
SoundBase::SoundBase(const SoundBase&) :_SoundEngine(irrklang::createIrrKlangDevice()) {};
SoundBase& SoundBase::operator=(const SoundBase&) { return *this; };