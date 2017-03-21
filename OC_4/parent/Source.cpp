#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <stdlib.h> 
using namespace std;
HANDLE hMutex;
HANDLE Events[6];
int main(int argc, char *argv[]){
	setlocale(LC_ALL, "rus");
	int i;
	string s;
	_cputs("Parent created.");
	cout << endl;
	hMutex = OpenMutex(SYNCHRONIZE, FALSE, "DemoMutex");
	Events[0] = OpenEvent(EVENT_ALL_ACCESS, TRUE, "EventA");
	Events[1] = OpenEvent(EVENT_ALL_ACCESS, TRUE, "EventB");
	Events[4] = OpenEvent(EVENT_ALL_ACCESS, TRUE, "closeParent");
	WaitForSingleObject(hMutex, INFINITE);

	while (s != "close"){
		cout << "Type something, type \"close\" to exit" << endl;
		cin >> s;
		if (s == "A")SetEvent(Events[0]);
		if (s == "B")SetEvent(Events[1]);
	}
	SetEvent(Events[4]);



	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return 0;
}
