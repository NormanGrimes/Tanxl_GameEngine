#pragma once

#include "Tanxl_GameState.h"

//Core

//StateUnit

StateUnit::StateUnit(GameEvent* GE, int State_Id, int Move_Status)
	:_Move_Status(Move_Status), _GameEvents(GE), _State_Id(State_Id) {}

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
	return this->_Version;
}

std::string GameStateBase::Locate_Extend_State(std::string State_Id)
{
	if (State_Id == "NULL")
		return "NULL";
	if (this->Get_Engine_File())
		for (int i{ 0 }; i <= static_cast<int>((this->_Data_Height + 1) * (this->_Data_Width + 1)); ++i)
		{
			Id_Link* Link{ this->_Data_Base.Id_Link_Locate(1, i) };
			if (Link->_Data->_Data_Units.at(0)->_Data == State_Id)
				return Link->_Data->_Data_Units.at(1)->_Data;
		}
	return "NULL";
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
		if (this->_GameState_Extend._MIDD)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._MIDD);
		if (this->_GameState_Extend._LEFT)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT);
		if (this->_GameState_Extend._RIGH)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH);
		if (this->_GameState_Extend._ABOV)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._ABOV);
		if (this->_GameState_Extend._BELO)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._BELO);
		if (this->_GameState_Extend._LEFT_ABOV)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_ABOV);
		if (this->_GameState_Extend._LEFT_BELO)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_BELO);
		if (this->_GameState_Extend._RIGH_ABOV)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_ABOV);
		if (this->_GameState_Extend._RIGH_BELO)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_BELO);
		return;
	}
	switch (Clear_Id)
	{
	case STATE_EXTEND_MIDD:
		if (this->_GameState_Extend._MIDD)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._MIDD);
		return;
	case STATE_EXTEND_LEFT:
		if (this->_GameState_Extend._LEFT)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT);
		return;
	case STATE_EXTEND_RIGH:
		if (this->_GameState_Extend._RIGH)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH);
		return;
	case STATE_EXTEND_ABOV:
		if (this->_GameState_Extend._ABOV)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._ABOV);
		return;
	case STATE_EXTEND_BELO:
		if (this->_GameState_Extend._BELO)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._BELO);
		return;
	case STATE_EXTEND_LEFT_ABOV:
		if (this->_GameState_Extend._LEFT_ABOV)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_ABOV);
		return;
	case STATE_EXTEND_LEFT_BELO:
		if (this->_GameState_Extend._LEFT_BELO)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_BELO);
		return;
	case STATE_EXTEND_RIGH_ABOV:
		if (this->_GameState_Extend._RIGH_ABOV)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_ABOV);
		return;
	case STATE_EXTEND_RIGH_BELO:
		if (this->_GameState_Extend._RIGH_BELO)
			std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_BELO);
		return;
	}
}

void GameStateBase::Set_Display_State(int Width, int Height)
{
	this->_GameState_Width = Width;
	this->_Half_State_Width = 1.0f / Width;
	this->_GameState_Height = Height;
	this->_Half_State_Height = 1.0f / Height;
}

void GameStateBase::Set_Data_Length(unsigned Width, unsigned Height)
{
	this->_Data_Width = Width - 1;
	this->_Data_Height = Height - 1;
}

void GameStateBase::CompileStateUnits(std::string Infor, EState_Extend Extend)
{
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
			State_Status = 0;

			if (this->_Policy.size() != 0)
			{
				for (int i{}; i < this->_Policy.size(); i++)
				{
					if (this->_Policy.at(i)->_Name == Text_Reader)
					{
						State_Status = this->_Policy.at(i)->_State_Status;
						break;
					}
				}
			}
			Text_Reader = "";
			Status_Id = 0;
		}
		else
			Text_Reader += Infor.at(i);
	}
	_Compile_Success = true;
}

