#include "users.h" 
#include <iostream>
#include <string>

struct Admin : User {};

void userManage() {
    int choice;

    do {
        std::cout << "\nWhat would you do?";
        std::cout << "\n1. Add user";
        std::cout << "\n2. Change user";
        std::cout << "\n3. Delete user";
        std::cout << "\n4. Exit\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            registration();
            break;

        case 2: {
            std::string nameToChange;
            std::cout << "\nInput name of user to change: ";
            std::cin >> nameToChange;

            for (auto& user : users) {
                if (user.userName == nameToChange) {
                    int subChoice;

                    do {
                        std::cout << "\nWhat would you like to change?";
                        std::cout << "\n1. Username";
                        std::cout << "\n2. Password";
                        std::cout << "\n3. Privileges";
                        std::cout << "\n4. Balance name";
                        std::cout << "\n5. Balance funds";
                        std::cout << "\n6. Exit\n";
                        std::cin >> subChoice;

                        switch (subChoice) {
                        case 1: {
                            bool userNameFlag = true;
                            while (userNameFlag) {
                                std::cout << "\nNew username: ";
                                std::string newUsername;
                                std::cin >> newUsername;

                                userNameFlag = false;
                                for (const auto& existingUser : users) {
                                    if (existingUser.userName == newUsername) {
                                        std::cout << "\nThis username is already taken.\n";
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
                                std::cout << "\nNew password (min 5 characters): ";
                                std::cin >> newPassword;
                            } while (newPassword.length() < 5);

                            user.password = newPassword;
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 3: {
                            char adminInput;
                            std::cout << "\nIs this user an admin? (y/n): ";
                            std::cin >> adminInput;
                            user.isAdmin = (adminInput == 'y' || adminInput == 'Y');
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 4: {
                            std::string balanceName;
                            std::cout << "\nInput name of balance to change: ";
                            std::cin >> balanceName;

                                for (auto& balance : user.balances) {
                                    if (balance.name == balanceName) {
                                        std::cout << "\nNew balance name: ";
                                        std::cin >> balance.name;
                                        break;
                                    }
                                }
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 5: {
                            std::string balanceName;
                            std::cout << "\nInput name of balance to change: ";
                            std::cin >> balanceName;

                            for (auto& balance : user.balances) {
                                if (balance.name == balanceName) {
                                    std::cout << "\nNew balance funds: ";
                                    std::cin >> balance.funds;
                                    break;
                                }
                            }
                            user.printUserToFile(user.userName + ".txt");
                            break;
                        }

                        case 6:
                            std::cout << "Returning to main menu...\n";
                            break;

                        default:
                            std::cout << "Invalid input!\n";
                        }

                    } while (subChoice != 6);

                    break; // выход из цикла for, пользователь найден
                }
            }
            break;
        }

        case 3: {
            std::string nameToDelete;
            std::cout << "\nInput name of user to delete: ";
            std::cin >> nameToDelete;

            for (size_t i = 0; i < users.size(); ++i) {
                if (users[i].userName == nameToDelete) {
                    users.erase(users.begin() + i);
                    std::cout << "User deleted.\n";
                    break;
                }
            }
            break;
        }

        case 4:
            std::cout << "Exiting admin panel...\n";
            break;

        default:
            std::cout << "Invalid choice.\n";
        }

    } while (choice != 4);
}