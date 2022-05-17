#include "Tanxl_OpenGL_Draw.h"
//#include "Tanxl_DataBase.h"
int main()
{
	GameStateBase* GSB = &GameStateBase::GetStateBase();
	GSB->SetState(5, 5);
	cout << GSB->GetStateHeight();
	mainLoop(GSB);
}