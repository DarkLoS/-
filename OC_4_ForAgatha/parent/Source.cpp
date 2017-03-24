#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <stdlib.h> 
using namespace std;
HANDLE hMutex;
HANDLE Events;
int main(int argc, char *argv[]){
	setlocale(LC_ALL, "rus");
	string s;
	_cputs("Parent created.");
	cout << endl;
	hMutex = OpenMutex(SYNCHRONIZE, FALSE, "DemoMutex");
	Events = OpenEvent(EVENT_ALL_ACCESS, TRUE, "EventA");
	WaitForSingleObject(hMutex, INFINITE);
	while (true){
		cout << "Type something (like A)" << endl;
		cin >> s;
		if (s == "A")SetEvent(Events);
	}
	return 0;
}
