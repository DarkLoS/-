#include <windows.h> 
#include <iostream> 
using namespace std;
int k;
int*mas = new int[10000];
int n;
int sum = 0;
CRITICAL_SECTION cs,cs2;HANDLE hAddEvent;
int isPrime(unsigned long a){
	unsigned long i;
	if (a == 2)return 1;
	if (a == 0 || a == 1 || a % 2 == 0)return 0;
	for (i = 3; i*i <= a && a % i; i += 2);
	return i*i > a;
}
DWORD WINAPI worker(){
	EnterCriticalSection(&cs);
	cout << "¬веди врем€,которое мы будем спать после каждого прохода" << endl;
	int t;
	cin >> t;
	int *right = new int[10000];
	int lengthRight=0;
	int *left = new int[10000];
	int lengthLeft=0;
	int count = 0;
	for (int i = 0; i < n; i++){
		if (isPrime(mas[i])){
			right[lengthRight] = mas[i];
			lengthRight++;
		}
		else{
			left[lengthLeft] = mas[i];
			lengthLeft++;
		}
		Sleep(t);
		count++;
		if (k==count)
			LeaveCriticalSection(&cs);
	}
	for (int i = 0; i < lengthRight; i++){
		cout << right[i] << " ";
	}
	for (int i = 0; i < lengthLeft; i++){
		cout << left[i] << " ";
	}
	return 0;
}
DWORD WINAPI SumElement(){
	WaitForSingleObject(hAddEvent, INFINITE);
	EnterCriticalSection(&cs2);
	for (int i = 0; i < k; i++){
		sum += mas[i];
	}
	LeaveCriticalSection(&cs2);
	return 0;
}
int main(){
	InitializeCriticalSection(&cs);	InitializeCriticalSection(&cs2);	hAddEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	setlocale(LC_ALL, "rus");
	int t1, t2;
	cout << "¬веди размер массива" << endl;
	cin >> n;
	for (int i = 0; i<n; i++){
		cout << "¬води элемент " << (i + 1) << endl;
		cin >> mas[i];
	}
	cout << "¬веди k" << endl;
	cin >> k;
	HANDLE hThread, countThread;
	DWORD IDThread, IDThread1;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, NULL, 0, &IDThread);
	countThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SumElement, NULL, 0, &IDThread1);
	if (hThread == NULL)
		return GetLastError();
	if (countThread == NULL)
		return GetLastError();
	Sleep(100);//это не просто так


	EnterCriticalSection(&cs);
		SetEvent(hAddEvent);
		Sleep(100);//это не просто так
		EnterCriticalSection(&cs2);
			cout << "sum=" << sum << endl;;
		LeaveCriticalSection(&cs2);
	LeaveCriticalSection(&cs);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	WaitForSingleObject(countThread, INFINITE);
	CloseHandle(countThread);

	system("pause");
	return 0;
}