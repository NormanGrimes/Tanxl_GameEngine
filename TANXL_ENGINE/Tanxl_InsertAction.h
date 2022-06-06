//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-02 22:34
// 所有内容重写 在早期版本中测试可用

#include <vector>
#include <iostream>

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
	int GLFW_KEY{ NULL };
	bool MoveToX{ false };
	bool MoveToY{ false };
	float MoveLen{ 0.0f };
};

class InsertEventBase
{
public:
	static InsertEventBase& GetInsertBase()
	{
		InsertEventBase* IEB = new InsertEventBase;
		return *IEB;
	}

	void RegistEvent(Key_Unit KU)
	{
		KeyEventS.push_back(KU);
	}

	void GetInsert(GLFWwindow* window, float* MoveX, float* MoveY)
	{
		for (int i = 0; i < KeyEventS.size(); i++)
		{
			if (glfwGetKey(window, KeyEventS.at(i).GLFW_KEY) == GLFW_PRESS)
			{
				if (KeyEventS.at(i).MoveToX)
					*MoveX += KeyEventS.at(i).MoveLen;
				if (KeyEventS.at(i).MoveToY)
					*MoveY += KeyEventS.at(i).MoveLen;
			}
		}
	}

private:
	std::vector<Key_Unit> KeyEventS;
	InsertEventBase() {};
	~InsertEventBase() {};
	InsertEventBase(const InsertEventBase&) {};
	InsertEventBase& operator=(const InsertEventBase&) { return *this; };
};