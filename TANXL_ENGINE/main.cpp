#include "Tanxl_OpenGL_Draw.h"
#include "Tanxl_UniqueID.h"
//#include "Tanxl_DataBase.h"
int main()
{
	GameStateBase* GSB = &GameStateBase::GetStateBase(10, 10);
	mainLoop(GSB);
}