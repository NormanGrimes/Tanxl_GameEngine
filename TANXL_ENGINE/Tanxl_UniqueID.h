//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-09-15 21:18
// 添加根据种子生成随机ID的功能
// 格式调整
// 增加生成储存条目功能
// 增加每次调用都会修改种子的生成函数

#pragma once

#ifndef _TANXL_UNIQUEID_
#define _TANXL_UNIQUEID_

#include <string>
#include <iostream>
//using namespace std;

class UniqueIdBase
{
public:
    static UniqueIdBase& GetIdGenerator()
    {
        static UniqueIdBase UNIBase;
        return UNIBase;
    }

    //Random by Time 不适合短时间大量生成
    std::string Generate()
    {
        std::string Data{};
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < 15; i++)
        {
            if (i % 5 == 0 && i != 0)
                Data += "-";
            Data += Uniqt[rand() % 62];
        }
        return Data;
    }

    //Random by Seed
    std::string Generate(int seed)
    {
        std::string Data{};
        srand(static_cast<unsigned int>(seed));
        for (int i = 0; i < 15; i++)
        {
            if (i % 5 == 0 && i != 0)
                Data += "-";
            Data += Uniqt[rand() % 62];
        }
        return Data;
    }

    std::string GenerateAutoSeed()
    {
        static unsigned int seed = 0;
        std::string Data{};
        srand(seed++);
        for (int i = 0; i < 15; i++)
        {
            if (i % 5 == 0 && i != 0)
                Data += "-";
            Data += Uniqt[rand() % 62];
        }
        return Data;
    }

    int Random(int Start, int End)
    {
        if (End - Start <= 0)
            return 0;
        
        return (rand() % (End - Start)) + Start;
    }

    std::string Generate_Data(int Type, int Exac, std::string Key)
    {
        std::string Data;
        Data = "\t<Type_Status : " + std::to_string(Type) + ">"
            + "\t\t<Exac_Status : " + std::to_string(Exac) + ">"
            + "\t\t\t<TDB_Item>"
            + "\t\t\t\t<Oth1: " + Key + "</Oth1>"
            + "\t\t\t</TDB_Item>"
            + "\t\t</Exac_Status>"
            + "\t</Type_Status>";
        return Data;
    }

private:

    std::string Uniqt[62] = {
    {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"0"},
    {"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}, {"h"}, {"i"}, {"j"},
    {"k"}, {"l"}, {"m"}, {"n"}, {"o"}, {"p"}, {"q"}, {"r"}, {"s"}, {"t"},
    {"u"}, {"v"}, {"w"}, {"x"}, {"y"}, {"z"}, {"A"}, {"B"}, {"C"}, {"D"},
    {"E"}, {"F"}, {"G"}, {"H"}, {"I"}, {"J"}, {"K"}, {"L"}, {"M"}, {"N"},
    {"O"}, {"P"}, {"Q"}, {"R"}, {"S"}, {"T"}, {"U"}, {"V"}, {"W"}, {"X"},
    {"Y"}, {"Z"} };

    UniqueIdBase() { srand(static_cast<unsigned int>(time(0))); }
    ~UniqueIdBase() {}
    UniqueIdBase(const UniqueIdBase&) {}
    UniqueIdBase& operator=(const UniqueIdBase&) { return *this; }
};

#endif