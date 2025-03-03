//_VERSION_1_8_ UPDATE LOG
// LAST_UPDATE 2023-01-05 16:44
// Display_Once改为非阻塞式（暂时屏蔽Insert_Action函数）
// 增加版本变量与获取接口
// 输入功能调整为OpenGL输入（不稳定，测试中）
// 回退输入操作方面的改动
// 指针初始化nullptr取代NULL
// 移除未使用的私有成员
// 代码整理优化
// 修改选项成员为无符号数
// 增加重新设置选项名称的功能
// 改为继承自引擎基础类

#pragma once

#ifndef _TANXL_CONSOLE_LIST_
#define _TANXL_CONSOLE_LIST_

#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>

#include "Tanxl_EngineBase.h"

enum EFont_Color
{
	FONT_UNDEFINED       = 0x00,
	FONT_COLOR_RED       = 0x10,
	FONT_COLOR_GREEN     = 0x20,
	FONT_COLOR_ORANGE    = 0x30,
	FONT_COLOR_BLUE      = 0x40,
	FONT_COLOR_PURPLE    = 0x50,
	FONT_COLOR_LIGHTBLUE = 0x60,
	FONT_COLOR_WHITE     = 0x70
};

enum EBack_Color
{
	BACK_UNDEFINED       = 0x00,
	BACK_COLOR_RED       = 0x01,
	BACK_COLOR_GREEN     = 0x02,
	BACK_COLOR_ORANGE    = 0x03,
	BACK_COLOR_BLUE      = 0x04,
	BACK_COLOR_PURPLE    = 0x05,
	BACK_COLOR_LIGHTBLUE = 0x06,
	BACK_COLOR_WHITE     = 0x07
};

//void Col是原Console_List的核心功能，使用了Linux控制台的指令
void Col(unsigned ColN = NULL, bool Under_Line = false);//设置自定义行的背景颜色
//物品类
class CONSOLE : public Tanxl_ClassBase
{
public:
	explicit CONSOLE(std::string Name = "UNdefined", unsigned Space = 0x171109, void(*FunC)() = nullptr);

	const std::string Get_Version();

	void Display_Once();

	void Append_Item(std::string New_Item, unsigned Space = 0x171109, void(*FunC)() = nullptr, int Depth = 0, int* Ids = nullptr);

	void Reset_Name(std::string Name);

private:
	void Display(int Depth = 0, unsigned Def_Col = FONT_COLOR_WHITE | BACK_COLOR_RED, unsigned Real_Sel = FONT_COLOR_WHITE | BACK_COLOR_PURPLE);

	bool Insert_Action(unsigned* Action_Num, bool* Action_Bol, size_t List_Size);

	CONSOLE* Locate(int Target = 0);

	// _Name 选项当前显示的字符串
	std::string _Name;
	// _Selector 用于记录当前列表指向的选项序号
	unsigned _Selector;
	// _Page 用于记录当前指定的页面序号
	int _Page;
	// _Is_Selected 用于记录当前是否已选定此选项
	bool _Is_Selected;
	// _Is_Funcwork 记录该选项是否绑定了可执行的函数
	bool _Is_Funcwork;

	std::vector<CONSOLE> _SonList;

	void (*_Func)();

	unsigned _SSpace;// { 0x171109 }选项和标题的空格数 AA-BB-CC AA左空格 BB右空格 CC页面物品限制数量
};

#endif