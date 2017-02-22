#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <ctime>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int main(){
	srand(time(0));
	setlocale(LC_ALL, "rus");
	int n;
	string s = "";
	string str;
	char mas[] = "";
	cout << "¬веди размер массива" << endl;
	cin >> n;
	getline(cin, str);
	cout << "¬веди 0,если хочешь чтобы числа были рандомными,и всЄ что угодно в противном случае" << endl;
	getline(cin, str);
	if (str == "0"){
		for (int i = 0; i < n; i++){
			char *q = new char[10];
			itoa(rand() % 1000, q,10);
			s += string(q)+ " ";
			cout <<i+1<<" Ёлемент: "<<q << endl;
		}
	}
	else{
		for (int i = 0; i < n; i++){
			cout << "¬води элемент " << (i + 1) << endl;
			getline(cin, str);
			s += str + " ";
		}
	}
	char lpszAppName[] = "\\Child.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	if (!CreateProcess(lpszAppName, (LPSTR)(s.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)){
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	_cputs("The new process is created.\n");
	_cputs("Press 0 to terminate child ot 1 to exit parent\n");
	getline(cin, str);
	if (str == "0"){
		TerminateProcess(piApp.hProcess, 1);
	}
	if (str == "1"){
		ExitProcess(1);	}
	WaitForSingleObject(piApp.hProcess, INFINITE);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	system("pause");
	return 0;
}