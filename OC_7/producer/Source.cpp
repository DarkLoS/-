#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <stdlib.h> 
#include <ctime>
using namespace std;
HANDLE semaphoreProduce;
HANDLE Events[6];
int main(int argc, char *argv[]){
	srand(time(0));
	setlocale(LC_ALL, "rus");
	HANDLE hWritePipe, hReadPipe;
	hWritePipe = (HANDLE)atoi(argv[1]);
	hReadPipe = (HANDLE)atoi(argv[2]);
	string s;
	_cputs("producer created.");
	cout << endl;
	semaphoreProduce = OpenSemaphore(SYNCHRONIZE, FALSE, "semaphoreProduce");
	Events[0] = OpenEvent(EVENT_ALL_ACCESS, TRUE, "qPush");
	while (s != "close"){
		cout << "Type one or many, type \"close\" to exit" << endl;
		cin >> s;
		if (s == "one"){
			int value;
			WaitForSingleObject(semaphoreProduce, INFINITE);
			cout << "type value to put in queue" << endl;
			cin >> value;
			
			DWORD dwBytesWritten;
			if (!WriteFile(hWritePipe, &value, sizeof(value), &dwBytesWritten, NULL)){
				_cputs("Write to file failed.\n");
				_cputs("Press any key to finish.\n");
				_getch();
				return GetLastError();
			}
			SetEvent(Events[0]);
			cout << "Поток - Produser" << argv[3] << " , произвёл продукт " << value << endl;
		}
		if (s == "many"){
			int size;
			cout << "type size" << endl;
			cin >> size;
			for (int i = 0; i < size; i++){
				WaitForSingleObject(semaphoreProduce, INFINITE);
				int value = rand() % 20000000000L;

				DWORD dwBytesWritten;
				if (!WriteFile(hWritePipe, &value, sizeof(value), &dwBytesWritten, NULL)){
					_cputs("Write to file failed.\n");
					_cputs("Press any key to finish.\n");
					_getch();
					return GetLastError();
				}
				SetEvent(Events[0]);
				cout << "Поток - Produser" << argv[3] << " , произвёл продукт " << value << endl;
			}
		}
		//if (s == "B")SetEvent(Events[1]);
	}



	//ReleaseMutex(mutexProduce);

	return 0;
}
