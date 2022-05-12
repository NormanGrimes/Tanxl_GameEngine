#include "Tanxl_InsertAction.h"

Key_Unit::Key_Unit() :GLFW_KEY(NULL), MoveToX(false), MoveToY(false), MoveLen(0.0f) {}

Key_Unit::Key_Unit(int GLKEY, bool MOVX, bool MOVY, float MOVL)
	: GLFW_KEY(GLKEY), MoveToX(MOVX), MoveToY(MOVY), MoveLen(MOVL) {}

InsertEventBase& InsertEventBase::GetInsertBase()
{
	InsertEventBase* IEB = new InsertEventBase;
	return *IEB;
}

void InsertEventBase::RegistEvent(Key_Unit KU)
{
	KeyEventS.push_back(KU);
}

void InsertEventBase::GetInsert(GLFWwindow* window, float* MoveX, float* MoveY)
{
	for (int i = 0; i < KeyEventS.size(); i++)
	{
		if (glfwGetKey(window, KeyEventS.at(i).GLFW_KEY) == GLFW_PRESS)
		{
			if (KeyEventS.at(i).MoveToX)
				*MoveX += KeyEventS.at(i).MoveLen;
			if (KeyEventS.at(i).MoveToY)
				*MoveY += KeyEventS.at(i).MoveLen;
			std::cout << "BUTTON PUSHED x_" << *MoveX << "y_" << *MoveY << std::endl;
		}
	}
}

//UnImportant µ¥ÀýÊµÏÖ

InsertEventBase::InsertEventBase() :KeyEventS(NULL) {}

InsertEventBase::~InsertEventBase()
{
	for (int i = 0; i < KeyEventS.size(); i++)
		delete &KeyEventS.at(i);
	KeyEventS.clear();
}

InsertEventBase::InsertEventBase(const InsertEventBase&) {}

InsertEventBase& InsertEventBase::operator=(const InsertEventBase&)
{
	return *this;
}