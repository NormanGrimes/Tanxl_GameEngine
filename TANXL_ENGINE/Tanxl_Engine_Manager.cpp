#include "Tanxl_Engine_Manager.h"

Tanxl_Engine::Tanxl_Engine() :Tanxl_Engine_Console_List(new CONSOLE),
Tanxl_Engine_DataBase(new TANXL_DataBase()),
Tanxl_Engine_GameEvent(&GameEventBase::GetEventBase()),
Tanxl_Engine_GameState(&GameStateBase::Get_StateBase(5, 5)),
Tanxl_Engine_OpenGL_Draw(&OpenGL_Draw::GetOpenGLBase()),
Tanxl_Engine_InsertBase(&InsertEventBase::GetInsertBase()),
Tanxl_Engine_RandomBase(&RandomBase::GetRandomBase())
{
	
	if (!this->Tanxl_Engine_Console_List ||
		!this->Tanxl_Engine_DataBase     ||
		!this->Tanxl_Engine_GameEvent    ||
		!this->Tanxl_Engine_GameState    ||
		!this->Tanxl_Engine_OpenGL_Draw  ||
		!this->Tanxl_Engine_InsertBase   ||
		!this->Tanxl_Engine_RandomBase)
	{
		std::cout << "Fail to start Engine !" << std::endl;
		this->_Engine_Status = 1;
	}

#if _STEAM_ALPHA_TEST_EDITION_
	if (SteamAPI_RestartAppIfNecessary(1929530))
		std::cout << "Fail to init SteamAPI_RestartAppIfNecessary(1929530) !" << std::endl;
	if (!SteamAPI_Init())
		std::cout << "Fail to init Steam API !" << std::endl;
	else
	{
		std::cout << "Current user Name :" << SteamFriends()->GetPersonaName() << std::endl;
		std::cout << "Current user State :" << SteamFriends()->GetPersonaState() << std::endl;
		std::cout << "Current user SteamId :" << SteamApps()->GetAppOwner().GetAccountID() << std::endl;
		std::cout << "Current user VAC Status :" << SteamApps()->BIsVACBanned() << std::endl;
	}
#endif
}

unsigned Tanxl_Engine::Check_Engine_Status()
{
	return this->_Engine_Status;//0 正常运行 1 初始化失败
}

void Tanxl_Engine::Engine_State_Set_Display(int Width, int Height, int PreLoads)
{
	static int ReservWidth{ 5 };
	static int ReservHeight{ 5 };

	this->Tanxl_Engine_OpenGL_Draw->Set_PreLoad(PreLoads);
	if ((ReservWidth != Width) || (ReservHeight != Height))
	{
		ReservWidth = Width;
		ReservHeight = Height;
		this->Tanxl_Engine_GameState->Get_StateBase(Width, Height);
		this->Tanxl_Engine_GameState->Set_Display_State(Width, Height);
	}
}

void Tanxl_Engine::Engine_State_Compile_Units(int Width, int Height, std::string Infor)
{
	this->Tanxl_Engine_GameState->CompileStateUnits(Infor);
	this->Tanxl_Engine_GameState->Set_DataAll_State(Width, Height);
}

void Tanxl_Engine::Engine_Insert_State_Limit(bool Enable, float Max_Height, float Max_Widtd)
{
	this->Tanxl_Engine_InsertBase->Set_StateRange(Enable);
	if (Enable)
	{
		this->Tanxl_Engine_InsertBase->Set_MaxFloat_Height(this->Tanxl_Engine_InsertBase->Get_AutoFloat(this->Tanxl_Engine_GameState->Get_StateHeight()));
		this->Tanxl_Engine_InsertBase->Set_MaxFloat_Width(this->Tanxl_Engine_InsertBase->Get_AutoFloat(this->Tanxl_Engine_GameState->Get_StateWidth()));
	}
	else
	{
		this->Tanxl_Engine_InsertBase->Set_MaxFloat_Height(Max_Height);
		this->Tanxl_Engine_InsertBase->Set_MaxFloat_Width(Max_Widtd);
	}
}

void Tanxl_Engine::Engine_Insert_Satate_MoveWith(bool Enable, bool Mode, float Compare_Height, float Compare_Width)
{
	this->Tanxl_Engine_OpenGL_Draw->Set_Trigger_Mode(Mode);
	this->Tanxl_Engine_OpenGL_Draw->Set_Trigger_Range(Enable, Compare_Height, Compare_Width);
}

void Tanxl_Engine::Engine_Adjust_Multi_Set(bool Enable_Adjust, float Adjust_Value, bool Enable_While_Move)
{
	this->Tanxl_Engine_GameState->Set_Enable_Adjust(Enable_Adjust);
	this->Tanxl_Engine_GameState->Set_Adjust(Adjust_Value);
	this->Tanxl_Engine_GameState->Set_Adjust_While_Move(Enable_While_Move);
}

