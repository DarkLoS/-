#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string> 
#include <string>
#include <sstream>
#include <stdlib.h> 
#include <ctime>
using namespace std;

int isPrime(unsigned long a){
	unsigned long i;
	if (a == 2)return 1;
	if (a == 0 || a == 1 || a % 2 == 0)return 0;
	for (i = 3; i*i <= a && a % i; i += 2);
	return i*i > a;
}


int main(int argc, char *argv[])
{
	srand(time(0));
	setlocale(LC_ALL, "rus");

	HANDLE hWritePipe, hReadPipe;
	HANDLE hEnableRead;    // для синхронизации обмена данными 
	char lpszEnableRead[] = "EnableRead";

	// открываем событие, разрешающее чтение 
	hEnableRead = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszEnableRead);

	// преобразуем символьное представление дескрипторов в число 
	hWritePipe = (HANDLE)atoi(argv[1]);
	hReadPipe = (HANDLE)atoi(argv[2]);
	// ждем команды о начале записи в анонимный канал 
	_cputs("Press any key to start communication.\n");
	_getch();

	int nData;
	DWORD dwBytesRead;
	if (!ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL)){		_cputs("Read from the pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	_cprintf("The number %d is read from the pipe.\n", nData);

	SetEvent(hEnableRead);

	int * A = new int[nData];
	for (int i = 0; i < nData; i++){
		A[i] = rand() % 10000;
		cout << i + 1 << " Элемент: " << A[i] << endl;
	}





	// пишем в анонимный канал 
	for (int i = 0; i < nData; i++){
		if (isPrime(A[i])){
			DWORD dwBytesWritten;
			if (!WriteFile(hWritePipe, &A[i], sizeof(A[i]), &dwBytesWritten, NULL)){
				_cputs("Write to file failed.\n");
				_cputs("Press any key to finish.\n");
				_getch();
				return GetLastError();
			}
			_cprintf("The number %d is written to the pipe.\n", A[i]);
		}
	}
	_cputs("The process finished writing to the pipe.\n");
	int x = INT_MAX;
	DWORD dwBytesWritten;
	WriteFile(hWritePipe, &x, sizeof(x), &dwBytesWritten, NULL);


	// закрываем дескрипторы канала 
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEnableRead);
	_cputs("Press any key to exit.\n");
	_getch();

	return 0;
}