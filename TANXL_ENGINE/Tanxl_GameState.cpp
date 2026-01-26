#pragma once

#include "Tanxl_GameState.h"

//Core

//StateUnit

StateUnit::StateUnit(GameEvent* GE, int State_Id, int Move_Status)
	:_Extra_Status(Move_Status), _GameEvents(GE), _State_Id(State_Id) {}

void StateUnit::SetEvent(std::string GameEventName, int State_Id)
{
	GameEventBase* EventBase{ &GameEventBase::GetEventBase() };
	if (EventBase->GetGameEvent(GameEventName))
		this->_GameEvents = EventBase->GetEventBase().GetGameEvent(GameEventName);
	if (State_Id != -1)
		this->_State_Id = State_Id;
}

//GameStateBase

const std::string GameStateBase::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

float GameStateBase::Set_ExacHeight(double Current, float& MoveState, double Scale)
{
	if (_Adjust_Enable == false)
		return 0.0f;
	float& State_MoveY{ this->Get_State_Loc()._Coord_Y };
	float Temp_Move{};
	float Temp_GameState_Adjust{ static_cast<float>(_GameState_Adjust * Scale) };
	if (static_cast<float>(Current) < static_cast<float>(this->_GameState_Length._Coord_Y) * 0.5f)
	{
		if (MoveState < 0 && MoveState + Temp_GameState_Adjust > 0)
		{
			Temp_Move = MoveState;
#if _TANXL_GAMESTATE_SETEXAC_LOCATION_OUTPUT_
			std::cout << "A Temp_Move  _" << Temp_Move << std::endl;
			std::cout << "A MoveState  _" << MoveState << std::endl;
#endif
			State_MoveY += Temp_Move;
			MoveState = 0;
		}
		else
		{
			MoveState += Temp_GameState_Adjust;
			State_MoveY += Temp_GameState_Adjust;
		}
		this->_Is_Adjusting = true;
	}
	else if (static_cast<float>(Current) > static_cast<float>(this->_GameState_Length._Coord_Y) * 0.5f)
	{
		if (MoveState > Temp_GameState_Adjust)
		{
			MoveState -= Temp_GameState_Adjust;
			State_MoveY -= Temp_GameState_Adjust;
		}
		else if (MoveState - Temp_GameState_Adjust < 0)
		{
			Temp_Move = MoveState;
#if _TANXL_GAMESTATE_SETEXAC_LOCATION_OUTPUT_
			std::cout << "B Temp_Move  _" << Temp_Move << std::endl;
			std::cout << "B MoveState  _" << MoveState << std::endl;
#endif
			State_MoveY -= Temp_Move;
			Temp_Move = -Temp_Move;
			MoveState = 0;
		}
		this->_Is_Adjusting = true;
	}
	return Temp_Move;
}

float GameStateBase::Set_ExacWidth(double Current, float& MoveState, double Scale)
{
	if (_Adjust_Enable == false)
		return 0.0f;
	float& State_MoveX{ this->Get_State_Loc()._Coord_X };
	float Temp_Move{};
	float Temp_GameState_Adjust{ static_cast<float>(_GameState_Adjust * Scale) };
	if (static_cast<float>(Current) < static_cast<float>(this->_GameState_Length._Coord_X) * 0.5f)
	{
		if (-MoveState < 0 && (Temp_GameState_Adjust + -MoveState > 0))//微调小于最小值的情况 直接调整到屏幕中间
		{
			Temp_Move = MoveState;
			while (Temp_Move > 2.5)
				Temp_Move -= 2.5;
#if _TANXL_GAMESTATE_SETEXAC_LOCATION_OUTPUT_
			std::cout << "A Temp_Move  _" << Temp_Move << std::endl;
			std::cout << "A MoveState  _" << MoveState << std::endl;
#endif
			State_MoveX += Temp_Move;
			MoveState = 0;
		}
		else
		{
			MoveState += Temp_GameState_Adjust;
			State_MoveX += Temp_GameState_Adjust;
		}
		this->_Is_Adjusting = true;
	}
	else if (static_cast<float>(Current) > static_cast<float>(this->_GameState_Length._Coord_X) * 0.5f)
	{
		if (MoveState > Temp_GameState_Adjust)
		{
			MoveState -= Temp_GameState_Adjust;
			State_MoveX -= Temp_GameState_Adjust;
		}
		else if (MoveState < Temp_GameState_Adjust)//微调小于最小值的情况 直接调整到屏幕中间
		{
			Temp_Move = MoveState;
			while (Temp_Move > 2.5)
				Temp_Move -= 2.5;
#if _TANXL_GAMESTATE_SETEXAC_LOCATION_OUTPUT_
			std::cout << "B Temp_Move  _" << Temp_Move << std::endl;
			std::cout << "B MoveState  _" << MoveState << std::endl;
#endif
			State_MoveX -= Temp_Move;
			Temp_Move = -Temp_Move;
			MoveState = 0;
		}
		this->_Is_Adjusting = true;
	}
	return Temp_Move;
}

std::string GameStateBase::Locate_Extend_State(std::string State_Id)
{
	if (State_Id == "NULL")
		return "NULL";
	if (this->Get_Engine_File())
	{
		Id_Link* Target_Link{ Locate_Link(State_Id) };
		if (Target_Link != nullptr)
			return Target_Link->_Data->_Data_Units.at(1)->_Data;
		return "NULL";
	}
	return "NULL";
}

void GameStateBase::Single_Connect(std::vector<Data_Unit*>* Build_Target, EState_Current CurrentState, int State_Id, int OffSet)
{
	try {
		std::vector<Data_Unit*>* Connect_Target;
		if (OffSet == 0)
			Connect_Target = &this->_Data_Base.Id_Link_Locate(1, State_Id)->_Data->_Data_Units;
		else
			Connect_Target = &this->_Data_Base.Get_Last_Located(1, State_Id, OffSet)->_Data->_Data_Units;
		//this->_Data_Base.Print_Data();
#if _TANXL_GAMESTATE_CONNECT_DEBUG_OUTPUT_
		std::cout << "Connect Targrt :" << Connect_Target->at(0)->_Data << " Size :" << Connect_Target->size()
			<< " " << CurrentState << std::endl;
#endif
		Connect_Target->at(CurrentState)->_Data = Build_Target->at(0)->_Data;
#if _TANXL_GAMESTATE_CONNECT_DEBUG_OUTPUT_
		std::cout << "Build_Target Id : " << Build_Target->at(0)->_Data << std::endl;
#endif

		EState_Current TempState{ CurrentState };
		switch (CurrentState)
		{
		case STATE_LEFT:
			TempState = STATE_RIGH;
			break;
		case STATE_RIGH:
			TempState = STATE_LEFT;
			break;
		case STATE_ABOV:
			TempState = STATE_BELO;
			break;
		case STATE_BELO:
			TempState = STATE_ABOV;
			break;
		case STATE_LEFT_ABOV:
			TempState = STATE_RIGH_BELO;
			break;
		case STATE_LEFT_BELO:
			TempState = STATE_RIGH_ABOV;
			break;
		case STATE_RIGH_ABOV:
			TempState = STATE_LEFT_BELO;
			break;
		case STATE_RIGH_BELO:
			TempState = STATE_LEFT_ABOV;
			break;
		}

		Build_Target->at(TempState)->_Data = Connect_Target->at(0)->_Data;
#if _TANXL_GAMESTATE_CONNECT_DEBUG_OUTPUT_
		std::cout << "Connect_Target Id : " << Connect_Target->at(0)->_Data << std::endl;
		std::cout << "Connect_Target : PASS" << std::endl;
#endif
	}
	catch (std::string ErrorMessage)
	{
#if _TANXL_GAMESTATE_CONNECT_DEBUG_OUTPUT_
		std::cout << "Connect_Target : FAIL - " << ErrorMessage << std::endl;
#endif
	}
	catch (std::out_of_range)
	{
#if _TANXL_GAMESTATE_CONNECT_DEBUG_OUTPUT_
		std::cout << "Connect_Target : OUT OF RANGE" << std::endl;
#endif
	}
}

std::string GameStateBase::Get_State_Id(int Location)
{
	if (this->Get_Engine_File())
		return this->_Data_Base.Data_Link_Locate(1, Location, 0)->_Data;
	return "NULL";
}

TANXL_DataBase* GameStateBase::Get_Data_Source()
{
	return &this->_Data_Base;
}

