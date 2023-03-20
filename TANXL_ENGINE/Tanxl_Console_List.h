//_VERSION_1_7_ UPDATE LOG
// LAST_UPDATE 2022-11-17 00:30
// Display�ӿ�ȥ������Ҫ����ɫ�������

#pragma once

#ifndef IOSTREAM//����Ƿ��Ѿ�����IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR//����Ƿ��Ѿ�����VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef CONIO_H//����Ƿ��Ѿ�����CONIO_H
#define CONIO_H
#include <conio.h>
#endif

#ifndef IOMANIP//����Ƿ��Ѿ�����IOMANIP
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

//void Col��ԭConsole_List�ĺ��Ĺ��ܣ�ʹ����Linux����̨��ָ��
void Col(unsigned ColN = NULL, bool Under_Line = false);//�����Զ����еı�����ɫ
//��Ʒ��
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

	std::string _Name;

	int _Selector;
	int _Page;
	bool _Is_Selected;
	bool _Is_Funcwork;

	std::vector<CONSOLE> _SonList;

	void (*_Func)();

	unsigned _SSpace;// { 0x171109 }ѡ��ͱ���Ŀո��� AA-BB-CC AA��ո� BB�ҿո� CCҳ����Ʒ��������
};