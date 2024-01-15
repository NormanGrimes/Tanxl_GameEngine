#pragma once

#include "Tanxl_GameState.h"

//Core

//StateUnit

StateUnit::StateUnit(GameEvent* GE, int State_Id, bool MoveTarget)
	:_Is_Move_Target(MoveTarget), _GameEvents(GE), _State_Id(State_Id) {}

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
		for (int i{ 0 }; i <= static_cast<int>(0xFF); ++i)
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

void GameStateBase::Clear_Display_Vector()
{
	for (int i{ 0 }; i < _GameState.size(); ++i)
		delete _GameState.at(i);
	_GameState.clear();
}

void GameStateBase::Set_Display_State(int Width, int Height)
{
	this->_GameState_Width = Width;
	this->_Half_State_Width = 1.0f / Width;
	this->_GameState_Height = Height;
	this->_Half_State_Height = 1.0f / Height;
}

void GameStateBase::Set_DataAll_State(unsigned Width, unsigned Height)
{
	this->_Data_Width = Width - 1;
	this->_Data_Height = Height - 1;
}

void GameStateBase::CompileStateUnits(std::string Infor, EState_Extend Extend)
{
	std::string Text_Reader{};
	int Status_Id{};
	bool State_Move{};
	std::vector<StateUnit*>* Target{ nullptr };
	switch (Extend)
	{
	case STATE_ORIGIN_MIDD:
		Target = &this->_GameState;
		break;
	case STATE_EXTEND_MIDD:
		delete this->_GameState_Extend._MIDD;
		this->_GameState_Extend._MIDD = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._MIDD;
		break;
	case STATE_EXTEND_LEFT:
		delete this->_GameState_Extend._LEFT;
		this->_GameState_Extend._LEFT = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._LEFT;
		break;
	case STATE_EXTEND_RIGH:
		delete this->_GameState_Extend._RIGH;
		this->_GameState_Extend._RIGH = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._RIGH;
		break;
	case STATE_EXTEND_ABOV:
		delete this->_GameState_Extend._ABOV;
		this->_GameState_Extend._ABOV = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._ABOV;
		break;
	case STATE_EXTEND_BELO:
		delete this->_GameState_Extend._BELO;
		this->_GameState_Extend._BELO = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._BELO;
		break;
	case STATE_EXTEND_LEFT_ABOV:
		delete this->_GameState_Extend._LEFT_ABOV;
		this->_GameState_Extend._LEFT_ABOV = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._LEFT_ABOV;
		break;
	case STATE_EXTEND_LEFT_BELO:
		delete this->_GameState_Extend._LEFT_BELO;
		this->_GameState_Extend._LEFT_BELO = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._LEFT_BELO;
		break;
	case STATE_EXTEND_RIGH_ABOV:
		delete this->_GameState_Extend._RIGH_ABOV;
		this->_GameState_Extend._RIGH_ABOV = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._RIGH_ABOV;
		break;
	case STATE_EXTEND_RIGH_BELO:
		delete this->_GameState_Extend._RIGH_BELO;
		this->_GameState_Extend._RIGH_BELO = new std::vector<StateUnit*>;
		Target = this->_GameState_Extend._RIGH_BELO;
		break;
	}

	if (Infor == "NULL")
		return;

	for (int i{ 0 }; i < Infor.size(); ++i)
	{
		if ((Infor.at(i) != ',') && (Infor.at(i) != '-'))
			Text_Reader += Infor.at(i);
		else if (Infor.at(i) == ',')
		{
			Status_Id = std::stoi(Text_Reader);
			Target->push_back(new StateUnit(nullptr, Status_Id, State_Move));
			Text_Reader = "";
		}
		else if (Infor.at(i) == '-')
		{
			if(Text_Reader == "a")
				State_Move = true;
			else
				State_Move = false;
			Text_Reader = "";
			Status_Id = 0;
		}
	}
	_Compile_Success = true;
}

void GameStateBase::CompileStateEvent(std::string Infor)//Sample  A = 0, B = 1, C = 2.
{
	std::string Text_Reader{};
	int Status_Int{};
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
			this->_GameState.at(SetCount++)->SetEvent(Text_Reader, Status_Int);
			if (Infor.at(i) == '.')
				return;
			Text_Reader = "";
		}
	}
}