void GameStateBase::Clear_Display_Vector(EState_Extend Clear_Id) const
{
	if (Clear_Id == STATE_EXTEND_SPEC)
	{
		if (this->_GameState_Extend._MIDD._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._MIDD._Data);
		if (this->_GameState_Extend._LEFT._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT._Data);
		if (this->_GameState_Extend._RIGH._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH._Data);
		if (this->_GameState_Extend._ABOV._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._ABOV._Data);
		if (this->_GameState_Extend._BELO._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._BELO._Data);
		if (this->_GameState_Extend._LEFT_ABOV._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_ABOV._Data);
		if (this->_GameState_Extend._LEFT_BELO._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_BELO._Data);
		if (this->_GameState_Extend._RIGH_ABOV._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_ABOV._Data);
		if (this->_GameState_Extend._RIGH_BELO._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_BELO._Data);
		return;
	}
	switch (Clear_Id)
	{
	case STATE_EXTEND_MIDD:
		if (this->_GameState_Extend._MIDD._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._MIDD._Data);
		return;
	case STATE_EXTEND_LEFT:
		if (this->_GameState_Extend._LEFT._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT._Data);
		return;
	case STATE_EXTEND_RIGH:
		if (this->_GameState_Extend._RIGH._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH._Data);
		return;
	case STATE_EXTEND_ABOV:
		if (this->_GameState_Extend._ABOV._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._ABOV._Data);
		return;
	case STATE_EXTEND_BELO:
		if (this->_GameState_Extend._BELO._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._BELO._Data);
		return;
	case STATE_EXTEND_LEFT_ABOV:
		if (this->_GameState_Extend._LEFT_ABOV._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_ABOV._Data);
		return;
	case STATE_EXTEND_LEFT_BELO:
		if (this->_GameState_Extend._LEFT_BELO._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_BELO._Data);
		return;
	case STATE_EXTEND_RIGH_ABOV:
		if (this->_GameState_Extend._RIGH_ABOV._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_ABOV._Data);
		return;
	case STATE_EXTEND_RIGH_BELO:
		if (this->_GameState_Extend._RIGH_BELO._Data)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_BELO._Data);
		return;
	}
}

void GameStateBase::Set_Display_State(int Width, int Height)
{
	this->_GameState_Length._Coord_X = Width;
	this->_Half_State_Length._Coord_X = 1.0f / Width;
	this->_GameState_Length._Coord_Y = Height;
	this->_Half_State_Length._Coord_Y = 1.0f / Height;

	this->_Each_Height = 2.0f / this->_GameState_Length._Coord_Y;//10 0.2
	this->_Each_Width = 2.0f / this->_GameState_Length._Coord_X;//10 0.2
}

void GameStateBase::Set_Data_Length(unsigned Width, unsigned Height)
{
	this->_Data_Width = Width - 1;
	this->_Data_Height = Height - 1;
}

StateUnit* GameStateBase::Get_State()
{
	return Get_State(this->_Exac_Location._Coord_X, this->_Exac_Location._Coord_Y);
}

void GameStateBase::CompileStateUnits(std::string Infor, EState_Extend Extend)
{
	static GameEventBase* Event{ &GameEventBase::GetEventBase() };
	std::string Text_Reader{};
	int Status_Id{};
	int State_Status{};

	this->Clear_Display_Vector(Extend);
	std::vector<StateUnit*>* Target{ this->Get_GameState(Extend) };

	if (Infor == "NULL")
		return;

	for (int i{ 0 }; i < Infor.size(); ++i)
	{
		if (Infor.at(i) == ',')
		{
			Status_Id = std::stoi(Text_Reader);
			Target->push_back(new StateUnit(nullptr, Status_Id, State_Status));
			Text_Reader = "";
		}
		else if (Infor.at(i) == '-')
		{
			State_Status = std::stoi(Text_Reader);

			/*if (this->_Policy.size() != 0)
			{
				for (int i{}; i < this->_Policy.size(); i++)
				{
					if (this->_Policy.at(i)->_Name == Text_Reader)
					{
						State_Status = this->_Policy.at(i)->_State_Status;
						break;
					}
				}
			}*/

			Text_Reader = "";
			Status_Id = 0;
		}
		else
			Text_Reader += Infor.at(i);
	}
	_Compile_Success = true;
}

void GameStateBase::Set_State(int State_Id, std::string Cover_String, bool Start)
{
	if (this->Get_Engine_File())
	{
		Id_Link* Link{ this->_Data_Base.Id_Link_Locate(1, State_Id) };
		std::string Data_Name{ Link->_Data->_Data_Units.at(0)->_Data };
		Link->_Data->_Data_Units.at(1)->_Data = Cover_String;

		if (Start)
		{
			this->_Extend_Mid_Id = State_Id;

			if (Cover_String != "NULL")
				Link->_Data->_Data_Units.at(1)->_Data = Cover_String;
			this->CompileStateUnits(Link->_Data->_Data_Units.at(1)->_Data, STATE_EXTEND_MIDD);
			this->_GameState_Extend._MIDD._Id = Link->_Data->_Data_Units.at(0)->_Data;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(2)->_Data), STATE_EXTEND_LEFT);
			this->_GameState_Extend._LEFT._Id = Link->_Data->_Data_Units.at(2)->_Data;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(3)->_Data), STATE_EXTEND_RIGH);
			this->_GameState_Extend._RIGH._Id = Link->_Data->_Data_Units.at(3)->_Data;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(4)->_Data), STATE_EXTEND_ABOV);
			this->_GameState_Extend._ABOV._Id = Link->_Data->_Data_Units.at(4)->_Data;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(5)->_Data), STATE_EXTEND_BELO);
			this->_GameState_Extend._BELO._Id = Link->_Data->_Data_Units.at(5)->_Data;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(6)->_Data), STATE_EXTEND_LEFT_ABOV);
			this->_GameState_Extend._LEFT_ABOV._Id = Link->_Data->_Data_Units.at(6)->_Data;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(7)->_Data), STATE_EXTEND_LEFT_BELO);
			this->_GameState_Extend._LEFT_BELO._Id = Link->_Data->_Data_Units.at(7)->_Data;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(8)->_Data), STATE_EXTEND_RIGH_ABOV);
			this->_GameState_Extend._RIGH_ABOV._Id = Link->_Data->_Data_Units.at(8)->_Data;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(9)->_Data), STATE_EXTEND_RIGH_BELO);
			this->_GameState_Extend._RIGH_BELO._Id = Link->_Data->_Data_Units.at(9)->_Data;
			this->Set_Data_Length(10, 10);
		}
	}
}

void GameStateBase::Set_State_Counts(int Width, int Height)
{
	this->_State_WidthS = Width;
	this->_State_HeightS = Height;
}

GameStateBase& GameStateBase::GetStateBase(int Display_Width, int Display_Height)
{
	static GameStateBase GameState(Display_Width, Display_Height);
	return GameState;
}

Square_State& GameStateBase::Get_Square_State()
{
	return this->_MState;
}

Tanxl_Coord<float>& GameStateBase::Get_State_Loc() const
{
	return LocationBase::GetLocationBase().Get_LocationS(this->_State_Loc);
}

Tanxl_Coord<float>& GameStateBase::Get_Screen_Distance() const
{
	return LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Screen_Mid);
}

Tanxl_Coord<float>& GameStateBase::Get_Move_Distance() const
{
	return LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move);
}

Tanxl_Coord<float>& GameStateBase::Get_Last_Move() const
{
	return LocationBase::GetLocationBase().Get_LocationS(this->_Last_Move);
}

Tanxl_Coord<float> GameStateBase::Auto_Adjust(double Move_Scale)
{
	static Tanxl_Coord<float>& DistMid{ LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Screen_Mid) };
	Tanxl_Coord<float> Temp_Move(0.0f, 0.0f);
	double Current_Height{ (static_cast<double>(DistMid._Coord_Y) * 2 + 1) / (this->_Each_Height) };
	double Current_Width{ (static_cast<double>(DistMid._Coord_X) * 2 + 1) / (this->_Each_Width) };

	if (this->_Is_Adjusting)//Auto Adjust Part
	{
		Temp_Move._Coord_Y = this->Set_ExacHeight(Current_Height, DistMid._Coord_Y, Move_Scale);
		Temp_Move._Coord_X = this->Set_ExacWidth(Current_Width, DistMid._Coord_X, Move_Scale);
	}
	return Temp_Move + DistMid;
}

double GameStateBase::Get_Each_Width() const
{
	return this->_Each_Width;
}

double GameStateBase::Get_Each_Height() const
{
	return this->_Each_Height;
}

