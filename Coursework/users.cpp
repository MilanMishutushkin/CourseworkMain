#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "users.h"

void loadUsers() {
    std::ifstream file("user_list.txt");
    if (!file.is_open()) {
        std::cerr << "\n[Error] Unable to open user list file.\n";
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
        std::cerr << "\n[Error] Unable to open user list file for writing.\n";
        return;
    }

    for (const auto& user : users) {
        file << user.userName + ".txt" << std::endl;
    }
    file.close();
}

void registration() {
    User user;
    bool userNameFlag = true;

    while (userNameFlag) {
        std::cout << "\nNew username: ";
        std::cin >> user.userName;

        userNameFlag = false;
        for (const auto& existingUser : users) {
            if (user.userName == existingUser.userName) {
                std::cout << "\n[!] Username already taken. Try again.\n";
                userNameFlag = true;
                break;
            }
        }
    }

    bool passwordFlag = true;
    while (passwordFlag) {
        std::cout << "New password (min 5 chars): ";
        std::cin >> user.password;

        if (user.password.length() < 5) {
            std::cout << "\n[!] Password too short.\n";
        }
        else {
            passwordFlag = false;
        }
    }

    char adminInput;
    std::cout << "Is this user an admin? (y/n): ";
    std::cin >> adminInput;
    user.isAdmin = (adminInput == 'y' || adminInput == 'Y');

    users.push_back(user);
    user.printUserToFile(user.userName + ".txt");
    saveUserList();

    std::cout << "\n[+] Registration completed!\n";
}

void login() {
    while (true) {
        std::string userName, password;
        std::cout << "\nUsername: ";
        std::cin >> userName;

        std::cout << "Password: ";
        std::cin >> password;

        for (int i = 0; i < users.size(); ++i) {
            if (users[i].userName == userName && users[i].password == password) {
                userIndex = i;
                std::cout << "\n[+] Welcome, " << userName << "!";
                if (users[i].isAdmin) {
                    std::cout << "\n[Admin Access Granted]\n";
                }
                return;
            }
        }

        std::cout << "\n[!] Invalid username or password. Try again.\n";
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
    if (userIndex == -1) {
        std::cout << "\n[!] Please log in first.\n";
        return;
    }

    std::cout << "\nEnter new balance name: ";
    std::string name;
    std::cin >> name;

    if (!isNameUnique(name)) {
        std::cout << "\n[!] Balance name already exists.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000000, 99999999);
    int number = 100000000 + dis(gen);

    Balance newBalance{ name, number, 0 };
    users[userIndex].balances.push_back(newBalance);
    users[userIndex].printUserToFile(users[userIndex].userName + ".txt");

    std::cout << "\n[+] Balance created successfully:\n";
    std::cout << "Name: " << newBalance.name << "\n";
    std::cout << "Number: " << newBalance.number << "\n";
    std::cout << "Funds: " << newBalance.funds << "\n";
}

void showAllBalances() {
    if (userIndex == -1) {
        std::cout << "\n[!] Please log in first.\n";
        return;
    }
    if (users[userIndex].balances.empty()) {
        std::cout << "\n[!] You don't have any balances.\n";
        return;
    }
        std::cout << "\n[Your Balances]:\n";
    for (const auto& balance : users[userIndex].balances) {
        std::cout << "\n-----------------------------\n";
        std::cout << "Name: " << balance.name << "\n";
        std::cout << "Number: " << balance.number << "\n";
        std::cout << "Funds: " << balance.funds << "\n";
    }
}

void balanceFill() {
    if (userIndex == -1) {
        std::cout << "\n[!] Please log in first.\n";
        return;
    }

    std::cout << "\nEnter balance name to fill: ";
    std::string inputName;
    std::cin >> inputName;

    int balanceIndex = -1;
    for (size_t i = 0; i < users[userIndex].balances.size(); ++i) {
        if (users[userIndex].balances[i].name == inputName) {
            balanceIndex = i;
            break;
        }
    }

    if (balanceIndex == -1) {
        std::cout << "\n[!] Balance not found.\n";
        return;
    }

    int inputFunds;
    while (true) {
        std::cout << "Enter amount to add: ";
        std::cin >> inputFunds;

        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[!] Invalid input. Enter a number.\n";
        }
        else {
            break;
        }
    }

    users[userIndex].balances[balanceIndex].funds += inputFunds;
    users[userIndex].printUserToFile(users[userIndex].userName + ".txt");

    std::cout << "\n[+] Balance updated successfully.\n";
}