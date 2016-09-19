#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <time.h>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int main()
{
	srand(time(0));
	unsigned int  k, n, j;
	string st, g(" "), x;
	char r=',';
	setlocale(LC_ALL, "Russian");
	cout << "введите строку текста - St" << endl;
	getline(cin, st); k = 0;
	cout << "введите позицию слова для удаления" << endl;
	int COUNT;
	cin >> COUNT;
	int p = 0;
	string s1 = st;
	int pos1 = 0;
	int pos2 = 0;
	
	int proof = 0;
	int in = 0;
	while (s1.length() != 0)
	{
		while ((s1[0] == r) && (s1.length() != 0))
			s1.erase(0, 1);
		x = s1.substr(0, s1.find(r));
		int l = x.length();

		if (s1[0] == '0')
			p++;
		s1.erase(0, 1);
		if (s1[0] == 'b')
			p++;
		s1.erase(0, 1);

		for (int i = 2; i < l; i++)
		{
			if (s1[0] == '0' || s1[0] == '1')
				p++;
			s1.erase(0, 1);
		}
		if (p == l)
		{
			cout << x << " ";
			proof++;
		}
		
		if (proof < COUNT)
		{
			pos1 += l;
			pos2 += l;
		}
		if (proof == COUNT && in==0)
		{
			pos2 += l;
			in = 1;
		}
		p = 0;
	}
	st.erase(pos1, pos2-pos1+1);
	cout <<st<< endl;
	cout << endl;
	cout << "Поиск подстроки в строке" << endl;
	string str2;
	getline(cin, str2);
	getline(cin, str2);
	int index = st.find(str2);
	cout << "index of begin: " << index << endl;
	index = st.rfind(str2);
	cout << "index of end: " << index << endl;
	string s="45645";

	cout << "Переворот строки" << endl;
	reverse(st.begin(), st.end());
	cout << "Result: " << st << std::endl;
	cout << "Объединение" << endl;
	st = st + s + s + s;
	cout << "Result: " << st << std::endl;
	if (st.compare(s) == 0)
		cout << "st==s" << endl;
	if (st.compare(s) > 0)
		cout << "st>s" << endl;
	if (st.compare(s) < 0)
		cout << "st<s" << endl;

	char * lstr=new char[st.length()+1];
	strcpy(lstr, st.c_str());
	cout << lstr<<endl;
	system("pause");
	return 0;
}
