#pragma once

#include "Tanxl_Console_List.h"

//void Col��ԭConsole_List�ĺ��Ĺ��ܣ�ʹ����Linux����̨��ָ��
void Col(unsigned ColN, bool Under_Line)//�����Զ����еı�����ɫ
{
	if (ColN == NULL)std::cout << "\033[0m";//�����ɫ
	else
	{
		if (Under_Line == true)
			std::cout << "\033[7m";
		std::cout << "\033[4;1;m";
		if (((ColN & 0xf0) >> 4) > 0 && ((ColN & 0xf0) >> 4) <= 7)
			std::cout << "\033[3" << ((ColN & 0xf0) >> 4) << "m";
		else if ((ColN & 0xf0) >> 4 == 0);//ֵΪ0�����޸�
		else//������ɫ: 1��ɫ 2��ɫ 3��ɫ 4��ɫ 5��ɫ 6���� 7��ɫ
			std::cout << "\033[3" << rand() % 7 + 1 << "m";
		if ((ColN & 0x0f) > 0 && ((ColN & 0x0f) <= 7))
			std::cout << "\033[4" << (ColN & 0x0f) << "m";
		else if ((ColN & 0x0f) == 0);//ֵΪ0�����޸�
		else//������ɫ: 1��ɫ 2��ɫ 3��ɫ 4��ɫ 5��ɫ 6���� 7��ɫ
			std::cout << "\033[4" << rand() % 7 + 1 << "m";
	}
}
//���캯��
CONSOLE::CONSOLE(std::string NamE, unsigned Space, void(*FunC)())
	:_Selector(0), _Is_Selected(false), _SonList(NULL), _SSpace(Space), _Func(FunC), _Is_Funcwork(true), _Name(NamE), _Page(0)
{
	if (_Func == NULL)
		_Is_Funcwork = false;
}

//��Ӻ���
void CONSOLE::Append_Item(std::string New_Item, unsigned Space, void (*FunC)(), int Depth, int* Ids)
{
	if (Depth == 0)
		_SonList.push_back(CONSOLE(New_Item, Space, FunC));
	else
	{
		CONSOLE* CP{ this };
		for (int i = 0; i < Depth; i++)
			CP = &CP->_SonList.at(Ids[i]);
		CP->_SonList.push_back(CONSOLE(New_Item, Space, FunC));
	}
}

void CONSOLE::Display(int Depth, unsigned Def_Col, unsigned Real_Sel)
{
	bool Is_Line_Need{ false };
	_Page = this->_Selector / (_SSpace & 0x00ff);
	for (int i = _Page * (_SSpace & 0x00ff); i < _SonList.size() && i < (_Page + 1) * static_cast<int>(_SSpace & 0x00ff); i++)
	{
		for (int j = Depth; j > 0; j--)
			std::cout << "\t";
		if (i == _Selector)
			Col(Real_Sel);
		else
			Col(Def_Col);
		std::cout << std::setw((_SSpace & 0xff0000) >> 16) << _SonList.at(i)._Name << std::setw((_SSpace & 0x00ff00) >> 8) << " " << std::endl;
		Col();
		if (_SonList.at(i)._SonList.size() == 0 && this->_Is_Selected == true && this->_Selector == i)//�ڰ�������ĿΪ0ʱ�Զ��˳�
		{
			if (_SonList.at(i)._Is_Funcwork)
				_SonList.at(i)._Func();
			this->_Is_Selected = false;
		}
		if (_SonList.at(i)._SonList.size() != 0 && this->_Is_Selected == true && this->_Selector == i)
		{
			std::cout << std::endl;
			this->_SonList.at(i).Display(Depth + 1, (Def_Col & 0x0f) * 16 + (Def_Col & 0xf0) / 16, Real_Sel);
			Is_Line_Need = 1;
		}
		if (!Is_Line_Need)
			std::cout << std::endl;
		if (Is_Line_Need)
			Is_Line_Need = false;
	}
}

void CONSOLE::MainLoop(unsigned Def_Col, unsigned Real_Sel)
{
	bool Insert{ true };
	bool Cover{ false };
	int* Action_Num{ &Locate()->_Selector };
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
	}
}

bool CONSOLE::Insert_Action(int* Action_Num, bool* Action_Bol, size_t List_Size)
{
	char key = _getch();
	if (key == 'c' || key == 'C')//��������˴�Сд��C�򷵻���һ��
	{
		*Action_Bol = false;
		return false;
	}
	if (static_cast<int>(key - 48) >= 0 && static_cast<int>(key - 48) <= 9)//�ж��Ƿ��Ǵ��㵽�ŵ�����
	{
		if (static_cast<int>(key - 48) <= static_cast<int>(List_Size))//����ǣ���С�ڵ���ѡ��������ֱ��ָ�����ѡ��
			*Action_Num = static_cast<int>(key - 48) - 1;
		else
			*Action_Num = static_cast<int>(List_Size) - 1;//������������ֵ����ָ�����ֵ
		*Action_Bol = true;
	}
	else if (key == 'w' || key == 'W' || key == 72)//��������˴�Сд��W�����ϼ�ͷ����ִ��MoveUp
		*Action_Num = *Action_Num == 0 ? static_cast<int>(List_Size) - 1 : -- * Action_Num;
	else if (key == 's' || key == 'S' || key == 80)//��������˴�Сд��S�����¼�ͷ����ִ��MoveDown
		*Action_Num = *Action_Num == static_cast<int>(List_Size) - 1 ? 0 : ++ * Action_Num;
	else if (key == 'a' || key == 'A' || key == 75)//��������˴�Сд��A�������ͷ����ִ�����Ϸ�ҳ
		*Action_Num = *Action_Num - static_cast<int>(_SSpace & 0x0000ff) < 0 ? 0 : *Action_Num - (_SSpace & 0x0000ff);
	else if (key == 'd' || key == 'D' || key == 77)//��������˴�Сд��D�����Ҽ�ͷ����ִ�����·�ҳ
		*Action_Num = *Action_Num + static_cast<int>(_SSpace & 0x0000ff) > static_cast<int>(List_Size) - 1 ? static_cast<int>(List_Size) - 1 : *Action_Num + (_SSpace & 0x0000ff);
	else if (key == '\r')//�س�ȷ��
		*Action_Bol = true;
	return true;
}

CONSOLE* CONSOLE::Locate(int Target)
{
	if (Target == 0)
	{
		for (int i = 0; i < _SonList.size(); i++)
		{
			if (i == _Selector && _Is_Selected == true)
				return _SonList.at(i).Locate();
		}
		return this;
	}
	else
	{
		for (int i = 0; i < _SonList.size(); i++)
		{
			if (i == _Selector && _Is_Selected == true && _SonList.at(i)._SonList.size() != 0)
				if (_SonList.at(i)._Is_Selected == false)
					return this;
				else
					return _SonList.at(i).Locate(-1);
		}
		return this;
	}
}