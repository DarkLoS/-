#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <ctime>
#include <queue>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
HANDLE semaphoreConsume, semaphoreProduce, hSemaphore;
HANDLE Events[2];
struct Node{
	long x;
	Node *Next;
}*Head,*Tail;
void push(long x){
	Node *temp = new Node; 
	temp->x = x; 
	temp->Next = NULL;
	if (Head != NULL) 
	{
		Tail->Next = temp; 
		Tail = temp;
	}
	else Head = Tail = temp; 
}
long pop(){
	long r;
	if (Head != NULL)  {
		Node *temp = Head; 
		r = Head->x;
		Head = Head->Next; 
		delete temp; 
	}
	return r;
}
bool isEmpty(){
	return Head == NULL;
}
bool isFull(int size){
	long s = 0;
	Node *temp = Head; 
	while (temp != NULL) 
	{
		s++;
		temp = temp->Next; 
	}
	return s>size;
}
int main(){
	setlocale(LC_ALL, "rus");
	int qSize;
	cout << " /$$$$$$$$                                            /$$                                                                            \n|__  $$__/                                           |__/                                                                            \n   | $$ /$$   /$$  /$$$$$$   /$$$$$$         /$$$$$$$ /$$ /$$$$$$$$  /$$$$$$         /$$$$$$  /$$   /$$  /$$$$$$  /$$   /$$  /$$$$$$ \n   | $$| $$  | $$ /$$__  $$ /$$__  $$       /$$_____/| $$|____ /$$/ /$$__  $$       /$$__  $$| $$  | $$ /$$__  $$| $$  | $$ /$$__  $$\n   | $$| $$  | $$| $$  \\ $$| $$$$$$$$      |  $$$$$$ | $$   /$$$$/ | $$$$$$$$      | $$  \\ $$| $$  | $$| $$$$$$$$| $$  | $$| $$$$$$$$\n   | $$| $$  | $$| $$  | $$| $$_____/       \\____  $$| $$  /$$__/  | $$_____/      | $$  | $$| $$  | $$| $$_____/| $$  | $$| $$_____/\n   | $$|  $$$$$$$| $$$$$$$/|  $$$$$$$       /$$$$$$$/| $$ /$$$$$$$$|  $$$$$$$      |  $$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$/|  $$$$$$$\n   |__/ \\____  $$| $$____/  \\_______/      |_______/ |__/|________/ \\_______/       \\____  $$ \\______/  \\_______/ \\______/  \\_______/\n        /$$  | $$| $$                                                                    | $$                                        \n       |  $$$$$$/| $$                                                                    | $$                                        \n        \\______/ |__/                                                                    |__/                                        " << endl;
	cin >> qSize;
	qSize--;
	HANDLE hWriteProduce, hReadProduce;
	HANDLE hWriteConsume, hReadConsume;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	SECURITY_ATTRIBUTES sa2;
	sa2.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa2.lpSecurityDescriptor = NULL;
	sa2.bInheritHandle = TRUE;

	if (!CreatePipe(&hReadProduce, &hWriteProduce, &sa, 0))  {
		_cputs("Create pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	if (!CreatePipe(&hReadConsume, &hWriteConsume, &sa2, 0))  {
		_cputs("Create pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}

	semaphoreProduce = CreateSemaphore(NULL, 0, 1, "semaphoreProduce");
	semaphoreConsume = CreateSemaphore(NULL, 0, 1, "semaphoreConsume");
	Events[0] = CreateEvent(NULL, FALSE, FALSE, "qPush");
	Events[1] = CreateEvent(NULL, FALSE, FALSE, "qPop");
	ReleaseSemaphore(semaphoreProduce, 1, NULL);

	string str;
	int size1, size2, count = 0;
	cout << "Пожалуйста введите вначале количество процессов consumer, а потом количество процессов producer" << endl;
	cin >> size1 >> size2;

	
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	for (int i = 0; i < size2; i++){
		char lpszComLine2[180];
		wsprintf(lpszComLine2, "c:\\Users\\User\\Documents\\Visual Studio 2013\\Projects\\OC_7\\Debug\\consumer.exe %d %d %d",
			(int)hWriteConsume, (int)hReadConsume, (int)(i+1));
		if (!CreateProcess(NULL, lpszComLine2, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)){
			_cputs("The new process is not created.\n");
			_cputs("Check a name of the process.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return 0;
		}
		else{
			_cputs("The Parent process is created.\n");
		}
	}
	for (int i = 0; i < size1; i++){
		char lpszComLine[180];
		wsprintf(lpszComLine, "c:\\Users\\User\\Documents\\Visual Studio 2013\\Projects\\OC_7\\Debug\\producer.exe %d %d %d",
			(int)hWriteProduce, (int)hReadProduce, (int)(i+1));
		if (!CreateProcess(NULL, lpszComLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)){
			_cputs("The new process is not created.\n");
			_cputs("Check a name of the process.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return 0;
		}
		else{
			_cputs("The Child process is created.\n");
		}
	}
	
	while (true){		DWORD dwRet = WaitForMultipleObjects(2, Events, FALSE, INFINITE);
		if (dwRet == 0){			int r = 0;			if (isEmpty()){				r = 1;			}			cout << "push" << endl;			long nData;
			DWORD dwBytesRead;
			if (!ReadFile(hReadProduce, &nData, sizeof(nData), &dwBytesRead, NULL)){
				_cputs("Read from the pipe failed.\n");
				_cputs("Press any key to finish.\n");
				_getch();
				return GetLastError();
			}			cout << nData << endl;			push(nData);			if (!isFull(qSize)){				ReleaseSemaphore(semaphoreProduce, 1, NULL);			}			if (r == 1){				ReleaseSemaphore(semaphoreConsume, 1, NULL);			}		}		if (dwRet == 1) {			int r = 0;			if (isFull(qSize)){				r = 1;			}			DWORD dwBytesWritten;			cout << "pop" << endl;			long x = pop();			if (!WriteFile(hWriteConsume, &x, sizeof(x), &dwBytesWritten, NULL)){
				_cputs("Write to file failed.\n");
				_cputs("Press any key to finish.\n");
				_getch();
				return GetLastError();
			}			if (!isEmpty()){				ReleaseSemaphore(semaphoreConsume, 1, NULL);			}			if (r == 1){				ReleaseSemaphore(semaphoreProduce, 1, NULL);			}		}	}
	
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	system("pause");
	return 0;

}