void GameStateBase::Set_SquareState(int State_Id)
{
	if (this->Get_Engine_File())
	{
		std::string Data_Name{ this->Get_State_Id(State_Id) };
		for (int i{ 0 }; i <= static_cast<int>(0xFF); ++i)
		{
			Id_Link* Link{ this->_Data_Base.Id_Link_Locate(1, i) };
			if (Link->_Data->_Data_Units.at(0)->_Data == Data_Name)
			{
				this->CompileStateUnits(Link->_Data->_Data_Units.at(1)->_Data, STATE_EXTEND_MIDD);
				this->_GameState_Id._MIDD = Link->_Data->_Data_Units.at(0)->_Id;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(2)->_Data), STATE_EXTEND_LEFT);
				this->_GameState_Id._LEFT = Link->_Data->_Data_Units.at(2)->_Id;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(3)->_Data), STATE_EXTEND_RIGH);
				this->_GameState_Id._RIGH = Link->_Data->_Data_Units.at(3)->_Id;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(4)->_Data), STATE_EXTEND_ABOV);
				this->_GameState_Id._ABOV = Link->_Data->_Data_Units.at(4)->_Id;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(5)->_Data), STATE_EXTEND_BELO);
				this->_GameState_Id._BELO = Link->_Data->_Data_Units.at(5)->_Id;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(6)->_Data), STATE_EXTEND_LEFT_ABOV);
				this->_GameState_Id._LEFT_ABOV = Link->_Data->_Data_Units.at(6)->_Id;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(7)->_Data), STATE_EXTEND_LEFT_BELO);
				this->_GameState_Id._LEFT_BELO = Link->_Data->_Data_Units.at(7)->_Id;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(8)->_Data), STATE_EXTEND_RIGH_ABOV);
				this->_GameState_Id._RIGH_ABOV = Link->_Data->_Data_Units.at(8)->_Id;
				this->CompileStateUnits(Locate_Extend_State(Link->_Data->_Data_Units.at(9)->_Data), STATE_EXTEND_RIGH_BELO);
				this->_GameState_Id._RIGH_BELO = Link->_Data->_Data_Units.at(9)->_Id;

				this->Set_DataAll_State(10, 10);
				return;
			}
		}
	}
}

GameStateBase& GameStateBase::GetStateBase(int Display_Width, int Display_Height)
{
	static GameStateBase GameState(Display_Width, Display_Height);
	return GameState;
}

Move_State GameStateBase::Get_Move_State()
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