void GameStateBase::CompileStateEvent(std::string Infor, EState_Extend Extend)//Sample  A = 0, B = 1, C = 2.
{
	std::string Text_Reader{};
	int Status_Int{};

	std::vector<StateUnit*>* Target{ this->Get_GameState(Extend) };

	for (int i{ 0 }, SetCount{ 0 }; i < Infor.size(); ++i)
	{
		if ((Infor.at(i) != ',') && (Infor.at(i) != '='))
			Text_Reader += Infor.at(i);
		else if (Infor.at(i) == '=')//读取等号后的数字ID值
		{
			std::string Status_Reader{};
			while (Infor.at(i) != ',')
			{
				if ((Infor.at(i) != ' ') && ((Infor.at(i) >= '0') && (Infor.at(i) <= '9')))
					Status_Reader += Infor.at(i);
			}
			Status_Int = std::stoi(Status_Reader);
		}
		else
		{
			Target->at(SetCount++)->SetEvent(Text_Reader, Status_Int);
			if (Infor.at(i) == '.')
				return;
			Text_Reader = "";
		}
	}
}

void GameStateBase::Set_StartState(int State_Id, std::string Cover_String)
{
	if (State_Id < 0)
		State_Id = 0;
	else if (State_Id >= this->Get_State_Size())
		State_Id = this->Get_State_Size() - 1;
	if (this->Get_Engine_File())
	{
		std::string Data_Name{ this->Get_State_Id(State_Id) };
		for (int i{ 0 }; i < (this->_State_WidthS * this->_State_HeightS); ++i)
		{
			Id_Link* Link{ this->_Data_Base.Id_Link_Locate(1, i) };
			if (Link->_Data->_Data_Units.at(0)->_Data == Data_Name)
			{
				if (Cover_String != "NULL")
					Link->_Data->_Data_Units.at(1)->_Data = Cover_String;
				this->CompileStateUnits(Link->_Data->_Data_Units.at(1)->_Data, STATE_EXTEND_MIDD);
				this->_GameState_Id._MIDD = Link->_Data->_Data_Units.at(0)->_Data;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(2)->_Data), STATE_EXTEND_LEFT);
				this->_GameState_Id._LEFT = Link->_Data->_Data_Units.at(2)->_Data;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(3)->_Data), STATE_EXTEND_RIGH);
				this->_GameState_Id._RIGH = Link->_Data->_Data_Units.at(3)->_Data;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(4)->_Data), STATE_EXTEND_ABOV);
				this->_GameState_Id._ABOV = Link->_Data->_Data_Units.at(4)->_Data;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(5)->_Data), STATE_EXTEND_BELO);
				this->_GameState_Id._BELO = Link->_Data->_Data_Units.at(5)->_Data;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(6)->_Data), STATE_EXTEND_LEFT_ABOV);
				this->_GameState_Id._LEFT_ABOV = Link->_Data->_Data_Units.at(6)->_Data;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(7)->_Data), STATE_EXTEND_LEFT_BELO);
				this->_GameState_Id._LEFT_BELO = Link->_Data->_Data_Units.at(7)->_Data;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(8)->_Data), STATE_EXTEND_RIGH_ABOV);
				this->_GameState_Id._RIGH_ABOV = Link->_Data->_Data_Units.at(8)->_Data;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(9)->_Data), STATE_EXTEND_RIGH_BELO);
				this->_GameState_Id._RIGH_BELO = Link->_Data->_Data_Units.at(9)->_Data;
				this->_Extend_State_Enable = true;
				this->Set_Data_Length(10, 10);
				return;
			}
		}
	}
}

