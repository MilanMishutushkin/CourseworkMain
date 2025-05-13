#include "users.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

struct Admin : User {};

void showAllUsers()
{
    printf("\n");
    printf("\t%-20s\t%-15s\n", "��� ������������", "������");
    printf("**********************************************************\n");

    for (const auto& user : users) {
        printf(" \t%-20s\t%-15d\n", user.userName.c_str(), user.password);
    }
}

void userManage() {
    int choice = 0;

    do {
        
        std::cout << "\n**********************************\n";
        std::cout << "*        ������� ����               *\n";
        std::cout << "*************************************\n";
        std::cout << "* 1. �������� ������������          *\n";
        std::cout << "* 2. �������� ������������          *\n";
        std::cout << "* 3. ������� ������������           *\n";
        std::cout << "* 4. �������� ���� �������������    *\n";
        std::cout << "* 5. �����                          *\n";
        std::cout << "*************************************\n";

        char key = _getch();
        switch (key) {
        case '1': choice = 1; break;
        case '2': choice = 2; break;
        case '3': choice = 3; break;
        case '4': choice = 4; break;
        default:
            std::cout << "������: ������� �������� ��������. ���������� �����.\n";
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
            std::cout << "\n������� ��� ������������, �������� ������ ��������: ";
            std::cin >> nameToChange;

            for (auto& user : users) {
                if (user.userName == nameToChange) {
                    int subChoice;

                    do {
                        
                        std::cout << "\n*********************************************************\n";
                        std::cout << "*               ��� �� ������ ��������?                 *\n";
                        std::cout << "*********************************************************\n";
                        std::cout << "* 1. ��� ������������                                   *\n";
                        std::cout << "* 2. ������                                             *\n";
                        std::cout << "* 3. ����                                               *\n";
                        std::cout << "* 4. �������� �������                                   *\n";
                        std::cout << "* 5. ���������� ����� �� �������                        *\n";
                        std::cout << "* 6. �����                                              *\n";
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
                            std::cout << "������: ������� �������� ��������. ���������� �����.\n";
                            system("pause");
                            continue;
                        }

                        switch (subChoice) {
                        case 1: {
                            std::string newUsername;
                            bool userNameFlag = true;
                            while (userNameFlag) {
                                std::cout << "\n����� ��� ������������: ";
                                std::cin >> newUsername;
                                userNameFlag = false;

                                for (const auto& existingUser : users) {
                                    if (existingUser.userName == newUsername) {
                                        std::cout << "\n ��� ��� ������������ ��� ������.\n";
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
                                std::cout << "\n����� ������ (������� 5 ��������): ";
                                std::cin >> newPassword;
                            } while (newPassword.length() < 5);

                            user.password = newPassword;
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 3: {
                            char adminInput;
                            std::cout << "\n���� ������������ �������������? (y/n): ";
                            std::cin >> adminInput;
                            user.isAdmin = (adminInput == 'y' || adminInput == 'Y');
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 4: {
                            if (user.balances.empty()) {
                                std::cout << "\n====================================\n";
                                std::cout << "� ������������ ��� ��������!\n";
                                std::cout << "====================================\n";
                                break;
                            }

                            std::string balanceName;
                            std::cout << "\n������� �������� ������� ��� ���������: ";
                            std::cin >> balanceName;
                            bool found = false;

                            for (auto& balance : user.balances) {
                                if (balance.name == balanceName) {
                                    std::cout << "\n�������� ������ �������: ";
                                    std::cin >> balance.name;
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                std::cout << "\n=====================================\n";
                                std::cout << "������ � ����� ������ �� ������!\n";
                                std::cout << "=====================================\n";
                            }

                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 5: {
                            if (user.balances.empty()) {
                                std::cout << "\n====================================\n";
                                std::cout << "� ������������ ��� ��������!\n";
                                std::cout << "====================================\n";
                                break;
                            }

                            std::string balanceName;
                            std::cout << "\n������� �������� ������� ��� ���������: ";
                            std::cin >> balanceName;

                            for (auto& balance : user.balances) {
                                if (balance.name == balanceName) {
                                    std::cout << "\n������� ����� ���������� ����� �� �������: ";
                                    std::cin >> balance.funds;
                                    break;
                                }
                            }

                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 6:
                            std::cout << "����������� � ������� ����...\n";
                            break;
                        }

                    } while (subChoice != 6);

                    break;
                }
            }
            break;
        }

        case 3: {
            std::string nameToDelete;
            std::cout << "\n������� ��� ������������, �������� ������ �������: ";
            std::cin >> nameToDelete;
            std::string choiceToDelete;
            std::cout << "\n�� �������, ��� ������ ������� ������������ " << nameToDelete << "? (��/���): ";
            std::cin >> choiceToDelete;

            if (choiceToDelete == "��" || choiceToDelete == "��" || choiceToDelete == "yes" || choiceToDelete == "Yes" || choiceToDelete == "y") {
                users.erase(std::remove_if(users.begin(), users.end(),
                    [&](const User& u) { return u.userName == nameToDelete; }),
                    users.end());
                std::cout << "������������ ������.\n";
            }
            else {
                std::cout << "�������� ��������.\n";
            }
            break;
        }

        case 4:
            showAllUsers();
            break;
        case 5:
            std::cout << "����� �� ������ ��������������...\n";
            break;
        }

    } while (choice != 5);
}
