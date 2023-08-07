#include "Tanxl_Engine_Manager.h"

Tanxl_Engine::Tanxl_Engine() :Tanxl_Engine_Console_List(new CONSOLE),
Tanxl_Engine_DataBase(new TANXL_DataBase),
Tanxl_Engine_GameEvent(&GameEventBase::GetEventBase()),
Tanxl_Engine_GameState(&GameStateBase::Get_StateBase(5, 5)),
Tanxl_Engine_OpenGL_Draw(&OpenGL_Draw::GetOpenGLBase()),
Tanxl_Engine_InsertBase(&InsertEventBase::GetInsertBase())
{
	if (!Tanxl_Engine_Console_List ||
		!Tanxl_Engine_DataBase ||
		!Tanxl_Engine_GameEvent ||
		!Tanxl_Engine_GameState ||
		!Tanxl_Engine_OpenGL_Draw ||
		!Tanxl_Engine_InsertBase)
	{
		std::cout << "Fail to start Engine !" << std::endl;
		delete this;
	}
}

void Tanxl_Engine::Engine_State_Set_Display(int Width, int Height)
{
	static int ReservWidth{ 5 };
	static int ReservHeight{ 5 };

	if (ReservWidth != Width || ReservHeight != Height)
	{
		ReservWidth = Width;
		ReservHeight = Height;
		Tanxl_Engine_GameState->Get_StateBase(Width, Height);
		Tanxl_Engine_GameState->Set_Display_State(Width, Height);
	}
}

void Tanxl_Engine::Engine_State_Compile_Units(int Width, int Height, std::string Infor)
{
	Tanxl_Engine_GameState->CompileStateUnits(Infor);
	Tanxl_Engine_GameState->Set_DataAll_State(Width, Height);
}

void Tanxl_Engine::Engine_Insert_State_Limit(bool Enable, float Max_Height, float Max_Widtd)
{
	Tanxl_Engine_InsertBase->Set_StateRange(Enable);
	if (Enable)
	{
		Tanxl_Engine_InsertBase->Set_MaxFloat_Height(Tanxl_Engine_InsertBase->Get_AutoFloat(Tanxl_Engine_GameState->Get_StateHeight()));
		Tanxl_Engine_InsertBase->Set_MaxFloat_Width(Tanxl_Engine_InsertBase->Get_AutoFloat(Tanxl_Engine_GameState->Get_StateWidth()));
	}
	else
	{
		Tanxl_Engine_InsertBase->Set_MaxFloat_Height(Max_Height);
		Tanxl_Engine_InsertBase->Set_MaxFloat_Width(Max_Widtd);
	}
}

void Tanxl_Engine::Engine_Insert_Satate_MoveWith(bool Enable, bool Mode, float Compare_Height, float Compare_Width)
{
	Tanxl_Engine_OpenGL_Draw->Set_Trigger_Mode(Mode);
	Tanxl_Engine_OpenGL_Draw->Set_Trigger_Range(Enable, Compare_Height, Compare_Width);
}

void Tanxl_Engine::Engine_Adjust_Multi_Set(bool Enable_Adjust, float Adjust_Value, bool Enable_While_Move)
{
	Tanxl_Engine_GameState->Set_Enable_Adjust(Enable_Adjust);
	Tanxl_Engine_GameState->Set_Adjust(Adjust_Value);
	Tanxl_Engine_GameState->Set_Adjust_While_Move(Enable_While_Move);
}

void Tanxl_Engine::Engine_Save_Source_Infor(std::string FileName)
{
	Tanxl_Engine_DataBase->Set_Internal_Id(0x0000, "00-VERSION_INFORMATION", "00-ENGINE-CORE");
	Data_Link* Data = new Data_Link(0, "VERSION " + Tanxl_Engine_Console_List->Get_Version());
	Data->Append_Data(1, "VERSION " + Tanxl_Engine_DataBase->Get_Version());
	Data->Append_Data(2, "VERSION " + Tanxl_Engine_GameEvent->Get_Version());
	Data->Append_Data(3, "VERSION " + Tanxl_Engine_GameState->Get_Version());
	Data->Append_Data(4, "VERSION " + Tanxl_Engine_InsertBase->Get_Version());
	Data->Append_Data(5, "VERSION " + Tanxl_Engine_OpenGL_Draw->Get_Version());
	Data->Append_Data(6, "VERSION " + this->__ENGINE_VERSION__);
	delete Data;
	//Tanxl_Engine_DataBase->SortDataBase(FILE_UNITED, FileName, FileName, true);
}