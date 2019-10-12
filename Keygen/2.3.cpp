#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Point
{
	unsigned int x;
	unsigned int y;
};

unsigned int t1 = 0x00, t2 = 0x00;
string Name, serial;
unsigned int Namelen, SizeMaze;
string Maze;
Point start, finish;
string key;

void Init()//Khởi tạo t1 và t2
{
	for (int i = 3; i >= 0; i--)
	{
		char s = Name[i] & 0xff;
		t1 = t1 << 8;
		t1 = t1 + int(s);
	}
	Namelen = Name.length();
	for (int i = Namelen - 1; i >= 4; i--)
	{
		char s = Name[i] & 0xff;
		t2 = t2 << 8;
		t2 = t2 + int(s);
	}
}

int Getrandom(unsigned int num)// lấy 1 số ngẫu nhiên
{
	unsigned int a = t1;
	unsigned int d = 0x5dc1;
	a = a * d;
	unsigned int c = 0x560b;
	d = 0;
	t1 = a % c;
	a = t2;
	d = 0x549d;
	a = a * d;
	c = 0x51a1;
	d = 0;
	t2 = a % c;
	a = t1;
	d = t2;
	a = a + d;
	c = num;
	unsigned int b = a % c;
	a = b;
	return a;
}

void Createmaze()// tạo mê cung
{
	unsigned int num = 0x14;
	unsigned int a = Getrandom(num);
	a += 0x14;
	SizeMaze = a;
	unsigned int b = 0;
	while (b < SizeMaze*SizeMaze)
	{
		num = 0x4;
		a = Getrandom(num);
		if (a == 0)
			Maze += "=";
		else
			Maze += ".";
		b++;
	}

	num = SizeMaze;
	start.x = Getrandom(num);
	start.y = Getrandom(num);

	do
	{
		num = SizeMaze;
		finish.x = Getrandom(num);
	} while (start.x == finish.x);

	do
	{
		num = SizeMaze;
		finish.y = Getrandom(num);
	} while (start.y == finish.y);

	a = start.x;
	unsigned int d = SizeMaze;
	a = a * d;
	d = start.y;
	a += d;
	Maze[a] = 'S';

	a = finish.x;
	d = SizeMaze;
	a = a * d;
	d = finish.y;
	a += d;
	Maze[a] = 'F';
}

bool SolveMaze(int x, int y)
{
	if (x > SizeMaze - 1 || x < 0 ||  y > SizeMaze - 1 ||y < 0 )
		return false;
	if (Maze[x*SizeMaze + y] == 'S') 
		return true;
	if (Maze[x*SizeMaze + y] != '.' && Maze[x*SizeMaze + y] != 'S')
		return false;
	Maze[x*SizeMaze + y] = '+';

	if (SolveMaze(x - 1, y) == true)
	{
		key += 'l';
		return true;
	}
	if (SolveMaze(x + 1, y) == true)
	{
		key += 'r';
		return true;
	}
	if (SolveMaze(x, y + 1) == true)
	{
		key += 'd';
		return true;
	}
	if (SolveMaze(x, y - 1) == true)
	{
		key += 'u';
		return true;
	}
	Maze[x*SizeMaze + y] = ' ';
	return false;
}

string GetKey()//hàm trả ra key
{
	if (SolveMaze(start.x, start.y))
	{
		string temp = "";
		for (int i = key.length() - 1; i >= 0; i--)
		{
			temp += key[i];
		}
		return temp;
	}
	else
	{
		return "Unsolvable";
	}
}

void Printmaze()//In ma trận ra màn hình(không cần thiết)
{
	for (int i = 0; i < SizeMaze; i++)
	{
		for (int j = 0; j < SizeMaze; j++)
			cout << Maze[i*SizeMaze + j];
		cout << endl;
	}
}

int main(void)
{
	do {
		cout << "UserName(5 -> 8 char): ";
		cin >> Name;
	} while (Name.length() < 5 || Name.length() > 8);
	cout << "r: Down" << endl;
	cout << "l: Up" << endl;
	cout << "d: Right" << endl;
	cout << "u: Left" << endl;
	cout << "S: Starting Point" << endl;
	cout << "F: Finshing Point" << endl;
	cout << "The machine will go away automatically." << endl;
	Init();
	Createmaze();
	Printmaze();
	cout << "\nKey: " << GetKey() << endl;
	system("pause");
}