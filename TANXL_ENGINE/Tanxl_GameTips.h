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
// 所有涉及显示的字体设为宽字符串
// 修复获取提示接口二次调用错误的问题
// 增加游戏内的法语文本显示功能
// 优化提示类的内存结构
// 重置语言文字接口增加英文选项
// 提示文本使用容器存储
// 修改部分提示文本内容

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

	std::wstring GetTips();

	std::wstring Get_DisplayVersion();

	std::wstring Get_GameOverName();

	std::wstring Get_PlayerCoinName();

	int Update_Count();

	const std::string Get_Version();

private:
	GameTips();

	~GameTips();
	GameTips(const GameTips&);
	GameTips& operator=(const GameTips&);

	TANXL_DataBase* Tips_Data;

	bool _File_Loaded;
	int _Internal_Count{ 0 };

	ECurren_Language _Internal_Language{ LANGUAGE_ENGLISH };

	std::vector<std::wstring> _Tips;

	std::wstring _VersionDisplay{};
	std::wstring _GameOverName{};
	std::wstring _PlayerCoinName{};
};

#endif