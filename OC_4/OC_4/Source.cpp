#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <ctime>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
HANDLE hMutex, hSemaphore;
HANDLE Events[6];

int main(){
	hMutex = CreateMutex(NULL, FALSE, "DemoMutex");
	hSemaphore = CreateSemaphore(NULL, 0, 1, "DemoSemaphore");
	Events[0] = CreateEvent(NULL, FALSE, FALSE, "EventA");
	Events[1] = CreateEvent(NULL, FALSE, FALSE, "EventB");
	Events[2] = CreateEvent(NULL, FALSE, FALSE, "EventC");
	Events[3] = CreateEvent(NULL, FALSE, FALSE, "EventD");
	Events[4] = CreateEvent(NULL, FALSE, FALSE, "closeParent");
	Events[5] = CreateEvent(NULL, FALSE, FALSE, "closeChild");
	setlocale(LC_ALL, "rus");
	string str;
	int size1, size2,count=0;
	cout << "Пожалуйста введите вначале количество процессов Child, а потом количество процессов Parent" << endl;
	cin >> size1 >> size2;
	char lpszAppName[] = "c:\\Users\\User\\Documents\\Visual Studio 2013\\Projects\\OC_4\\Debug\\parent.exe";
	char lpszAppName2[] = "c:\\Users\\User\\Documents\\Visual Studio 2013\\Projects\\OC_4\\Debug\\child.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	for (int i = 0; i < size2;i++)
	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)){
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	else{
		_cputs("The Parent process is created.\n");
	}
	for (int i = 0; i < size1; i++)
	if (!CreateProcess(lpszAppName2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)){
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	else{
		_cputs("The Child process is created.\n");
	}


	ReleaseSemaphore(hSemaphore, 1, NULL);
	Sleep(50);
	ReleaseSemaphore(hSemaphore, 1, NULL);
	while (true){		DWORD dwRet = WaitForMultipleObjects(6, Events, FALSE, INFINITE);
		if (dwRet == 0) cout << "Event A in parent" << endl;		if (dwRet == 1) cout << "Event B in parent" << endl;		if (dwRet == 2) cout << "Event C in child" << endl;		if (dwRet == 3) cout << "Event D in child" << endl;		if (dwRet == 4) {			cout << "Parent close" << endl;			count++;		}		if (dwRet == 5) {			cout << "Child close" << endl;			ReleaseSemaphore(hSemaphore, 1, NULL);			count++;		}		if (count == size1 + size2) break;	}

	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	system("pause");
	return 0;

}