void GameStateBase::Reload_Display_State(EState_Extend Extend_Dire)
{
	switch (Extend_Dire)
	{
	case STATE_EXTEND_ABOV:
	{
		Replace_State(this->_Extend_Mid_Id + 255, this->_GameState_Extend._LEFT_BELO, this->_GameState_Extend._LEFT);
		Replace_State(this->_Extend_Mid_Id, this->_GameState_Extend._BELO, this->_GameState_Extend._MIDD);
		Replace_State(this->_Extend_Mid_Id + 1, this->_GameState_Extend._RIGH_BELO, this->_GameState_Extend._RIGH);

		this->_Extend_Mid_Id -= 256;
		
		Generate_StateBlock(this->_Extend_Mid_Id - 257);
		Generate_StateBlock(this->_Extend_Mid_Id - 256);
		Generate_StateBlock(this->_Extend_Mid_Id - 255);

		this->_GameState_Extend._LEFT = this->_GameState_Extend._LEFT_ABOV;
		this->_GameState_Extend._MIDD = this->_GameState_Extend._ABOV;
		this->_GameState_Extend._RIGH = this->_GameState_Extend._RIGH_ABOV;

		Id_Link* Link{ this->Locate_Link(this->_GameState_Extend._MIDD._Id) };

		if (Link && (Link->_Data->_Data_Units.size() == 10))
		{
			this->_GameState_Extend._LEFT_ABOV._Id = Link->_Data->_Data_Units.at(6)->_Data;
			this->_GameState_Extend._LEFT_ABOV._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(6)->_Data), STATE_EXTEND_LEFT_ABOV);

			this->_GameState_Extend._ABOV._Id = Link->_Data->_Data_Units.at(4)->_Data;
			this->_GameState_Extend._ABOV._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(4)->_Data), STATE_EXTEND_ABOV);

			this->_GameState_Extend._RIGH_ABOV._Id = Link->_Data->_Data_Units.at(8)->_Data;
			this->_GameState_Extend._RIGH_ABOV._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(8)->_Data), STATE_EXTEND_RIGH_ABOV);
		}

		break;
	}
	case STATE_EXTEND_BELO:
	{
		Replace_State(this->_Extend_Mid_Id - 257, this->_GameState_Extend._LEFT_ABOV, this->_GameState_Extend._LEFT);
		Replace_State(this->_Extend_Mid_Id - 256, this->_GameState_Extend._ABOV, this->_GameState_Extend._MIDD);
		Replace_State(this->_Extend_Mid_Id - 255, this->_GameState_Extend._RIGH_ABOV, this->_GameState_Extend._RIGH);
		
		this->_Extend_Mid_Id += 256;

		Generate_StateBlock(this->_Extend_Mid_Id + 255);
		Generate_StateBlock(this->_Extend_Mid_Id + 256);
		Generate_StateBlock(this->_Extend_Mid_Id + 257);

		this->_GameState_Extend._LEFT = this->_GameState_Extend._LEFT_BELO;
		this->_GameState_Extend._MIDD = this->_GameState_Extend._BELO;
		this->_GameState_Extend._RIGH = this->_GameState_Extend._RIGH_BELO;

		Id_Link* Link{ this->Locate_Link(this->_GameState_Extend._MIDD._Id) };

		if (Link && (Link->_Data->_Data_Units.size() == 10))
		{
			this->_GameState_Extend._LEFT_BELO._Id = Link->_Data->_Data_Units.at(7)->_Data;
			this->_GameState_Extend._LEFT_BELO._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(7)->_Data), STATE_EXTEND_LEFT_BELO);

			this->_GameState_Extend._BELO._Id = Link->_Data->_Data_Units.at(5)->_Data;
			this->_GameState_Extend._BELO._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(5)->_Data), STATE_EXTEND_BELO);

			this->_GameState_Extend._RIGH_BELO._Id = Link->_Data->_Data_Units.at(9)->_Data;
			this->_GameState_Extend._RIGH_BELO._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(9)->_Data), STATE_EXTEND_RIGH_BELO);
		}

		break;
	}
	case STATE_EXTEND_LEFT:
	{
		Replace_State(this->_Extend_Mid_Id - 255, this->_GameState_Extend._RIGH_ABOV, this->_GameState_Extend._ABOV);
		Replace_State(this->_Extend_Mid_Id + 1, this->_GameState_Extend._RIGH, this->_GameState_Extend._MIDD);
		Replace_State(this->_Extend_Mid_Id + 257, this->_GameState_Extend._RIGH_BELO, this->_GameState_Extend._BELO);

		this->_Extend_Mid_Id -= 1;

		Generate_StateBlock(this->_Extend_Mid_Id - 257);
		Generate_StateBlock(this->_Extend_Mid_Id - 1);
		Generate_StateBlock(this->_Extend_Mid_Id + 255);

		this->_GameState_Extend._ABOV = this->_GameState_Extend._LEFT_ABOV;
		this->_GameState_Extend._MIDD = this->_GameState_Extend._LEFT;
		this->_GameState_Extend._BELO = this->_GameState_Extend._LEFT_BELO;

		Id_Link* Link{ this->Locate_Link(this->_GameState_Extend._MIDD._Id) };

		if (Link && (Link->_Data->_Data_Units.size() == 10))
		{
			this->_GameState_Extend._LEFT_ABOV._Id = Link->_Data->_Data_Units.at(6)->_Data;
			this->_GameState_Extend._LEFT_ABOV._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(6)->_Data), STATE_EXTEND_LEFT_ABOV);

			this->_GameState_Extend._LEFT._Id = Link->_Data->_Data_Units.at(2)->_Data;
			this->_GameState_Extend._LEFT._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(2)->_Data), STATE_EXTEND_LEFT);

			this->_GameState_Extend._LEFT_BELO._Id = Link->_Data->_Data_Units.at(7)->_Data;
			this->_GameState_Extend._LEFT_BELO._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(7)->_Data), STATE_EXTEND_LEFT_BELO);
		}

		break;
	}
	case STATE_EXTEND_RIGH:
	{
		Replace_State(this->_Extend_Mid_Id - 257, this->_GameState_Extend._LEFT_ABOV, this->_GameState_Extend._ABOV);
		Replace_State(this->_Extend_Mid_Id - 1, this->_GameState_Extend._LEFT, this->_GameState_Extend._MIDD);
		Replace_State(this->_Extend_Mid_Id + 255, this->_GameState_Extend._LEFT_BELO, this->_GameState_Extend._BELO);

		this->_Extend_Mid_Id += 1;

		Generate_StateBlock(this->_Extend_Mid_Id - 255);
		Generate_StateBlock(this->_Extend_Mid_Id + 1);
		Generate_StateBlock(this->_Extend_Mid_Id + 257);

		this->_GameState_Extend._ABOV = this->_GameState_Extend._RIGH_ABOV;
		this->_GameState_Extend._MIDD = this->_GameState_Extend._RIGH;
		this->_GameState_Extend._BELO = this->_GameState_Extend._RIGH_BELO;

		Id_Link* Link{ this->Locate_Link(this->_GameState_Extend._MIDD._Id) };

		if (Link && (Link->_Data->_Data_Units.size() == 10))
		{
			this->_GameState_Extend._RIGH_ABOV._Id = Link->_Data->_Data_Units.at(8)->_Data;
			this->_GameState_Extend._RIGH_ABOV._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(8)->_Data), STATE_EXTEND_RIGH_ABOV);

			this->_GameState_Extend._RIGH._Id = Link->_Data->_Data_Units.at(3)->_Data;
			this->_GameState_Extend._RIGH._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(3)->_Data), STATE_EXTEND_RIGH);

			this->_GameState_Extend._RIGH_BELO._Id = Link->_Data->_Data_Units.at(9)->_Data;
			this->_GameState_Extend._RIGH_BELO._Data = new std::vector<StateUnit*>;
			this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(9)->_Data), STATE_EXTEND_RIGH_BELO);
		}
		break;
	}
	}
}

