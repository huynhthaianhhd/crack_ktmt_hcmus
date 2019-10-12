#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

string LengthString(string s)
{
	int length = 0;
	string temp = "";
	string temp2 = "";
	while (s[length] != 0)
		length++;
	temp = s[length - 1];
	return temp;
}

void Out(char a[16][16], string s)
{
	system("cls");
	cout << "NAME :" << s << endl;
	cout << "HOW TO GET SERIAL : 9 is Snake - C is Apple - D is Destination" << endl;
	cout << "Move Snake to eat all Apple(C) and then move to Destination (D)" << endl;
	cout << "NOTE : This code isn't incomplete." << endl;
	cout << "1. Moving snake reasonably to get SERIAL correctly." << endl;
	cout << "2. Avoid moving snake circles ." << endl << endl;
	cout << "HOW TO MOVE :" << endl;
	cout << "W - UP" << endl;
	cout << "S - DOWN" << endl;
	cout << "A - LEFT" << endl;
	cout << "D - RIGHT" << endl;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (a[i][j] == 'C')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << a[i][j] << "  ";
			}
			else if (a[i][j] == 'D')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << a[i][j] << "  ";
			}
			else if (a[i][j] == '9')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << a[i][j] << "  ";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << a[i][j] << "  ";
			}
		}
		cout << endl;
	}
}
void Init(char a[16][16])
{
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			a[i][j] = '0';
}
void ShowKey(string &s)
{
	while (s.find("0000") != -1)
		s.replace(s.find("0000"), 4, "C");
	while (s.find("1111") != -1)
		s.replace(s.find("1111"), 4, "D");
	while (s.find("2222") != -1)
		s.replace(s.find("2222"), 4, "E");
	while (s.find("3333") != -1)
		s.replace(s.find("3333"), 4, "F");
}
void ShowKey2(string &s)
{
	while (s.find("000") != -1)
		s.replace(s.find("000"), 3, "8");
	while (s.find("111") != -1)
		s.replace(s.find("111"), 3, "9");
	while (s.find("222") != -1)
		s.replace(s.find("222"), 3, "A");
	while (s.find("333") != -1)
		s.replace(s.find("333"), 3, "B");
}
void ShowKey3(string &s)
{
	while (s.find("00") != -1)
		s.replace(s.find("00"), 2, "4");
	while (s.find("11") != -1)
		s.replace(s.find("11"), 2, "5");
	while (s.find("22") != -1)
		s.replace(s.find("22"), 2, "6");
	while (s.find("33") != -1)
		s.replace(s.find("33"), 2, "7");
}
int EnteredName(char a[16][16], string s, int &rsour, int &csour, int &rdes, int &cdes)
{
	int dl = 0;
	int length = 0;
	int i = 0;
	int div;
	int mod;
	int rapple[20];
	int capple[20];
	while (s[length] != 0)
	{
		dl = dl + s[length];
		length++;
	}
	int temp;
	for (int i = 0; i < length; i++)
	{
		temp = int(s[i]); // đây là dạng int của s[i]
		temp = int(s[i]) ^ int(dl);
		dl = dl - temp;
		if (dl < 0)
			dl = 256 + dl;
		div = (temp - 256 * (temp / 256)) / 16;
		mod = (temp - 256 * (temp / 256)) % 16;
		if (a[div][mod] == '0')
		{
			a[div][mod] = 'C';
		}
		else
			return 0;
		rapple[i] = div;
		capple[i] = mod;
	}
	dl = dl^temp;
	temp = temp - dl;
	if (temp < 0)
		temp = 256 + temp;
	div = (temp - 256 * (temp / 256)) / 16;
	mod = (temp - 256 * (temp / 256)) % 16;
	if (a[div][mod] == '0')
		a[div][mod] = 'D';
	else
		return 0;
	rdes = div;
	cdes = mod;
	temp = dl;
	div = (temp - 256 * (temp / 256)) / 16;
	mod = (temp - 256 * (temp / 256)) % 16;
	if (a[div][mod] == '0')
		a[div][mod] = '9';
	else
		return 0;
	rsour = div;
	csour = mod;
	return 1;

}
int main()
{
	char a[16][16];
	int rsour, csour, rdes, cdes;
	string s, name;
	s = " ";
	Init(a);
LOOP:
	cout << "NAME :";
	getline(cin, name);
	cout << endl << endl;
	if (EnteredName(a, name, rsour, csour, rdes, cdes))
		Out(a, name);
	else
		goto LOOP;
	int k = 1;
	while (k)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				if (LengthString(s) == "0")
					break;
				else
					a[rsour][csour] = '0';
				if (rsour - 1 < 0)
					break;
				rsour--;
				a[rsour][csour] = '9';
				s = s + "1";
				system("cls");
				Out(a, name);
				break;
			case 's':
				if (LengthString(s) == "1")
					break;
				else
					a[rsour][csour] = '0';
				if (rsour + 1 > 15)
					break;
				rsour++;
				a[rsour][csour] = '9';
				s = s + "0";
				system("cls");
				Out(a, name);
				break;
			case 'a':
				if (LengthString(s) == "3")
					break;
				else
					a[rsour][csour] = '0';
				if (csour - 1 < 0)
					break;
				csour--;
				a[rsour][csour] = '9';
				s = s + "2";
				system("cls");
				Out(a, name);
				break;
			case 'd':
				if (LengthString(s) == "2")
					break;
				else
					a[rsour][csour] = '0';
				if (csour + 1 > 15)
					break;
				csour++;
				a[rsour][csour] = '9';
				s = s + "3";
				system("cls");
				Out(a, name);
				break;
			}
			if (csour == cdes && rsour == rdes)
			{
				k = 0;
				break;
			}
		}
	}
	cout << "Move :" << s << endl;
	ShowKey(s);
	ShowKey2(s);
	ShowKey3(s);
	cout << "SERIAL is :" << s << endl;
	system("pause");
	return 0;
}