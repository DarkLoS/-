#include <iostream>
#include <windows.h>
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char* mas[2][5] = { { "Информатика", "Культурология" ,"Математика" ,"Иностранный язык" ,"Экономика" }, { "экзамен,зачет","зачет","экзамен,зачет","экзамен,зачет","экзамен" } };
	char str[20]="";
	cout << "Введите предмет" << endl;
	cin >> str;
	int check = 0;
	for (int i = 0; i < 5; i++){
		if (strcmp(mas[0][i], str) == 0){
			cout << mas[1][i] << endl;
			check = 1;
		}
	}
	if (check == 0) cout <<"Нет такого предмета!!!"<< endl;
	system("pause");
	return 0;
}