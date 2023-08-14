﻿//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2023-02-08 09:23
// 整理至引擎核心层

#pragma once

#ifndef _TANXL_RANDOMBASE_
#define _TANXL_RANDOMBASE_

#include <string>
#include <iostream>

class RandomBase
{
public:
    //单例获取函数
    static RandomBase& GetRandomBase();

    //根据当前时间生成一组序列号 不适合短时间大量生成
    std::string Generate();

    //根据提供的种子生成一组序列号 相同的种子结果相同
    std::string Generate(int seed);

    //根据内部提供的种子生成一组序列号 可用于短时间大量生成 重启后若不调用Suffle_UniData刷新字典再调用会出现重复序列号
    std::string GenerateAutoSeed();

    //随机生成一个介于Start与End之间的数字
    int Random(int Start, int End);

    //刷新随机字库
    void Suffle_UniData(int Times);

private:

    std::string UniData[62] = {
    {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"0"},
    {"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}, {"h"}, {"i"}, {"j"},
    {"k"}, {"l"}, {"m"}, {"n"}, {"o"}, {"p"}, {"q"}, {"r"}, {"s"}, {"t"},
    {"u"}, {"v"}, {"w"}, {"x"}, {"y"}, {"z"}, {"A"}, {"B"}, {"C"}, {"D"},
    {"E"}, {"F"}, {"G"}, {"H"}, {"I"}, {"J"}, {"K"}, {"L"}, {"M"}, {"N"},
    {"O"}, {"P"}, {"Q"}, {"R"}, {"S"}, {"T"}, {"U"}, {"V"}, {"W"}, {"X"},
    {"Y"}, {"Z"} };

    RandomBase() { srand(static_cast<unsigned int>(time(0))); }
    ~RandomBase() {}
    RandomBase(const RandomBase&) {}
    RandomBase& operator=(const RandomBase&) { return *this; }
};

#endif