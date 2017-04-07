#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string> 
using namespace std;
int main()
{
	char lpszComLine[80];

	HANDLE hEnableRead;
	char lpszEnableRead[] = "EnableRead";

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES sa;

	hEnableRead = CreateEvent(NULL, FALSE, FALSE, lpszEnableRead);

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;  
	sa.bInheritHandle = TRUE; 

	if (!CreatePipe(&hReadPipe,  &hWritePipe, &sa,0))  {
		_cputs("Create pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	wsprintf(lpszComLine, "C:\\Client.exe %d %d",
		(int)hWritePipe, (int)hReadPipe);

	int arraySize;
	cout << "Type array size" << endl;
	cin >> arraySize;


	if (!CreateProcess(NULL,lpszComLine,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,  NULL,NULL,&si,&pi)){
		_cputs("Create process failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);






	DWORD dwBytesWritten;
	if (!WriteFile(hWritePipe, &arraySize, sizeof(arraySize), &dwBytesWritten, NULL)){
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	_cprintf("The number %d is written to the pipe.\n", arraySize);
	WaitForSingleObject(hEnableRead, INFINITE);
	int *numbers = new int[arraySize];
	int count = 0;

	while (true){
		int nData;
		DWORD dwBytesRead;
		if (!ReadFile(hReadPipe,&nData,sizeof(nData),&dwBytesRead,NULL)){
			_cputs("Read from the pipe failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		if (nData == INT_MAX) break;
		numbers[count] = nData;
		count++;
	}
	_cputs("The process finished reading from the pipe.\n");

	cout << "My prime numbers:" << endl;
	for (int i = 0; i < count; i++){
		cout <<numbers[i]<<" ";
	}

	string s;

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(hEnableRead);
	while (s != "E"){
		cout << "Type something, type \"E\" to exit" << endl;
		cin >> s;
	}

	return 0;
}