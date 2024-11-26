#pragma once

#include "Tanxl_RandomBase.h"

RandomBase::RandomBase() {}

RandomBase::~RandomBase() {}

RandomBase::RandomBase(const RandomBase&) {}

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
        Data += UniData[UID(DRE)];
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
        Data += UniData[UID(DRE)];
    }
    return Data;
}

std::string RandomBase::Generate_State(unsigned Width, unsigned Height, bool Random_Event)
{
    static unsigned seed{ static_cast<unsigned>(time(0)) };
    std::default_random_engine DRE(seed++);
    std::uniform_int_distribution<int> UID(0, 6);
    std::uniform_int_distribution<int> SID(0, 3);
    this->Suffle_UniData(1);
    std::string ReturnVal{ "" };
    for (int i{ 0 }; i < static_cast<int>(Width) * static_cast<int>(Height); ++i)
    {
        int StateVal = UID(DRE);
        if (StateVal == 4)//OCEAN BLOCK
            ReturnVal += "1-";
        else if (Random_Event)
        {
            if (StateVal == 5)
            {
                StateVal = SID(DRE);
                ReturnVal += "2-";
            }
            else if (StateVal == 6)
            {
                StateVal = SID(DRE);
                ReturnVal += "3-";
            }
            else
                ReturnVal += "0-";
        }
        else
            ReturnVal += "0-";

        ReturnVal += std::to_string(StateVal);
        ReturnVal += ",";
    }
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
        Data += UniData[UID(DRE)];
    }
    return Data;
}

int RandomBase::GenerateNum(int seed)
{
    std::string Data{};
    std::default_random_engine DRE(seed++);
    std::uniform_int_distribution<int> UID(0, 9);
    return NumData[UID(DRE)];
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
            std::string Temp{ UniData[i] };
            int Exchange_Val{ UID(DRE)};
            UniData[i] = UniData[Exchange_Val];
            UniData[Exchange_Val] = Temp;
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
            int Temp{ NumData[i] };
            int Exchange_Val{ UID(DRE) };
            NumData[i] = NumData[Exchange_Val];
            NumData[Exchange_Val] = Temp;
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
        this->UniData[i] = SaveUniData[i];
    int SaveNumData[10] =
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    for (int i{ 0 }; i < 10; ++i)
        this->NumData[i] = SaveNumData[i];
}

const std::string RandomBase::Get_Version()
{
    return this->_Version;
}