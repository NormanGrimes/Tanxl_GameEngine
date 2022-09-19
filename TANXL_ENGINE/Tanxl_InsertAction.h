//_VERSION_0_4_ UPDATE LOG
// LAST_UPDATE 2022-05-30 01:18
// ����ԭLocationBaseģ��Ļ�������
// �ṩ�����ͼ�����Ĺ���
// �ṩ��ȡÿ�θ��ĵĹ���
// ���빦���ṩ�Ե�ͼ����Ŀ���

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
	//���ڱ�Ǵ˰����Ƿ�ᵼ����X�᷽���ƶ�
	bool  MoveToX;
	//���ڱ�Ǵ˰����Ƿ�ᵼ����Y�᷽���ƶ�
	bool  MoveToY;
	float MoveLen;
};

class InsertEventBase
{
public:
	static InsertEventBase& GetInsertBase();
	//�Զ�������֪��Ϣ���ط������ƶ������Χ ��ʽ 1 - ( 1 / ��Ϸ��ͼ�߳�����������)
	float Get_AutoFloat(int Blocks);
	//ע��һ���������ܣ�ʹ֮�ܹ��ڴ����з�Ӧ����������尴������ע���򲻻�����κ�Ч��
	void RegistEvent(Key_Unit KU);
	void GetInsert(GLFWwindow* window, float* MoveX, float* MoveY, float* StateX = NULL, float* StateY = NULL);
	//��ͼ�߳���ͬʱ ���������һ�������������ƶ�ʱʹ�� Max_float����ָ������ƶ����루��Ե�ͼ������
	void Set_MaxFloat(float Max_float);
	void Set_MaxLine(int Max_Line);
	void Get_MoveData(std::vector<bool>* PVB);
	float Get_Margin_X();
	float Get_Margin_Y();
private:
	void AutoCheck(float* MoveX, float* MoveY);
	std::vector<Key_Unit> _KeyEventS;
	std::vector<bool>* _PTB;
	float _Max_float;
	int _Max_Line;

	//_Margin_X ����ǰ��������Ʒ��X����
	float _Margin_X;
	//_Margin_Y ����ǰ��������Ʒ��Y����
	float _Margin_Y;

	InsertEventBase();
	~InsertEventBase();
	InsertEventBase(const InsertEventBase&);
	InsertEventBase& operator=(const InsertEventBase&);
};