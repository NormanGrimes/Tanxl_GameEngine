#pragma once

#include "Tanxl_RandomBase.h"

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
    return Data;
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
    srand(static_cast<unsigned int>(time(0)));
    return (rand() % (End - Start)) + Start;
}

void RandomBase::Suffle_UniData(int Times)
{
    srand(static_cast<unsigned int>(time(0)));
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