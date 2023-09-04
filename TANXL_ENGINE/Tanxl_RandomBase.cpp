#pragma once

#include "Tanxl_RandomBase.h"

RandomBase::RandomBase() 
{ 
    srand(static_cast<unsigned int>(time(0)));
}

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
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 15; ++i)
    {
        if (i % 5 == 0 && i != 0)
            Data += "-";
        Data += UniData[rand() % 62];
    }
    return Data;
}

std::string RandomBase::Generate(int seed)
{
    std::string Data{ "" };
    srand(static_cast<unsigned int>(seed));
    for (int i = 0; i < 15; ++i)
    {
        if (i % 5 == 0 && i != 0)
            Data += "-";
        Data += UniData[rand() % 62];
    }
    srand(static_cast<unsigned int>(time(0)));
    return Data;
}

std::string RandomBase::Generate_State(unsigned Width, unsigned Height)
{
    this->Suffle_UniData(1);
    std::string ReturnVal{ "" };
    for (int i{ 0 }; i < static_cast<int>(Width) * static_cast<int>(Height); ++i)
    {
        ReturnVal += "a-";
        ReturnVal += std::to_string(this->Random(0, 3));
        ReturnVal += ",";
    }
    return ReturnVal;
}

std::string RandomBase::GenerateAutoSeed()
{
    static unsigned int seed{ 0 };
    std::string Data{};
    srand(seed++);
    for (int i = 0; i < 15; ++i)
    {
        if (i % 5 == 0 && i != 0)
            Data += "-";
        Data += UniData[rand() % 62];
    }
    return Data;
}

int RandomBase::Random(int Start, int End)
{
    if (End <= Start)
        return Start;
    static unsigned seed = 0;
    srand(static_cast<unsigned int>(seed++));
    return (rand() % (End - Start)) + Start;
}

void RandomBase::Suffle_UniData(int Times)
{
    while (Times--)
    {
        for (int i{ 0 }; i < 62; ++i)
        {
            std::string Temp = UniData[i];
            int Exchange_Val = rand() % 62;
            UniData[i] = UniData[Exchange_Val];
            UniData[Exchange_Val] = Temp;
        }
    }
}