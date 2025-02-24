#include "Tanxl_Engine_Manager.h"

Tanxl_Engine::Tanxl_Engine() :_Engine_Status(0),
Tanxl_Engine_Console_List(new CONSOLE),
Tanxl_Engine_DataBase(new TANXL_DataBase()),
Tanxl_Engine_GameEvent(&GameEventBase::GetEventBase()),
Tanxl_Engine_GameState(&GameStateBase::GetStateBase(5, 5)),
Tanxl_Engine_OpenGL_Draw(&OpenGL_Draw::GetOpenGLBase()),
Tanxl_Engine_InsertBase(&InsertEventBase::GetInsertBase()),
Tanxl_Engine_RandomBase(&RandomBase::GetRandomBase()),
Tanxl_Engine_LocationBase(&LocationBase::GetLocationBase()),
Tanxl_Engine_ObjectBase(&GameObjectBase::GetObjectBase()),
Tanxl_Engine_Inventory(&Tanxl_Inventory::Get_InventoryBase())
{
	if (!this->Tanxl_Engine_Console_List)
		this->_Engine_Status = 0x1;
	else if (!this->Tanxl_Engine_DataBase)
		this->_Engine_Status = 0x2;
	else if (!this->Tanxl_Engine_GameEvent)
		this->_Engine_Status = 0x3;
	else if (!this->Tanxl_Engine_GameState)
		this->_Engine_Status = 0x4;
	else if (!this->Tanxl_Engine_OpenGL_Draw)
		this->_Engine_Status = 0x5;
	else if (!this->Tanxl_Engine_InsertBase)
		this->_Engine_Status = 0x6;
	else if (!this->Tanxl_Engine_RandomBase)
		this->_Engine_Status = 0x7;
	else if (!this->Tanxl_Engine_LocationBase)
		this->_Engine_Status = 0x8;
	else if (!this->Tanxl_Engine_ObjectBase)
		this->_Engine_Status = 0x9;

	if(this->_Engine_Status)
		std::cout << "Fail to fully start Engine !" << std::endl;

	/*this->Tanxl_Engine_GameState->Set_Compile_Policy("a", 1);
	this->Tanxl_Engine_GameState->Set_Compile_Policy("b", 0);
	this->Tanxl_Engine_GameState->Set_Compile_Policy("c", 2);
	this->Tanxl_Engine_GameState->Set_Compile_Policy("d", 3);*/
}

unsigned Tanxl_Engine::Engine_Check_Engine_Status(bool ShutDown)
{
	if (((this->_Engine_Status & 0xFF) != 0) && ShutDown)
	{
		std::cout << "Fault detected ! Fault Id :" << (_Engine_Status & 0xFF) << std::endl;
		this->Tanxl_Engine_OpenGL_Draw->Destroy_Window();
		exit(_Engine_Status & 0xFF);
	}
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
		this->Tanxl_Engine_GameState->GetStateBase(Width, Height);
		this->Tanxl_Engine_GameState->Set_Display_State(Width, Height);
	}
}

void Tanxl_Engine::Engine_State_Compile_Units(int Width, int Height, std::string Infor, EState_Extend Extend)
{
	this->Tanxl_Engine_GameState->CompileStateUnits(Infor, Extend);
	this->Tanxl_Engine_GameState->Set_State_Counts(Width, Height);
}

void Tanxl_Engine::Engine_Insert_State_Limit(bool Enable, float Max_Height, float Max_Widtd)
{
	this->Tanxl_Engine_InsertBase->Set_StateRange(Enable);
	if (Enable)
	{
		this->Tanxl_Engine_InsertBase->Set_MaxFloat_Height(this->Tanxl_Engine_InsertBase->Get_AutoFloat(this->Tanxl_Engine_GameState->Get_StateHeight()));
		this->Tanxl_Engine_InsertBase->Set_MaxFloat_Width(this->Tanxl_Engine_InsertBase->Get_AutoFloat(this->Tanxl_Engine_GameState->Get_StateWidth()));
		return;
	}
	this->Tanxl_Engine_InsertBase->Set_MaxFloat_Height(Max_Height);
	this->Tanxl_Engine_InsertBase->Set_MaxFloat_Width(Max_Widtd);
}

void Tanxl_Engine::Engine_Insert_State_MoveWith(bool Enable, float Compare_Ratio)
{
	this->Tanxl_Engine_GameState->Set_Trigger_Mode(Enable);
	this->Tanxl_Engine_OpenGL_Draw->Set_Trigger_Range(Compare_Ratio);
	this->Tanxl_Engine_InsertBase->Update_Move_Max();
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
	Data->Append_Data(6, "VERSION " + this->Tanxl_Engine_RandomBase->Get_Version());
	Data->Append_Data(7, "VERSION " + this->Tanxl_Engine_LocationBase->Get_Version());
	Data->Append_Data(8, "VERSION " + this->Tanxl_Engine_ObjectBase->Get_Version());
	Data->Append_Data(9, "VERSION " + this->__ENGINE_VERSION__);
	this->Tanxl_Engine_DataBase->Set_Internal_Data(Data, SIMPLE_SET);
	this->Tanxl_Engine_DataBase->AppendItem(APPENDTO_BOTH, FileName, true);

	this->Tanxl_Engine_DataBase->SortDataBase(SORT_MEMORY, FileName);
	this->_Engine_InforFile_Name = FileName;
	remove((FileName + ".usd").c_str());
}

