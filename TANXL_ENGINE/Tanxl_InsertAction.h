//_VERSION_0_4_ UPDATE LOG
// LAST_UPDATE 2022-05-30 01:18
// 整合原LocationBase模块的基本功能
// 提供编译地图场景的功能

#pragma once

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef GL_GLEW_H
#define GL_GLEW_H
#include <GL\glew.h>
#endif

#ifndef GLFW_GLFW3_H
#define GLFW_GLFW3_H
#include <GLFW\glfw3.h>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

struct Key_Unit
{
	Key_Unit();
	Key_Unit(int GLKEY, bool MOVX, bool MOVY, float MOVL);

	int   GLFW_KEY;
	bool  MoveToX;
	bool  MoveToY;
	float MoveLen;
};

class InsertEventBase
{
public:
	static InsertEventBase& GetInsertBase();
	//自动根据已知信息返回方块能移动的最大范围 公式 1 - ( 1 / 游戏地图边长（方块数）)
	float Get_AutoFloat(int Blocks);
	void RegistEvent(Key_Unit KU);
	void GetInsert(GLFWwindow* window, float* MoveX, float* MoveY);
	//地图边长相同时 或仅允许在一个正方形区域移动时使用 Max_float用于指定最大移动距离（相对地图比例）
	void Set_MaxFloat(float Max_float);
	void Set_MaxLine(int Max_Line);
	void Get_MoveData(std::vector<bool>* PVB);
private:
	void AutoCheck(float* MoveX, float* MoveY);
	std::vector<Key_Unit> _KeyEventS;
	std::vector<bool>* _PTB;
	float _Max_float;
	int _Max_Line;
	InsertEventBase();
	~InsertEventBase();
	InsertEventBase(const InsertEventBase&);
	InsertEventBase& operator=(const InsertEventBase&);
};