void GameStateBase::Set_State(int State_Id, std::string Cover_String)
{
	if (this->Get_Engine_File())
	{
		std::string Data_Name{ this->Get_State_Id(State_Id) };
		for (int i{ 0 }; i < (this->_State_WidthS * this->_State_HeightS); ++i)
		{
			Id_Link* Link{ this->_Data_Base.Id_Link_Locate(1, i) };
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

Square_State GameStateBase::Get_Square_State()
{
	return this->_MState;
}

SLocation& GameStateBase::Get_Screen_Distance()
{
	return LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Screen_Mid);
}

SLocation& GameStateBase::Get_Move_Distance()
{
	return LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move);
}

float GameStateBase::Set_ExacHeight(double Current, float& MoveState, float& State_MoveY)
{
	static int EHCountS{ 0 };
	static int EHCountL{ 0 };
	if (_Adjust_Enable == false)
		return 0.0f;
	float Temp_Move{};
	if ((float)Current < ((float)this->Get_StateHeight()) / 2)
	{
		EHCountS++;
		EHCountL = 0;
		if (EHCountS == this->_Adjust_Frame)
		{
			if (MoveState < 0 && MoveState + _GameState_Adjust > 0)
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
				MoveState += _GameState_Adjust;
				State_MoveY += _GameState_Adjust;
			}
			EHCountS = 0;
			this->_Is_Adjusting = true;
		}
	}
	else if ((float)Current > ((float)this->Get_StateHeight()) / 2)
	{
		EHCountL++;
		EHCountS = 0;
		if (EHCountL == this->_Adjust_Frame)
		{
			if (MoveState > _GameState_Adjust)
			{
				MoveState -= _GameState_Adjust;
				State_MoveY -= _GameState_Adjust;
			}
			else if (MoveState - _GameState_Adjust < 0)
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
			EHCountL = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
	{
		EHCountS = 0;
		EHCountL = 0;
	}
	return Temp_Move;
}

float GameStateBase::Set_ExacWidth(double Current, float& MoveState, float& State_MoveX)
{
	static int EWCountS{ 0 };
	static int EWCountL{ 0 };
	if (_Adjust_Enable == false)
		return 0.0f;
	float Temp_Move{};
	if ((float)Current < ((float)this->Get_StateWidth()) / 2)
	{
		EWCountS++;
		EWCountL = 0;
		if (EWCountS == this->_Adjust_Frame)
		{
			if (-MoveState < 0 && _GameState_Adjust + -MoveState>0)
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
				MoveState += _GameState_Adjust;
				State_MoveX += _GameState_Adjust;
			}
			EWCountS = 0;
			this->_Is_Adjusting = true;
		}
	}
	else if ((float)Current > ((float)this->Get_StateWidth()) / 2)
	{
		EWCountL++;
		EWCountS = 0;
		if (EWCountL == this->_Adjust_Frame)
		{
			if (MoveState > _GameState_Adjust)
			{
				MoveState -= _GameState_Adjust;
				State_MoveX -= _GameState_Adjust;
			}
			else if (MoveState < _GameState_Adjust)
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
			EWCountL = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
	{
		EWCountS = 0;
		EWCountL = 0;
	}
	return Temp_Move;
}

void GameStateBase::Set_Adjust_Frequency(int Frame)
{
	this->_Adjust_Frame = Frame;
}

void GameStateBase::Set_Extend_State_Enable(bool Enable)
{
	this->_Extend_State_Enable = Enable;
}

std::vector<bool>* GameStateBase::Get_GameState_MoveAble(EState_Extend State_Id)
{
	static std::vector<bool> MAB{};
	if (MAB.size() != 0)
		std::vector<bool>().swap(MAB);
	std::vector<StateUnit*>* GameState{ this->Get_GameState(State_Id) };
	for (const auto& State : *GameState)
	{
		if (State->Get_Move_Status())
			MAB.push_back(true);
		else
			MAB.push_back(false);
	}
	return &MAB;
}

void GameStateBase::Set_Move_State(int NX, int PX, int NY, int PY)
{
	this->_MState._Move_NX = NX;
	this->_MState._Move_PX = PX;
	this->_MState._Move_NY = NY;
	this->_MState._Move_PY = PY;
}

void GameStateBase::Set_Move_State(EMove_State_EventId Event_Id, int Multi_Set)
{
	switch (Event_Id)
	{
	case MoveToNW:
		this->_MState._Move_NX += Multi_Set;
		this->_MState._Move_PX += Multi_Set;
		break;
	case MoveToPW:
		this->_MState._Move_NX -= Multi_Set;
		this->_MState._Move_PX -= Multi_Set;
		break;
	case MoveToNH:
		this->_MState._Move_NY += Multi_Set;
		this->_MState._Move_PY += Multi_Set;
		break;
	case MoveToPH:
		this->_MState._Move_NY -= Multi_Set;
		this->_MState._Move_PY -= Multi_Set;
		break;

	case MoveToNWNH:
		this->_MState._Move_NX += Multi_Set;
		this->_MState._Move_PX += Multi_Set;
		this->_MState._Move_NY += Multi_Set;
		this->_MState._Move_PY += Multi_Set;
		break;

	case MoveToNWPH:
		this->_MState._Move_NX += Multi_Set;
		this->_MState._Move_PX += Multi_Set;
		this->_MState._Move_NY -= Multi_Set;
		this->_MState._Move_PY -= Multi_Set;
		break;

	case MoveToPWNH:
		this->_MState._Move_NX -= Multi_Set;
		this->_MState._Move_PX -= Multi_Set;
		this->_MState._Move_NY += Multi_Set;
		this->_MState._Move_PY += Multi_Set;
		break;

	case MoveToPWPH:
		this->_MState._Move_NX -= Multi_Set;
		this->_MState._Move_PX -= Multi_Set;
		this->_MState._Move_NY += Multi_Set;
		this->_MState._Move_PY += Multi_Set;
		break;
	}
}

void GameStateBase::Reload_State(EState_Extend Extend_Dire)
{
	switch (Extend_Dire)
	{
	case STATE_EXTEND_ABOV:
	{
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_BELO);
		this->_GameState_Id._LEFT_BELO = this->_GameState_Id._LEFT;
		this->_GameState_Extend._LEFT_BELO = this->_GameState_Extend._LEFT;
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._BELO);
		this->_GameState_Id._BELO = this->_GameState_Id._MIDD;
		this->_GameState_Extend._BELO = this->_GameState_Extend._MIDD;
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_BELO);
		this->_GameState_Id._RIGH_BELO = this->_GameState_Id._RIGH;
		this->_GameState_Extend._RIGH_BELO = this->_GameState_Extend._RIGH;

		this->_GameState_Id._LEFT = this->_GameState_Id._LEFT_ABOV;
		this->_GameState_Extend._LEFT = this->_GameState_Extend._LEFT_ABOV;
		this->_GameState_Id._MIDD = this->_GameState_Id._ABOV;
		this->_GameState_Extend._MIDD = this->_GameState_Extend._ABOV;
		this->_GameState_Id._RIGH = this->_GameState_Id._RIGH_ABOV;
		this->_GameState_Extend._RIGH = this->_GameState_Extend._RIGH_ABOV;

		Id_Link* Link{ this->Locate_Link(this->_GameState_Id._MIDD) };

		this->_GameState_Id._LEFT_ABOV = Link->_Data->_Data_Units.at(6)->_Data;
		this->_GameState_Extend._LEFT_ABOV = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(6)->_Data), STATE_EXTEND_LEFT_ABOV);

		this->_GameState_Id._ABOV = Link->_Data->_Data_Units.at(4)->_Data;
		this->_GameState_Extend._ABOV = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(4)->_Data), STATE_EXTEND_ABOV);

		this->_GameState_Id._RIGH_ABOV = Link->_Data->_Data_Units.at(8)->_Data;
		this->_GameState_Extend._RIGH_ABOV = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(8)->_Data), STATE_EXTEND_RIGH_ABOV);

		break;
	}
	case STATE_EXTEND_BELO:
	{
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_ABOV);
		this->_GameState_Id._LEFT_ABOV = this->_GameState_Id._LEFT;
		this->_GameState_Extend._LEFT_ABOV = this->_GameState_Extend._LEFT;
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._ABOV);
		this->_GameState_Id._ABOV = this->_GameState_Id._MIDD;
		this->_GameState_Extend._ABOV = this->_GameState_Extend._MIDD;
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_ABOV);
		this->_GameState_Id._RIGH_ABOV = this->_GameState_Id._RIGH;
		this->_GameState_Extend._RIGH_ABOV = this->_GameState_Extend._RIGH;

		this->_GameState_Id._LEFT = this->_GameState_Id._LEFT_BELO;
		this->_GameState_Extend._LEFT = this->_GameState_Extend._LEFT_BELO;
		this->_GameState_Id._MIDD = this->_GameState_Id._BELO;
		this->_GameState_Extend._MIDD = this->_GameState_Extend._BELO;
		this->_GameState_Id._RIGH = this->_GameState_Id._RIGH_BELO;
		this->_GameState_Extend._RIGH = this->_GameState_Extend._RIGH_BELO;

		Id_Link* Link{ this->Locate_Link(this->_GameState_Id._MIDD) };

		this->_GameState_Id._LEFT_BELO = Link->_Data->_Data_Units.at(7)->_Data;
		this->_GameState_Extend._LEFT_BELO = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(7)->_Data), STATE_EXTEND_LEFT_BELO);

		this->_GameState_Id._BELO = Link->_Data->_Data_Units.at(5)->_Data;
		this->_GameState_Extend._BELO = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(5)->_Data), STATE_EXTEND_BELO);

		this->_GameState_Id._RIGH_BELO = Link->_Data->_Data_Units.at(9)->_Data;
		this->_GameState_Extend._RIGH_BELO = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(9)->_Data), STATE_EXTEND_RIGH_BELO);

		break;
	}
	case STATE_EXTEND_LEFT:
	{
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_ABOV);
		this->_GameState_Id._RIGH_ABOV = this->_GameState_Id._ABOV;
		this->_GameState_Extend._RIGH_ABOV = this->_GameState_Extend._ABOV;
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH);
		this->_GameState_Id._RIGH = this->_GameState_Id._MIDD;
		this->_GameState_Extend._RIGH = this->_GameState_Extend._MIDD;
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._RIGH_BELO);
		this->_GameState_Id._RIGH_BELO = this->_GameState_Id._BELO;
		this->_GameState_Extend._RIGH_BELO = this->_GameState_Extend._BELO;

		this->_GameState_Id._ABOV = this->_GameState_Id._LEFT_ABOV;
		this->_GameState_Extend._ABOV = this->_GameState_Extend._LEFT_ABOV;
		this->_GameState_Id._MIDD = this->_GameState_Id._LEFT;
		this->_GameState_Extend._MIDD = this->_GameState_Extend._LEFT;
		this->_GameState_Id._BELO = this->_GameState_Id._LEFT_BELO;
		this->_GameState_Extend._BELO = this->_GameState_Extend._LEFT_BELO;

		Id_Link* Link{ this->Locate_Link(this->_GameState_Id._MIDD) };

		this->_GameState_Id._LEFT_ABOV = Link->_Data->_Data_Units.at(6)->_Data;
		this->_GameState_Extend._LEFT_ABOV = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(6)->_Data), STATE_EXTEND_LEFT_ABOV);

		this->_GameState_Id._LEFT = Link->_Data->_Data_Units.at(2)->_Data;
		this->_GameState_Extend._LEFT = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(2)->_Data), STATE_EXTEND_LEFT);

		this->_GameState_Id._LEFT_BELO = Link->_Data->_Data_Units.at(7)->_Data;
		this->_GameState_Extend._LEFT_BELO = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(7)->_Data), STATE_EXTEND_LEFT_BELO);

		break;
	}
	case STATE_EXTEND_RIGH:
	{
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_ABOV);
		this->_GameState_Id._LEFT_ABOV = this->_GameState_Id._ABOV;
		this->_GameState_Extend._LEFT_ABOV = this->_GameState_Extend._ABOV;
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT);
		this->_GameState_Id._LEFT = this->_GameState_Id._MIDD;
		this->_GameState_Extend._LEFT = this->_GameState_Extend._MIDD;
		std::vector<StateUnit*>().swap(*this->_GameState_Extend._LEFT_BELO);
		this->_GameState_Id._LEFT_BELO = this->_GameState_Id._BELO;
		this->_GameState_Extend._LEFT_BELO = this->_GameState_Extend._BELO;

		this->_GameState_Id._ABOV = this->_GameState_Id._RIGH_ABOV;
		this->_GameState_Extend._ABOV = this->_GameState_Extend._RIGH_ABOV;
		this->_GameState_Id._MIDD = this->_GameState_Id._RIGH;
		this->_GameState_Extend._MIDD = this->_GameState_Extend._RIGH;
		this->_GameState_Id._BELO = this->_GameState_Id._RIGH_BELO;
		this->_GameState_Extend._BELO = this->_GameState_Extend._RIGH_BELO;

		Id_Link* Link{ this->Locate_Link(this->_GameState_Id._MIDD) };

		this->_GameState_Id._RIGH_ABOV = Link->_Data->_Data_Units.at(8)->_Data;
		this->_GameState_Extend._RIGH_ABOV = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(8)->_Data), STATE_EXTEND_RIGH_ABOV);

		this->_GameState_Id._RIGH = Link->_Data->_Data_Units.at(3)->_Data;
		this->_GameState_Extend._RIGH = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(3)->_Data), STATE_EXTEND_RIGH);

		this->_GameState_Id._RIGH_BELO = Link->_Data->_Data_Units.at(9)->_Data;
		this->_GameState_Extend._RIGH_BELO = new std::vector<StateUnit*>;
		this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(9)->_Data), STATE_EXTEND_RIGH_BELO);

		break;
	}
	}
}

