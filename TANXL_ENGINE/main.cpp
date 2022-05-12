//2022-05-08 14:01 CSDN WiChP
//-------------无关内容已删减
//---------OpenGL环境配置完毕
//需要使用VS2022的生成工具编译！
//如果没有VS2022可以在文件夹找到对应EXE执行查看效果

#include "Tanxl_OpenGL_Draw.h"
//#include "Tanxl_UniqueID.h"
//#include "Tanxl_DataBase.h"
int main()
{
	GameStateBase* GSB = &GameStateBase::GetStateBase();
	GSB->SetState(1, 1);
	mainLoop(GSB);
}