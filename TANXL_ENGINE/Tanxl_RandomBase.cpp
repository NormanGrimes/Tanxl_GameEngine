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

std::string RandomBase::Generate_State(unsigned Width, unsigned Height)
{
    std::default_random_engine DRE(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> UID(0, 3);
    this->Suffle_UniData(1);
    std::string ReturnVal{ "" };
    for (int i{ 0 }; i < static_cast<int>(Width) * static_cast<int>(Height); ++i)
    {
        ReturnVal += "a-";
        ReturnVal += std::to_string(UID(DRE));
        ReturnVal += ",";
    }
    return ReturnVal;
}

std::string RandomBase::GenerateAutoSeed()
{
    static unsigned int seed{ 0 };
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

int RandomBase::Random(int Start, int End)
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
        for (int i{ 0 }; i < 62; ++i)
        {
            std::string Temp{ UniData[i] };
            int Exchange_Val{ UID(DRE)};
            UniData[i] = UniData[Exchange_Val];
            UniData[Exchange_Val] = Temp;
        }
    }
}

const std::string RandomBase::Get_Version()
{
    return this->_Version;
}