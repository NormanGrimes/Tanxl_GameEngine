//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-05-04 21:40
// �����������������
// �ṩ�Կɲ��ݷ��������ƶ�λ�����ƵĹ���
// �޸��������ܴ��������

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
	void RegistEvent(Key_Unit KU);
	void GetInsert(GLFWwindow* window, float* MoveX, float* MoveY);
	void Set_MaxFloat(float Max_float);
private:
	void AutoCheck(float* MoveX, float* MoveY);
	std::vector<Key_Unit> KeyEventS;
	float _Max_float;
	InsertEventBase();
	~InsertEventBase();
	InsertEventBase(const InsertEventBase&);
	InsertEventBase& operator=(const InsertEventBase&);
};