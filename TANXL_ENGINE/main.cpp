﻿#pragma once

#include "Tanxl_Engine_Manager.h"
#include <iomanip>
int main()
{
	//Data Function Test

	Tanxl_Engine TGE;
	CONSOLE TCL;

	TCL.Append_Item("New Item");
	TCL.Append_Item("Sec Item");

	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };
	std::cout << "Generate : " << UIB->Generate() << std::endl;

	TANXL_DataBase NData(true);
	unsigned n = 0x10101010, i = 10;
	while (i--)
	{
		if (i % 10 != 0)
			n++;
		else
			n += 0x01000000;

		if ((n & 0x0f000000) == 0x0f000000)
			n -= 0x0f000000;

		if ((n & 0xf0000000) == 0xf0000000)
			n -= 0xf0000000;

		//std::cout << "Updating : " << std::setbase(16) << n << std::endl;
		NData.Set_Instance(n, "Updating" + std::to_string(n));
		std::cout << NData;
		NData.AppendItem(false);
	}
	NData.Print_Data();

	//Get Instance

	GameStateBase* GSB{ &GameStateBase::Get_StateBase(1, 1) };

	/*TGE.Engine_State_Compile_Uints(
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,");*/

	TGE.Engine_State_Compile_Uints(10, 10,
		"a-2,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-2,"
		"a-1,a-2,a-0,a-0,a-0,a-0,a-0,a-0,a-2,a-1,"
		"a-1,a-0,a-2,a-1,a-1,a-1,a-1,a-2,a-0,a-1,"
		"a-1,a-0,a-1,a-2,a-0,a-0,a-2,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-2,a-2,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-2,a-2,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-2,a-0,a-0,a-2,a-1,a-0,a-1,"
		"a-1,a-0,a-2,a-1,a-1,a-1,a-1,a-2,a-0,a-1,"
		"a-1,a-2,a-0,a-0,a-0,a-0,a-0,a-0,a-2,a-1,"
		"a-2,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-2,");

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };

	bool CurrStatus = false;
	bool Appended = false;

	Key_Unit* KU = new Key_Unit(GLFW_KEY_E, &CurrStatus);

	IEB->RegistEvent(KU);
	OpenGL_Draw* OGD{ &OpenGL_Draw::GetOpenGLBase() };
	OGD->Set_PreLoad(5);

	TGE.Engine_State_Set_Display(5, 5);
	TGE.Engine_Insert_State_Limit(true);
	TGE.Engine_Adjust_Multi_Set(true, 0.005f, true);
	
	//system("cls");

	while (1)
	{
		static int First = 0;
		static int Timer = 0;
		Timer++;
		//std::cout << Appended << KU->MoveToX;
		OGD->Render_Once(GSB);
		if (Timer == 50)
		{
			Timer = 0;
			if (KU->MoveToX == true)
			{
				First++;
				if (First == 1)
				{
					Key_Unit MOVE_UP = Key_Unit(GLFW_KEY_UP, false, true, 0.01);
					IEB->RegistEvent(&MOVE_UP);
					MOVE_UP = Key_Unit(GLFW_KEY_W, false, true, 0.01);
					IEB->RegistEvent(&MOVE_UP);

					Key_Unit MOVE_LEFT = Key_Unit(GLFW_KEY_LEFT, true, false, -0.01);
					IEB->RegistEvent(&MOVE_LEFT);
					MOVE_LEFT = Key_Unit(GLFW_KEY_A, true, false, -0.01);
					IEB->RegistEvent(&MOVE_LEFT);

					Key_Unit MOVE_RIGHT = Key_Unit(GLFW_KEY_RIGHT, true, false, 0.01);
					IEB->RegistEvent(&MOVE_RIGHT);
					MOVE_RIGHT = Key_Unit(GLFW_KEY_D, true, false, 0.01);
					IEB->RegistEvent(&MOVE_RIGHT);

					Key_Unit MOVE_DOWN = Key_Unit(GLFW_KEY_DOWN, false, true, -0.01);
					IEB->RegistEvent(&MOVE_DOWN);
					MOVE_DOWN = Key_Unit(GLFW_KEY_S, false, true, -0.01);
					IEB->RegistEvent(&MOVE_DOWN);
				}
				Appended = true;
			}
			else
			{
				First = 0;
				if (Appended)
				{
					Appended = false;
					int i = 8;
					while (i > 0)
					{
						i--;
						IEB->RemoveEvent();
					}
				}
			}
		}
	}
}