void GameStateBase::Update_Move(float MoveX, float MoveY, ECheck_Edge Check)
{
	static SLocation* Distance{ &LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move) };

	if ((this->_Half_State_Width == 0.0f) || (this->_Half_State_Height == 0.0f))
		this->Set_Display_State(this->_GameState_Width, this->_GameState_Height);

	static float State_Above_Below_Width{ this->_Half_State_Width * 2 / 3 };
	static float State_Above_Below_Height{ this->_Half_State_Height * 2 / 3 };

	switch (Check)
	{
	case CHECK_EDGE_CURR:
		MoveX += 0.0f;
		MoveY += 0.0f;
		break;
	case CHECK_EDGE_LEFT:
		MoveX -= this->_Half_State_Width * 2 / 3;
		MoveY += State_Above_Below_Height;
		State_Above_Below_Height = -State_Above_Below_Height;
		break;
	case CHECK_EDGE_RIGH:
		MoveX += this->_Half_State_Width * 2 / 3;
		MoveY += State_Above_Below_Height;
		State_Above_Below_Height = -State_Above_Below_Height;
		break;
	case CHECK_EDGE_BELO:
		MoveX += State_Above_Below_Width;
		MoveY -= this->_Half_State_Height * 2 / 3;
		State_Above_Below_Width = -State_Above_Below_Width;
		break;
	case CHECK_EDGE_ABOV:
		MoveX += State_Above_Below_Width;
		MoveY += this->_Half_State_Height * 2 / 3;
		State_Above_Below_Width = -State_Above_Below_Width;
		break;
	}

	float Temp_LocationX = (Distance->_Location_X + MoveX) * (this->_GameState_Width / 2.0f);
	float Temp_LocationY = (Distance->_Location_Y + MoveY) * (this->_GameState_Height / 2.0f);

