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
		return this->_Data_Base.Get_Specified(1, Location, 0)->_Data;
	return "NULL";
}

void GameStateBase::Clear_Display_Vector(EState_Extend Clear_Id)
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

void GameStateBase::Set_StartState(int State_Id, std::string Cover_String)
{
	if (this->Get_Engine_File())
	{
		Id_Link* Link{ this->_Data_Base.Id_Link_Locate(1, State_Id) };
		std::string Data_Name{ Link->_Data->_Data_Units.at(0)->_Data };
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
		return;
	}
}

void GameStateBase::Set_State(int State_Id, std::string Cover_String)
{
	if (this->Get_Engine_File())
	{
		std::string Data_Name{ this->Get_State_Id(State_Id) };
		for (int i{ 0 }; i < (this->_State_WidthS * this->_State_HeightS); ++i)
		{
			Id_Link* Link{ this->_Data_Base.Id_Link_Search(i) };
			if (Link->_Data->_Data_Units.at(0)->_Data == Data_Name)
			{
				Link->_Data->_Data_Units.at(1)->_Data = Cover_String;
				return;
			}
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

Tanxl_Coord<float>& GameStateBase::Get_Screen_Distance()
{
	return LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Screen_Mid);
}

Tanxl_Coord<float>& GameStateBase::Get_Move_Distance()
{
	return LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move);
}

float GameStateBase::Set_ExacHeight(double Current, float& MoveState, float& State_MoveY, double Scale)
{
	if (_Adjust_Enable == false)
		return 0.0f;
	float Temp_Move{};
	float Temp_GameState_Adjust{ static_cast<float>(_GameState_Adjust * Scale) };
	if ((float)Current < ((float)this->Get_StateLength()._Coord_Y) / 2)
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
	else if ((float)Current > ((float)this->Get_StateLength()._Coord_Y) / 2)
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

float GameStateBase::Set_ExacWidth(double Current, float& MoveState, float& State_MoveX, double Scale)
{
	if (_Adjust_Enable == false)
		return 0.0f;
	float Temp_Move{};
	float Temp_GameState_Adjust{ static_cast<float>(_GameState_Adjust * Scale) };
	if ((float)Current < ((float)this->Get_StateLength()._Coord_X) / 2)
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
	else if ((float)Current > ((float)this->Get_StateLength()._Coord_X) / 2)
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

void GameStateBase::Reload_Display_State(EState_Extend Extend_Dire)
{
	static RandomBase* TRB{ &RandomBase::GetRandomBase() };
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

void GameStateBase::Reload_State_Data(int State_Length, glm::ivec2* StateInfor)
{
	int Move_NX{ this->Get_Square_State()._Move_NX };
	int Move_PX{ this->Get_Square_State()._Move_PX };
	int Move_NY{ this->Get_Square_State()._Move_NY };
	int Move_PY{ this->Get_Square_State()._Move_PY };

#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
	std::cout << "Move_NX: " << Move_NX << "Move_PX: " << Move_PX << std::endl;
	std::cout << "Move_NY: " << Move_NY << "Move_PY: " << Move_PY << std::endl;
#endif

	if ((!this->Get_Compile_Status()) || (this->Get_GameState()->size() == 0))
		return;

	for (int i{ 0 }; i < State_Length; ++i)
	{
		StateInfor[i].x = 4;
		StateInfor[i].y = 1;

		if (Move_NX > static_cast<int>(this->Get_DataWidth()))//RIGH AREA
		{
			if (Move_NY > static_cast<int>(this->Get_DataHeight()))
			{
				if (this->Is_State_Exist(STATE_EXTEND_RIGH_BELO))
				{
					unsigned x{ Move_NX - this->Get_DataWidth() - 1 + (Move_NY - this->Get_DataHeight() - 1) * (this->Get_DataWidth() + 1) };
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
					unsigned x{ Move_NX - this->Get_DataWidth() - 1 + Move_NY * (this->Get_DataWidth() + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_RIGH, x % this->Get_GameState(STATE_EXTEND_RIGH)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= -static_cast<int>(this->Get_DataHeight()))
			{
				if (this->Is_State_Exist(STATE_EXTEND_RIGH_ABOV))
				{
					unsigned x{ Move_NX - this->Get_DataWidth() - 1 + (Move_NY + this->Get_DataHeight() + 1) * (this->Get_DataWidth() + 1) };
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
			if (Move_NY > static_cast<int>(this->Get_DataHeight()))
			{
				if (this->Is_State_Exist(STATE_EXTEND_BELO))
				{
					unsigned x{ Move_NX + (Move_NY - this->Get_DataHeight() - 1) * (this->Get_DataWidth() + 1) };
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
					unsigned x{ Move_NX + Move_NY * (this->Get_DataWidth() + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_MIDD, x % this->Get_GameState(STATE_EXTEND_MIDD)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= -static_cast<int>(this->Get_DataHeight()))
			{
				if (this->Is_State_Exist(STATE_EXTEND_ABOV))
				{
					unsigned x{ Move_NX + (Move_NY + this->Get_DataHeight() + 1) * (this->Get_DataWidth() + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_ABOV, x % this->Get_GameState(STATE_EXTEND_ABOV)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
		}
		else if (Move_NX >= -static_cast<int>(this->Get_DataWidth()))//LEFT AREA
		{
			if (Move_NY > static_cast<int>(this->Get_DataHeight()))
			{
				if (this->Is_State_Exist(STATE_EXTEND_LEFT_BELO))
				{
					unsigned x{ Move_NX + this->Get_DataWidth() + 1 + (Move_NY - this->Get_DataHeight() - 1) * (this->Get_DataWidth() + 1) };
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
					unsigned x{ Move_NX + this->Get_DataWidth() + 1 + Move_NY * (this->Get_DataWidth() + 1) };
					StateUnit* Unit{ this->Get_StateUnit(STATE_EXTEND_LEFT, x % this->Get_GameState(STATE_EXTEND_LEFT)->size()) };
					StateInfor[i].x = Unit->Get_State_Id();
					StateInfor[i].y = Unit->Get_Extra_Status();
#if _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_
					std::cout << i << "_State_Id :" << StateInfor[i].x << std::endl;
#endif
				}
			}
			else if (Move_NY >= -static_cast<int>(this->Get_DataHeight()))
			{
				if (this->Is_State_Exist(STATE_EXTEND_LEFT_ABOV))
				{
					unsigned x{ Move_NX + this->Get_DataWidth() + 1 + (Move_NY + this->Get_DataHeight() + 1) * (this->Get_DataWidth() + 1) };
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
			Move_NX = this->Get_Square_State()._Move_NX;
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

	float Temp_LocationX = (Distance->_Coord_X + MoveX) * (this->_GameState_Length._Coord_X / 2.0f);
	float Temp_LocationY = (Distance->_Coord_Y + MoveY) * (this->_GameState_Length._Coord_Y / 2.0f);

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

void GameStateBase::StateMove_Edge_Set(int Dist_Mid, int Stat_Loc, int Move_Loc, short Edge, double Scale)//Reach Screen Edge : Then push screen to move
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };

	int Moves{};
	if (_Trigger_Mode)
		Moves = this->Auto_Update_Trigger(Edge);

	if ((Moves & MoveToNH) == MoveToNH)
	{
#if _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_
		std::cout << "FLAG ----------------------------Y+" << std::endl;
#endif
		LCB->Get_LocationY(Stat_Loc) += static_cast<float>(0.35f * Scale);
		LCB->Get_LocationY(Move_Loc) += static_cast<float>(0.35f * Scale);
		this->Get_Move_Distance()._Coord_Y -= static_cast<float>(0.35f * Scale);
	}
	if ((Moves & MoveToPH) == MoveToPH)
	{
#if _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_
		std::cout << "FLAG ----------------------------Y-" << std::endl;
#endif
		LCB->Get_LocationY(Stat_Loc) -= static_cast<float>(0.35f * Scale);
		LCB->Get_LocationY(Move_Loc) -= static_cast<float>(0.35f * Scale);
		this->Get_Move_Distance()._Coord_Y += static_cast<float>(0.35f * Scale);
	}
	if ((Moves & MoveToNW) == MoveToNW)
	{
#if _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_
		std::cout << "FLAG ----------------------------X+" << std::endl;
#endif
		LCB->Get_LocationX(Stat_Loc) += static_cast<float>(0.35f * Scale);
		LCB->Get_LocationX(Move_Loc) += static_cast<float>(0.35f * Scale);
		this->Get_Move_Distance()._Coord_X -= static_cast<float>(0.35f * Scale);
	}
	if ((Moves & MoveToPW) == MoveToPW)
	{
#if _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_
		std::cout << "FLAG ----------------------------X-" << std::endl;
#endif
		LCB->Get_LocationX(Stat_Loc) -= static_cast<float>(0.35f * Scale);
		LCB->Get_LocationX(Move_Loc) -= static_cast<float>(0.35f * Scale);
		this->Get_Move_Distance()._Coord_X += static_cast<float>(0.35f * Scale);
	}
}

void GameStateBase::Set_Trigger_Mode(bool Mode)
{
	this->_Trigger_Mode = Mode;
}

void GameStateBase::Generate_StateBlock(int State_Id)
{
	static RandomBase* TRB{ &RandomBase::GetRandomBase() };
	std::cout << std::endl << "Generate_StateBlock " << State_Id << " CALLED" << std::endl;
	try
	{
		this->_Data_Base.Id_Link_Locate(1, State_Id);
	}
	catch (std::string)
	{
		if (State_Id < 65536)
		{
			Set_Data_Size(this->_Data_Size + 1);

			this->_Data_Base.Append_DataChain(TRB->GenerateAutoSeed(), 10, 1, State_Id);
			this->_Data_Base.Append_DataChain(TRB->Generate_State(10, 10, true), 0, 1, State_Id);

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

GameStateBase::GameStateBase(int Width, int Height) :
	_GameState_Length(Width, Height), _GameState_Adjust(0.0f), _Compile_Success(false), _Extend_Mid_Id(0),
	_CurrentMid(nullptr), _MState(0), _Data_Height(Height), _Data_Width(Width), _Is_Adjusting(false), Tanxl_ClassBase("1.1"),
	_Adjust_Enable(false), _Exac_Location(0, 0), _GameState_Extend(), _Is_Data_Set(false)
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };
	this->_Distance_Move = LCB->New_Location_set("Distance_Move");
	this->_Distance_Screen_Mid = LCB->New_Location_set("Distance_Screen_Mid");

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

//unimportant Stuff (GET/SET)

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

int StateUnit::Get_Extra_Status()
{
	return this->_Extra_Status;
}

int StateUnit::Get_State_Id()
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

void GameStateBase::Set_CurrentLoc(float& CurrentX, float& CurrentY)
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

void GameStateBase::Set_Adjust_While_Move(bool Enable)
{
	this->_Adjust_While_Move = Enable;
}

void GameStateBase::Set_Enable_Adjust(bool Enable)
{
	this->_Adjust_Enable = Enable;
}

bool GameStateBase::Is_State_Exist(EState_Extend State_Id)
{
	switch (State_Id)
	{
	case STATE_EXTEND_MIDD:
		return (this->_GameState_Extend._MIDD._Data->size() != 0);
	case STATE_EXTEND_LEFT:
		return (this->_GameState_Extend._LEFT._Data->size() != 0);
	case STATE_EXTEND_RIGH:
		return (this->_GameState_Extend._RIGH._Data->size() != 0);
	case STATE_EXTEND_ABOV:
		return (this->_GameState_Extend._ABOV._Data->size() != 0);
	case STATE_EXTEND_BELO:
		return (this->_GameState_Extend._BELO._Data->size() != 0);
	case STATE_EXTEND_LEFT_ABOV:
		return (this->_GameState_Extend._LEFT_ABOV._Data->size() != 0);
	case STATE_EXTEND_LEFT_BELO:
		return (this->_GameState_Extend._LEFT_BELO._Data->size() != 0);
	case STATE_EXTEND_RIGH_ABOV:
		return (this->_GameState_Extend._RIGH_ABOV._Data->size() != 0);
	case STATE_EXTEND_RIGH_BELO:
		return (this->_GameState_Extend._RIGH_BELO._Data->size() != 0);
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
	if (LocationX > static_cast<int>(this->Get_DataWidth()))
	{
		if (LocationY > static_cast<int>(this->Get_DataHeight()))
		{
			if (this->Is_State_Exist(STATE_EXTEND_RIGH_BELO))
			{
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
#if _TANXL_OPENGLDRAW_EDGE_LOCATION_VALUE_OUTPUT_
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
_Compile_Success(false), _CurrentMid(nullptr), _MState(0), _Data_Height(0), _Data_Width(0), _Is_Adjusting(false), Tanxl_ClassBase("1.1"),
_Adjust_Enable(false), _Exac_Location(0, 0), _GameState_Extend(), _Is_Data_Set(false)
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };
	this->_Distance_Move = LCB->New_Location_set("Distance_Move");
	this->_Distance_Screen_Mid = LCB->New_Location_set("Distance_Screen_Mid");

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

bool GameStateBase::Get_Compile_Status()
{
	return this->_Compile_Success;
}

void GameStateBase::Set_Adjust_Flag(bool Adjust_Flag)
{
	this->_Is_Adjusting = Adjust_Flag;
}

bool GameStateBase::Get_Adjust_Flag()
{
	return this->_Is_Adjusting;
}

bool GameStateBase::Is_Adjust_While_Move()
{
	return this->_Adjust_While_Move;
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

Tanxl_Coord<int> GameStateBase::Get_Exac_Location()
{
	return this->_Exac_Location;
}

int GameStateBase::Get_Distance_Screen_Id()
{
	return this->_Distance_Screen_Mid;
}

int GameStateBase::Get_Distance_Move_Id()
{
	return this->_Distance_Move;
}

Tanxl_Coord<int> GameStateBase::Get_StateLength()const
{
	return this->_GameState_Length;
}

EMove_State_EventId GameStateBase::Auto_Update_Trigger(short Edge)
{
	return static_cast<EMove_State_EventId>(Edge);
}

std::vector<StateUnit*>* GameStateBase::Get_GameState(EState_Extend State_Id)
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

bool StateEvent::Check_Event_Status()
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
