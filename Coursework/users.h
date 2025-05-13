#pragma once
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <vector>

struct Balance {
	std::string name = " ";
	int number = 0;
	int funds = 0;
};

struct User {
	std::string userName = " ";
	std::string password = " ";
	bool isAdmin;
	std::vector<Balance> balances;

	void printUserToFile(const std::string& filename);
	void readUserFromFile(const std::string& filename);
};

extern std::vector<User> users;
extern int userIndex;

void saveUsersData(const std::vector<User>& users, const std::string& filename);
void printUsersData(const std::string& filename);
void registration();
void login();
void loadUsers();
void saveUserList();
bool isNameUnique(const std::string& name);
void balanceCreate();
void showAllBalances();
void balanceFill();
std::string caesarCipher(const std::string& text);