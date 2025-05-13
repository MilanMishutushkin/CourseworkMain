#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "users.h"

void User::printUserToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "\n============================================\n";
        std::cerr << "  Ошибка:Не удалось открыть файл для записи!" << std::endl;
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
        std::cerr << "  Ошибка:Не удалось открыть файл для чтения!" << std::endl;
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
        std::cout << "   Ошибка:Не удалось открыть файл пользователей для чтения!";
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
        std::cout << "   Ошибка:Не удалось открыть файл пользователей для чтения!";
        std::cout << "\n=============================================================\n";
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
        std::cout << "\nИмя пользователя: ";
        std::cin >> user.userName;

        userNameFlag = false;
        for (const auto& existingUser : users) {
            if (user.userName == existingUser.userName) {
                std::cout << "\n==============================================\n";
                std::cout << "      Ошибка:Такое имя пользователя уже занято!";
                std::cout << "\n==============================================\n";
                userNameFlag = true;
                break;
            }
        }
    }

    bool passwordFlag = true;
    while (passwordFlag) {
        std::cout << "Новый пароль(минимум 5 символов): ";
        std::cin >> user.password;

        if (user.password.length() < 5) {
            std::cout << "\n==============================================\n";
            std::cout << "      Ошибка:Пароль слишком короткий";
            std::cout << "\n==============================================\n";
        }
        else {
            passwordFlag = false;
        }
    }

    char adminInput;
    std::cout << "Этот пользователь администратор? (y/n): ";
    std::cin >> adminInput;
    user.isAdmin = (adminInput == 'y' || adminInput == 'Y');

    users.push_back(user);
    user.printUserToFile(user.userName + ".txt");
    saveUserList();
    std::cout << "\n----------------------------------------\n";
    std::cout << "      Регистрация успешно завершена!";
    std::cout << "\n----------------------------------------\n";
}

void login() {
    while (true) {
        std::string userName, password;
        std::cout << "\nИмя пользователя: ";
        std::cin >> userName;

        std::cout << "Пароль: ";
        std::cin >> password;

        for (int i = 0; i < users.size(); ++i) {
            if (users[i].userName == userName && users[i].password == password) {
                userIndex = i;
                system("cls");
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                std::cout << "      Приветствуем, " << userName << "!";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                if (users[i].isAdmin) {
                    std::cout << "\n ----------------------------------------------------\n";
                    std::cout << "          Пользователь является администратором   ";
                    std::cout << "\n ----------------------------------------------------\n";
                }
                return;
            }
        }
        std::cout << "\n===================================\n";
        std::cout << "   Ошибка:Неверный логин или пароль!";
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
        std::cout << "\nПожалуйста,сначала войдите  в аккаунт.\n";
        return;
    }

    std::cout << "\nВведите название нового баланса: ";
    std::string name;
    std::cin >> name;

    if (!isNameUnique(name)) {
        std::cout << "\n=================================================\n";
        std::cout << "   Ошибка:Баланс с таким названием уже существует!";
        std::cout << "\n=================================================\n";
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
    std::cout << "\n       Баланс успешно создан:                    \n";
    printf("\t%-20s\t%-15s\t%-15s\n", "Название", "Номер", "Средства");
    printf("**********************************************************\n");
    printf("\t%-20s\t%-15d\t%-15d\n", newBalance.name.c_str(), newBalance.number, newBalance.funds);



}

void showAllBalances() {
    system("cls");
    if (userIndex == -1) {
        std::cout << "\nПожалуйста, сначала войдите в аккаунт.\n";
        return;
    }
    if (users[userIndex].balances.empty()) {
        std::cout << "\nУ вас нет ни одного баланса.\n";
        return;
    }

    printf("\n");
    printf("\t%-20s\t%-15s\t%-15s\n", "Название", "Номер", "Средства");
    printf("**********************************************************\n");

    for (const auto& balance : users[userIndex].balances) {
        printf(" \t%-20s\t%-15d\t%-15d\n", balance.name.c_str(), balance.number, balance.funds);
    }

    printf("\n");
}

void balanceFill() {
    system("cls");
    if (userIndex == -1) {
        std::cout << "\nПожалуйста, сначала войдите в аккаунт.\n";
        return;
    }

    std::cout << "\nВведите название баланса для пополнения: ";
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
        std::cout << "\n=================================================\n";
        std::cout << "      Ошибка:Баланс с таким именем не найден!";
        std::cout << "\n=================================================\n";
        return;
    }

    int inputFunds;
    while (true) {
        std::cout << "Количество: ";
        std::cin >> inputFunds;

        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n=================================================\n";
            std::cout << "              Ошибка:Неверное значение!";
            std::cout << "\n=================================================\n";
        }
        else {
            break;
        }
    }

    users[userIndex].balances[balanceIndex].funds += inputFunds;
    users[userIndex].printUserToFile(users[userIndex].userName + ".txt");

    std::cout << "\n----------------------------------------\n";
    std::cout << "          Баланс успешно обновлен!";
    std::cout << "\n----------------------------------------\n";
}