void Tanxl_Engine::Engine_Save_Infinite_State(bool Build_Connect, int Width, int Height, int Begin_PosX, int Begin_PosY)
{
	this->_Engine_Infinite_State_Set._Is_State_Set = true;
	this->_Engine_Infinite_State_Set._Last_Range_Width = Width;
	this->_Engine_Infinite_State_Set._Last_Range_Height = Height;
	this->_Engine_Infinite_State_Set._Last_Begin_Width = Begin_PosX;
	this->_Engine_Infinite_State_Set._Last_Begin_Height = Begin_PosY;

	this->_Engine_Status |= 0x100;
	for (int i{ 0 }; i < Width; ++i)
	{
		for (int j{ 0 }; j < Height; ++j)
		{
			int TempVal{ Begin_PosX + j + (i + Begin_PosY) * 256 };
			this->Tanxl_Engine_RandomBase->Suffle_UniData(1);
			this->Tanxl_Engine_DataBase->Append_DataChain(this->Tanxl_Engine_RandomBase->GenerateAutoSeed(), 2, 1, TempVal);
			this->Tanxl_Engine_DataBase->Append_DataChain(this->Tanxl_Engine_RandomBase->Generate_State(10, 10, true), 0, 1, TempVal);
		}
	}
	this->Tanxl_Engine_GameState->Set_Data_Size(Width * Height);
	this->Tanxl_Engine_GameState->Set_State_Counts(256, 256);

	if (Build_Connect)
	{
		for (int i{ Begin_PosY }; i < Begin_PosY + Height; ++i)
			for (int j{ Begin_PosX }; j < Begin_PosX + Width; ++j)
			{
				std::string LEFT_STR{ "NULL" }, LEFT_ABOV_STR{ "NULL" };
				std::string RIGH_STR{ "NULL" }, LEFT_BELO_STR{ "NULL" };
				std::string ABOV_STR{ "NULL" }, RIGH_ABOV_STR{ "NULL" };
				std::string BELO_STR{ "NULL" }, RIGH_BELO_STR{ "NULL" };

				if (j != Begin_PosX)
					LEFT_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, i * 256 + j - 1, 0)->_Data;
				if (j != Begin_PosX + Width - 1)
					RIGH_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, i * 256 + j + 1, 0)->_Data;
				if (i != Begin_PosY)
					ABOV_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i - 1) * 256 + j, 0)->_Data;
				if (i != Begin_PosY + Height - 1)
					BELO_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i + 1) * 256 + j, 0)->_Data;

				if ((j != Begin_PosX) && (i != Begin_PosY))
					LEFT_ABOV_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i - 1) * 256 + j - 1, 0)->_Data;
				if ((j != Begin_PosX) && (i != Begin_PosY + Height - 1))
					LEFT_BELO_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i + 1) * 256 + j - 1, 0)->_Data;
				if ((j != Begin_PosX + Width - 1) && (i != Begin_PosY))
					RIGH_ABOV_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i - 1) * 256 + j + 1, 0)->_Data;
				if ((j != Begin_PosX + Width - 1) && (i != Begin_PosY + Height - 1))
					RIGH_BELO_STR = this->Tanxl_Engine_DataBase->Get_Specified(1, (i + 1) * 256 + j + 1, 0)->_Data;

				this->Tanxl_Engine_DataBase->Set_Specified(1, i * 256 + j, NULL, ADD_UNIT_IDADAT, 2, LEFT_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * 256 + j, NULL, ADD_UNIT_IDADAT, 3, RIGH_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * 256 + j, NULL, ADD_UNIT_IDADAT, 4, ABOV_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * 256 + j, NULL, ADD_UNIT_IDADAT, 5, BELO_STR);

				this->Tanxl_Engine_DataBase->Set_Specified(1, i * 256 + j, NULL, ADD_UNIT_IDADAT, 6, LEFT_ABOV_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * 256 + j, NULL, ADD_UNIT_IDADAT, 7, LEFT_BELO_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * 256 + j, NULL, ADD_UNIT_IDADAT, 8, RIGH_ABOV_STR);
				this->Tanxl_Engine_DataBase->Set_Specified(1, i * 256 + j, NULL, ADD_UNIT_IDADAT, 9, RIGH_BELO_STR);
			}
	}
}

