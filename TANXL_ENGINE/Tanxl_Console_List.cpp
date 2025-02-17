#pragma once

#include "Tanxl_Console_List.h"

//void Col是原Console_List的核心功能，使用了Linux控制台的指令
void Col(unsigned ColN, bool Under_Line)//设置自定义行的背景颜色
{
	if (ColN == NULL)
		std::cout << "\033[0m";//清除颜色
	else
	{
		if (Under_Line == true)
			std::cout << "\033[7m";
		std::cout << "\033[4;1;m";
		if (((ColN & 0xf0) >> 4) > 0 && ((ColN & 0xf0) >> 4) <= 7)
			std::cout << "\033[3" << ((ColN & 0xf0) >> 4) << "m";
		else if ((ColN & 0xf0) >> 4 == 0);//值为0不作修改
		else//字体颜色: 1红色 2绿色 3橙色 4蓝色 5紫色 6淡蓝 7白色
			std::cout << "\033[3" << rand() % 7 + 1 << "m";
		if ((ColN & 0x0f) > 0 && ((ColN & 0x0f) <= 7))
			std::cout << "\033[4" << (ColN & 0x0f) << "m";
		else if ((ColN & 0x0f) == 0);//值为0不作修改
		else//背景颜色: 1红色 2绿色 3橙色 4蓝色 5紫色 6淡蓝 7白色
			std::cout << "\033[4" << rand() % 7 + 1 << "m";
	}
}
//构造函数
CONSOLE::CONSOLE(std::string NamE, unsigned Space, void(*FunC)())
	:_Selector(0), _Is_Selected(false), _SonList(NULL), _SSpace(Space), _Func(FunC), _Is_Funcwork(true), _Name(NamE), _Page(0)
{
	if (_Func == nullptr)
		this->_Is_Funcwork = false;
}

//添加函数
void CONSOLE::Append_Item(std::string New_Item, unsigned Space, void (*FunC)(), int Depth, int* Ids)
{
	if (Depth == 0)
		this->_SonList.push_back(CONSOLE(New_Item, Space, FunC));
	else
	{
		CONSOLE* CP{ this };
		for (int i{ 0 }; i < Depth; ++i)
			CP = &CP->_SonList.at(Ids[i]);
		CP->_SonList.push_back(CONSOLE(New_Item, Space, FunC));
	}
}

void CONSOLE::Reset_Name(std::string Name)
{
	this->_Name = Name;
}

void CONSOLE::Display(int Depth, unsigned Def_Col, unsigned Real_Sel)
{
	Col();
	bool Is_Line_Need{ false };
	this->_Page = this->_Selector / (_SSpace & 0x00ff);
	for (int i = this->_Page * (_SSpace & 0x00ff); (i < _SonList.size()) && (i < (this->_Page + 1) * static_cast<int>(this->_SSpace & 0x00ff)); ++i)
	{
		for (int j{ Depth }; j > 0; j--)
			std::cout << "\t";
		if (i == this->_Selector)
			Col(Real_Sel);
		else
			Col(Def_Col);
		std::cout << std::setw((this->_SSpace & 0xff0000) >> 16) << this->_SonList.at(i)._Name << std::setw((this->_SSpace & 0x00ff00) >> 8) << " " << std::endl;
		Col();
		if ((this->_SonList.at(i)._SonList.size() == 0) && (this->_Is_Selected == true) && (this->_Selector == i))//在包含子项目为0时自动退出
		{
			if (this->_SonList.at(i)._Is_Funcwork)
				this->_SonList.at(i)._Func();
			this->_Is_Selected = false;
		}
		if ((this->_SonList.at(i)._SonList.size() != 0) && (this->_Is_Selected == true) && (this->_Selector == i))
		{
			std::cout << std::endl;
			this->_SonList.at(i).Display(Depth + 1, ((Def_Col & 0x0f) << 4) + ((Def_Col & 0xf0) >> 4), Real_Sel);
			Is_Line_Need = 1;
		}
		if (!Is_Line_Need)
			std::cout << std::endl;
		if (Is_Line_Need)
			Is_Line_Need = false;
		Col();
	}
}

