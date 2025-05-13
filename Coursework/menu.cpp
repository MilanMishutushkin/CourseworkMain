#include "iostream"
#include "users.h"
#include "admin.h"
#include <conio.h>
void runMenu() {
    bool flag = true;

    while (flag) {
        std::cout << "\n        �� �� ������ ������������������ ��� �����?\n1. �����\n2. ������������������\n3. �����";
        int choice;
        char key = _getch();
        switch (key) {
        case '1': choice = 1; break;
        case '2': choice = 2; break;
        case '3': choice = 3; break;
        default:
            std::cout << "������: ������� �������� ��������. ���������� �����.\n";
            system("pause");
            continue;
        }
            std::string inputChoice;
        switch (choice) {
        case 1: {
            login();
            loadUsers();
            if (users[userIndex].isAdmin)
            {
                userManage();
            }
            else
            {
                int subChoice;
                do {
                    std::cout << "\n******************************************";
                    std::cout << "\n*             ������� ����               *";
                    std::cout << "\n******************************************";
                    std::cout << "\n* 1. ������� ����� �������               *";
                    std::cout << "\n* 2. �������� ���������� � ���� �������� *";
                    std::cout << "\n* 3. ��������� ������                    *";
                    std::cout << "\n* 4. �����                               *";
                    std::cout << "\n******************************************";
                    char key = _getch();
                    switch (key) {
                    case '1': subChoice = 1; break;
                    case '2': subChoice = 2; break;
                    case '3': subChoice = 3; break;
                    case '4': subChoice = 4; break;
                    default:
                        std::cout << "\n====================================================\n";
                        std::cout << " ������: ������� �������� ��������. ���������� �����!";
                        std::cout << "\n====================================================\n";
                        system("pause");
                        continue;
                    }

                    switch (subChoice) {
                    case 1:
                        balanceCreate();
                        break;
                    case 2:
                        showAllBalances();
                        break;
                    case 3:
                        balanceFill();
                        break;
                    case 4:
                        std::cout << "�����...\n";
                        break;
                    default:
                        std::cout << "\n====================================================\n";
                        std::cout << " ������: ������� �������� ��������. ���������� �����!";
                        std::cout << "\n====================================================\n";
                    }
                } while (subChoice != 4);

                break;
            }
        case 2:
        {
            registration();
            std::cout << "\n�� �� ������ �����?\n��/���\n";
            std::cin >> inputChoice;
            if (inputChoice == "��" || inputChoice == "��" || inputChoice == "yes" || inputChoice == "Yes" || inputChoice == "y")
            {
                login();
                loadUsers();

                int subChoice;
                do {
                    std::cout << "\n******************************************";
                    std::cout << "\n*             ������� ����               *";
                    std::cout << "\n******************************************";
                    std::cout << "\n* 1. ������� ����� ������                *";
                    std::cout << "\n* 2. �������� ���������� � ���� �������� *";
                    std::cout << "\n* 3. ��������� ������                    *";
                    std::cout << "\n* 4. �����                               *";
                    std::cout << "\n******************************************";
                    char key = _getch();
                    switch (key) {
                    case '1': subChoice = 1; break;
                    case '2': subChoice = 2; break;
                    case '3': subChoice = 3; break;
                    case '4': subChoice = 4; break;
                    default:
                        std::cout << "\n====================================================\n";
                        std::cout << " ������: ������� �������� ��������. ���������� �����!\n";
                        std::cout << "\n====================================================\n";
                        system("pause");
                        continue;
                    }

                    switch (subChoice) {
                    case 1:
                        balanceCreate();
                        break;
                    case 2:
                        showAllBalances();
                        break;
                    case 3:
                        balanceFill();
                        break;
                    case 4:
                        std::cout << "\n�����...\n";
                        break;
                    default:
                        std::cout << "\n====================================================\n";
                        std::cout << " ������: ������� �������� ��������. ���������� �����!";
                        std::cout << "\n====================================================\n";
                    }
                } while (subChoice != 4);
            }
        }
        break;
        case 3:
            flag = false;
            break;
        default:
            std::cout << "\n====================================================\n";
            std::cout << " ������: ������� �������� ��������. ���������� �����!";
            std::cout << "\n====================================================\n";
        }
        }
    }
}
