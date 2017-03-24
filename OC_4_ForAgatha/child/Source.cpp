#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <stdlib.h> 
using namespace std;
HANDLE hSemaphore;
HANDLE Events;
int main(int argc, char *argv[]){
	setlocale(LC_ALL, "rus");
	string s;
	_cputs("Child created.");
	cout << endl;
	hSemaphore = OpenSemaphore(SYNCHRONIZE, FALSE, "DemoSemaphore");
	Events = OpenEvent(EVENT_ALL_ACCESS, TRUE, "EventB");
	WaitForSingleObject(hSemaphore, INFINITE);

	while (true){
		cout << "Type something (like B)" << endl;
		cin >> s;
		if (s == "B")SetEvent(Events);
	}
	return 0;
}