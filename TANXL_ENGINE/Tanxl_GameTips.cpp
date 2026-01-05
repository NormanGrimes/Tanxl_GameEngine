#pragma once

#include "Tanxl_GameTips.h"

GameTips& GameTips::GetTipsBase()
{
	static GameTips* TipBase{ new GameTips };
	return *TipBase;
}

void GameTips::ResetFonts(ECurren_Language Language)
{
	if (Language == ECurren_Language::LANGUAGE_CHINESE)
	{
		_Tips[0] = "提示一 : 金币道具可以提供五个金币";
		_Tips[1] = "提示二 : 按W键或者上方向箭向上移动";
		_Tips[2] = "提示三 : 按S键或者下方向箭向下移动";
		_Tips[3] = "提示四 : 注意红色的方块!";
		_Tips[4] = "提示五 : 按A键或者左方向箭向左移动";
		_Tips[5] = "提示六 : 按D键或者右方向箭向右移动";
		_Tips[6] = "提示七 : 你无法通过红色的方块";
		_Tips[7] = "提示八 : 红色方块在造成伤害的同时也提供金币";

		_VersionDisplay = "TANXL 版本编号";
		_GameOverName = "游戏结束";
		_PlayerCoinName = "金币";
	}
	else if (Language == ECurren_Language::LANGUAGE_RUSSIAN)
	{
		_Tips[0] = "Советы: Золотой круг дает пять золотых монет";
		_Tips[1] = "Советы: Нажмите кнопку W или вверх, чтобы переместиться вверх";
		_Tips[2] = "Советы: Нажмите кнопку S или вниз, чтобы двигаться вниз";
		_Tips[3] = "Советы: Осторожно, красные квадраты!";
		_Tips[4] = "Советы: Нажмите кнопку A или левую кнопку, чтобы переместиться влево";
		_Tips[5] = "Советы: Нажмите D или правую кнопку, чтобы двигаться вправо";
		_Tips[6] = "Советы: Нельзя пересекать синие квадраты";
		_Tips[7] = "Советы: Красные квадраты также могут дать монету";

		_VersionDisplay = "ВЕРСИЯ ИГРЫ TANXL";
		_GameOverName = "ИГРА ЗАКОНЧЕНА";
		_PlayerCoinName = "Монета";
	}
	else if (Language == ECurren_Language::LANGUAGE_FRENCH)
	{
		_Tips[0] = "Le cercle d or donne cinq points";
		_Tips[1] = "Appuyez sur le bouton W ou vers le haut pour monter";
		_Tips[2] = "Appuyez sur le bouton S ou vers le bas pour descendre";
		_Tips[3] = "Attention aux treillis rouges !";
		_Tips[4] = "Appuyez sur A ou sur le bouton gauche pour aller vers la gauche";
		_Tips[5] = "Appuyez sur le bouton D ou droit pour aller vers la droite";
		_Tips[6] = "Vous ne pouvez pas traverser les treillis bleus";
		_Tips[7] = "Les treillis rouges peuvent aussi fournir de la monnaie";

		_VersionDisplay = "JEU TANXL VERSION";
		_GameOverName = "FIN DU JEU";
		_PlayerCoinName = "Pièce";
	}
}

std::string GameTips::GetTips()
{
	static int Current_Internal_Count{ -1 };
	static std::string Last_String;

	if (Current_Internal_Count == _Internal_Count)
		return Last_String;

	Current_Internal_Count = _Internal_Count;
	if (_File_Loaded)
		return Last_String = Tips_Data.Id_Link_Locate(1, _Internal_Count)->_Data->_Data_Units.at(0)->_Data;
	return Last_String = _Tips[_Internal_Count];
}

std::string GameTips::Get_DisplayVersion()
{
	return this->_VersionDisplay;
}

std::string GameTips::Get_GameOverName()
{
	return this->_GameOverName;
}

std::string GameTips::Get_PlayerCoinName()
{
	return this->_PlayerCoinName;
}

int GameTips::Update_Count()
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

const std::string GameTips::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

GameTips::GameTips() :_File_Loaded(true), Tanxl_ClassBase("0.1")
{
	if (Tips_Data.Get_LocalData("Tanxl_Tips"))
		Tips_Data.Print_Data();
	else
		_File_Loaded = false;
}

GameTips::~GameTips() {}
GameTips::GameTips(const GameTips&) :_File_Loaded(true), Tanxl_ClassBase("0.1") {}
GameTips& GameTips::operator=(const GameTips&) { return *this; }