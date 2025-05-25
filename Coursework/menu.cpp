#include "iostream"
#include "users.h"
#include "admin.h"
#include <conio.h>
void menu()
{
    int subChoice=0;
    do {
        std::cout << "\n******************************************";
        std::cout << "\n*             Главное меню               *";
        std::cout << "\n******************************************";
        std::cout << "\n* 1. Создать новый баланс                *";
        std::cout << "\n* 2. Показать информацию о всех балансах *";
        std::cout << "\n* 3. Пополнить баланс                    *";
        std::cout << "\n* 4. Переводы между балансами            *";
        std::cout << "\n* 5. Сортировать балансы по параметру    *";
        std::cout << "\n* 6. Выйти                               *";
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
            std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!";
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
            std::cout << "\nВыход...\n";
            system("cls");
            break;
        default:
            std::cout << "\n====================================================\n";
            std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!";
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
    std::cout << "|\t\tБАНКОВСКАЯ СИСТЕМА ВЕДЕНИЯ ЭЛЕКТРОННЫХ КАРТ ПОЛЬЗОВАТЕЛЕЙ               |";
    std::cout << "\n+---------------------------------------------------------------------------------------+";

        std::cout << "\n        Вы бы хотели зарегистрироваться или войти?\n1. Войти\n2. Зарегистрироваться\n3. Выйти";
        int choice;
        char key = _getch();
        switch (key) {
        case '1': choice = 1; break;
        case '2': choice = 2; break;
        case '3': choice = 3; break;
        default:
            std::cout << "\n====================================================\n";
            std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!";
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
            std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!";
            std::cout << "\n====================================================\n";
            system("pause");
        }
        }
    }
}
