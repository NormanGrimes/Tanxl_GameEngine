//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-07 16:41
// ��Ϊ�̳�����������ಢ���Ӱ汾��ȡ����
// ���ӽӿ�����������ʾ��Ϣ������
// ���ӷ������Ϸ���ı�

#pragma once

#ifndef _TANXL_GAME_TIPS_
#define _TANXL_GAME_TIPS_

#include <string>

#include "Tanxl_DataBase.h"
#include "Tanxl_EngineBase.h"
#include "Tanxl_FontBase.h"

class GameTips : public Tanxl_ClassBase
{
public:
	static GameTips& GetTipsBase()
	{
		static GameTips* TipBase{ new GameTips };
		return *TipBase;
	}

	void ResetTips(ECurren_Language Language)
	{
		if (Language == ECurren_Language::LANGUAGE_CHINESE)
		{
			Tips[0] = "��ʾ : ��ҵ��߿����ṩ������";
			Tips[1] = "��ʾ : ��W�������Ϸ���������ƶ�";
			Tips[2] = "��ʾ : ��S�������·���������ƶ�";
			Tips[3] = "��ʾ : ע���ɫ�ķ���!";
			Tips[4] = "��ʾ : ��A����������������ƶ�";
			Tips[5] = "��ʾ : ��D�������ҷ���������ƶ�";
			Tips[6] = "��ʾ : ���޷�ͨ����ɫ�ķ���";
			Tips[7] = "��ʾ : ��ɫ����������˺���ͬʱҲ�ṩ���";
		}
		else if (Language == ECurren_Language::LANGUAGE_RUSSIAN)
		{
			Tips[0] = "Zolotoy krug daet pqt' zolotjx monet";
			Tips[1] = "Nazhmite knopku W ili vverx, chtobj peremestit'sq vverx";
			Tips[2] = "Nazhmite knopku S ili vniz, chtobj dvigat'sq vniz";
			Tips[3] = "Ostorozhno, krasnje kvadratj!";
			Tips[4] = "Nazhmite knopku A ili levu�� knopku, chtobj peremestit'sq vlevo";
			Tips[5] = "Nazhmite D ili pravu�� knopku, chtobj dvigat'sq vpravo";
			Tips[6] = "Nel'zq peresekat' sinie kvadratj";
			Tips[7] = "Krasnje kvadratj takzhe mogut dat' monetu";
		}
		else if (Language == ECurren_Language::LANGUAGE_FRENCH)
		{
			Tips[0] = "Le cercle d or donne cinq points";
			Tips[1] = "Appuyez sur le bouton W ou vers le haut pour monter";
			Tips[2] = "Appuyez sur le bouton S ou vers le bas pour descendre";
			Tips[3] = "Attention aux treillis rouges !";
			Tips[4] = "Appuyez sur A ou sur le bouton gauche pour aller vers la gauche";
			Tips[5] = "Appuyez sur le bouton D ou droit pour aller vers la droite";
			Tips[6] = "Vous ne pouvez pas traverser les treillis bleus";
			Tips[7] = "Les treillis rouges peuvent aussi fournir de la monnaie";
		}
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

	const std::string Get_Version()
	{
		return Tanxl_ClassBase::Get_Version();
	}

private:
	GameTips() :_File_Loaded(true), Tanxl_ClassBase("0.1")
	{
		if (Tips_Data.Get_LocalData("Tanxl_Tips"))
			Tips_Data.Print_Data();
		else
			_File_Loaded = false;
	}

	~GameTips() {}
	GameTips(const GameTips&) :_File_Loaded(true), Tanxl_ClassBase("0.1") {}
	GameTips& operator=(const GameTips&) {}

	TANXL_DataBase Tips_Data;

	bool _File_Loaded;
	int _Internal_Count{ 0 };

	std::string Tips[8]
	{
		"Tips : The golden circle provides five gold coins",
		"Tips : Press W or up button to move upward",
		"Tips : Press S or down button to move downward",
		"Tips : Watch out red squares !",
		"Tips : Press A or left button to move leftward",
		"Tips : Press D or right button to move rightward",
		"Tips : You can not cross the blue squares",
		"Tips : Red squares can also provide coin"
	};
};

#endif