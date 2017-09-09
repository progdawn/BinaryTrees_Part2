//Programmer:  Dawn Myers
#include "myInfo.h"
#include <iostream> 
#include <iomanip> 
using namespace std;

myInfo::myInfo()
{
	programmer = "Dawn Myers";
	instructor = "Ligocki";
}

myInfo::~myInfo()
{

}

void myInfo::identity(string assignment, string currentDate)
{
	cout << setw(66) << setfill('*');
	cout << "\n";
	cout << "Programmer   : " << programmer << endl;
	cout << "Assignment   : " << assignment << endl;
	cout << "Instructor   : " << instructor << endl;
	cout << "Current Date : " << currentDate << endl;
	cout << "CompileDate  : " << __DATE__ << endl;
	cout << setw(66) << setfill('*');
	cout << "\n";
	system("pause");
	system("cls");
}