void GameStateBase::Reload_State_Data(int PreLoads, glm::ivec2* StateInfor)
{
	int Move_NX{ this->_MState._Move_NX };
	int Move_PX{ this->_MState._Move_PX };
	int Move_NY{ this->_MState._Move_NY };
	int Move_PY{ this->_MState._Move_PY };

#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
	std::cout << "Move_NX: " << Move_NX << "Move_PX: " << Move_PX << std::endl;
	std::cout << "Move_NY: " << Move_NY << "Move_PY: " << Move_PY << std::endl;
#endif

	if ((!this->_Compile_Success) || (this->Get_GameState()->size() == 0))
		return;

	int State_Length{ (this->_GameState_Length._Coord_Y + PreLoads * 2) * (this->_GameState_Length._Coord_X + PreLoads * 2) + 1 };

	for (int i{ 0 }; i < State_Length; ++i)
	{
		StateInfor[i].x = 4;
		StateInfor[i].y = 1;

		if (Move_NX > static_cast<int>(this->_Data_Width))//RIGH AREA
		{
			if (Move_NY > static_cast<int>(this->_Data_Height))
			{
				if (this->Is_State_Exist(STATE_EXTEND_RIGH_BELO))
				{
					unsigned x{ Move_NX - this->_Data_Width - 1 + (Move_NY - this->_Data_Height - 1) * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_RIGH_BELO, x % this->Get_GameState(STATE_EXTEND_RIGH_BELO)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= 0)
			{
				if (this->Is_State_Exist(STATE_EXTEND_RIGH))
				{
					unsigned x{ Move_NX - this->_Data_Width - 1 + Move_NY * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_RIGH, x % this->Get_GameState(STATE_EXTEND_RIGH)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= -static_cast<int>(this->_Data_Height))
			{
				if (this->Is_State_Exist(STATE_EXTEND_RIGH_ABOV))
				{
					unsigned x{ Move_NX - this->_Data_Width - 1 + (Move_NY + this->_Data_Height + 1) * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_RIGH_ABOV, x % this->Get_GameState(STATE_EXTEND_RIGH_ABOV)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
		}
		else if (Move_NX >= 0)//MID AREA
		{
			if (Move_NY > static_cast<int>(this->_Data_Height))
			{
				if (this->Is_State_Exist(STATE_EXTEND_BELO))
				{
					unsigned x{ Move_NX + (Move_NY - this->_Data_Height - 1) * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_BELO, x % this->Get_GameState(STATE_EXTEND_BELO)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= 0)
			{
				if (this->Is_State_Exist(STATE_EXTEND_MIDD))
				{
					unsigned x{ Move_NX + Move_NY * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_MIDD, x % this->Get_GameState(STATE_EXTEND_MIDD)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= -static_cast<int>(this->_Data_Height))
			{
				if (this->Is_State_Exist(STATE_EXTEND_ABOV))
				{
					unsigned x{ Move_NX + (Move_NY + this->_Data_Height + 1) * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_ABOV, x % this->Get_GameState(STATE_EXTEND_ABOV)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
		}
		else if (Move_NX >= -static_cast<int>(this->_Data_Width))//LEFT AREA
		{
			if (Move_NY > static_cast<int>(this->_Data_Height))
			{
				if (this->Is_State_Exist(STATE_EXTEND_LEFT_BELO))
				{
					unsigned x{ Move_NX + this->_Data_Width + 1 + (Move_NY - this->_Data_Height - 1) * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_LEFT_BELO, x % this->Get_GameState(STATE_EXTEND_LEFT_BELO)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= 0)
			{
				if (this->Is_State_Exist(STATE_EXTEND_LEFT))
				{
					unsigned x{ Move_NX + this->_Data_Width + 1 + Move_NY * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_LEFT, x % this->Get_GameState(STATE_EXTEND_LEFT)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= -static_cast<int>(this->_Data_Height))
			{
				if (this->Is_State_Exist(STATE_EXTEND_LEFT_ABOV))
				{
					unsigned x{ Move_NX + this->_Data_Width + 1 + (Move_NY + this->_Data_Height + 1) * (this->_Data_Width + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_LEFT_ABOV, x % this->Get_GameState(STATE_EXTEND_LEFT_ABOV)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
		}

		Move_NX++;
		if (Move_NX > Move_PX)//抵达尽头 重新获取初值
		{
			Move_NX = this->_MState._Move_NX;
			Move_NY++;
		}
	}
}

void GameStateBase::Update_Move(float MoveX, float MoveY, ECheck_Edge Check)
{
	static Tanxl_Coord<float>* Distance{ &LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move) };

	if ((this->_Half_State_Length._Coord_X == 0.0f) || (this->_Half_State_Length._Coord_Y == 0.0f))
		this->Set_Display_State(this->_GameState_Length._Coord_X, this->_GameState_Length._Coord_Y);

	static float State_Above_Below_Width{ this->_Half_State_Length._Coord_X * 2 / 3 };
	static float State_Above_Below_Height{ this->_Half_State_Length._Coord_Y * 2 / 3 };

	switch (Check)
	{
	case CHECK_EDGE_CURR:
		MoveX += 0.0f;
		MoveY += 0.0f;
		break;
	case CHECK_EDGE_LEFT:
		MoveX -= this->_Half_State_Length._Coord_X * 2 / 3;
		MoveY += State_Above_Below_Height;
		State_Above_Below_Height = -State_Above_Below_Height;
		break;
	case CHECK_EDGE_RIGH:
		MoveX += this->_Half_State_Length._Coord_X * 2 / 3;
		MoveY += State_Above_Below_Height;
		State_Above_Below_Height = -State_Above_Below_Height;
		break;
	case CHECK_EDGE_BELO:
		MoveX += State_Above_Below_Width;
		MoveY -= this->_Half_State_Length._Coord_Y * 2 / 3;
		State_Above_Below_Width = -State_Above_Below_Width;
		break;
	case CHECK_EDGE_ABOV:
		MoveX += State_Above_Below_Width;
		MoveY += this->_Half_State_Length._Coord_Y * 2 / 3;
		State_Above_Below_Width = -State_Above_Below_Width;
		break;
	}

	float Temp_LocationX{ (Distance->_Coord_X + MoveX) * (this->_GameState_Length._Coord_X / 2.0f) };
	float Temp_LocationY{ (Distance->_Coord_Y + MoveY) * (this->_GameState_Length._Coord_Y / 2.0f) };

#if _TANXL_GAMESTATE_UPDATE_MOVE_OUTPUT_
	std::cout << "Before Adjust :" << Temp_LocationX << "____" << Temp_LocationY << std::endl;
#endif

	Temp_LocationX = static_cast<int>(Temp_LocationX + 0.5f) > static_cast<int>(Temp_LocationX) ? Temp_LocationX + 0.5f : Temp_LocationX;
	Temp_LocationY = static_cast<int>(Temp_LocationY - 0.5f) < static_cast<int>(Temp_LocationY) ? Temp_LocationY - 0.5f : Temp_LocationY;

	this->_Exac_Location._Coord_X = static_cast<int>(Temp_LocationX);
	this->_Exac_Location._Coord_Y = static_cast<int>(Temp_LocationY);

	if (Distance->_Coord_X + MoveX < -0.24f)
		--this->_Exac_Location._Coord_X;
	if (Distance->_Coord_Y + MoveY > 0.24f)
		++this->_Exac_Location._Coord_Y;

	this->_Exac_Location._Coord_Y = -this->_Exac_Location._Coord_Y;

#if _TANXL_GAMESTATE_UPDATE_MOVE_OUTPUT_
	std::cout << "After :" << Temp_LocationX << "____" << Temp_LocationY << std::endl;
	std::cout << this->_Exac_Location._Coord_X << "____" << this->_Exac_Location._Coord_Y << std::endl;
#endif
}

void GameStateBase::StateMove_Edge_Set(short Edge, double Scale)//Reach Screen Edge : Then push screen to move
{
	int Moves{};
	if (_Trigger_Mode)
		Moves = this->Auto_Update_Trigger(Edge);

	if ((Moves & MoveToNH) == MoveToNH)
	{
#if _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_
		std::cout << "FLAG ----------------------------Y+" << std::endl;
#endif
		this->Get_State_Loc()._Coord_Y += static_cast<float>(0.35f * Scale);
		this->Get_Move_Distance()._Coord_Y -= static_cast<float>(0.35f * Scale);
	}
	if ((Moves & MoveToPH) == MoveToPH)
	{
#if _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_
		std::cout << "FLAG ----------------------------Y-" << std::endl;
#endif
		this->Get_State_Loc()._Coord_Y -= static_cast<float>(0.35f * Scale);
		this->Get_Move_Distance()._Coord_Y += static_cast<float>(0.35f * Scale);
	}
	if ((Moves & MoveToNW) == MoveToNW)
	{
#if _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_
		std::cout << "FLAG ----------------------------X+" << std::endl;
#endif
		this->Get_State_Loc()._Coord_X += static_cast<float>(0.35f * Scale);
		this->Get_Move_Distance()._Coord_X -= static_cast<float>(0.35f * Scale);
	}
	if ((Moves & MoveToPW) == MoveToPW)
	{
#if _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_
		std::cout << "FLAG ----------------------------X-" << std::endl;
#endif
		this->Get_State_Loc()._Coord_X -= static_cast<float>(0.35f * Scale);
		this->Get_Move_Distance()._Coord_X += static_cast<float>(0.35f * Scale);
	}
}

void GameStateBase::Set_Trigger_Mode(bool Mode)
{
	this->_Trigger_Mode = Mode;
}

void GameStateBase::Generate_StateBlock(int State_Id)
{
#if _TANXL_GAMESTATE_GENERATE_STATE_OUTPUT_
	std::cout << std::endl << "Generate_StateBlock " << State_Id << " CALLED" << std::endl;
#endif
	try
	{
		this->_Data_Base.Id_Link_Locate(1, State_Id);
	}
	catch (std::string)
	{
		if (State_Id < 65536)
		{
			Set_Data_Size(this->_Data_Size + 1);

			this->_Data_Base.Append_DataChain(RandomBase::GenerateAutoSeed(), 10, 1, State_Id);
			this->_Data_Base.Append_DataChain(RandomBase::Generate_State(10, 10, true), 0, 1, State_Id);

			this->_Data_Base.Append_DataChain("NULL", 0, 1, State_Id);
			this->_Data_Base.Append_DataChain("NULL", 0, 1, State_Id);
			this->_Data_Base.Append_DataChain("NULL", 0, 1, State_Id);
			this->_Data_Base.Append_DataChain("NULL", 0, 1, State_Id);
			this->_Data_Base.Append_DataChain("NULL", 0, 1, State_Id);
			this->_Data_Base.Append_DataChain("NULL", 0, 1, State_Id);
			this->_Data_Base.Append_DataChain("NULL", 0, 1, State_Id);
			this->_Data_Base.Append_DataChain("NULL", 0, 1, State_Id);

			Build_Connect(State_Id);
		}
	}
}

void GameStateBase::Build_Connect(int State_Id)
{
	std::vector<Data_Unit*>* Build_Target{ &this->_Data_Base.Id_Link_Locate(1, State_Id)->_Data->_Data_Units };

	Single_Connect(Build_Target, STATE_LEFT, State_Id - 1);
	Single_Connect(Build_Target, STATE_RIGH, State_Id + 1, 1);
	Single_Connect(Build_Target, STATE_BELO, State_Id + 256);
	Single_Connect(Build_Target, STATE_LEFT_BELO, State_Id + 255, -1);
	Single_Connect(Build_Target, STATE_RIGH_BELO, State_Id + 257, 1);
	Single_Connect(Build_Target, STATE_ABOV, State_Id - 256);
	Single_Connect(Build_Target, STATE_LEFT_ABOV, State_Id - 257, -1);
	Single_Connect(Build_Target, STATE_RIGH_ABOV, State_Id - 255, -1);
}

void GameStateBase::Replace_State(int Cover_Id, SExtend_State& State_Target, SExtend_State& State_Id)
{
	this->Set_State(Cover_Id, State_Target.Get_Stand_Data());
	std::vector<StateUnit*>().swap(*State_Target._Data);
	State_Target._Id = State_Id._Id;
	State_Target._Data->assign(State_Id._Data->begin(), State_Id._Data->end());
}

void GameStateBase::Move_State(EMove_State_EventId Direction, int Times)
{
	while (Times--)
		this->_MState.Set_Move_State(Direction);
}

void GameStateBase::Update_Last_Location()
{
	static int Dist_Mid{ this->_Distance_Screen_Mid };
	this->_Location_Distance_Mid = LocationBase::GetLocationBase().Get_LocationS(Dist_Mid);
	this->_Location_Move_Distance = this->Get_Move_Distance();
}

void GameStateBase::State_Check_Event()
{
	static SoundBase* SB{ &SoundBase::GetSoundBase() };
	static Tanxl_Achievement* AC{ &Tanxl_Achievement::Get_AchievementBase() };
	static GameObject* MC{ Main_Character::Get_Main_Character() };
	static bool Achievement{ true };
	this->Update_Move(0.0f, 0.0f, CHECK_EDGE_CURR);
	StateUnit* CheckUnit{ this->Get_State() };
	if (!CheckUnit)
		return;
	int Unit_State_Id{ CheckUnit->Get_Extra_Status() };

	AC->CheckAchievement(g_rgAchievements[1]);

	if ((MC->Get_Money() >= 100) && Achievement)
	{
		Achievement = false;
		if (AC->RequestStats())
		{
			std::cout << "Achievement Unlocked !" << std::endl;
			AC->UnlockAchievement(g_rgAchievements[1]);
			SB->Play_Sound(SOUND_ACHIEVEMENT);
		}
		else
		{
			std::cout << "Achievement Request Fail !" << std::endl;
		}
	}

	if (Unit_State_Id == 2)
	{
		if (MC->Get_Is_Alive())
		{
			SB->Play_Sound(SOUND_EVENT_START);
			MC->TakeDamage(1);
			MC->Add_Money(1);

			CheckUnit->Set_Status(0);
		}
	}
	else if (Unit_State_Id == 3)
	{
		SB->Play_Sound(SOUND_RESTORE_HEALTH);
		MC->Add_Money(5);

		CheckUnit->Set_Status(0);
	}
	else if (Unit_State_Id == 4)
	{
		if (MC->Check_Health() < MC->Get_MaxHealth())
		{
			SB->Play_Sound(SOUND_SYSTEM_CALL);
			MC->RestoreHealth(1);
			CheckUnit->Set_Status(0);
		}
	}
	else if (Unit_State_Id == 5)
	{
		static int Internal_Cnt{ 0 };
		Internal_Cnt++;
		SB->Play_Sound(SOUND_SECRET_CORE);
		CheckUnit->Set_Status(0);

		if (Internal_Cnt == 4)
		{
			Internal_Cnt = 0;
			std::cout << "Achievement Unlocked !" << std::endl;
			AC->UnlockAchievement(g_rgAchievements[0]);
			SB->Play_Sound(SOUND_ACHIEVEMENT);
		}

		std::cout << "Secret Core Found !" << std::endl;
	}
}

void GameStateBase::HitEdge_Check()
{
	static double State_Data_Width{ this->_Data_Width * this->_Each_Width * 2 + this->_Each_Width };
	static double State_Data_Height{ this->_Data_Height * this->_Each_Height * 2 + this->_Each_Height };

	static Tanxl_Coord<float>* Distance{ &LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move) };

	if (this->Get_Last_Move()._Coord_X < 0)
	{
		if (Distance->_Coord_X < -static_cast<int>(this->Get_DataWidth()) - 1)
		{
			this->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
			this->Get_Move_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
#if _TANXL_GAMESTATE_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "LEFT RES :" << this->_Location_Distance_Mid._Coord_X << std::endl;
#endif
		}
		else
		{
			for (int i{ 0 }; i < 2; ++i)
			{
				this->Update_Move(this->Get_Last_Move()._Coord_X, 0.0f, CHECK_EDGE_LEFT);

				if (this->_Exac_Location._Coord_X >= -static_cast<int>(this->Get_DataWidth()) - 1)
					this->State_Check_Block(CHECK_EDGE_LEFT);
			}
		}
	}
	else if (this->Get_Last_Move()._Coord_X > 0)
	{
		if (Distance->_Coord_X > State_Data_Width)
		{
			this->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
			this->Get_Move_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
#if _TANXL_GAMESTATE_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "RIGH RES :" << this->_Location_Distance_Mid._Coord_X << std::endl;
#endif
		}
		else
		{
			for (int i{ 0 }; i < 2; ++i)
			{
				this->Update_Move(this->Get_Last_Move()._Coord_X, 0.0f, CHECK_EDGE_RIGH);

				if (this->_Exac_Location._Coord_X <= static_cast<int>(this->Get_DataWidth()) * 2 + 1)
					this->State_Check_Block(CHECK_EDGE_RIGH);
			}
		}
	}

	if (this->Get_Last_Move()._Coord_Y > 0)
	{
		if (Distance->_Coord_Y > this->Get_DataHeight() + 1)
		{
			this->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
			this->Get_Move_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
#if _TANXL_GAMESTATE_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "ABOV RES :" << this->_Location_Distance_Mid._Coord_Y << std::endl;
#endif
		}
		else
		{
			for (int i{ 0 }; i < 2; ++i)
			{
				this->Update_Move(0.0f, this->Get_Last_Move()._Coord_Y, CHECK_EDGE_ABOV);

				if (this->_Exac_Location._Coord_Y >= -static_cast<int>(this->Get_DataHeight()) - 1)
					this->State_Check_Block(CHECK_EDGE_ABOV);
			}
		}
	}
	else if (this->Get_Last_Move()._Coord_Y < 0)
	{
		if (Distance->_Coord_Y < -State_Data_Height)
		{
			this->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
			this->Get_Move_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
#if _TANXL_GAMESTATE_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "DOWN RES :" << this->_Location_Distance_Mid._Coord_Y << std::endl;
#endif
		}
		else
		{
			for (int i{ 0 }; i < 2; ++i)
			{
				this->Update_Move(0.0f, this->Get_Last_Move()._Coord_Y, CHECK_EDGE_BELO);

				if (this->_Exac_Location._Coord_Y <= static_cast<int>(this->Get_DataHeight()) * 2 + 1)
					this->State_Check_Block(CHECK_EDGE_BELO);
			}
		}
	}
}

void GameStateBase::Move_Adjust()
{
	Tanxl_Coord<float>& State_Loc{ LocationBase::GetLocationBase().Get_LocationS(this->_State_Loc) };
	if (!this->_Is_Adjusting || this->_Adjust_While_Move)//Move Adjust Part
	{
		this->_Is_Adjusting = true;

		if (this->_New_Current_Loc._Coord_Y != this->_Current_Move._Coord_Y)
		{
#if _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_
			std::cout << "NCUH __ " << this->_New_Current_Loc._Coord_Y << " CUH __ " << this->_Current_Move._Coord_Y << std::endl;
#endif
			int TempVal{ this->_New_Current_Loc._Coord_Y };
#if _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_
			std::cout << "NCUH != CUH !_Is_Adjusting RELOAD" << std::endl;
#endif
			if (this->_New_Current_Loc._Coord_Y > this->_Current_Move._Coord_Y)
			{
				while (this->_New_Current_Loc._Coord_Y-- > this->_Current_Move._Coord_Y)
				{
#if _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_
					std::cout << "Adjust_Flag() __HN---" << this->_Is_Adjusting << std::endl;
#endif
					this->_MState.Set_Move_State(MoveToNH);
					State_Loc._Coord_Y -= static_cast<float>(this->_Each_Height);
				}
			}
			else if (this->_New_Current_Loc._Coord_Y < this->_Current_Move._Coord_Y)
			{
				while (this->_New_Current_Loc._Coord_Y++ < this->_Current_Move._Coord_Y)
				{
#if _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_
					std::cout << "Adjust_Flag() __HP___" << this->_Is_Adjusting << std::endl;
#endif
					this->_MState.Set_Move_State(MoveToPH);
					State_Loc._Coord_Y += static_cast<float>(this->_Each_Height);
				}
			}
			this->_Current_Move._Coord_Y = TempVal;
		}

		if (this->_New_Current_Loc._Coord_X != this->_Current_Move._Coord_X)
		{
#if _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_
			std::cout << "NCUW __ " << this->_New_Current_Loc._Coord_X << " CUW __ " << this->_Current_Move._Coord_X << std::endl;
#endif
			int TempVal{ this->_New_Current_Loc._Coord_X };
#if _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_
			std::cout << "NCUW != CUW !_Is_Adjusting RELOAD" << std::endl;
#endif
			if (this->_New_Current_Loc._Coord_X > this->_Current_Move._Coord_X)
			{
				while (this->_New_Current_Loc._Coord_X-- > this->_Current_Move._Coord_X)
				{
#if _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_
					std::cout << "Adjust_Flag() __WN---" << this->_Is_Adjusting << std::endl;
#endif
					this->_MState.Set_Move_State(MoveToPW);
					State_Loc._Coord_X -= static_cast<float>(this->_Each_Width);
				}
			}
			else if (this->_New_Current_Loc._Coord_X < this->_Current_Move._Coord_X)
			{
				while (this->_New_Current_Loc._Coord_X++ < this->_Current_Move._Coord_X)
				{
#if _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_
					std::cout << "Adjust_Flag() __WP---" << this->_Is_Adjusting << std::endl;
#endif
					this->_MState.Set_Move_State(MoveToNW);
					State_Loc._Coord_X += static_cast<float>(this->_Each_Width);
				}
			}
			this->_Current_Move._Coord_X = TempVal;
		}
	}
}

void GameStateBase::State_Check_Block(ECheck_Edge Check_Direction)
{
	float Check_Range{ 1.0f };
	static double LastTime{ glfwGetTime() };
	double DeltaTime{ glfwGetTime() - LastTime };
	LastTime = glfwGetTime();

	float Marg_Width{ static_cast<float>(this->_Each_Width * 10) };
	float Marg_Height{ static_cast<float>(this->_Each_Height * 10) };

	int State_Unit_Width{ static_cast<int>(this->_Data_Width) + 1 };
	int State_Unit_Height{ static_cast<int>(this->_Data_Height) + 1 };

	bool Reset{ this->Check_Edge_Reached(Check_Direction) };

	if ((this->Get_State() == nullptr) ||
		(this->Get_State()->Get_Extra_Status() == 1))
	{
		switch (Check_Direction)
		{
		case CHECK_EDGE_LEFT:
		case CHECK_EDGE_RIGH:
			this->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
			this->Get_Move_Distance()._Coord_X = this->_Location_Move_Distance._Coord_X;
			break;
		case CHECK_EDGE_BELO:
		case CHECK_EDGE_ABOV:
			this->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
			this->Get_Move_Distance()._Coord_Y = this->_Location_Move_Distance._Coord_Y;
			break;
		}

		while (true)
		{
			this->Update_Move(0.0f, 0.0f, Check_Direction);
			if ((this->Get_State() == nullptr) ||
				(this->Get_State()->Get_Extra_Status() == 1))
			{
				//std::cout << "Adjusting" << DeltaTime << std::endl;
				if (DeltaTime < 0.1f)
					Check_Range = 0.0035f;
				else
				{
					Check_Range = static_cast<float>(Check_Range * DeltaTime);
					if (Check_Range < 0.0035f)
						Check_Range = 0.0035f;
				}

				switch (Check_Direction)
				{
				case CHECK_EDGE_LEFT:
					this->_Location_Distance_Mid._Coord_X += Check_Range;
					this->_Location_Move_Distance._Coord_X += Check_Range;

					this->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
					this->Get_Move_Distance()._Coord_X = this->_Location_Move_Distance._Coord_X;
					break;
				case CHECK_EDGE_RIGH:
					this->_Location_Distance_Mid._Coord_X -= Check_Range;
					this->_Location_Move_Distance._Coord_X -= Check_Range;

					this->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
					this->Get_Move_Distance()._Coord_X = this->_Location_Move_Distance._Coord_X;
					break;
				case CHECK_EDGE_BELO:
					this->_Location_Distance_Mid._Coord_Y += Check_Range;
					this->_Location_Move_Distance._Coord_Y += Check_Range;

					this->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
					this->Get_Move_Distance()._Coord_Y = this->_Location_Move_Distance._Coord_Y;
					break;
				case CHECK_EDGE_ABOV:
					this->_Location_Distance_Mid._Coord_Y -= Check_Range;
					this->_Location_Move_Distance._Coord_Y -= Check_Range;

					this->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
					this->Get_Move_Distance()._Coord_Y = this->_Location_Move_Distance._Coord_Y;
					break;
				}
			}
			else
				break;
		}
	}
	else if (Reset)
	{
		std::cout << "Enter Adjust Map" << std::endl;

		switch (Check_Direction)
		{
		case CHECK_EDGE_LEFT:
			this->Get_Move_Distance()._Coord_X += Marg_Width;
			break;
		case CHECK_EDGE_RIGH:
			this->Get_Move_Distance()._Coord_X -= Marg_Width;
			break;
		case CHECK_EDGE_BELO:
			this->Get_Move_Distance()._Coord_Y += Marg_Height;
			break;
		case CHECK_EDGE_ABOV:
			this->Get_Move_Distance()._Coord_Y -= Marg_Height;
			break;
		}

		this->Update_Move(0.0f, 0.0f, Check_Direction);

		this->Update_State(Check_Direction);
	}
}

void GameStateBase::Update_State(ECheck_Edge Check_Direction)
{
	int State_Unit_Width{ static_cast<int>(this->_Data_Width) + 1 };
	int State_Unit_Height{ static_cast<int>(this->_Data_Height) + 1 };

	int Temp_Height{ this->_New_Current_Loc._Coord_Y };
	int Temp_Width{ this->_New_Current_Loc._Coord_X };

	this->_New_Current_Loc._Coord_Y = -static_cast<int>((this->Get_Move_Distance()._Coord_Y + 2.0f) / this->_Each_Height);
	this->_New_Current_Loc._Coord_X = -static_cast<int>((this->Get_Move_Distance()._Coord_X - 2.0f) / this->_Each_Width);

	switch (Check_Direction)
	{
	case CHECK_EDGE_LEFT:
		this->_Current_Move._Coord_Y -= (Temp_Height - this->_New_Current_Loc._Coord_Y);
		this->_Current_Move._Coord_X -= (Temp_Width - this->_New_Current_Loc._Coord_X + 1);

		this->Reload_Display_State(STATE_EXTEND_LEFT);
		this->Move_State(MoveToNW, State_Unit_Width);
		break;
	case CHECK_EDGE_RIGH:
		this->_Current_Move._Coord_Y -= (Temp_Height - this->_New_Current_Loc._Coord_Y);
		this->_Current_Move._Coord_X -= (Temp_Width - this->_New_Current_Loc._Coord_X - 1);

		this->Reload_Display_State(STATE_EXTEND_RIGH);
		this->Move_State(MoveToPW, State_Unit_Width);
		break;
	case CHECK_EDGE_BELO:
		this->_Current_Move._Coord_Y -= (Temp_Height - this->_New_Current_Loc._Coord_Y + 1);
		this->_Current_Move._Coord_X -= (Temp_Width - this->_New_Current_Loc._Coord_X);

		this->Reload_Display_State(STATE_EXTEND_BELO);
		this->Move_State(MoveToPH, State_Unit_Height);
		break;
	case CHECK_EDGE_ABOV:
		this->_Current_Move._Coord_Y -= (Temp_Height - this->_New_Current_Loc._Coord_Y - 1);
		this->_Current_Move._Coord_X -= (Temp_Width - this->_New_Current_Loc._Coord_X);

		this->Reload_Display_State(STATE_EXTEND_ABOV);
		this->Move_State(MoveToNH, State_Unit_Height);
		break;
	}
}

GameStateBase::GameStateBase(int Width, int Height) :
	_GameState_Length(Width, Height), _GameState_Adjust(0.0f), _Compile_Success(false), _Extend_Mid_Id(0),
	_MState(0), _Data_Height(Height), _Data_Width(Width), _Is_Adjusting(false), Tanxl_ClassBase("1.1"),
	_Adjust_Enable(false), _Exac_Location(0, 0), _GameState_Extend(), _Is_Data_Set(false)
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };
	this->_Distance_Move = LCB->New_Location_set("Distance_Move");
	this->_Distance_Screen_Mid = LCB->New_Location_set("Distance_Screen_Mid");
	this->_State_Loc = LCB->New_Location_set("State_Move_Location");
	this->_Last_Move = LCB->New_Location_set("Last_Move");

	this->_Each_Height = 2.0f / this->_GameState_Length._Coord_Y;//10 0.2
	this->_Each_Width = 2.0f / this->_GameState_Length._Coord_X;//10 0.2

	this->_GameState_Extend._MIDD._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._ABOV._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._BELO._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT_ABOV._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT_BELO._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH_ABOV._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH_BELO._Data = new std::vector<StateUnit*>;
}

GameStateBase::~GameStateBase()
{
	Clear_Display_Vector(STATE_EXTEND_SPEC);
}

//GameEvent

std::string GameEvent::GetEventName()
{
	return this->_EventName;
}

void GameEvent::Set_EventTarget(GameObject* Obejct)
{
	this->_GameObejct = Obejct;
}

//GameEventBase

GameEventBase::GameEventBase() :_GameEvents(NULL), Tanxl_ClassBase("0.1") {}

GameEventBase::~GameEventBase()
{
	std::vector<GameEvent*>().swap(this->_GameEvents);
	delete& _GameEvents;
}

GameEventBase::GameEventBase(const GameEventBase&) :_GameEvents(NULL), Tanxl_ClassBase("0.1") {}

GameEventBase& GameEventBase::operator=(const GameEventBase&) { return *this; }

//StateUnit

int StateUnit::Get_Extra_Status() const
{
	return this->_Extra_Status;
}

int StateUnit::Get_State_Id() const
{
	return this->_State_Id;
}

void StateUnit::Set_State_Id(int State_Id)
{
	this->_State_Id = State_Id;
}

void StateUnit::Set_Status(int Extra_Status)
{
	this->_Extra_Status = Extra_Status;
}

//GameStateBase

void GameStateBase::Set_CurrentLoc(float& CurrentX, float& CurrentY) const
{
	static Tanxl_Coord<float>* Distance{ &LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move) };
	Distance->_Coord_X = CurrentX;
	Distance->_Coord_Y = CurrentY;
}

void GameStateBase::Set_Compile_Policy(std::string State_Name, int Set_To_Status)
{
	this->_Policy.push_back(new State_Policy(State_Name, Set_To_Status));
}

void GameStateBase::Set_Data_Size(int Size)
{
	this->_Data_Size = Size;
}

unsigned GameStateBase::Get_DataHeight()const
{
	return this->_Data_Height;
}

unsigned GameStateBase::Get_DataWidth()const
{
	return this->_Data_Width;
}

void GameStateBase::Set_Adjust(float Adjust)
{
	this->_GameState_Adjust = Adjust;
}

void GameStateBase::Set_Enable_Adjust(bool Enable_Adjust, bool Enable_While_Move)
{
	this->_Adjust_Enable = Enable_Adjust;
	this->_Adjust_While_Move = Enable_While_Move;
}

bool GameStateBase::Is_State_Exist(EState_Extend State_Id)
{
	switch (State_Id)
	{
	case STATE_EXTEND_MIDD:
		return ((this->_GameState_Extend._MIDD._Data) &&
			(this->_GameState_Extend._MIDD._Data->size() != 0));
	case STATE_EXTEND_LEFT:
		return ((this->_GameState_Extend._LEFT._Data) &&
			(this->_GameState_Extend._LEFT._Data->size() != 0));
	case STATE_EXTEND_RIGH:
		return ((this->_GameState_Extend._RIGH._Data) &&
			(this->_GameState_Extend._RIGH._Data->size() != 0));
	case STATE_EXTEND_ABOV:
		return ((this->_GameState_Extend._ABOV._Data) &&
			(this->_GameState_Extend._ABOV._Data->size() != 0));
	case STATE_EXTEND_BELO:
		return ((this->_GameState_Extend._BELO._Data) &&
			(this->_GameState_Extend._BELO._Data->size() != 0));
	case STATE_EXTEND_LEFT_ABOV:
		return ((this->_GameState_Extend._LEFT_ABOV._Data) &&
			(this->_GameState_Extend._LEFT_ABOV._Data->size() != 0));
	case STATE_EXTEND_LEFT_BELO:
		return ((this->_GameState_Extend._LEFT_BELO._Data) &&
			(this->_GameState_Extend._LEFT_BELO._Data->size() != 0));
	case STATE_EXTEND_RIGH_ABOV:
		return ((this->_GameState_Extend._RIGH_ABOV._Data) &&
			(this->_GameState_Extend._RIGH_ABOV._Data->size() != 0));
	case STATE_EXTEND_RIGH_BELO:
		return ((this->_GameState_Extend._RIGH_BELO._Data) &&
			(this->_GameState_Extend._RIGH_BELO._Data->size() != 0));
	}
	return 0;
}

StateUnit* GameStateBase::Get_StateUnit(EState_Extend State, int Pos)
{
	switch (State)
	{
	case STATE_EXTEND_MIDD:
		return this->_GameState_Extend._MIDD._Data->at(Pos);
	case STATE_EXTEND_LEFT:
		return this->_GameState_Extend._LEFT._Data->at(Pos);
	case STATE_EXTEND_RIGH:
		return this->_GameState_Extend._RIGH._Data->at(Pos);
	case STATE_EXTEND_ABOV:
		return this->_GameState_Extend._ABOV._Data->at(Pos);
	case STATE_EXTEND_BELO:
		return this->_GameState_Extend._BELO._Data->at(Pos);
	case STATE_EXTEND_LEFT_ABOV:
		return this->_GameState_Extend._LEFT_ABOV._Data->at(Pos);
	case STATE_EXTEND_LEFT_BELO:
		return this->_GameState_Extend._LEFT_BELO._Data->at(Pos);
	case STATE_EXTEND_RIGH_ABOV:
		return this->_GameState_Extend._RIGH_ABOV._Data->at(Pos);
	case STATE_EXTEND_RIGH_BELO:
		return this->_GameState_Extend._RIGH_BELO._Data->at(Pos);
	}
	return nullptr;
}

StateUnit* GameStateBase::Get_State(int LocationX, int LocationY)
{
	StateUnit* Unit{ nullptr };
	if (LocationX > static_cast<int>(this->_Data_Width))
	{
		if (LocationY > static_cast<int>(this->_Data_Height))
		{
			if (this->Is_State_Exist(STATE_EXTEND_RIGH_BELO))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "RIGH BELO AREA" << LocationX << "_" << LocationY << "_"
					<< (LocationY - Get_DataHeight() - 1) * (Get_DataWidth() + 1) + LocationX - Get_DataWidth() - 1 << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_RIGH_BELO, (LocationY - Get_DataHeight() - 1) * (Get_DataWidth() + 1) + LocationX - Get_DataWidth() - 1);
			}
		}
		else if (LocationY >= 0)
		{
			if (Is_State_Exist(STATE_EXTEND_RIGH))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "RIGH AREA" << LocationX << "_" << LocationY << "_"
					<< LocationY * (Get_DataWidth() + 1) + LocationX - Get_DataWidth() - 1 << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_RIGH, LocationY * (Get_DataWidth() + 1) + LocationX - Get_DataWidth() - 1);
			}
		}
		else if (LocationY >= -static_cast<int>(Get_DataHeight()))
		{
			if (Is_State_Exist(STATE_EXTEND_RIGH_ABOV))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "RIGH ABOV AREA" << LocationX << "_" << LocationY << "_"
					<< (LocationY + Get_DataHeight() + 1) * (Get_DataWidth() + 1) + LocationX << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_RIGH_ABOV, (LocationY + Get_DataHeight() + 1) * (Get_DataWidth() + 1) + LocationX - Get_DataWidth() - 1);
			}
		}
	}
	else if (LocationX >= 0)
	{
		if (LocationY > static_cast<int>(Get_DataHeight()))
		{
			if (Is_State_Exist(STATE_EXTEND_BELO))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "BELO AREA" << LocationX << "_" << LocationY << "_"
					<< (LocationY - Get_DataHeight() - 1) * (Get_DataWidth() + 1) + LocationX << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_BELO, (LocationY - Get_DataHeight() - 1) * (Get_DataWidth() + 1) + LocationX);
			}
		}
		else if (LocationY >= 0)
		{
			if (Is_State_Exist(STATE_EXTEND_MIDD))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "MIDD AREA" << LocationX << "_" << LocationY << "_"
					<< LocationY * (Get_DataWidth() + 1) + LocationX << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_MIDD, LocationY * (Get_DataWidth() + 1) + LocationX);
			}
		}
		else if (LocationY >= -static_cast<int>(Get_DataHeight()))
		{
			if (Is_State_Exist(STATE_EXTEND_ABOV))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "ABOV AREA" << LocationX << "_" << LocationY << "_"
					<< (LocationY + Get_DataHeight() + 1) * (Get_DataWidth() + 1) + LocationX << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_ABOV, (LocationY + Get_DataHeight() + 1) * (Get_DataWidth() + 1) + LocationX);
			}
		}
	}
	else if (LocationX >= -static_cast<int>(Get_DataWidth()))
	{
		if (LocationY > static_cast<int>(Get_DataHeight()))
		{
			if (Is_State_Exist(STATE_EXTEND_LEFT_BELO))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "LEFT BELO AREA" << LocationX << "_" << LocationY << "_"
					<< (LocationY - Get_DataHeight() - 1) * (Get_DataWidth() + 1) + LocationX + Get_DataWidth() + 1 << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_LEFT_BELO, (LocationY - Get_DataHeight() - 1) * (Get_DataWidth() + 1) + LocationX + Get_DataWidth() + 1);
			}
		}
		else if (LocationY >= 0)
		{
			if (Is_State_Exist(STATE_EXTEND_LEFT))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "LEFT AREA" << LocationX << "_" << LocationY << "_"
					<< LocationY * (Get_DataWidth() + 1) + LocationX + Get_DataWidth() + 1 << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_LEFT, LocationY * (Get_DataWidth() + 1) + LocationX + Get_DataWidth() + 1);
			}
		}
		else if (LocationY >= -static_cast<int>(Get_DataHeight()))
		{
			if (Is_State_Exist(STATE_EXTEND_LEFT_ABOV))
			{
#if _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_
				std::cout << "LEFT ABOV AREA" << LocationX << "_" << LocationY << "_"
					<< (LocationY + Get_DataHeight() + 1) * (Get_DataWidth() + 1) + LocationX + Get_DataWidth() + 1 << std::endl;
#endif
				Unit = Get_StateUnit(STATE_EXTEND_LEFT_ABOV, (LocationY + Get_DataHeight() + 1) * (Get_DataWidth() + 1) + LocationX + Get_DataWidth() + 1);
			}
		}
	}
	return Unit;
}

Id_Link* GameStateBase::Locate_Link(std::string Link_Name)
{
	for (int i{ 1 }; i < (this->_Data_Size + 1); ++i)
	{
		Id_Link* Link{ this->_Data_Base.Id_Link_Search(i) };
#if _TANXL_GAMESTATE_LINK_SEARCH_DATA_OUTPUT_
		std::cout << i << " : " << Link->_Data->_Data_Units.at(0)->_Data << std::endl;
#endif
		if (Link->_Data->_Data_Units.at(0)->_Data == Link_Name)
			return Link;
	}
	return nullptr;
}

GameStateBase::GameStateBase(const GameStateBase&) :_GameState_Length(0, 0), _GameState_Adjust(0), _Extend_Mid_Id(0),
_Compile_Success(false), _MState(0), _Data_Height(0), _Data_Width(0), _Is_Adjusting(false), Tanxl_ClassBase("1.1"),
_Adjust_Enable(false), _Exac_Location(0, 0), _GameState_Extend(), _Is_Data_Set(false)
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };
	this->_Distance_Move = LCB->New_Location_set("Distance_Move");
	this->_Distance_Screen_Mid = LCB->New_Location_set("Distance_Screen_Mid");
	this->_Last_Move = LCB->New_Location_set("Last_Move");

	this->_Each_Height = 2.0f / this->_GameState_Length._Coord_Y;//10 0.2
	this->_Each_Width = 2.0f / this->_GameState_Length._Coord_X;//10 0.2

	this->_GameState_Extend._MIDD._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._ABOV._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._BELO._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT_ABOV._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT_BELO._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH_ABOV._Data = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH_BELO._Data = new std::vector<StateUnit*>;
}