#if _TANXL_GAMESTATE_UPDATE_MOVE_OUTPUT_
	std::cout <<"Before Adjust :" << Temp_LocationX << "____" << Temp_LocationY << std::endl;
#endif

	Temp_LocationX = static_cast<int>(Temp_LocationX + 0.5f) > static_cast<int>(Temp_LocationX) ? Temp_LocationX + 0.5f : Temp_LocationX;
	Temp_LocationY = static_cast<int>(Temp_LocationY - 0.5f) < static_cast<int>(Temp_LocationY) ? Temp_LocationY - 0.5f : Temp_LocationY;

	this->_Exac_LocationX = static_cast<int>(Temp_LocationX);
	this->_Exac_LocationY = static_cast<int>(Temp_LocationY);

	if (Distance->_Location_X + MoveX < -0.24f)
		--this->_Exac_LocationX;
	if (Distance->_Location_Y + MoveY > 0.24f)
		++this->_Exac_LocationY;

	this->_Exac_LocationY = -this->_Exac_LocationY;

#if _TANXL_GAMESTATE_UPDATE_MOVE_OUTPUT_
	std::cout <<"After :"<< Temp_LocationX << "____" << Temp_LocationY << std::endl;
	std::cout << this->_Exac_LocationX << "____" << this->_Exac_LocationY << std::endl;
