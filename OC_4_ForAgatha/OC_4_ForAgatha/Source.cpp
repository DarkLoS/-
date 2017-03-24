#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <ctime>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int size1, size2, countChild = 0, countParent = 0;
HANDLE hMutex, hSemaphore;
HANDLE Events[4];
void Count(){
	Events[3] = CreateEvent(NULL, FALSE, FALSE, "closeParent");
	Events[2] = CreateEvent(NULL, FALSE, FALSE, "closeChild");
	string s;
	while (true){
		cout << "Type \"closeChild\" or  \"closeParent\"" << endl;
		cout << endl;
		cin >> s;
		if (s == "closeChild"){
			if (size1!=countChild)SetEvent(Events[3]);
			else cout << "Nothing to close!" << endl;
		}
		if (s == "closeParent"){
			if (size2 != countParent)SetEvent(Events[2]);
			else cout << "Nothing to close!" << endl;
		}
		Sleep(50);
		if (countChild == size1 && countParent == size2) break;
	}
}
int main(){
	hMutex = CreateMutex(NULL, FALSE, "DemoMutex");
	hSemaphore = CreateSemaphore(NULL, 0, 1, "DemoSemaphore");
	Events[0] = CreateEvent(NULL, FALSE, FALSE, "EventA");
	Events[1] = CreateEvent(NULL, FALSE, FALSE, "EventB");
	setlocale(LC_ALL, "rus");
	string str;

	cout << "Пожалуйста введите вначале количество процессов Child, а потом количество процессов Parent" << endl;
	cin >> size1 >> size2;
	char lpszAppName[] = "c:\\Users\\User\\Documents\\Visual Studio 2013\\Projects\\OC_4_ForAgatha\\Debug\\parent.exe";
	char lpszAppName2[] = "c:\\Users\\User\\Documents\\Visual Studio 2013\\Projects\\OC_4_ForAgatha\\Debug\\child.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION *piApp = new PROCESS_INFORMATION[size1];
	PROCESS_INFORMATION *piApp2 = new PROCESS_INFORMATION[size2];
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	for (int i = 0; i < size2; i++)
	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp2[i])){
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
	if (!CreateProcess(lpszAppName2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp[i])){
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	else{
		_cputs("The Child process is created.\n");
	}
	HANDLE myThread;
	DWORD IDThread;
	myThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Count, NULL, NULL, &IDThread);
	ReleaseSemaphore(hSemaphore, 1, NULL);
	while (true){		DWORD dwRet = WaitForMultipleObjects(4, Events, FALSE, INFINITE);
		if (dwRet == 0) cout << "Event A in parent" << endl;		if (dwRet == 1) cout << "Event B in child" << endl;		if (dwRet == 2) {			TerminateProcess(piApp2[countParent].hProcess, 1);			cout << "Parent close" << endl;			countParent++;		}		if (dwRet == 3) {			TerminateProcess(piApp[countChild].hProcess, 1);			cout << "Child close" << endl;			ReleaseSemaphore(hSemaphore, 1, NULL);			countChild++;		}		if (countChild == size1 && countParent == size2) break;	}
	system("pause");
	return 0;
}