GameStateBase& GameStateBase::operator=(const GameStateBase&) { return *this; }

bool GameStateBase::Get_Compile_Status() const
{
	return this->_Compile_Success;
}

void GameStateBase::Check_Adjust_Status(bool Is_Key_Pressed)
{
	if (!this->_Adjust_While_Move)
	{
		if (Is_Key_Pressed)
			this->_Is_Adjusting = false;
		else
			this->_Is_Adjusting = true;
	}
}

bool GameStateBase::Get_Engine_File()
{
	if (!this->_Is_Data_Set)
	{
		this->_Is_Data_Set = true;
		if (!this->_Data_Base.Get_LocalData("Tanxl Engine SystemInfor"))
			return false;
}
	return true;
}

bool GameStateBase::Check_Edge_Reached(ECheck_Edge Check) const
{
	switch (Check)
	{
	case CHECK_EDGE_LEFT:
		if (this->_Exac_Location._Coord_X < 0)
			return true;
		break;
	case CHECK_EDGE_RIGH:
		if (this->_Exac_Location._Coord_X > 10)
			return true;
		break;
	case CHECK_EDGE_BELO:
		if (this->_Exac_Location._Coord_Y > 10)
			return true;
		break;
	case CHECK_EDGE_ABOV:
		if (this->_Exac_Location._Coord_Y < 0)
			return true;
		break;
	}
	return false;
}

