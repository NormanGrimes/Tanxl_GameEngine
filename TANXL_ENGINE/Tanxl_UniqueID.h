//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-04-28 22:11
// Uniqt移动至类的私有成员

#include <string>
#include <iostream>
using namespace std;

class UniqueIdBase
{
public:
    static UniqueIdBase& GetIdGenerator()
    {
        static UniqueIdBase UNIBase;
        return UNIBase;
    }
    std::string Generate()
    {
        std::string Data{};
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < 15; i++)
        {
            if (i % 5 == 0 && i != 0)
                Data += "-";
            Data += Uniqt[rand() % 62];
        }
        return Data;
    }
private:
    std::string Uniqt[62] = {
    {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"0"},
    {"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}, {"h"}, {"i"}, {"j"},
    {"k"}, {"l"}, {"m"}, {"n"}, {"o"}, {"p"}, {"q"}, {"r"}, {"s"}, {"t"},
    {"u"}, {"v"}, {"w"}, {"x"}, {"y"}, {"z"}, {"A"}, {"B"}, {"C"}, {"D"},
    {"E"}, {"F"}, {"G"}, {"H"}, {"I"}, {"J"}, {"K"}, {"L"}, {"M"}, {"N"},
    {"O"}, {"P"}, {"Q"}, {"R"}, {"S"}, {"T"}, {"U"}, {"V"}, {"W"}, {"X"},
    {"Y"}, {"Z"} };

    UniqueIdBase(){}
    ~UniqueIdBase(){}
    UniqueIdBase(const UniqueIdBase&){}
    UniqueIdBase& operator=(const UniqueIdBase&) { return *this; }
};