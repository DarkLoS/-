#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <stdlib.h> 
using namespace std;
HANDLE semaphoreConsume;
HANDLE Events[6];
int main(int argc, char *argv[]){
	setlocale(LC_ALL, "rus");
	HANDLE hWritePipe, hReadPipe;
	hWritePipe = (HANDLE)atoi(argv[1]);
	hReadPipe = (HANDLE)atoi(argv[2]);
	int i;
	string s;
	_cputs("consumer created.");
	cout << endl;
	semaphoreConsume = OpenSemaphore(SYNCHRONIZE, FALSE, "semaphoreConsume");
	Events[1] = OpenEvent(EVENT_ALL_ACCESS, TRUE, "qPop");
	while (s != "close"){
		cout << "Type read or readMany, type \"close\" to exit" << endl;
		cin >> s;
		if (s == "read"){
			WaitForSingleObject(semaphoreConsume, INFINITE);
			long nData;
			DWORD dwBytesRead;
			SetEvent(Events[1]);
			if (!ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL)){
				_cputs("Read from the pipe failed.\n");
				_cputs("Press any key to finish.\n");
				_getch();
				return GetLastError();
			}			cout << "Поток - Consumer" << argv[3]<<" ,потребил продукт "<< nData << endl;
		
		}
		if (s == "readMany"){
			int size;
			cout << "type size" << endl;
			cin >> size;
			for (int i = 0; i < size; i++){
				WaitForSingleObject(semaphoreConsume, INFINITE);
				long nData;
				DWORD dwBytesRead;
				SetEvent(Events[1]);
				if (!ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL)){
					_cputs("Read from the pipe failed.\n");
					_cputs("Press any key to finish.\n");
					_getch();
					return GetLastError();
				}				cout << "Поток - Consumer" << argv[3] << " ,потребил продукт " << nData << endl;

			}
		}
	}
	return 0;
}