Tanxl_Coord<int> GameStateBase::Get_Exac_Location() const
{
	return this->_Exac_Location;
}

Tanxl_Coord<int> GameStateBase::Get_StateLength()const
{
	return this->_GameState_Length;
}

EMove_State_EventId GameStateBase::Auto_Update_Trigger(short Edge)
{
	return static_cast<EMove_State_EventId>(Edge);
}

std::vector<StateUnit*>* GameStateBase::Get_GameState(EState_Extend State_Id) const
{
	switch (State_Id)
	{
	case STATE_EXTEND_MIDD:
		return this->_GameState_Extend._MIDD._Data;
	case STATE_EXTEND_LEFT:
		return this->_GameState_Extend._LEFT._Data;
	case STATE_EXTEND_RIGH:
		return this->_GameState_Extend._RIGH._Data;
	case STATE_EXTEND_ABOV:
		return this->_GameState_Extend._ABOV._Data;
	case STATE_EXTEND_BELO:
		return this->_GameState_Extend._BELO._Data;
	case STATE_EXTEND_LEFT_ABOV:
		return this->_GameState_Extend._LEFT_ABOV._Data;
	case STATE_EXTEND_LEFT_BELO:
		return this->_GameState_Extend._LEFT_BELO._Data;
	case STATE_EXTEND_RIGH_ABOV:
		return this->_GameState_Extend._RIGH_ABOV._Data;
	case STATE_EXTEND_RIGH_BELO:
		return this->_GameState_Extend._RIGH_BELO._Data;
	}
	return nullptr;
}