void Tanxl_Engine::Engine_Draw_State_Adjust(int PreLoad_Adjust)
{
	this->Tanxl_Engine_OpenGL_Draw->Render_Once(&this->Tanxl_Engine_GameState->GetStateBase());
	int Temp_Preload = this->Tanxl_Engine_OpenGL_Draw->Get_PreLoad() + PreLoad_Adjust;
	this->Tanxl_Engine_OpenGL_Draw->Set_PreLoad(Temp_Preload < 0 ? 0 : Temp_Preload);
}

void Tanxl_Engine::Engine_Insert_State_Update()
{
	if (this->Tanxl_Engine_OpenGL_Draw->Get_Window() == nullptr)
		return;
	this->Tanxl_Engine_InsertBase->GetInsert(this->Tanxl_Engine_OpenGL_Draw->Get_Window(), this->Tanxl_Engine_GameState);
	this->Tanxl_Engine_OpenGL_Draw->Update_Current();//更新地图加载区块
}

Key_Unit* Tanxl_Engine::Engine_Insert_Regist_Move(int GLFW_KEY, bool Width_Move, bool Height_Move, double Move_Length)
{
	Key_Unit* KEYU;
	if ((Width_Move == false) && (Height_Move == false))
		KEYU = new Key_Unit(GLFW_KEY);
	else
		KEYU = new Key_Unit(GLFW_KEY, Width_Move, Height_Move, Move_Length);
	this->Tanxl_Engine_InsertBase->RegistEvent(KEYU);
	return KEYU;
}

void Tanxl_Engine::Engine_Reset_Engine_Base(EENGINE_BASES Engine_Class)
{
	bool All_Selected{ false };
	if (Engine_Class == EENGINE_BASES::ENGINE_ALL_SELECTED)
	{
		Engine_Class = EENGINE_BASES::ENGINE_CONSOLE_LIST;
		All_Selected = true;
	}
	switch (Engine_Class)
	{
	case EENGINE_BASES::ENGINE_CONSOLE_LIST:
		delete this->Tanxl_Engine_Console_List;
		this->Tanxl_Engine_Console_List = new CONSOLE();
		if (!All_Selected)
			break;
	case EENGINE_BASES::ENGINE_DATABASE:
		delete this->Tanxl_Engine_DataBase;
		this->Tanxl_Engine_DataBase = new TANXL_DataBase();
		if (!All_Selected)
			break;
	case EENGINE_BASES::ENGINE_GAMEEVENT:
		this->Tanxl_Engine_GameEvent->Remove_GameEvent(-1);
		if (!All_Selected)
			break;
	case EENGINE_BASES::ENGINE_GAMESTATE:
		this->Tanxl_Engine_GameState->Clear_Display_Vector(STATE_EXTEND_SPEC);
		remove("Tanxl Engine SystemInfor.sd");
		if (!All_Selected)
			break;
	case EENGINE_BASES::ENGINE_OPENGL_DRAW:
		this->Tanxl_Engine_OpenGL_Draw->Destroy_Window();
		if (!All_Selected)
			break;
	case EENGINE_BASES::ENGINE_INSERTBASE:
		for (int i{ 0 }; i < this->Tanxl_Engine_InsertBase->Get_KeyEvent_Size(); ++i)
			this->Tanxl_Engine_InsertBase->RemoveEvent();
		if (!All_Selected)
			break;
	case EENGINE_BASES::ENGINE_RANDOMBASE:
		this->Tanxl_Engine_RandomBase->Reset_Default();
		if (!All_Selected)
			break;
	case EENGINE_BASES::ENGINE_LOCATIONBASE:
		this->Tanxl_Engine_LocationBase->Remove_LocationS(-1);
		if (!All_Selected)
			break;
	case EENGINE_BASES::ENGINE_OBJECTBASE:
		if (!All_Selected)
			break;
	}
}

void Tanxl_Engine::Engine_Invent_Update_Drop()
{
	this->Tanxl_Engine_Inventory->RefreshFromServer();
	this->Tanxl_Engine_Inventory->CheckForItemDrops();
}

void Tanxl_Engine::Engine_Event_State_Regist(std::string Name, int LocationX, int LocationY, std::string Cover_String)
{
	this->Tanxl_Engine_GameEvent->RegistEvent(new State_ChangeEvent(Name, LocationX, LocationY, Cover_String));
}

void Tanxl_Engine::Engine_State_Set_Data(int State_Id, bool Is_Begin, std::string State_Infor)
{
	if (((this->_Engine_Status & 0x100) == 0x0))
	{
		std::cout << "当前未开启扩展世界功能";
		return;
	}
	if (Is_Begin)
		this->Tanxl_Engine_GameState->Set_StartState(State_Id, State_Infor);
	else
		this->Tanxl_Engine_GameState->Set_State(State_Id, State_Infor);
}

void Tanxl_Engine::Engine_Insert_Adjust_Speed(int Start, int End, double Adjust_Value)
{
	this->Tanxl_Engine_InsertBase->Set_MultiSpeed(Start, End, Adjust_Value);
}