//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-08 22:51
// �����ܹ�����ȷ��
// ��Ʒ�����ṩ����������
// ��Ʒ�����ṩɾ���������
// ��Ϸ��Ʒ������һ��ִ������������ܵĺ���

#ifndef VECTOR//����Ƿ��Ѿ�����VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STRING//����Ƿ��Ѿ�����STRING
#define STRING
#include <string>
#endif

//�����

class ComponmentBase
{
public:
	ComponmentBase(std::string Name) :ComponmentName(Name) {}
	std::string GetName()
	{
		return this->ComponmentName;
	}
	virtual void Special() = 0;
private:
	std::string ComponmentName;
};

//��Ϸ��Ʒ��

class GameObjectBase
{
	bool AppendComponment(ComponmentBase* CM);
	bool RemoveComponment(std::string Name);
	void FinishComponment();
private:
	std::vector<ComponmentBase*> CMB;
};

bool GameObjectBase::AppendComponment(ComponmentBase* CM)
{
	for (int i = 0; i < CMB.size(); i++)//�����������
	{
		if (CMB.at(i)->GetName() == CM->GetName())
			return false;//����ͬ������������ʧ��
	}
	CMB.push_back(CM);
	return true;
}

bool GameObjectBase::RemoveComponment(std::string Name)
{
	for (std::vector<ComponmentBase*>::iterator IOCB; IOCB!= CMB.end(); IOCB++)//��������ɾ��
	{
		if (( * IOCB)->GetName() == Name)
		{
			CMB.erase(IOCB);
			return true;
		}
	}
	return false;
}

void GameObjectBase::FinishComponment()
{
	for (int i = 0; i < CMB.size(); i++)
		CMB.at(i)->Special();
}