State_Policy::State_Policy(std::string Name, int State_Status)
	:_Name(Name), _State_Status(State_Status) {}

SExtend_State::SExtend_State(std::string Id, std::vector<StateUnit*>* Data)
	:_Id(Id), _Data(Data) {}

std::string SExtend_State::Get_Stand_Data()
{
	std::string Data{};
	for (int i{ 0 }; i < this->_Data->size(); ++i)
	{
		Data += std::to_string(this->_Data->at(i)->Get_Extra_Status()) + "-" +
			std::to_string(this->_Data->at(i)->Get_State_Id()) + ",";
	}
	return Data;
}

StateEvent::StateEvent(int State_Id, int Counts)
	:_State_Id(State_Id), _Trigger_Counts(Counts), _Event_Enable(false) {}

bool StateEvent::Check_State_Id(int State_Id)
{
	if (this->_State_Id == State_Id)
	{
		this->_Trigger_Counts--;
		if (this->_Trigger_Counts < 0)
		{
			this->_Trigger_Counts = 0;
			this->_Event_Enable = true;
		}
		return true;
	}
	return false;
}

bool StateEvent::Check_Event_Status() const
{
	return this->_Event_Enable;
}

//Square_State

Square_State::Square_State(int NX, int PX, int NY, int PY, int StateWidth, int StateHeight) :
	_Move_NX(NY), _Move_NY(NY), _Move_PX(PX), _Move_PY(PY), _State_Width(StateWidth), _State_Height(StateHeight) {};

