#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <stdlib.h> 
using namespace std;
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[]){
	int i;
	string s;
	_cputs("I am created.");
	cout << endl;
	double*mas = new double[argc];
	for (i = 0; i < argc; i++){
		mas[i] = (float)atof(argv[i]);
	}
	double temp;
	for (int i = 0; i < argc - 1; i++) {
		for (int j = 0; j < argc - i - 1; j++) {
			if (mas[j] > mas[j + 1]) {
				temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
	cout << "Sorted:" << endl;
	for (i = 0; i < argc; i++){
		cout<<mas[i]<<" ";
	}
	_cputs("\nPress any key to finish.\n");
	_getch();

	return 0;
}