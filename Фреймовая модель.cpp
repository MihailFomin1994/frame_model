#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include "interface.h"
int main()
{
	//Только под windows. 
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	std::string nameBase = "Шкаф с посудой";
	std::string filename = "base.txt";
	Interface(nameBase, filename);
	return 0;
}