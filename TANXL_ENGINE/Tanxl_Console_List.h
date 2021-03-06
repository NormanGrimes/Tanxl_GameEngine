//_VERSION_1_5++_Final UPDATE LOG
// LAST_UPDATE 2022-05-01 15:28
// 调整添加物品的输入序列

#ifndef TANXL_CONSOLE_LIST
#define TANXL_CONSOLE_LIST

#ifndef IOSTREAM//检查是否已经包含IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR//检查是否已经包含VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef CONIO_H//检查是否已经包含CONIO_H
#define CONIO_H
#include <conio.h>
#endif

#ifndef IOMANIP//检查是否已经包含IOMANIP
#define IOMANIP
#include <iomanip>
#endif

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
class CONSOLE
{
public:
	explicit CONSOLE(std::string Name = "UNdefined", unsigned Space = 0x171109, void(*FunC)() = NULL);

	void Display(int Depth = 0, unsigned Def_Col = FONT_COLOR_WHITE | BACK_COLOR_RED, unsigned Real_Sel = FONT_COLOR_WHITE | BACK_COLOR_PURPLE);

	void MainLoop(unsigned Def_Col = FONT_COLOR_WHITE | BACK_COLOR_RED, unsigned Real_Sel = FONT_COLOR_WHITE | BACK_COLOR_PURPLE);

	void Append_Item(std::string New_Item, unsigned Space = 0x171109, void(*FunC)() = NULL, int Depth = 0, int* Ids = 0);

private:

	bool Insert_Action(int* Action_Num, bool* Action_Bol, size_t List_Size);

	CONSOLE* Locate(int Target = 0);

	std::string Name;

	int Selector;
	int Page;
	bool Is_Selected;
	bool Is_Funcwork;

	std::vector<CONSOLE>SonList;

	void (*Func)();

	unsigned SSpace;// { 0x171109 }选项和标题的空格数 AA-BB-CC AA左空格 BB右空格 CC页面物品限制数量
};
#endif