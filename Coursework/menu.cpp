#include "iostream"
#include "users.h"
#include "admin.h"
#include <conio.h>
void runMenu() {
    bool flag = true;

    while (flag) {
        std::cout << "\n        Вы бы хотели зарегистрироваться или войти?\n1. Войти\n2. Зарегистрироваться\n3. Выйти";
        int choice;
        char key = _getch();
        switch (key) {
        case '1': choice = 1; break;
        case '2': choice = 2; break;
        case '3': choice = 3; break;
        default:
            std::cout << "Ошибка: Введено неверное значение. Попробуйте снова.\n";
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
                    std::cout << "\n*             Главное меню               *";
                    std::cout << "\n******************************************";
                    std::cout << "\n* 1. Создать новый баланск               *";
                    std::cout << "\n* 2. Показать информацию о всех балансах *";
                    std::cout << "\n* 3. Пополнить баланс                    *";
                    std::cout << "\n* 4. Выйти                               *";
                    std::cout << "\n******************************************";
                    char key = _getch();
                    switch (key) {
                    case '1': subChoice = 1; break;
                    case '2': subChoice = 2; break;
                    case '3': subChoice = 3; break;
                    case '4': subChoice = 4; break;
                    default:
                        std::cout << "\n====================================================\n";
                        std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!";
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
                        std::cout << "Выход...\n";
                        break;
                    default:
                        std::cout << "\n====================================================\n";
                        std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!";
                        std::cout << "\n====================================================\n";
                    }
                } while (subChoice != 4);

                break;
            }
        case 2:
        {
            registration();
            std::cout << "\nВы бы хотели войти?\nДа/Нет\n";
            std::cin >> inputChoice;
            if (inputChoice == "Да" || inputChoice == "да" || inputChoice == "yes" || inputChoice == "Yes" || inputChoice == "y")
            {
                login();
                loadUsers();

                int subChoice;
                do {
                    std::cout << "\n******************************************";
                    std::cout << "\n*             Главное меню               *";
                    std::cout << "\n******************************************";
                    std::cout << "\n* 1. Создать новый баланс                *";
                    std::cout << "\n* 2. Показать информацию о всех балансах *";
                    std::cout << "\n* 3. Пополнить баланс                    *";
                    std::cout << "\n* 4. Выйти                               *";
                    std::cout << "\n******************************************";
                    char key = _getch();
                    switch (key) {
                    case '1': subChoice = 1; break;
                    case '2': subChoice = 2; break;
                    case '3': subChoice = 3; break;
                    case '4': subChoice = 4; break;
                    default:
                        std::cout << "\n====================================================\n";
                        std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!\n";
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
                        std::cout << "\nВыход...\n";
                        break;
                    default:
                        std::cout << "\n====================================================\n";
                        std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!";
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
            std::cout << " Ошибка: Введено неверное значение. Попробуйте снова!";
            std::cout << "\n====================================================\n";
        }
        }
    }
}
