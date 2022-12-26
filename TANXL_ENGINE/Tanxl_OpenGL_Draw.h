//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-08-15 22:41
// 增加对地图额外一圈载入的相关操作
// 主绘制循环现在支持无限世界展示
// 地图绘制部分的总地图尺寸采用自动获取方式
// 绘制半边长采用函数自动获取
// 提升重新载入世界的判断坐标精确性
// 增加私有变量PreLoad用于自定义预加载环形区域数量
// 增加总地图尺寸的获取与设置功能
// 修复预加载内容非环状扩展的问题
// 修复计算坐标部分负浮点数化为整数有偏移的问题
// 启用移动受限功能
// 启用自动移动测试

#pragma once

#ifndef TANXL_DATABASE_H
#define TANXL_DATABASE_H
#include "Tanxl_DataBase.h"
#endif

#ifndef TANXL_GAMESTATE_H
#define TANXL_GAMESTATE_H
#include "Tanxl_GameState.h"
#endif

#ifndef TANXL_INSERTACTION_H
#define TANXL_INSERTACTION_H
#include "Tanxl_InsertAction.h"
#endif

#ifndef TANXL_OPENGL_RENDER_H
#define TANXL_OPENGL_RENDER_H
#include "Tanxl_OpenGL_Render.h"
#endif

#ifndef TANXL_UNIQUEID
#define TANXL_UNIQUEID
#include "Tanxl_UniqueID.h"
#endif

#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

class OpenGL_Draw
{
public:
	OpenGL_Draw(int ScreenWidth = 600, int ScreenHeight = 600);
	//绘制模块主要初始化函数 window为需要绘制的窗口 State为单例类，需要完成地图设置后再调用此函数初始化
	void init(GLFWwindow* window, GameStateBase* State);
	void display(GLFWwindow* window, double currentTime, GameStateBase* State);
	//绘制主循环 在此之后的一切操作都会被忽略
	void mainLoop(GameStateBase* State);
	void UpdateMargin(float& Margin);
	void Set_PreLoad(int PreLoads);
	//用于第一次或重新加载整个地图场景
	void ReLoadState(GameStateBase* State, int PosX, int PosY);
private:

	GLuint _Position;

	GLint _StateInfor[201];

	bool _Clear_Function;
	bool _Is_State_Changed;

	GLuint _renderingProgram;
	GLuint _vao[1];

	//记录地图场景的方块行数
	int _HeightInt;
	//记录地图场景的方块列数
	int _WidthInt;
	//窗口的宽度
	int _ScreenWidth;
	//窗口的高度
	int _ScreenHeight;
	//记载额外加载的地图环数量
	int _PreLoads;
};