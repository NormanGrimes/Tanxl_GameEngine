#pragma once

#include "Tanxl_RandomBase.h"

RandomBase::RandomBase() :Tanxl_ClassBase("0.3") {}

RandomBase::~RandomBase() {}

RandomBase::RandomBase(const RandomBase&) :Tanxl_ClassBase("0.3") {}

RandomBase& RandomBase::operator=(const RandomBase&) 
{ 
    return *this;
}

RandomBase& RandomBase::GetRandomBase()
{
    static RandomBase RB;
    return RB;
}

std::string RandomBase::Generate()
{
    std::string Data{};
    std::default_random_engine DRE(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> UID(0, 61);
    for (int i{ 0 }; i < 15; ++i)
    {
        if ((i % 5 == 0) && (i != 0))
            Data += "-";
        Data += this->_UniData[UID(DRE)];
    }
    return Data;
}

std::string RandomBase::Generate(int seed)
{
    std::string Data{ "" };
    std::default_random_engine DRE(seed);
    std::uniform_int_distribution<int> UID(0, 61);
    for (int i{ 0 }; i < 15; ++i)
    {
        if ((i % 5 == 0) && (i != 0))
            Data += "-";
        Data += this->_UniData[UID(DRE)];
    }
    return Data;
}

std::string RandomBase::Generate_State(unsigned Width, unsigned Height, bool Random_Event)
{
    static unsigned seed{ static_cast<unsigned>(time(0)) };
    std::default_random_engine DRE(seed++);
    std::uniform_int_distribution<int> SID(0, 3);
    std::uniform_int_distribution<int> EID(0, 6);
    this->Suffle_UniData(1);
    std::string ReturnVal{ "" };
    for (int i{ 0 }; i < static_cast<int>(Width) * static_cast<int>(Height); ++i)
    {
        int StateVal{ SID(DRE) };
        int EventVal{ EID(DRE) };

        if (EventVal > 4)
            EventVal = 0;

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
    static unsigned seed{ static_cast<unsigned>(time(0)) };
    std::string Data{};
    std::default_random_engine DRE(seed++);
    std::uniform_int_distribution<int> UID(0, 61);
    for (int i{ 0 }; i < 15; ++i)
    {
        if ((i % 5 == 0) && (i != 0))
            Data += "-";
        Data += this->_UniData[UID(DRE)];
    }
    return Data;
}

int RandomBase::GenerateNum(int seed)
{
    std::default_random_engine DRE(seed++);
    std::uniform_int_distribution<int> UID(0, 9);
    return this->_NumData[UID(DRE)];
}

int RandomBase::RandomAutoSeed(int Start, int End)
{
    if (End <= Start)
        return Start;
    static unsigned seed{ 0 };
    std::default_random_engine DRE(++seed + static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> UID(Start, End);
    return UID(DRE);
}

void RandomBase::Suffle_UniData(int Times)
{
    std::default_random_engine DRE(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> UID(0, 61);
    while (Times--)
    {
        for (int i{ 0 }; i < 31; ++i)
        {
            std::string Temp{ this->_UniData[i] };
            int Exchange_Val{ UID(DRE)};
            this->_UniData[i] = this->_UniData[Exchange_Val];
            this->_UniData[Exchange_Val] = Temp;
        }
    }
}

void RandomBase::Suffle_NumData(int Times)
{
    std::default_random_engine DRE(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> UID(0, 9);
    while (Times--)
    {
        for (int i{ 0 }; i < 10; ++i)
        {
            int Temp{ this->_NumData[i] };
            int Exchange_Val{ UID(DRE) };
            this->_NumData[i] = this->_NumData[Exchange_Val];
            this->_NumData[Exchange_Val] = Temp;
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
        this->_UniData[i] = SaveUniData[i];
    int SaveNumData[10] =
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    for (int i{ 0 }; i < 10; ++i)
        this->_NumData[i] = SaveNumData[i];
}

const std::string RandomBase::Get_Version()
{
    return Tanxl_ClassBase::Get_Version();
}