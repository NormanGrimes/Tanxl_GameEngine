//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-05-15 22:43
// »ù´¡°æ±¾

class LocationBase
{
public:
	void Set_LocationBase(float LocX, float LocY);
private:
	float Location_x;
	float Location_y;
};

void LocationBase::Set_LocationBase(float LocX, float LocY)
{
	Location_x = LocX;
	Location_y = LocY;
}