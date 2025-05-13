#pragma once
#include <iostream>
#include <string>
#include <random>
#include <fstream>

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


    void printUserToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "\n======================================\n";
            std::cerr << "  Error opening file for writing!" << std::endl;
            std::cout << "\n======================================\n";
            return;
        }
        file << userName << "\t"
            << password << "\t"
            << isAdmin << std::endl;
        for (const auto& balance : balances)
        {
            file << balance.name << "\t"
                << balance.number << "\t"
                << balance.funds << std::endl;
        }
        file.close();
    }

    void readUserFromFile(const std::string& filename) {
        std::ifstream file(filename);
        Balance balance;
        if (!file.is_open()) {
            std::cout << "\n======================================\n";
            std::cerr << "  Error opening file for reading!" << std::endl;
            std::cout << "\n======================================\n";
            return;
        }
        file >> userName >> password >> isAdmin;
        while (file >> balance.name >> balance.number >> balance.funds) {
            balances.push_back(balance);
        }
        file.close();
    }
};

std::vector<User> users;
int userIndex = -1;


void registration();
void login();
void loadUsers();
void saveUserList();
bool isNameUnique(const std::string& name);
void balanceCreate();
void showAllBalances();
void balanceFill();