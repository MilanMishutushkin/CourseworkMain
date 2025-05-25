#include "iostream"
#include "users.h"
#include "admin.h"
#include <conio.h>
void menu()
{
    int subChoice=0;
    do {
        std::cout << "\n******************************************";
        std::cout << "\n*             ������� ����               *";
        std::cout << "\n******************************************";
        std::cout << "\n* 1. ������� ����� ������                *";
        std::cout << "\n* 2. �������� ���������� � ���� �������� *";
        std::cout << "\n* 3. ��������� ������                    *";
        std::cout << "\n* 4. �������� ����� ���������            *";
        std::cout << "\n* 5. ����������� ������� �� ���������    *";
        std::cout << "\n* 6. �����                               *";
        std::cout << "\n******************************************";
        char key = _getch();
        switch (key) {
        case '1': subChoice = 1; break;
        case '2': subChoice = 2; break;
        case '3': subChoice = 3; break;
        case '4': subChoice = 4; break;
        case '5': subChoice = 5; break;
        case '6': subChoice = 6; break;
        default:
            std::cout << "\n====================================================\n";
            std::cout << " ������: ������� �������� ��������. ���������� �����!";
            std::cout << "\n====================================================\n";
            system("pause");
            continue;
        }

        switch (subChoice) {
        case 1:
            system("cls");
            balanceCreate();
            break;
        case 2:
            system("cls");
            showAllBalances();
            break;
        case 3:
            system("cls");
            balanceFill();
            break;
        case 4:
            system("cls");
            transactions();
            break;
        case 5:
            system("cls");
            sortBalances();
            break;
        case 6:
            std::cout << "\n�����...\n";
            system("cls");
            break;
        default:
            std::cout << "\n====================================================\n";
            std::cout << " ������: ������� �������� ��������. ���������� �����!";
            std::cout << "\n====================================================\n";
            system("pause");
        }
    } while (subChoice != 6);
}
void runMenu() {
    bool flag = true;
    while (flag) {
    system("cls");
    std::cout << "\n+---------------------------------------------------------------------------------------+\n";
    std::cout << "|\t\t���������� ������� ������� ����������� ���� �������������               |";
    std::cout << "\n+---------------------------------------------------------------------------------------+";

        std::cout << "\n        �� �� ������ ������������������ ��� �����?\n1. �����\n2. ������������������\n3. �����";
        int choice;
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
                break;
            }
            else
            {
                menu();
                break;
            }
        case 2:
        {
            registration();
            system("cls");
        }
        break;
        case 3:
            flag = false;
            break;
        default:
            std::cout << "\n====================================================\n";
            std::cout << " ������: ������� �������� ��������. ���������� �����!";
            std::cout << "\n====================================================\n";
            system("pause");
        }
        }
    }
}
