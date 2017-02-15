#include <windows.h> 
#include <iostream> 
using namespace std;
struct myStruct{   //� �����,����� ����� ��������� ������.�� ������- � ������� ������ ������������ ���������� ����������,� � ����� ����� �������� ������ ���� ��������. ������� ����� ���������� ������ �� ���������
	int* mas;//������ ������
	int n;//�����������
	int x;//����� ��� ��������������� �������
};
DWORD WINAPI worker(void*m){ //� ��������� ����� ���������� ������ void*
	Sleep(200);//���������� ������ ������ �� 0.2 ������� - ��� ����� �� �������
	myStruct *my = (myStruct*)(m);  //����� ������� ������������� void* � ���������
	cout << "�������� ������ ��� x:" << endl;
	for (int i = 0; i<my->n; i++){//�������������� �������
		if (my->mas[i]>my->x) cout<<my->mas[i]<<endl;
	}
	cout << "Thread is finished." << endl;
	return 0;
}
DWORD WINAPI Count(){//��� �����������
	cout << "������ �������� ���������:"<<endl;
	long long f = 1;
	long long f2 = 1;
	cout << "1-� ����� - 1 " << endl;
	cout << "2-� ����� - 1 " << endl;
	for (int i = 0;i<45; i++){
		f2 = f2 + f; cout <<2+i*2<< "-� ����� - " <<f2<< endl;
		f = f + f2; cout << 3 + i * 2 << "-� ����� - " << f << endl;
	}
	cout << "����� �������� ������. ������� ����� ��������� �� ������ � long long." << endl;
	return 0;
}
int main(){
	setlocale(LC_ALL, "rus");
	myStruct my;
	int t1, t2;
	cout<<"����� ������ �������"<<endl;
	cin>>my.n;
	my.mas = new int[my.n];
	for (int i = 0; i<my.n; i++){
		cout<<"����� ������� "<<(i+1)<<endl;
		cin>>my.mas[i];
	}
	cout<<"����� �����,����� ������� ������������� �����"<<endl;
	cin>>t1;
	cout << "����� �����,����� ������� ����������� �����" << endl;
	cin >> t2;
	cout << "����� x" << endl;
	cin >> my.x;


	HANDLE hThread, countThread;
	DWORD IDThread, IDThread1;
	hThread = CreateThread(NULL, 0, worker, (void*)&my, 0, &IDThread);  //��� �������� ������ �� ���������
	countThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Count, NULL, CREATE_SUSPENDED, &IDThread1);  // �������� CREATE_SUSPENDED ��������,��� �� ������� ����� � ����������� ��������� - �� �� ����� ������� ��� ������ ���������� ����� �� ����.� ������� �����,��������
	Sleep(t1);//������������� ������ �������� ������(��� � ����� �� �������) .�� ����,� ������ worker �� ��� 200���, � ���� t1 �����, ��������, 100���, �� ���� ����� ��� � ����� ������- �� ��������� ������� t2. ������ t1 ������ 200��� ��� ������- �� ����� �������� �������, �.� ����� ����� ������ ��������
	SuspendThread(hThread);//���������������� ����� worker
	Sleep(t2);//��� ������� �����
	ResumeThread(hThread);//����� ���������
	if (hThread == NULL)
		return GetLastError();
	WaitForSingleObject(hThread, INFINITE);//��� ���� worker �������� ������
	CloseHandle(hThread);//��������� ���
	ResumeThread(countThread); //������ ��������� ����� count
	WaitForSingleObject(countThread, INFINITE);//��� ��� �����
	CloseHandle(countThread);//��������� ���
	system("pause");
	return 0;
}