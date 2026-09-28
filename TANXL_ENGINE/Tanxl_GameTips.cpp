#pragma once

#include "Tanxl_GameTips.h"

GameTips& GameTips::GetTipsBase()
{
	static GameTips* TipBase{ new GameTips };
	return *TipBase;
}

void GameTips::ResetFonts(ECurren_Language Language)
{
	if (Language == ECurren_Language::LANGUAGE_ENGLISH)
	{
		_Tips.erase(_Tips.begin(), _Tips.end());
		_Tips.push_back(L"Tips : The golden coin provides five coins");
		_Tips.push_back(L"Tips : Press W or up button to move upward");
		_Tips.push_back(L"Tips : Press S or down button to move downward");
		_Tips.push_back(L"Tips : Watch out red squares !");
		_Tips.push_back(L"Tips : Press A or left button to move leftward");
		_Tips.push_back(L"Tips : Press D or right button to move rightward");
		_Tips.push_back(L"Tips : You can't get through the blue mesh blocks");
		_Tips.push_back(L"Tips : Red squares can also provide coin");

		_VersionDisplay = L"TANXL GAME VERSION";
		_GameOverName = L"GAME OVER";
		_PlayerCoinName = L"Coin";
	}
	else if (Language == ECurren_Language::LANGUAGE_CHINESE)
	{
		_Tips.erase(_Tips.begin(), _Tips.end());
		_Tips.push_back(L"提示一 : 金币道具可以提供五个金币");
		_Tips.push_back(L"提示二 : 按W键或者上方向箭向上移动");
		_Tips.push_back(L"提示三 : 按S键或者下方向箭向下移动");
		_Tips.push_back(L"提示四 : 注意红色的方块!");
		_Tips.push_back(L"提示五 : 按A键或者左方向箭向左移动");
		_Tips.push_back(L"提示六 : 按D键或者右方向箭向右移动");
		_Tips.push_back(L"提示七 : 你无法通过蓝色的网状方块");
		_Tips.push_back(L"提示八 : 红色方块在造成伤害的同时也提供金币");

		_VersionDisplay = L"TANXL 版本编号";
		_GameOverName = L"游戏结束";
		_PlayerCoinName = L"金币";
	}
	else if (Language == ECurren_Language::LANGUAGE_RUSSIAN)
	{
		_Tips.erase(_Tips.begin(), _Tips.end());
		_Tips.push_back(L"Советы: Золотой круг дает пять золотых монет");
		_Tips.push_back(L"Советы: Нажмите кнопку W или вверх, чтобы переместиться вверх");
		_Tips.push_back(L"Советы: Нажмите кнопку S или вниз, чтобы двигаться вниз");
		_Tips.push_back(L"Советы: Осторожно, красные квадраты!");
		_Tips.push_back(L"Советы: Нажмите кнопку A или левую кнопку, чтобы переместиться влево");
		_Tips.push_back(L"Советы: Нажмите D или правую кнопку, чтобы двигаться вправо");
		_Tips.push_back(L"Советы: Через синие сетчатые блоки не пройдешь");
		_Tips.push_back(L"Советы: Красные квадраты также могут дать монету");

		_VersionDisplay = L"ВЕРСИЯ ИГРЫ TANXL";
		_GameOverName = L"ИГРА ЗАКОНЧЕНА";
		_PlayerCoinName = L"Монета";
	}
	else if (Language == ECurren_Language::LANGUAGE_FRENCH)
	{
		_Tips.erase(_Tips.begin(), _Tips.end());
		_Tips.push_back(L"Conseils: La pièce d’or fournit cinq pièces");
		_Tips.push_back(L"Conseils : Appuyez sur le bouton W ou haut pour vous déplacer vers le haut");
		_Tips.push_back(L"Conseils : Appuyez sur le bouton S ou bas pour descendre");
		_Tips.push_back(L"Bons plans : Attention aux carrés rouges !");
		_Tips.push_back(L"Astuces : Appuyez sur A ou sur le bouton gauche pour vous déplacer vers la gauche");
		_Tips.push_back(L"Astuces : Appuyez sur D ou bouton droit pour vous déplacer vers la droite");
		_Tips.push_back(L"Conseils : Vous ne pouvez pas passer à travers les blocs de maille bleue");
		_Tips.push_back(L"Conseils : Les carrés rouges peuvent aussi fournir de la monnaie");

		_VersionDisplay = L"Numéro de version de TANXL";
		_GameOverName = L"Fin du jeu";
		_PlayerCoinName = L"argent";
	}
}

std::wstring GameTips::GetTips()
{
	static int Current_Internal_Count{ -1 };
	static std::wstring Last_String;

	if (Current_Internal_Count == _Internal_Count)
		return Last_String;

	Current_Internal_Count = _Internal_Count;
	if (_File_Loaded)
	{
		std::string Data{ Tips_Data->Id_Link_Locate(1, _Internal_Count)->_Data->_Data_Units.at(0)->_Data };
		std::wstring WData{ std::wstring(Data.begin(),Data.end()) };
		Last_String = WData;
		return WData;
	}
	Last_String = _Tips.at(_Internal_Count);
	return _Tips.at(_Internal_Count);
}

std::wstring GameTips::Get_DisplayVersion()
{
	return this->_VersionDisplay;
}

std::wstring GameTips::Get_GameOverName()
{
	return this->_GameOverName;
}

std::wstring GameTips::Get_PlayerCoinName()
{
	return this->_PlayerCoinName;
}

int GameTips::Update_Count()
{
	this->_Internal_Count++;

	if (_File_Loaded)
	{
		if (Tips_Data->Id_Link_Locate(1, _Internal_Count) == nullptr)
			return this->_Internal_Count = 0;
		else
			return this->_Internal_Count;
	}
	return this->_Internal_Count > this->_Tips.size() ? this->_Internal_Count = 0 : this->_Internal_Count;
}

const std::string GameTips::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

GameTips::GameTips() :_File_Loaded(true), Tanxl_ClassBase("0.1"), Tips_Data(new TANXL_DataBase())
{
	if (Tips_Data->Get_LocalData("Tanxl_Tips"))
		Tips_Data->Print_Data();
	else
		_File_Loaded = false;
	this->ResetFonts(LANGUAGE_ENGLISH);
}

GameTips::~GameTips() {}
GameTips::GameTips(const GameTips&) :_File_Loaded(true), Tanxl_ClassBase("0.1"), Tips_Data(new TANXL_DataBase())
{
	this->ResetFonts(LANGUAGE_ENGLISH);
}
GameTips& GameTips::operator=(const GameTips&) { return *this; }