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
	:Selector(0), Is_Selected(false), SonList(NULL), SSpace(Space), Func(FunC), Is_Funcwork(true), Name(NamE),Page(0)
{
	if (Func == NULL)
		Is_Funcwork = false;
}

//��Ӻ���
void CONSOLE::Append_Item(std::string New_Item, unsigned Space, void (*FunC)(), int Depth, int* Ids)
{
	if (Depth == 0)
		SonList.push_back(CONSOLE(New_Item, Space, FunC));
	else
	{
		CONSOLE* CP{ this };
		for (int i = 0; i < Depth; i++)
			CP = &CP->SonList.at(Ids[i]);
		CP->SonList.push_back(CONSOLE(New_Item, Space, FunC));
	}
}

void CONSOLE::Display(int Depth, unsigned Def_Col, unsigned Real_Sel)
{
	Col();
	bool Is_Line_Need{ false };
	Page = this->Selector / (SSpace & 0x00ff);
	for (int i = Page * (SSpace & 0x00ff); i < SonList.size() && i < (Page + 1) * static_cast<int>(SSpace & 0x00ff); i++)
	{
		for (int j = Depth; j > 0; j--)
			std::cout << "\t";
		if (i == Selector)
			Col(Real_Sel);
		else
			Col(Def_Col);
		std::cout << std::setw((SSpace & 0xff0000) >> 16) << SonList.at(i).Name << std::setw((SSpace & 0x00ff00) >> 8) << " " << std::endl;
		Col();
		if (SonList.at(i).SonList.size() == 0 && this->Is_Selected == true && this->Selector == i)//�ڰ�������ĿΪ0ʱ�Զ��˳�
		{
			if (SonList.at(i).Is_Funcwork)
				SonList.at(i).Func();
			this->Is_Selected = false;
		}
		if (SonList.at(i).SonList.size() != 0 && this->Is_Selected == true && this->Selector == i)
		{
			std::cout << std::endl;
			this->SonList.at(i).Display(Depth + 1, (Def_Col & 0x0f) * 16 + (Def_Col & 0xf0) / 16, Real_Sel);
			Is_Line_Need = 1;
		}
		if (!Is_Line_Need)
			std::cout << std::endl;
		if (Is_Line_Need)
			Is_Line_Need = false;
		Col();
	}
}

void CONSOLE::MainLoop(unsigned Def_Col, unsigned Real_Sel)
{
	bool Insert{ true };
	bool Cover{ false };
	int* Action_Num{ &Locate()->Selector };
	bool* Action_Bol{ &Locate()->Is_Selected };
	size_t List_Size{ Locate()->SonList.size() };
	while (1)
	{
		system("cls");
		this->Display();
		if (!Cover)
		{
			Action_Num = &Locate()->Selector;
			Action_Bol = &Locate()->Is_Selected;
			List_Size = Locate()->SonList.size();
		}
		else
			Cover = false;
		if (!Insert)
		{
			Action_Num = &Locate(-1)->Selector;
			Action_Bol = &Locate(-1)->Is_Selected;
			List_Size = Locate(-1)->SonList.size();
			Locate(-1)->Is_Selected = false;
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
		*Action_Num = *Action_Num - static_cast<int>(SSpace & 0x0000ff) < 0 ? 0 : *Action_Num - (SSpace & 0x0000ff);
	else if (key == 'd' || key == 'D' || key == 77)//��������˴�Сд��D�����Ҽ�ͷ����ִ�����·�ҳ
		*Action_Num = *Action_Num + static_cast<int>(SSpace & 0x0000ff) > static_cast<int>(List_Size) - 1 ? static_cast<int>(List_Size) - 1 : *Action_Num + (SSpace & 0x0000ff);
	else if (key == '\r')//�س�ȷ��
		*Action_Bol = true;
	return true;
}

CONSOLE* CONSOLE::Locate(int Target)
{
	if (Target == 0)
	{
		for (int i = 0; i < SonList.size(); i++)
		{
			if (i == Selector && Is_Selected == true)
				return SonList.at(i).Locate();
		}
		return this;
	}
	else
	{
		for (int i = 0; i < SonList.size(); i++)
		{
			if (i == Selector && Is_Selected == true && SonList.at(i).SonList.size() != 0)
				if (SonList.at(i).Is_Selected == false)
					return this;
				else
					return SonList.at(i).Locate(-1);
		}
		return this;
	}
}