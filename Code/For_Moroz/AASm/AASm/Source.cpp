#include <iostream>
#include <cstdlib>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int CONST = 0;
int constant = 0;
char conststring[20];
extern "C" void _fastcall Bin(char*, int);
extern "C" void Print(char* s1, char *s2)
{
	constant += 1;
	for (int i = 0; i < s2 - s1-1; i++)
		cout << s1[i];
	cout << endl;
	if (constant == CONST)
	{
		for (int i = 0; i < s2 - s1 - 1; i++)
			conststring[i]= s1[i];
	}
}
int main()
{
	cout << "vvedi stroky,cherez zapyatye" << endl;
	char str[1000] = "";
	cin >> str;
	cout << "vvedi pos to delete" << endl;
	cin >> CONST;
	Bin(str, strlen(str));


	char s2[10] = "";
	cout << "vvedi stroky dlya poiska" << endl;
	cin>> s2;
	int len1 = strlen(str), len2 = strlen(s2);
	int result;
	int index = len1;
	_asm
	{
		cld
			mov ecx, len1
			mov al, s2
			lea edi, str
		m_beg :
		repne scasb
			sub index, ecx
			jecxz m_not
			push edi
			push ecx
			mov ecx, len2
			dec ecx
			lea esi, s2 + 1
			repe cmpsb
			jz m_found
		m_notfound :
		pop ecx
			add index,ecx
			pop edi
			jmp m_beg
		m_not :
		mov eax, 0
			jmp m_end
		m_found :
		pop ecx
			pop edi
			mov eax, 1
		m_end :
			  mov result, eax
			  cmp result,0
			  jne end_i
			  mov index,0
			  end_i:
	}
	if (result==0)
	cout <<"not found"<<endl;
	else
		cout << "found at position" << index << endl;


	char*p = strstr(str, conststring);
	char buf[] = "";
	int lenght = strlen(str)+1;
	int buf1 = strlen(str) - strlen(p)-2;
	int buf2 = strlen(str) - strlen(p) + strlen(conststring);
	int make_america_great_again = 0;
	_asm
	{
		cld
			mov ecx, lenght
			lea edi, buf
			lea esi, str
			jecxz MY_end
		m_loop:
		mov al, [esi]
			mov[edi], al
			inc edi

		nexttip2:
		inc make_america_great_again
		inc esi
		mov eax,buf1
		cmp  make_america_great_again, eax
			jg nexttip
			
			loop m_loop
		nexttip:
		mov eax, buf2
		    cmp make_america_great_again, eax
			jl nexttip2
			
			loop m_loop
		MY_end :
	}
	cout <<"with delete:"<< buf << endl;
	system("pause"); 
	exit(0);
	return 0;
}