//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-05-02 22:34
// ��ʼ�汾

#ifndef VECTOR//����Ƿ��Ѿ�����VECTOR
#define VECTOR
#include <vector>
#endif

class ComponmentBase
{
	virtual void SpecialAbility() = 0;
};

class GameObjectBase
{

private:
	std::vector<ComponmentBase*> CMB;
};
