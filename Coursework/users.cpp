#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "users.h"
#include <sstream>
#include <conio.h>


void User::printUserToFile(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cout << "\n============================================\n";
		std::cout << "  ������:�� ������� ������� ���� ��� ������!" << std::endl;
		std::cout << "\n============================================\n";
		return;
	}
	file << userName << "\t"
		<< password << "\t"
		<< isAdmin << std::endl;
	for (const auto& balance : balances) {
		file << balance.name << "\t"
			<< balance.number << "\t"
			<< balance.funds << std::endl;
	}
	file.close();
}

void User::readUserFromFile(const std::string& filename) {
	std::ifstream file(filename);
	Balance balance;
	if (!file.is_open()) {
		std::cout << "\n============================================\n";
		std::cout << "  ������:�� ������� ������� ���� ��� ������!" << std::endl;
		std::cout << "\n============================================\n";
		return;
	}
	file >> userName >> password >> isAdmin;
	while (file >> balance.name >> balance.number >> balance.funds) {
		balances.push_back(balance);
	}
	file.close();
}

std::vector<User> users;
int userIndex = -1;

void loadUsers() {
	std::ifstream file("user_list.txt");
	if (!file.is_open()) {
		std::cout << "\n=============================================================\n";
		std::cout << "   ������:�� ������� ������� ���� ������������� ��� ������!";
		std::cout << "\n=============================================================\n";
		return;
	}

	std::string userFileName;
	while (file >> userFileName) {
		User user;
		user.readUserFromFile(userFileName);
		users.push_back(user);
	}
	file.close();
}

void saveUserList() {
	std::ofstream file("user_list.txt");
	if (!file.is_open()) {
		std::cout << "\n=============================================================\n";
		std::cout << "   ������:�� ������� ������� ���� ������������� ��� ������!";
		std::cout << "\n=============================================================\n";
		return;
	}

	for (const auto& user : users) {
		file << user.userName + ".txt" << std::endl;
	}
	file.close();
}

void saveUsersData(const std::vector<User>& users, const std::string& filename)
{
	std::ofstream file(filename, std::ios::app);
	if (!file.is_open()) {
		std::cout << "\n============================================\n";
		std::cout << "  ������:�� ������� ������� ���� ��� ������!" << std::endl;
		std::cout << "\n============================================\n";
		return;
	}

	const User& user = users.back();
	file << user.userName << '\t' << user.password << '\n';

	file.close();
}

void printUsersData(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "\n============================================\n";
		std::cout << "  ������:�� ������� ������� ���� ��� ������!";
		std::cout << "\n============================================\n";
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string name;
		std::string password;
		iss >> name >> password;
		std::cout << '\t' << name << '\t' << '\t' << '\t' << password << std::endl;
	}
}

