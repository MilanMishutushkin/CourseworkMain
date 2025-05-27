#include "iostream"
#include "users.h"
#include "menu.h"
#include <windows.h>
int main() {
	SetConsoleCP(1251);         
	SetConsoleOutputCP(1251);
	loadUsers();

	//const char* entranceFilename = "entrance.txt";
	
	runMenu();
}