float GameStateBase::Set_ExacHeight(double Current, float& MoveState, float& State_MoveY, float& Auto_Adjust_Length)
{
	static int EHCountS{ 0 };
	static int EHCountL{ 0 };
	if (_Adjust_Enable == false)
		return 0.0f;
	float Temp_Move{ 0.0f };
	if ((float)Current < ((float)this->Get_StateHeight()) / 2)
	{
		EHCountS++;
		if (EHCountS == this->_Adjust_Frame)
		{
			if (MoveState < 0 && MoveState + _GameState_Adjust > 0)
			{
				Temp_Move = MoveState;
				std::cout << "A Temp_Move  _" << Temp_Move << std::endl;
				std::cout << "A MoveState  _" << MoveState << std::endl;
				State_MoveY += Temp_Move;
				Auto_Adjust_Length += Temp_Move;
				MoveState = 0;
				std::cout << " MoveState  _" << MoveState << std::endl;
			}
			else
			{
				Auto_Adjust_Length += _GameState_Adjust;
				MoveState += _GameState_Adjust;
				State_MoveY += _GameState_Adjust;
			}
			EHCountS = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
		EHCountS = 0;

	if ((float)Current > ((float)this->Get_StateHeight()) / 2)
	{
		EHCountL++;
		if (EHCountL == this->_Adjust_Frame)
		{
			if (MoveState > _GameState_Adjust)
			{
				Auto_Adjust_Length -= _GameState_Adjust;
				MoveState -= _GameState_Adjust;
				State_MoveY -= _GameState_Adjust;
			}
			else if (MoveState - _GameState_Adjust < 0)
			{
				float Temp_Move = MoveState;
				std::cout << "B Temp_Move  _" << Temp_Move << std::endl;
				std::cout << "B MoveState  _" << MoveState << std::endl;
				State_MoveY -= Temp_Move;
				Auto_Adjust_Length -= Temp_Move;
				Temp_Move = -Temp_Move;
				MoveState = 0;
				std::cout << " MoveState  _" << MoveState << std::endl;
			}
			EHCountL = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
		EHCountL = 0;
	return Temp_Move;
}

float GameStateBase::Set_ExacWidth(double Current, float& MoveState, float& State_MoveX, float& Auto_Adjust_Length)
{
	static int EWCountS{ 0 };
	static int EWCountL{ 0 };
	if (_Adjust_Enable == false)
		return 0.0f;
	float Temp_Move{ 0.0f };
	if ((float)Current < ((float)this->Get_StateWidth()) / 2)
	{
		EWCountS++;
		if (EWCountS == this->_Adjust_Frame)
		{
			if (-MoveState < 0 && _GameState_Adjust + -MoveState>0)
			{
				Temp_Move = MoveState;
				while (Temp_Move > 2.5)
					Temp_Move -= 2.5;
				std::cout << "A Temp_Move  _" << Temp_Move << std::endl;
				std::cout << "A MoveState  _" << MoveState << std::endl;
				State_MoveX += Temp_Move;
				Auto_Adjust_Length += Temp_Move;
				MoveState = 0;
				std::cout << " MoveState  _" << MoveState << std::endl;
			}
			else
			{
				Auto_Adjust_Length += _GameState_Adjust;
				MoveState += _GameState_Adjust;
				State_MoveX += _GameState_Adjust;
			}
			EWCountS = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
		EWCountS = 0;

	if ((float)Current > ((float)this->Get_StateWidth()) / 2)
	{
		EWCountL++;
		if (EWCountL == this->_Adjust_Frame)
		{
			if (MoveState > _GameState_Adjust)
			{
				Auto_Adjust_Length -= _GameState_Adjust;
				MoveState -= _GameState_Adjust;
				State_MoveX -= _GameState_Adjust;
			}
			else if (MoveState < _GameState_Adjust)
			{
				float Temp_Move = MoveState;
				while (Temp_Move > 2.5)
					Temp_Move -= 2.5;
				std::cout << "B Temp_Move  _" << Temp_Move << std::endl;
				std::cout << "B MoveState  _" << MoveState << std::endl;
				State_MoveX -= Temp_Move;
				Auto_Adjust_Length -= Temp_Move;
				Temp_Move = -Temp_Move;
				MoveState = 0;
				std::cout << " MoveState  _" << MoveState << std::endl;
			}
			EWCountL = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
		EWCountL = 0;
	return Temp_Move;
}

void GameStateBase::Set_Adjust_Frequency(int Frame)
{
	this->_Adjust_Frame = Frame;
}

std::vector<bool>* GameStateBase::Get_GameState_MoveAble()
{
	static std::vector<bool> MAB{};
	for (const auto& State : _GameState)
	{
		if (State->GetMoveAble())
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

	int Line_Width{ this->_MState._Move_PX - this->_MState._Move_NX };
	int Coum_Width{ this->_MState._Move_PX - this->_MState._Move_PY };

	//TODO
}

void GameStateBase::Set_Move_State(int Event_Id)
{
	switch (Event_Id)
	{
	case MoveToNW:
		this->_MState._Move_NX++;
		this->_MState._Move_PX++;
		break;
	case MoveToPW:
		this->_MState._Move_NX--;
		this->_MState._Move_PX--;
		break;
	case MoveToNH:
		this->_MState._Move_NY++;
		this->_MState._Move_PY++;
		break;
	case MoveToPH:
		this->_MState._Move_NY--;
		this->_MState._Move_PY--;
		break;
	}
}

void GameStateBase::Reload_State(float& CurrentX, float& CurrentY)
{

}

void GameStateBase::Update_Move(float MoveX, float MoveY, ECheck_Edge Check)
{
	static SLocation* Distance{ &LocationBase::GetLocationBase().Get_LocationS(this->_Distance_Move) };

	if ((this->_Half_State_Width == 0.0f) || (this->_Half_State_Height == 0.0f))
		this->Set_Display_State(this->_GameState_Width, this->_GameState_Height);

	static float State_Above_Below{ this->_Half_State_Width * 2 / 3 };

	switch (Check)
	{
	case CHECK_EDGE_CURR:
		MoveX += 0.0f;
		MoveY += 0.0f;
		break;
	case CHECK_EDGE_LEFT:
		MoveX -= this->_Half_State_Width * 2 / 3;
		MoveY += State_Above_Below;
		State_Above_Below = -State_Above_Below;
		break;
	case CHECK_EDGE_RIGH:
		MoveX += this->_Half_State_Width * 2 / 3;
		MoveY += State_Above_Below;
		State_Above_Below = -State_Above_Below;
		break;
	case CHECK_EDGE_BELO:
		MoveX += State_Above_Below;
		MoveY -= this->_Half_State_Height * 2 / 3;
		State_Above_Below = -State_Above_Below;
		break;
	case CHECK_EDGE_ABOV:
		MoveX += State_Above_Below;
		MoveY += this->_Half_State_Height * 2 / 3;
		State_Above_Below = -State_Above_Below;
		break;
	}

	float Temp_LocationX = (Distance->_Location_X + MoveX) * (this->_GameState_Width / 2.0f);
	float Temp_LocationY = (Distance->_Location_Y + MoveY) * (this->_GameState_Height / 2.0f);

	Temp_LocationX = static_cast<int>(Temp_LocationX + 0.5f) > static_cast<int>(Temp_LocationX) ? Temp_LocationX + 0.5f : Temp_LocationX;
	Temp_LocationY = static_cast<int>(Temp_LocationY - 0.5f) < static_cast<int>(Temp_LocationY) ? Temp_LocationY - 0.5f : Temp_LocationY;

	this->_Exac_LocationX = static_cast<int>(Temp_LocationX);
	this->_Exac_LocationY = static_cast<int>(Temp_LocationY);

	if (Distance->_Location_X + MoveX < 0.0f)
		--this->_Exac_LocationX;
	if (Distance->_Location_Y + MoveY > 0.0f)
		++this->_Exac_LocationY;

	this->_Exac_LocationY = -this->_Exac_LocationY;
}

GameStateBase::GameStateBase(int Width, int Height) :
	_GameState_Width(Height), _GameState_Height(Width), _GameState(NULL), _GameState_Adjust(0.0f), _Compile_Success(false),
	_CurrentMid(nullptr), _MState(0), _Data_Height(Height), _Data_Width(Width), _Is_Adjusting(false), _Adjust_Frame(1),
	_Adjust_Enable(false), _Exac_LocationX(0), _Exac_LocationY(0), _GameState_Extend(), _Is_Data_Set(false)
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };
	this->_Distance_Move = LCB->New_Location_set("Distance_Move");
	this->_Distance_Screen_Mid = LCB->New_Location_set("Distance_Screen_Mid");
}

GameStateBase::~GameStateBase()
{
	std::vector<StateUnit*>().swap(this->_GameState);
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

bool StateUnit::GetMoveAble()
{
	return this->_Is_Move_Target;
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

size_t GameStateBase::Get_StateSize()
{
	return _GameState.size();
}

StateUnit* GameStateBase::Get_StateUnit(int Pos)
{
	return this->_GameState.at(Pos);
}

StateUnit* GameStateBase::Get_StateUnit(EState_Extend State, int Pos)
{
	switch (State)
	{
	case STATE_ORIGIN_MIDD:
		return this->_GameState.at(Pos);
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

GameStateBase::GameStateBase(const GameStateBase&) :_GameState_Width(0), _GameState_Height(0), _GameState_Adjust(0),
_Compile_Success(false), _CurrentMid(nullptr), _MState(0), _Data_Height(0), _Data_Width(0), _Is_Adjusting(false),
_Adjust_Frame(1), _Adjust_Enable(false), _Exac_LocationX(0), _Exac_LocationY(0), _GameState_Extend(), _Is_Data_Set(false)
{
	LocationBase* LCB{ &LocationBase::GetLocationBase() };
	this->_Distance_Move = LCB->New_Location_set("Distance_Move");
	this->_Distance_Screen_Mid = LCB->New_Location_set("Distance_Screen_Mid");
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

bool GameStateBase::Get_Adjust_While_Move()
{
	return this->_Adjust_While_Move;
}

bool GameStateBase::Get_Engine_File()
{
	if (!this->_Is_Data_Set)
		if (!this->_Data_Base.Get_LocalData("Tanxl Engine VersionMes"))
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

int GameStateBase::Get_StateHeight()const
{
	return this->_GameState_Height;
}

int GameStateBase::Get_StateWidth()const
{
	return this->_GameState_Width;
}

std::vector<StateUnit*>* GameStateBase::Get_GameState()
{
	return &this->_GameState;
}

//Move_State

Move_State::Move_State(int NX, int PX, int NY, int PY) :_Move_NX(NY), _Move_NY(NY), _Move_PX(PX), _Move_PY(PY) {}