//2022-05-08 14:01 CSDN WiChP
//-------------�޹�������ɾ��
//---------OpenGL�����������
//��Ҫʹ��VS2022�����ɹ��߱��룡
//���û��VS2022�������ļ����ҵ���ӦEXEִ�в鿴Ч��

#include "Tanxl_OpenGL_Draw.h"
//#include "Tanxl_UniqueID.h"
//#include "Tanxl_DataBase.h"
int main()
{
	GameStateBase* GSB = &GameStateBase::GetStateBase();
	GSB->SetState(1, 1);
	mainLoop(GSB);
}