void Tanxl_Engine::Engine_Save_Source_Infor(std::string FileName)
{
	this->Tanxl_Engine_DataBase->Set_Internal_Id(0x0000, "VERSION_INFORMATION", "ENGINE_CORE");
	Data_Link* Data{ new Data_Link(0, "VERSION " + Tanxl_Engine_Console_List->Get_Version()) };
	Data->Append_Data(1, "VERSION " + this->Tanxl_Engine_DataBase->Get_Version());
	Data->Append_Data(2, "VERSION " + this->Tanxl_Engine_GameEvent->Get_Version());
	Data->Append_Data(3, "VERSION " + this->Tanxl_Engine_GameState->Get_Version());
	Data->Append_Data(4, "VERSION " + this->Tanxl_Engine_InsertBase->Get_Version());
	Data->Append_Data(5, "VERSION " + this->Tanxl_Engine_OpenGL_Draw->Get_Version());
	Data->Append_Data(6, "VERSION " + this->__ENGINE_VERSION__);
	this->Tanxl_Engine_DataBase->Set_Internal_Data(Data, SIMPLE_SET);
	this->Tanxl_Engine_DataBase->AppendItem(APPENDTO_BOTH, FileName, true);
	this->Tanxl_Engine_DataBase->SortDataBase(SORT_MEMORY, FileName);
	remove((FileName + ".usd").c_str());
}

void Tanxl_Engine::Engine_Save_Infinite_State(bool Build_Connect, unsigned State_Size, int Width, int Height)
{
	for (int i{ 0 }; i < static_cast<int>(State_Size); ++i)//16x16
	{
		this->Tanxl_Engine_RandomBase->Suffle_UniData(1);
		this->Tanxl_Engine_DataBase->Append_DataChain(this->Tanxl_Engine_RandomBase->GenerateAutoSeed(), 2);
		this->Tanxl_Engine_DataBase->Append_DataChain(this->Tanxl_Engine_RandomBase->Generate_State(10, 10));
	}
	this->Tanxl_Engine_DataBase->SortDataBase(SORT_LOCALF, "TANXL_STATE_DATA", "Data_Chain_File");
	this->Tanxl_Engine_GameState->Set_DataAll_State(Width * 10, Height * 10);
	remove("Data_Chain_File.usd");

	if (Build_Connect)
	{
		for (int i{ 0 }; i < Height; ++i)
			for (int j{ 0 }; j < Width; ++j)
			{
				std::string LEFT_STR{ "NULL" }, LEFT_ABOV_STR{ "NULL" };
				std::string RIGH_STR{ "NULL" }, LEFT_BELO_STR{ "NULL" };
				std::string ABOV_STR{ "NULL" }, RIGH_ABOV_STR{ "NULL" };
				std::string BELO_STR{ "NULL" }, RIGH_BELO_STR{ "NULL" };

				if (j != 0)
					LEFT_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, i * Width + j - 1, 0)->_Data;
				if (j != Width - 1)
					RIGH_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, i * Width + j + 1, 0)->_Data;
				if (i != 0)
					ABOV_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i - 1) * Width + j, 0)->_Data;
				if (i != Height - 1)
					BELO_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i + 1) * Width + j, 0)->_Data;

				if ((j != 0) && (i != 0))
					LEFT_ABOV_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i - 1) * Width + j - 1, 0)->_Data;
				if ((j != 0) && (i != Height - 1))
					LEFT_BELO_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i + 1) * Width + j - 1, 0)->_Data;
				if ((j != Width - 1) && (i != 0))
					RIGH_ABOV_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i - 1) * Width + j + 1, 0)->_Data;
				if ((j != Width - 1) && (i != Height - 1))
					RIGH_BELO_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i + 1) * Width + j + 1, 0)->_Data;

				this->Tanxl_Engine_DataBase->Set_Specified(1, i * Width + j, NULL, ADD_UNIT_IDADAT, 2, LEFT_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * Width + j, NULL, ADD_UNIT_IDADAT, 3, RIGH_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * Width + j, NULL, ADD_UNIT_IDADAT, 4, ABOV_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * Width + j, NULL, ADD_UNIT_IDADAT, 5, BELO_STR);

				this->Tanxl_Engine_DataBase->Set_Specified(1, i * Width + j, NULL, ADD_UNIT_IDADAT, 6, LEFT_ABOV_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * Width + j, NULL, ADD_UNIT_IDADAT, 7, LEFT_BELO_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * Width + j, NULL, ADD_UNIT_IDADAT, 8, RIGH_ABOV_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * Width + j, NULL, ADD_UNIT_IDADAT, 9, RIGH_BELO_STR);
			}
	}
}

void Tanxl_Engine::Engine_Draw_State_Adjust(int PreLoad_Adjust)
{
	this->Tanxl_Engine_OpenGL_Draw->Render_Once(&this->Tanxl_Engine_GameState->Get_StateBase());
	int Temp_Preload = this->Tanxl_Engine_OpenGL_Draw->Get_PreLoad() + PreLoad_Adjust;
	this->Tanxl_Engine_OpenGL_Draw->Set_PreLoad(Temp_Preload < 0 ? 0 : Temp_Preload);
}

std::string Tanxl_Engine::Engine_Insert_Regist_Move(int GLFW_KEY, bool Width_Move, bool Height_Move, double Move_Length)
{
	Key_Unit* KEYU{ new Key_Unit(GLFW_KEY, Width_Move, Height_Move, Move_Length) };
	this->Tanxl_Engine_InsertBase->RegistEvent(KEYU);
	return KEYU->Unit_Name;
}