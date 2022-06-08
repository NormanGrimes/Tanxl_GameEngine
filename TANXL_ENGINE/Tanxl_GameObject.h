//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-05-02 22:34
// 初始版本

#ifndef VECTOR//检查是否已经包含VECTOR
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