#endif
}

GameStateBase::GameStateBase(int Width, int Height) :
	_GameState_Width(Height), _GameState_Height(Width), _GameState_Adjust(0.0f), _Compile_Success(false),
	_CurrentMid(nullptr), _MState(0), _Data_Height(Height), _Data_Width(Width), _Is_Adjusting(false), _Adjust_Frame(1),
	_Adjust_Enable(false), _Exac_LocationX(0), _Exac_LocationY(0), _GameState_Extend(), _Is_Data_Set(false), _Extend_State_Enable(false)
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };
	this->_Distance_Move = LCB->New_Location_set("Distance_Move");
	this->_Distance_Screen_Mid = LCB->New_Location_set("Distance_Screen_Mid");

	this->_GameState_Extend._MIDD = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH = new std::vector<StateUnit*>;
	this->_GameState_Extend._ABOV = new std::vector<StateUnit*>;
	this->_GameState_Extend._BELO = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT_ABOV = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT_BELO = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH_ABOV = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH_BELO = new std::vector<StateUnit*>;
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

//GameEventBase

GameEventBase::GameEventBase() :_GameEvents(NULL) {}

GameEventBase::~GameEventBase()
{
	std::vector<GameEvent*>().swap(this->_GameEvents);
	delete& _GameEvents;
}

