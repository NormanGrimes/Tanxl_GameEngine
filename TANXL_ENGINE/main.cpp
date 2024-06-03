
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

	while (1)
	{
		TGE.Engine_Insert_State_Update();//Key Insert

		TGE.Engine_Draw_State_Adjust(0);//Draw Once

		if (KU->MoveToY == true)
		{
			if (Appended == false)
			{
				Appended = true;
				TGE.Engine_Insert_Adjust_Speed(0, 8, 0.01);
			}
		}
		else
		{
			if (Appended == true)
			{
				Appended = false;
				TGE.Engine_Insert_Adjust_Speed(0, 8, -0.01);
			}
		}
	}
}
