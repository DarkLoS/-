#include <windows.h> 
#include <iostream> 
using namespace std;
struct myStruct{   //в общем,зачем нужна структура данных.Всё просто- в задании нельзя использовать глоюальные переменные,а в поток можно передать только одно значение. Поэтому будет передавать ссылку на структуру
	int* mas;//массив данных
	int n;//размерность
	int x;//число для индивидуального задания
};
DWORD WINAPI worker(void*m){ //в структуру можно передавать только void*
	Sleep(200);//остановили работу потока на 0.2 секунды - так нужно по заданию
	myStruct *my = (myStruct*)(m);  //таким образом преобразовали void* в структуру
	cout << "Значения больше чем x:" << endl;
	for (int i = 0; i<my->n; i++){//индивидуальное задание
		if (my->mas[i]>my->x) cout<<my->mas[i]<<endl;
	}
	cout << "Thread is finished." << endl;
	return 0;
}
DWORD WINAPI Count(){//без коментариев
	cout << "Начали выводить фибоначчи:"<<endl;
	long long f = 1;
	long long f2 = 1;
	cout << "1-е число - 1 " << endl;
	cout << "2-е число - 1 " << endl;
	for (int i = 0;i<45; i++){
		f2 = f2 + f; cout <<2+i*2<< "-е число - " <<f2<< endl;
		f = f + f2; cout << 3 + i * 2 << "-е число - " << f << endl;
	}
	cout << "Поток закончил работу. Большие числа Фибоначчи не влезут в long long." << endl;
	return 0;
}
int main(){
	setlocale(LC_ALL, "rus");
	myStruct my;
	int t1, t2;
	cout<<"Введи размер массива"<<endl;
	cin>>my.n;
	my.mas = new int[my.n];
	for (int i = 0; i<my.n; i++){
		cout<<"Вводи элемент "<<(i+1)<<endl;
		cin>>my.mas[i];
	}
	cout<<"Введи время,через которое приостановить поток"<<endl;
	cin>>t1;
	cout << "Введи время,через которое возобновить поток" << endl;
	cin >> t2;
	cout << "Введи x" << endl;
	cin >> my.x;


	HANDLE hThread, countThread;
	DWORD IDThread, IDThread1;
	hThread = CreateThread(NULL, 0, worker, (void*)&my, 0, &IDThread);  //тут передали ссылку на структуру
	countThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Count, NULL, CREATE_SUSPENDED, &IDThread1);  // параметр CREATE_SUSPENDED означает,что мы создали поток в подвешенном состоянии - он не будет запущен как только компилятор дойдёт до него.А прошлый будет,например
	Sleep(t1);//приостановили работу главного потока(как и нужно по заданию) .То есть,в потоке worker мы ждём 200млс, и если t1 равно, например, 100млс, то этот поток так и начнёт работу- до окончания времени t2. Делать t1 больше 200млс нет смысла- не будет никакого эффекта, т.к поток очень быстро работает
	SuspendThread(hThread);//приостанавливаем поток worker
	Sleep(t2);//ждём сколько нужно
	ResumeThread(hThread);//опять запускаем
	if (hThread == NULL)
		return GetLastError();
	WaitForSingleObject(hThread, INFINITE);//ждём пока worker завершит работу
	CloseHandle(hThread);//закрываем кго
	ResumeThread(countThread); //теперь запускаем поток count
	WaitForSingleObject(countThread, INFINITE);//ждём его конца
	CloseHandle(countThread);//закрываем его
	system("pause");
	return 0;
}