GameEventBase::GameEventBase(const GameEventBase&) {}

GameEventBase& GameEventBase::operator=(const GameEventBase&) { return *this; }

//StateUnit

int StateUnit::Get_Move_Status()
{
	return this->_Move_Status;
}

int StateUnit::Get_State_Id()
{
	return this->_State_Id;
}

void StateUnit::Set_State_Id(int State_Id)
{
	this->_State_Id = State_Id;
}

//GameStateBase

void GameStateBase::Set_CurrentLoc(float& CurrentX, float& CurrentY)
{
	static SLocation* Distance{ &LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move) };
	Distance->_Location_X = CurrentX;
	Distance->_Location_Y = CurrentY;
}

void GameStateBase::Set_Compile_Policy(std::string State_Name, int Set_To_Status)
{
	this->_Policy.push_back(new State_Policy(State_Name, Set_To_Status));
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
		return (this->_GameState_Extend._MIDD->size() != 0);
	case STATE_EXTEND_LEFT:
		return (this->_GameState_Extend._LEFT->size() != 0);
	case STATE_EXTEND_RIGH:
		return (this->_GameState_Extend._RIGH->size() != 0);
	case STATE_EXTEND_ABOV:
		return (this->_GameState_Extend._ABOV->size() != 0);
	case STATE_EXTEND_BELO:
		return (this->_GameState_Extend._BELO->size() != 0);
	case STATE_EXTEND_LEFT_ABOV:
		return (this->_GameState_Extend._LEFT_ABOV->size() != 0);
	case STATE_EXTEND_LEFT_BELO:
		return (this->_GameState_Extend._LEFT_BELO->size() != 0);
	case STATE_EXTEND_RIGH_ABOV:
		return (this->_GameState_Extend._RIGH_ABOV->size() != 0);
	case STATE_EXTEND_RIGH_BELO:
		return (this->_GameState_Extend._RIGH_BELO->size() != 0);
	}
	return 0;
}

StateUnit* GameStateBase::Get_StateUnit(EState_Extend State, int Pos)
{
	switch (State)
	{
	case STATE_EXTEND_MIDD:
		return this->_GameState_Extend._MIDD->at(Pos);
	case STATE_EXTEND_LEFT:
		return this->_GameState_Extend._LEFT->at(Pos);
	case STATE_EXTEND_RIGH:
		return this->_GameState_Extend._RIGH->at(Pos);
	case STATE_EXTEND_ABOV:
		return this->_GameState_Extend._ABOV->at(Pos);
	case STATE_EXTEND_BELO:
		return this->_GameState_Extend._BELO->at(Pos);
	case STATE_EXTEND_LEFT_ABOV:
		return this->_GameState_Extend._LEFT_ABOV->at(Pos);
	case STATE_EXTEND_LEFT_BELO:
		return this->_GameState_Extend._LEFT_BELO->at(Pos);
	case STATE_EXTEND_RIGH_ABOV:
		return this->_GameState_Extend._RIGH_ABOV->at(Pos);
	case STATE_EXTEND_RIGH_BELO:
		return this->_GameState_Extend._RIGH_BELO->at(Pos);
	}
	return nullptr;
}

