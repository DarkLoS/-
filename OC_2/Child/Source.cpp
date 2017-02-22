#include <windows.h> 
#include <conio.h> 
#include <iostream> 
#include <string>
#include <sstream>
#include <stdlib.h> 
using namespace std;
int isPrime(unsigned long a)
{
	unsigned long i;
	if (a == 2)return 1;
	if (a == 0 || a == 1 || a % 2 == 0)return 0;
	for (i = 3; i*i <= a && a % i; i += 2);
	return i*i > a;
}
int main(int argc, char *argv[]){
	setlocale(LC_ALL, "rus");
	int i;
	string s;
	_cputs("I am created.");
	cout << endl;
	cout << "Все простые:" << endl;
	for (i = 0; i < argc; i++){		if (isPrime(atoi(argv[i])))			cout << argv[i] << " ";		else		{			s += argv[i];			s += " ";		}	}	cout << "Теперь составные:" << endl;	cout << s;
	_cputs("\nPress any key to finish.\n");
	_getch();

	return 0;
}