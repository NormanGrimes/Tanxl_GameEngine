//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-07 16:41
// 改为继承自引擎基础类并增加版本获取功能
// 增加接口用于重置提示信息的语言
// 增加法语的游戏内文本
// 修改俄语文本的格式
// 增加游戏其他信息的多语言获取接口
// 重制提示语言接口改为重制所有相关语言字符
// 加入到引擎分类中
// 修复一个可能导致编译失败的问题

#pragma once

#ifndef _TANXL_GAME_TIPS_
#define _TANXL_GAME_TIPS_

#include <string>

#include "Tanxl_DataBase.h"
#include "Tanxl_EngineBase.h"

class GameTips : public Tanxl_ClassBase
{
public:
	static GameTips& GetTipsBase();

	void ResetFonts(ECurren_Language Language);

	std::string GetTips();

	std::string Get_DisplayVersion();

	std::string Get_GameOverName();

	std::string Get_PlayerCoinName();

	int Update_Count();

	const std::string Get_Version();

private:
	GameTips();

	~GameTips();
	GameTips(const GameTips&);
	GameTips& operator=(const GameTips&);

	TANXL_DataBase Tips_Data;

	bool _File_Loaded;
	int _Internal_Count{ 0 };

	std::string _Tips[8]
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

	std::string _VersionDisplay{ "TANXL GAME VERSION" };
	std::string _GameOverName{ "GAME OVER" };
	std::string _PlayerCoinName{ "Coin" };
};

#endif