const std::string CONSOLE::Get_Version()
{
	return this->_Version;
}

void CONSOLE::Display_Once()
{
	static bool Insert{ true };
	bool Cover{ false };
	unsigned* Action_Num{ &Locate()->_Selector };
	bool* Action_Bol{ &Locate()->_Is_Selected };
	size_t List_Size{ Locate()->_SonList.size() };
	while (1)
	{
		system("cls");
		this->Display();
		if (!Cover)
		{
			Action_Num = &Locate()->_Selector;
			Action_Bol = &Locate()->_Is_Selected;
			List_Size = Locate()->_SonList.size();
		}
		else
			Cover = false;
		if (!Insert)
		{
			Action_Num = &Locate(-1)->_Selector;
			Action_Bol = &Locate(-1)->_Is_Selected;
			List_Size = Locate(-1)->_SonList.size();
			Locate(-1)->_Is_Selected = false;
			Insert = true;
			Cover = true;
			continue;
		}
		Insert = Insert_Action(Action_Num, Action_Bol, List_Size);
		break;
	}
}

bool CONSOLE::Insert_Action(unsigned* Action_Num, bool* Action_Bol, size_t List_Size)
{
	char key = _getch();
	if ((key == 'c') || (key == 'C'))//如果输入了大小写的C则返回上一级
	{
		*Action_Bol = false;
		return false;
	}
	if ((key >= 48) && (key <= 57))//判断是否是从零到九的数字 
	{//(static_cast<int>(key - 48) >= 0) && (static_cast<int>(key - 48) <= 9)
		if (key <= List_Size + 48)//如果是，且小于等于选项总数则直接指定这个选项
			*Action_Num = key - 49;
		else
			*Action_Num = static_cast<unsigned>(List_Size) - 1;//如果超出了最大值，则指向最大值
		*Action_Bol = true;
	}
	else if ((key == 'w') || (key == 'W') || (key == 72))//如果输入了大小写的W或者上箭头，则执行MoveUp
		*Action_Num = *Action_Num == 0 ? static_cast<unsigned>(List_Size) - 1 : -- * Action_Num;
	else if ((key == 's') || (key == 'S') || (key == 80))//如果输入了大小写的S或者下箭头，则执行MoveDown
		*Action_Num = *Action_Num == List_Size - 1 ? 0 : ++ * Action_Num;
	else if ((key == 'a') || (key == 'A') || (key == 75))//如果输入了大小写的A或者左箭头，则执行向上翻页
		*Action_Num = *Action_Num - (this->_SSpace & 0x0000ff) < 0 ? 0 : *Action_Num - (this->_SSpace & 0x0000ff);
	else if ((key == 'd') || (key == 'D') || (key == 77))//如果输入了大小写的D或者右箭头，则执行向下翻页
		*Action_Num = *Action_Num + (this->_SSpace & 0x0000ff) > static_cast<unsigned>(List_Size) - 1 ? static_cast<unsigned>(List_Size) - 1 : *Action_Num + (this->_SSpace & 0x0000ff);
	else if (key == '\r')//回车确认
		*Action_Bol = true;
	return true;
}

CONSOLE* CONSOLE::Locate(int Target)
{
	if (Target == 0)
	{
		for (int i{ 0 }; i < this->_SonList.size(); ++i)
		{
			if ((i == this->_Selector) && (this->_Is_Selected == true))
				return this->_SonList.at(i).Locate();
		}
		return this;
	}
	else
	{
		for (int i{ 0 }; i < _SonList.size(); ++i)
		{
			if ((i == this->_Selector) && (this->_Is_Selected == true) && (this->_SonList.at(i)._SonList.size() != 0))
				if (this->_SonList.at(i)._Is_Selected == false)
					return this;
				else
					return this->_SonList.at(i).Locate(-1);
		}
		return this;
	}
}