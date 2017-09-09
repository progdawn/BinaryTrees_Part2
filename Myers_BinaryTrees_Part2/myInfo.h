//Programmer: Dawn Myers
#ifndef myInfo_H
#define myInfo_H
#include <string>
using namespace std;

class myInfo
{
private:
	string programmer;
	string instructor;
public:
	myInfo();
	void identity(string assignment, string compileDate);
	~myInfo();
};
#endif

