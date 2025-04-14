//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-07 16:41

#pragma once

#ifndef _TANXL_GAME_TIPS_
#define _TANXL_GAME_TIPS_

#include <string>
#include "Tanxl_DataBase.h"

class GameTips
{
public:
	static GameTips& GetTipsBase()
	{
		static GameTips* TipBase{ new GameTips };
		return *TipBase;
	}

	std::string GetTips()
	{
		static int Current_Internal_Count = -1;
		static std::string Last_String;

		if (Current_Internal_Count == _Internal_Count)
			return Last_String;

		Current_Internal_Count = _Internal_Count;
		if (_File_Loaded)
			return Last_String = Tips_Data.Id_Link_Locate(1, _Internal_Count)->_Data->_Data_Units.at(0)->_Data;
		return Last_String = Tips[_Internal_Count];
	}

	int Update_Count()
	{
		this->_Internal_Count++;

		if (_File_Loaded)
		{
			if (Tips_Data.Id_Link_Locate(1, _Internal_Count) == nullptr)
				return this->_Internal_Count = 0;
			else
				return this->_Internal_Count;
		}
		return this->_Internal_Count > 7 ? this->_Internal_Count = 0 : this->_Internal_Count;
	}

private:
	GameTips() :_File_Loaded(true)
	{
		if (Tips_Data.Get_LocalData("Tanxl_Tips"))
			Tips_Data.Print_Data();
		else
			_File_Loaded = false;
	}

	~GameTips() {}
	GameTips(const GameTips&) :_File_Loaded(true) {}
	GameTips& operator=(const GameTips&) {}

	TANXL_DataBase Tips_Data;

	bool _File_Loaded;
	int _Internal_Count{ 0 };

	std::string Tips[8]
	{
		"Tips : Golden square can restore your health",
		"Tips : Press W or up button to move upward",
		"Tips : Press S or down button to move downward",
		"Tips : Watch out red squares !",
		"Tips : Press A or left button to move leftward",
		"Tips : Press D or right button to move rightward",
		"Tips : You can not cross the blue squares",
		"Tips : Red squares can provide coins"
	};
};

#endif