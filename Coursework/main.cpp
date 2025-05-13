#include "iostream"
#include "users.h"
#include "menu.h"

int main() {
    
	loadUsers();

	const char* entranceFilename = "entrance.txt";
	
	runMenu();
}