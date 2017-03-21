#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <stdlib.h> 
using namespace std;
HANDLE hSemaphore;
HANDLE Events[6];
int main(int argc, char *argv[]){
	setlocale(LC_ALL, "rus");
	int i;
	string s;
	_cputs("Child created.");
	cout << endl;
	hSemaphore = OpenSemaphore(SYNCHRONIZE, FALSE, "DemoSemaphore");
	Events[2] = OpenEvent(EVENT_ALL_ACCESS, TRUE, "EventC");
	Events[3] = OpenEvent(EVENT_ALL_ACCESS, TRUE, "EventD");
	Events[6] = OpenEvent(EVENT_ALL_ACCESS, TRUE, "closeChild");
	WaitForSingleObject(hSemaphore, INFINITE);

	while (s != "close"){
		cout << "Type something, type \"close\" to exit" << endl;
		cin >> s;
		if (s == "C")SetEvent(Events[2]);
		if (s == "D")SetEvent(Events[3]);
	}
	SetEvent(Events[6]);
	CloseHandle(hSemaphore);
	return 0;
}