﻿
//████████╗  █████╗   ███╗      ██╗ ██╗    ██╗ ██╗
//╚══██╔══╝██╔══██╗ ████╗    ██║ ╚██╗██╔╝ ██║
//      ██║      ███████║ ██╔██╗  ██║   ╚███╔╝   ██║
//      ██║      ██╔══██║ ██║╚██╗██║   ██╔██╗   ██║
//      ██║      ██║    ██║ ██║  ╚████║ ██╔╝  ██╗ ███████╗
//      ╚═╝      ╚═╝    ╚═╝ ╚═╝    ╚═══╝ ╚═╝    ╚═╝ ╚══════╝


#pragma once

#include "Tanxl_Engine_Manager.h"

int main()
{	
	Tanxl_Engine TGE;

	TGE.Engine_Check_Engine_Status();

	TGE.Engine_Save_Infinite_State(true, 16, 4, 4);

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };

	TGE.Engine_Save_Source_Infor("Tanxl Engine SystemInfor");

	bool Appended = false;

	Key_Unit* KU = new Key_Unit(GLFW_KEY_E);

	IEB->RegistEvent(KU);

	std::cout << "KU NAME :" << KU->Unit_Name << std::endl;

	TGE.Engine_State_Set_Display(4, 4, 4);
	TGE.Engine_Insert_State_Limit(true);
	TGE.Engine_Adjust_Multi_Set(true, 0.005f, true);
	
	TGE.Engine_State_Set_Begin(5, true,
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"b-1,b-0,b-1,b-0,b-2,b-2,b-0,b-1,b-0,b-1,"
		"b-1,b-0,b-1,b-0,b-2,b-2,b-0,b-1,b-0,b-1,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,");

	std::vector<std::string> KeyUnitNames;

	while (1)
	{
		TGE.Engine_Insert_State_Update();//Key Insert

		TGE.Engine_Draw_State_Adjust(0);//Draw Once

		if (KU->MoveToY == true)
		{
			if (Appended == false)
			{
				KeyUnitNames.push_back(TGE.Engine_Insert_Regist_Move(GLFW_KEY_UP, false, true, 0.01));
				std::cout << "APPEND NAME :" << KeyUnitNames.back() << std::endl;
				KeyUnitNames.push_back(TGE.Engine_Insert_Regist_Move(GLFW_KEY_W, false, true, 0.01));
				std::cout << "APPEND NAME :" << KeyUnitNames.back() << std::endl;

				KeyUnitNames.push_back(TGE.Engine_Insert_Regist_Move(GLFW_KEY_LEFT, true, false, -0.01));
				std::cout << "APPEND NAME :" << KeyUnitNames.back() << std::endl;
				KeyUnitNames.push_back(TGE.Engine_Insert_Regist_Move(GLFW_KEY_A, true, false, -0.01));
				std::cout << "APPEND NAME :" << KeyUnitNames.back() << std::endl;

				KeyUnitNames.push_back(TGE.Engine_Insert_Regist_Move(GLFW_KEY_RIGHT, true, false, 0.01));
				std::cout << "APPEND NAME :" << KeyUnitNames.back() << std::endl;
				KeyUnitNames.push_back(TGE.Engine_Insert_Regist_Move(GLFW_KEY_D, true, false, 0.01));
				std::cout << "APPEND NAME :" << KeyUnitNames.back() << std::endl;

				KeyUnitNames.push_back(TGE.Engine_Insert_Regist_Move(GLFW_KEY_DOWN, false, true, -0.01));
				std::cout << "APPEND NAME :" << KeyUnitNames.back() << std::endl;
				KeyUnitNames.push_back(TGE.Engine_Insert_Regist_Move(GLFW_KEY_S, false, true, -0.01));
				std::cout << "APPEND NAME :" << KeyUnitNames.back() << std::endl;

				Appended = true;
			}
		}
		else
		{
			if (Appended == true)
			{
				Appended = false;
				std::cout << "Removing All Temp KeyEvent" << std::endl;

				for (int i{ 0 }; i < KeyUnitNames.size(); i++)
				{
					std::cout << "DELETE NAME :" << KeyUnitNames.at(i) << std::endl;
					if (IEB->RemoveEvent(KeyUnitNames.at(i)))
						std::cout << "Successfully REMOVE :" << i << std::endl;
					else
						std::cout << "Delete Fail !" << std::endl;
				}
				KeyUnitNames.erase(KeyUnitNames.begin(), KeyUnitNames.end());
				KeyUnitNames.clear();
			}
		}
	}
}