void Square_State::Set_Move_State(int PreSetX, int PreSetY, int PreLoad)
{
	this->_Move_NX = 0 - PreLoad + PreSetX;
	this->_Move_PX = this->_State_Width - 1 + PreLoad + PreSetX;
	this->_Move_NY = 0 - PreLoad + PreSetY;
	this->_Move_PY = this->_State_Height - 1 + PreLoad + PreSetY;
}

void Square_State::Set_Move_State(int NX, int PX, int NY, int PY)
{
	this->_Move_NX = NX;
	this->_Move_PX = PX;
	this->_Move_NY = NY;
	this->_Move_PY = PY;
}

void Square_State::Set_Move_State(EMove_State_EventId Event_Id, int Multi_Set)
{
	if ((Event_Id & MoveToNW) != 0)
	{
		this->_Move_NX += Multi_Set;
		this->_Move_PX += Multi_Set;
	}
	else if ((Event_Id & MoveToPW) != 0)
	{
		this->_Move_NX -= Multi_Set;
		this->_Move_PX -= Multi_Set;
	}

	if ((Event_Id & MoveToNH) != 0)
	{
		this->_Move_NY += Multi_Set;
		this->_Move_PY += Multi_Set;
	}
	else if ((Event_Id & MoveToPH) != 0)
	{
		this->_Move_NY -= Multi_Set;
		this->_Move_PY -= Multi_Set;
	}
}

void Square_State::Set_State_Length(int Width, int Height)
{
	this->_State_Width = Width;
	this->_State_Height = Height;
}