Id_Link* GameStateBase::Locate_Link(std::string Link_Name)
{
	for (int i{ 0 }; i < (this->_State_WidthS * this->_State_HeightS); ++i)
	{
		Id_Link* Link{ this->_Data_Base.Id_Link_Locate(1, i) };
		if (Link->_Data->_Data_Units.at(0)->_Data == Link_Name)
			return Link;
	}
	return nullptr;
}

GameStateBase::GameStateBase(const GameStateBase&) :_GameState_Width(0), _GameState_Height(0), _GameState_Adjust(0),
_Compile_Success(false), _CurrentMid(nullptr), _MState(0), _Data_Height(0), _Data_Width(0), _Is_Adjusting(false),
_Adjust_Frame(1), _Adjust_Enable(false), _Exac_LocationX(0), _Exac_LocationY(0), _GameState_Extend(), _Is_Data_Set(false), _Extend_State_Enable(false)
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };
	this->_Distance_Move = LCB->New_Location_set("Distance_Move");
	this->_Distance_Screen_Mid = LCB->New_Location_set("Distance_Screen_Mid");

	this->_GameState_Extend._MIDD = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH = new std::vector<StateUnit*>;
	this->_GameState_Extend._ABOV = new std::vector<StateUnit*>;
	this->_GameState_Extend._BELO = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT_ABOV = new std::vector<StateUnit*>;
	this->_GameState_Extend._LEFT_BELO = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH_ABOV = new std::vector<StateUnit*>;
	this->_GameState_Extend._RIGH_BELO = new std::vector<StateUnit*>;
}

GameStateBase& GameStateBase::operator=(const GameStateBase&) { return *this; }

bool GameStateBase::Get_Compile_Status()
{
	return this->_Compile_Success;
}

bool GameStateBase::Get_Extend_State()
{
	return this->_Extend_State_Enable;
}

void GameStateBase::Set_Adjust_Flag(bool Adjust_Flag)
{
	this->_Is_Adjusting = Adjust_Flag;
}

bool GameStateBase::Get_Adjust_Flag()
{
	return this->_Is_Adjusting;
}

bool GameStateBase::Get_Adjust_While_Move()
{
	return this->_Adjust_While_Move;
}

bool GameStateBase::Get_Engine_File()
{
	if (!this->_Is_Data_Set)
		if (!this->_Data_Base.Get_LocalData("Tanxl Engine SystemInfor"))
			return false;
	return true;
}

int GameStateBase::Get_LocationX()
{
	return this->_Exac_LocationX;
}

int GameStateBase::Get_LocationY()
{
	return this->_Exac_LocationY;
}

int GameStateBase::Get_Distance_Screen_Id()
{
	return this->_Distance_Screen_Mid;
}

int GameStateBase::Get_Distance_Move_Id()
{
	return this->_Distance_Move;
}

int GameStateBase::Get_State_Size()
{
	return this->_State_WidthS * this->_State_HeightS;
}

int GameStateBase::Get_StateHeight()const
{
	return this->_GameState_Height;
}

int GameStateBase::Get_StateWidth()const
{
	return this->_GameState_Width;
}

std::vector<StateUnit*>* GameStateBase::Get_GameState(EState_Extend State_Id)
{
	switch (State_Id)
	{
	case STATE_EXTEND_MIDD:
		return this->_GameState_Extend._MIDD;
	case STATE_EXTEND_LEFT:
		return this->_GameState_Extend._LEFT;
	case STATE_EXTEND_RIGH:
		return this->_GameState_Extend._RIGH;
	case STATE_EXTEND_ABOV:
		return this->_GameState_Extend._ABOV;
	case STATE_EXTEND_BELO:
		return this->_GameState_Extend._BELO;
	case STATE_EXTEND_LEFT_ABOV:
		return this->_GameState_Extend._LEFT_ABOV;
	case STATE_EXTEND_LEFT_BELO:
		return this->_GameState_Extend._LEFT_BELO;
	case STATE_EXTEND_RIGH_ABOV:
		return this->_GameState_Extend._RIGH_ABOV;
	case STATE_EXTEND_RIGH_BELO:
		return this->_GameState_Extend._RIGH_BELO;
	}
	return nullptr;
}

//Square_State

Square_State::Square_State(int NX, int PX, int NY, int PY) :_Move_NX(NY), _Move_NY(NY), _Move_PX(PX), _Move_PY(PY) {}