#pragma once
#include "Tanxl_Engine_Manager.h"
#include <iomanip>
int main()
{
	//Data Function Test

	Tanxl_Engine TGE;

	RandomBase* UIB{ &RandomBase::GetRandomBase() };

	UIB->Suffle_UniData(1);

	std::cout << UIB->GenerateAutoSeed() << std::endl;

	TANXL_DataBase NData;

	remove("Tanxl_Data.usd");

	NData.Set_Internal_Id(0x1322, "TANXL1", "GAME1");
	Data_Link* D4 = new Data_Link(1, "NUMS1 1");
	D4->Append_Data(2, "NUMS1 2");
	D4->Append_Data(3, "NUMS1 3");
	D4->Append_Data(4, "NUMS1 4");
	D4->Append_Data(5, "NUMS1 5");
	NData.Set_Internal_Data(D4, SIMPLE_SET);
	NData.AppendItem(APPENDTO_FILE);

	NData.Set_Internal_Id(0x1022, "TANXL2", "GAME2");
	Data_Link* D5 = new Data_Link(1, "NUMS2 1");
	D5->Append_Data(2, "NUMS2 2");
	D5->Append_Data(3, "NUMS2 3");
	D5->Append_Data(4, "NUMS2 4");
	D5->Append_Data(5, "NUMS2 5");
	D5->Append_Data(6, "NUMS2 6");
	NData.Set_Internal_Data(D5, SIMPLE_SET);
	NData.AppendItem(APPENDTO_FILE);

	NData.Print_Data();

	NData.SortDataBase();

	//Get Instance

	GameStateBase* GSB{ &GameStateBase::Get_StateBase(1, 1) };

	TGE.Engine_State_Compile_Units(20, 10,
		"a-2,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-2,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-1,a-2,a-0,a-0,a-0,a-0,a-0,a-0,a-2,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-2,a-1,a-1,a-1,a-1,a-2,a-0,a-1,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-1,a-0,a-1,a-2,a-0,a-0,a-2,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-2,a-2,a-0,a-1,a-0,a-1,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-1,a-0,a-1,a-0,a-2,a-2,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-2,a-0,a-0,a-2,a-1,a-0,a-1,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-1,a-0,a-2,a-1,a-1,a-1,a-1,a-2,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-2,a-0,a-0,a-0,a-0,a-0,a-0,a-2,a-1,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-2,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-2,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,");

	std::cout << UIB->Generate_State(10, 10) << std::endl;
	std::cout << UIB->Generate_State(10, 10) << std::endl;
	std::cout << UIB->Generate_State(10, 10) << std::endl;
	std::cout << UIB->Generate_State(10, 10) << std::endl;

	remove("Data_Chain_File.usd");
	TGE.Engine_Save_Infinite_State();

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };

	TGE.Engine_Save_Source_Infor("Tanxl Engine VersionMes");

	bool CurrStatus = false;
	bool Appended = false;

	Key_Unit* KU = new Key_Unit(GLFW_KEY_E, &CurrStatus);

	IEB->RegistEvent(KU);

	std::cout << "KU NAME :" << KU->Unit_Name << std::endl;

	TGE.Engine_State_Set_Display(5, 5, 4);
	TGE.Engine_Insert_State_Limit(true);
	TGE.Engine_Adjust_Multi_Set(true, 0.005f, true);

	std::vector<std::string> KeyUnitNames;
	while (1)
	{
		static int Timer = 0;
		Timer++;
		TGE.Engine_Draw_State_Adjust(0);
		if (Timer == 50)
		{
			Timer = 0;
			if (KU->MoveToX == true)
			{
				KU->MoveToX = false;
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
				else
				{
					Appended = false;
					std::cout << "Removing All Temp KeyEvent" << std::endl;

					for (int i = 0; i < KeyUnitNames.size(); i++)
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
}
