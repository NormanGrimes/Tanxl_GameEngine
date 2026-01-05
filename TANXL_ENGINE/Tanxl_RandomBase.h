//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2023-02-08 09:23
// 整理至引擎核心层
// 取随机数接口增加随机性
// 增加生成随机地图区块的功能
// 随机数接口代码简化
// 随机功能改用标准库实现
// 增加版本信息功能
// 增加纯数字版本字库
// 增加刷新纯数字字库的功能
// 增加随机数生成功能
// 增加恢复到初始状态功能
// 修复短时间内生成的地图信息一样的问题
// 地图生成功能修改参数
// 增加对新版随机地图的支持
// 随机地图事件参数改为数字
// 随机世界生成功能可选随机事件生成
// 修复随机世界生成错误数据的问题
// 刷新字库执行的次数减半
// 随机基础类改为继承自引擎基础类
// 地图生成接口解除纹理与事件的绑定
// 降低地图事件的生成概率
// 修改内部变量名称
// 多个成员函数设为常量
// 转为静态类

#pragma once

#ifndef _TANXL_RANDOMBASE_
#define _TANXL_RANDOMBASE_

#include <string>
#include <iostream>
#include <random>

class RandomBase
{
public:
    //根据当前时间生成一组序列号 不适合短时间大量生成
    static std::string Generate();

    //根据提供的种子生成一组序列号 相同的种子结果相同
    static std::string Generate(int seed);

    //随机生成一组地图数据 Width为数据宽度 Height为数据高度
    static std::string Generate_State(unsigned Width, unsigned Height, bool Random_Event = false);

    //根据内部提供的种子生成一组序列号 可用于短时间大量生成 重启后若不调用Suffle_UniData刷新字典再调用会出现重复序列号
    static std::string GenerateAutoSeed();

    //根据输入的种子生成一组数字
    static int GenerateNum(int seed);

    //随机生成一个介于Start与End之间的数字
    static int RandomAutoSeed(int Start, int End);

    //刷新随机字库
    static void Suffle_UniData(int Times);

    //刷新数字字库
    static void Suffle_NumData(int Times);

    //恢复到初始状态
    static void Reset_Default();

    //获取版本信息
    static const std::string Get_Version();

private:

    static std::string _UniData[62];
    static int _NumData[10];
    static std::string _Version;
};

#endif