std::string caesarCipher(const std::string& text) {
	std::string encryptedText;
	for (char c : text) {
		encryptedText += static_cast<char>(c - 15);
	}
	return encryptedText;
}
void transactions()
{
	std::cout << "\n������� �������� �������-�����������:";
	std::string balanceOutcomer;
	std::cin >> balanceOutcomer;

	int outcomerIndex = -1;
	for (int i = 0; i < users[userIndex].balances.size(); ++i) {
		if (users[userIndex].balances[i].name == balanceOutcomer) {
			outcomerIndex = i;
			break;
		}
	}

	if (outcomerIndex == -1) {
		std::cout << "\n============================================\n";
		std::cout << "  ������: ������-����������� �� ������!";
		std::cout << "\n============================================\n";
		return;
	}

	std::cout << "������� �������� �������-����������:";
	std::string balanceIncomer;
	std::cin >> balanceIncomer;

	int incomerIndex = -1;
	for (int i = 0; i < users[userIndex].balances.size(); ++i) {
		if (users[userIndex].balances[i].name == balanceIncomer) {
			incomerIndex = i;
			break;
		}
	}

	if (incomerIndex == -1) {
		std::cout << "\n============================================\n";
		std::cout << "  ������: ������-���������� �� ������!";
		std::cout << "\n============================================\n";
		return;
	}

	std::cout << "����� ��������: ";
	int transaction;
	std::cin >> transaction;

	if (transaction > users[userIndex].balances[outcomerIndex].funds) {
		std::cout << "\n============================================\n";
		std::cout << "  ������: ������������ �������!";
		std::cout << "\n============================================\n";
		return;
	}

	users[userIndex].balances[outcomerIndex].funds -= transaction;
	users[userIndex].balances[incomerIndex].funds += transaction;

	std::cout << "\n----------------------------------------\n";
	std::cout << "          ������� ������� ��������!";
	std::cout << "\n----------------------------------------\n";
}
void sortBalances() {
		int choice=0;
		char key = _getch();
		switch (key) {
		case '1': choice = 1; break;
		case '2': choice = 2; break;
		case '3': choice = 3; break;
		default:
			std::cout << "\n====================================================\n";
			std::cout << " ������: ������� �������� ��������. ���������� �����!";
			std::cout << "\n====================================================\n";
			system("pause");
		}
	do {
		std::cout << "\n������������� ���� ������� �� ������ ���������?"
			<< "\n1. �� ��������"
			<< "\n2. �� ������"
			<< "\n3. �� ���������� ����� �� �����"
			<< "\n4. �����\n";
		

		switch (choice) {
		case 1: {
			Balance temp;
			for (size_t i = 0; i < users[userIndex].balances.size(); i++) {
				for (size_t j = 0; j < users[userIndex].balances.size() - i - 1; j++) {
					if (users[userIndex].balances[j].name > users[userIndex].balances[j + 1].name) {
						std::swap(users[userIndex].balances[j], users[userIndex].balances[j + 1]);
					}
				}
			}
			break;
		}
		case 2: {
			Balance temp;
			for (size_t i = 0; i < users[userIndex].balances.size(); i++) {
				for (size_t j = 0; j < users[userIndex].balances.size() - i - 1; j++) {
					if (users[userIndex].balances[j].number > users[userIndex].balances[j + 1].number) {
						std::swap(users[userIndex].balances[j], users[userIndex].balances[j + 1]);
					}
				}
			}
			break;
		}
		case 3: {
			Balance temp;
			for (size_t i = 0; i < users[userIndex].balances.size(); i++) {
				for (size_t j = 0; j < users[userIndex].balances.size() - i - 1; j++) {
					if (users[userIndex].balances[j].funds > users[userIndex].balances[j + 1].funds) {
						std::swap(users[userIndex].balances[j], users[userIndex].balances[j + 1]);
					}
				}
			}
			break;
		}
		case 4:
		{
			std::cout << "�����...";
			system("pause");
			system("cls");
			break;
		}
		default:
			std::cout << "\n������: ������� �������� ��������. ���������� �����!\n";
			continue;
		}

		std::cout << "\n----------------------------------------\n";
		std::cout << "      ������ ������� ������������!";
		std::cout << "\n----------------------------------------\n";
		std::cout << "�����...";
		system("pause");
		system("cls");
		break;
		users[userIndex].printUserToFile(users[userIndex].userName + ".txt");

	} while (choice != 4);
}
std::string caesarDecipher(const std::string& text) {
	std::string decryptedText;
	for (char c : text) {
		decryptedText += static_cast<char>(c + 15);
	}
	return decryptedText;
}
void registration() {
	User user;
	bool userNameFlag = true;
	system("cls");
	std::cout << "\t\t�����������";
	while (userNameFlag) {
		std::cout << "\n��� ������������: ";
		std::cin >> user.userName;

		userNameFlag = false;
		for (const auto& existingUser : users) {
			if (user.userName == existingUser.userName) {
				std::cout << "\n==============================================\n";
				std::cout << "      ������:����� ��� ������������ ��� ������!";
				std::cout << "\n==============================================\n";
				userNameFlag = true;
				break;
			}
		}
	}

	bool passwordFlag = true;
	while (passwordFlag) {
		std::cout << "����� ������(������� 5 ��������): ";
		std::cin >> user.password;
		user.password = caesarCipher(user.password);

		if (user.password.length() < 5) {
			std::cout << "\n==============================================\n";
			std::cout << "      ������:������ ������� ��������";
			std::cout << "\n==============================================\n";
		}
		else {
			passwordFlag = false;
		}
	}

	char adminInput;
	std::cout << "���� ������������ �������������? (y/n): ";
	std::cin >> adminInput;
	user.isAdmin = (adminInput == 'y' || adminInput == 'Y');

	users.push_back(user);
	user.printUserToFile(user.userName + ".txt");
	saveUserList();
	saveUsersData(users, "users.txt");
	std::cout << "\n----------------------------------------\n";
	std::cout << "      ����������� ������� ���������!";
	std::cout << "\n----------------------------------------\n";
}

