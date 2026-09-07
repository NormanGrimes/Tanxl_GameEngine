#pragma once

#include "Tanxl_RandomBase.h"

std::string RandomBase::Generate()
{
    std::string Data{};
    unsigned seed{ static_cast<unsigned>(time(0)) };
    _RandomEngine.seed(seed);
    std::uniform_int_distribution<int> UID(0, 61);
    for (int i{ 0 }; i < 15; ++i)
    {
        if ((i % 5 == 0) && (i != 0))
            Data += "-";
        Data += _UniData[UID(_RandomEngine)];
    }
    return Data;
}

std::string RandomBase::Generate(int seed)
{
    std::string Data{ "" };
    _RandomEngine.seed(seed);
    std::uniform_int_distribution<int> UID(0, 61);
    for (int i{ 0 }; i < 15; ++i)
    {
        if ((i % 5 == 0) && (i != 0))
            Data += "-";
        Data += _UniData[UID(_RandomEngine)];
    }
    return Data;
}

std::string RandomBase::Generate_State(unsigned Width, unsigned Height, bool Random_Event)
{
    std::string ReturnVal{ "" };
    for (int i{ 0 }; i < static_cast<int>(Width) * static_cast<int>(Height); ++i)
    {
        int StateVal{ RandomId.Generate() };
        int EventVal{ RandomEvent.Generate() };

        if(Random_Event)
            ReturnVal += std::to_string(EventVal) + "-" + std::to_string(StateVal) + ",";
        else
            ReturnVal += "0-" + std::to_string(StateVal) + ",";
    }
    //std::cout << ReturnVal << std::endl;
    return ReturnVal;
}

std::string RandomBase::GenerateAutoSeed()
{
    std::string Data{};
    _RandomEngine.seed(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> UID(0, 61);
    for (int i{ 0 }; i < 15; ++i)
    {
        if ((i % 5 == 0) && (i != 0))
            Data += "-";
        Data += _UniData[UID(_RandomEngine)];
    }
    return Data;
}

int RandomBase::GenerateNum(int seed, int LowValue, int HighValue)
{
    _RandomEngine.seed(seed);
    std::uniform_int_distribution<int> UID(LowValue, HighValue);
    return UID(_RandomEngine);
}

int RandomBase::RandomAutoSeed(int Start, int End)
{
    if (End <= Start)
        return Start;
    _RandomEngine.seed(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> UID(Start, End);
    return UID(_RandomEngine);
}

void RandomBase::Suffle_UniData(int Times)
{
    _RandomEngine.seed(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> UID(0, 61);
    while (Times--)
    {
        for (int i{ 0 }; i < 31; ++i)
        {
            std::string Temp{ _UniData[i] };
            int Exchange_Val{ UID(_RandomEngine)};
            _UniData[i] = _UniData[Exchange_Val];
            _UniData[Exchange_Val] = Temp;
        }
    }
}

void RandomBase::Reset_Default()
{
    std::string SaveUniData[62] = {
    {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"0"},
    {"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}, {"h"}, {"i"}, {"j"},
    {"k"}, {"l"}, {"m"}, {"n"}, {"o"}, {"p"}, {"q"}, {"r"}, {"s"}, {"t"},
    {"u"}, {"v"}, {"w"}, {"x"}, {"y"}, {"z"}, {"A"}, {"B"}, {"C"}, {"D"},
    {"E"}, {"F"}, {"G"}, {"H"}, {"I"}, {"J"}, {"K"}, {"L"}, {"M"}, {"N"},
    {"O"}, {"P"}, {"Q"}, {"R"}, {"S"}, {"T"}, {"U"}, {"V"}, {"W"}, {"X"},
    {"Y"}, {"Z"} };
    for (int i{ 0 }; i < 62; ++i)
        _UniData[i] = SaveUniData[i];

    RandomEvent.Clear_Event();
    RandomId.Clear_Event();

    Set_RandomState(RANDOM_EVENT, 0, 9);
    Set_RandomState(RANDOM_EVENT, 1, 1);
    Set_RandomState(RANDOM_EVENT, 2, 3);
    Set_RandomState(RANDOM_EVENT, 3, 3);
    Set_RandomState(RANDOM_EVENT, 4, 3);
    Set_RandomState(RANDOM_EVENT, 5, 0);
    Set_RandomState(RANDOM_EVENT, 6, 1);
    Set_RandomState(RANDOM_EVENT, 7, 1);

    Set_RandomState(RANDOM_ID, 0, 1);
    Set_RandomState(RANDOM_ID, 1, 1);
    Set_RandomState(RANDOM_ID, 2, 1);
    Set_RandomState(RANDOM_ID, 3, 1);
}

void RandomBase::Set_RandomState(EState_WeightEvent RandomName, int Id, int Weight)
{
    if (RandomName == EState_WeightEvent::RANDOM_ID)
        RandomId.Append_State(Id, Weight);
    else
        RandomEvent.Append_State(Id, Weight);
}

const std::string RandomBase::Get_Version()
{
    return _Version;// "Tanxl_ClassBase::Get_Version();
}

std::default_random_engine RandomBase::_RandomEngine;

std::string RandomBase::_UniData[] = {
    {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"0"},
    {"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}, {"h"}, {"i"}, {"j"},
    {"k"}, {"l"}, {"m"}, {"n"}, {"o"}, {"p"}, {"q"}, {"r"}, {"s"}, {"t"},
    {"u"}, {"v"}, {"w"}, {"x"}, {"y"}, {"z"}, {"A"}, {"B"}, {"C"}, {"D"},
    {"E"}, {"F"}, {"G"}, {"H"}, {"I"}, {"J"}, {"K"}, {"L"}, {"M"}, {"N"},
    {"O"}, {"P"}, {"Q"}, {"R"}, {"S"}, {"T"}, {"U"}, {"V"}, {"W"}, {"X"},
    {"Y"}, {"Z"} };

std::string RandomBase::_Version{ "0.3" };

RandomState RandomBase::RandomId{};

RandomState RandomBase::RandomEvent{};

StateWeight::StateWeight(int StateId, int Weight) :
    _StateId(StateId), _Weight(Weight) {}

RandomState::RandomState() :_State_Weight_Count(0), _Event_Rate() {}

RandomState::~RandomState()
{
    this->Clear_Event();
}

int RandomState::Generate()
{
    unsigned seed{ static_cast<unsigned>(time(0)) };
    static int AppSeed{ RandomBase::RandomAutoSeed(100,500) };
    int RandomId{ RandomBase::GenerateNum(seed + AppSeed++, 0, this->_State_Weight_Count) };
    for (int i{ 0 }; i < this->_Event_Rate.size(); ++i)
        if (this->_Event_Rate.at(i)->_Weight >= RandomId)
            return this->_Event_Rate.at(i)->_StateId;
    return 0;
}

void RandomState::Append_State(int StateId, int Weight)
{
    if (Weight == 0)
        return;
    this->_State_Weight_Count += Weight;
    this->_Event_Rate.push_back(new StateWeight(StateId, this->_State_Weight_Count));
}

void RandomState::Clear_Event()
{
    _Event_Rate.erase(_Event_Rate.begin(), _Event_Rate.end());
}
