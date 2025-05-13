#include "users.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

struct Admin : User {};

void showAllUsers()
{
    printf("\n");
    printf("\t%-16s\t%-6s\n", "Имя пользователя", "Пароль");
    printf("**********************************************************\n");

    printUsersData("users.txt");
}

void userManage() {
    int choice = 0;

    do {
        
        std::cout << "\n*************************************\n";
        std::cout << "*        Главное меню               *\n";
        std::cout << "*************************************\n";
        std::cout << "* 1. Добавить пользователя          *\n";
        std::cout << "* 2. Изменить пользователя          *\n";
        std::cout << "* 3. Удалить пользователя           *\n";
        std::cout << "* 4. Показать всех пользователей    *\n";
        std::cout << "* 5. Выход                          *\n";
        std::cout << "*************************************\n";

        char key = _getch();
        switch (key) {
        case '1': choice = 1; break;
        case '2': choice = 2; break;
        case '3': choice = 3; break;
        case '4': choice = 4; break;
        case '5': choice = 5; break;
        default:
            std::cout << "Ошибка: Введено неверное значение. Попробуйте снова.\n";
            system("pause");
            continue;
        }

        switch (choice) {
        case 1:
            system("cls");
            registration();
            system("cls");
            break;

        case 2: {
            std::string nameToChange;
            std::cout << "\nВведите имя пользователя, которого хотите изменить: ";
            std::cin >> nameToChange;

            for (auto& user : users) {
                if (user.userName == nameToChange) {
                    int subChoice;

                    do {
                        system("cls");
                        std::cout << "\n*********************************************************\n";
                        std::cout << "*               Что Вы хотите изменить?                 *\n";
                        std::cout << "*********************************************************\n";
                        std::cout << "* 1. Имя пользователя                                   *\n";
                        std::cout << "* 2. Пароль                                             *\n";
                        std::cout << "* 3. Роль                                               *\n";
                        std::cout << "* 4. Название баланса                                   *\n";
                        std::cout << "* 5. Количество денег на балансе                        *\n";
                        std::cout << "* 6. Выход                                              *\n";
                        std::cout << "*********************************************************\n";

                        char subKey = _getch();
                        switch (subKey) {
                        case '1': subChoice = 1; break;
                        case '2': subChoice = 2; break;
                        case '3': subChoice = 3; break;
                        case '4': subChoice = 4; break;
                        case '5': subChoice = 5; break;
                        case '6': subChoice = 6; break;
                        default:
                            std::cout << "Ошибка: Введено неверное значение. Попробуйте снова.\n";
                            system("pause");
                            continue;
                        }

                        switch (subChoice) {
                        case 1: {
                            system("cls");
                            std::string newUsername;
                            bool userNameFlag = true;
                            while (userNameFlag) {
                                std::cout << "\nНовое имя пользователя: ";
                                std::cin >> newUsername;
                                userNameFlag = false;

                                for (const auto& existingUser : users) {
                                    if (existingUser.userName == newUsername) {
                                        std::cout << "\n Это имя пользователя уже занято.\n";
                                        userNameFlag = true;
                                        break;
                                    }
                                }

                                if (!userNameFlag)
                                    user.userName = newUsername;
                            }
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 2: {
                            std::string newPassword;
                            do {
                                system("cls");
                                std::cout << "\nНовый пароль (минимум 5 символов): ";
                                std::cin >> newPassword;
                            } while (newPassword.length() < 5);

                            user.password = newPassword;
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 3: {
                            system("cls");
                            char adminInput;
                            std::cout << "\nЭтот пользователь администратор? (y/n): ";
                            std::cin >> adminInput;
                            user.isAdmin = (adminInput == 'y' || adminInput == 'Y');
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 4: {
                            system("cls");
                            if (user.balances.empty()) {
                                std::cout << "\n====================================\n";
                                std::cout << "У пользователя нет балансов!\n";
                                std::cout << "====================================\n";
                                break;
                            }

                            std::string balanceName;
                            std::cout << "\nВведите название баланса для изменений: ";
                            std::cin >> balanceName;
                            bool found = false;

                            for (auto& balance : user.balances) {
                                if (balance.name == balanceName) {
                                    std::cout << "\nНазвание нового баланса: ";
                                    std::cin >> balance.name;
                                    found = true;
                                    break;
                                }
                            }

                                system("cls");
                            if (!found) {
                                std::cout << "\n=====================================\n";
                                std::cout << "Баланс с таким именем не найден!\n";
                                std::cout << "=====================================\n";
                            }

                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 5: {
                            system("cls");
                            if (user.balances.empty()) {
                                std::cout << "\n====================================\n";
                                std::cout << "У пользователя нет балансов!\n";
                                std::cout << "====================================\n";
                                break;
                            }

                            std::string balanceName;
                            std::cout << "\nВведите название баланса для изменений: ";
                            std::cin >> balanceName;

                            for (auto& balance : user.balances) {
                                if (balance.name == balanceName) {
                                    std::cout << "\nВведите новое количество денег на балансе: ";
                                    std::cin >> balance.funds;
                                    break;
                                }
                            }

                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 6:
                            std::cout << "Возвращение в главное меню...\n";
                            break;
                        }

                    } while (subChoice != 6);

                    break;
                }
            }
            break;
        }

        case 3: {
            system("cls");
            std::string nameToDelete;
            std::cout << "\nВведите имя пользователя, которого хотите удалить: ";
            std::cin >> nameToDelete;
            std::string choiceToDelete;
            std::cout << "\nВы уверены, что хотите удалить пользователя " << nameToDelete << "? (Да/Нет): ";
            std::cin >> choiceToDelete;

            if (choiceToDelete == "Да" || choiceToDelete == "да" || choiceToDelete == "yes" || choiceToDelete == "Yes" || choiceToDelete == "y") {
                users.erase(std::remove_if(users.begin(), users.end(),
                    [&](const User& u) { return u.userName == nameToDelete; }),
                    users.end());
                std::cout << "Пользователь удален.\n";
                saveUsersData(users, "users.txt");
            }
            else {
                std::cout << "Операция отменена.\n";
            }
            break;
        }

        case 4:
            system("cls");
            showAllUsers();
            break;
        case 5:
            std::cout << "Выход из панели администратора...\n";
            system("cls");
            break;
        }

    } while (choice != 5);
}