void login() {
	system("cls");
	std::cout << "\t\t����";
	while (true) {
		std::string userName, password;
		std::cout << "\n��� ������������: ";
		std::cin >> userName;

		std::cout << "������: ";
		std::cin >> password;

		for (int i = 0; i < users.size(); ++i) {
			if (users[i].userName == userName && caesarDecipher(users[i].password) == password) {
				userIndex = i;
				system("cls");
				std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				std::cout << "		������������, " << userName << "!";
				std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
				if (users[i].isAdmin) {
					std::cout << "\n ----------------------------------------------------\n";
					std::cout << "          ������������ �������� ���������������   ";
					std::cout << "\n ----------------------------------------------------";
				}
				return;
			}
		}
		std::cout << "\n===================================\n";
		std::cout << "   ������:�������� ����� ��� ������!";
		std::cout << "\n===================================\n";

		userIndex = -1;
	}
}

bool isNameUnique(const std::string& name) {
	for (const auto& balance : users[userIndex].balances) {
		if (balance.name == name) {
			return false;
		}
	}
	return true;
}

void balanceCreate() {
	system("cls");
	if (userIndex == -1) {
		std::cout << "\n����������,������� �������  � �������.\n";
		return;
	}

	std::cout << "\n������� �������� ������ �������: ";
	std::string name;
	std::cin >> name;

	if (!isNameUnique(name)) {
		std::cout << "\n=================================================\n";
		std::cout << "   ������:������ � ����� ��������� ��� ����������!";
		std::cout << "\n=================================================\n";
		system("pause");
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(10000000, 99999999);
	int number = 100000000 + dis(gen);

	Balance newBalance{ name, number, 0 };
	users[userIndex].balances.push_back(newBalance);
	users[userIndex].printUserToFile(users[userIndex].userName + ".txt");

	printf("\n");
	std::cout << "\n       ������ ������� ������:                    \n";
	printf("\t%-20s\t%-15s\t%-15s\n", "��������", "�����", "��������");
	printf("**********************************************************\n");
	printf("\t%-20s\t%-15d\t%-15d\n", newBalance.name.c_str(), newBalance.number, newBalance.funds);
	system("pause");
	system("cls");

}

void showAllBalances() {
	system("cls");
	if (userIndex == -1) {
		std::cout << "\n����������, ������� ������� � �������.\n";
		system("pause");
		return;
	}
	if (users[userIndex].balances.empty()) {
		std::cout << "\n� ��� ��� �� ������ �������.\n";
		system("pause");
		return;
	}

	printf("\n");
	printf("\t%-20s\t%-15s\t%-15s\n", "��������", "�����", "��������");
	printf("**********************************************************\n");

	for (const auto& balance : users[userIndex].balances) {
		printf(" \t%-20s\t%-15d\t%-15d\n", balance.name.c_str(), balance.number, balance.funds);
	}

	printf("\n");
	system("pause");
	system("cls");
}

void balanceFill() {
	system("cls");
	if (userIndex == -1) {
		std::cout << "\n����������, ������� ������� � �������.\n";
		system("pause");
		return;
	}

	std::cout << "\n������� �������� ������� ��� ����������: ";
	std::string inputName;
	std::cin >> inputName;

	int balanceIndex = -1;
	for (int i = 0; i < users[userIndex].balances.size(); ++i) {
		if (users[userIndex].balances[i].name == inputName) {
			balanceIndex = i;
			break;
		}
	}

	if (balanceIndex == -1) {
		std::cout << "\n=================================================\n";
		std::cout << "      ������:������ � ����� ������ �� ������!";
		std::cout << "\n=================================================\n";
		system("pause");
		return;
	}

	int inputFunds;
	while (true) {
		std::cout << "����������: ";
		std::cin >> inputFunds;

		if (std::cin.fail() || std::cin.peek() != '\n' || inputFunds < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\n=================================================\n";
			std::cout << "              ������:�������� ��������!";
			std::cout << "\n=================================================\n";
			system("pause");
		}
		else {

			break;
		}
	}


	users[userIndex].balances[balanceIndex].funds += inputFunds;
	users[userIndex].printUserToFile(users[userIndex].userName + ".txt");

	std::cout << "\n----------------------------------------\n";
	std::cout << "          ������ ������� ��������!";
	std::cout << "\n----------------------------------------\n";
	system("pause");
	system("cls");
}