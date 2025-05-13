#include "iostream"
#include "users.h"

void runMenu() {
    bool flag = true;

    while (flag) {
        std::cout << "\nWould you like to login or register?\n1. Login\n2. Registration\n3. Exit";
            std::string inputChoice;
        std::cout << "\nYour choice: ";
        int choice;

        if (!(std::cin >> choice) || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n_________________________________\n";
            std::cout << "Invalid input. Try entering digits!";
            std::cout << "\n_________________________________\n";
            continue;
        }

        switch (choice) {
        case 1: {
            login();
            loadUsers();

            int subChoice;
            do {
                std::cout << "\nMenu:";
                std::cout << "\n1. Create new balance";
                std::cout << "\n2. Show information about balances";
                std::cout << "\n3. Fill balance by name";
                std::cout << "\n4. Exit";
                std::cout << "\nChoice: ";

                if (!(std::cin >> subChoice) || std::cin.peek() != '\n') {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\n_________________________________\n";
                    std::cout << "Invalid input. Try entering digits!";
                    std::cout << "\n_________________________________\n";
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
                    std::cout << "Exiting to main menu.\n";
                    break;
                default:
                    std::cout << "\n======================================\n";
                    std::cout << "Invalid choice. Try again.";
                    std::cout << "\n======================================\n";
                }
            } while (subChoice != 4);

            break;
        }
        case 2:
        {
            registration();
            std::cout << "\nWould you like to login?\nYes/No\n";
            std::cin >> inputChoice;
            if (inputChoice == "Yes" || inputChoice == "yes")
            {
                login();
                loadUsers();

                int subChoice;
                do {
                    std::cout << "\nMenu:";
                    std::cout << "\n1. Create new balance";
                    std::cout << "\n2. Show information about balances";
                    std::cout << "\n3. Fill balance by name";
                    std::cout << "\n4. Exit";
                    std::cout << "\nChoice: ";

                    if (!(std::cin >> subChoice) || std::cin.peek() != '\n') {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "\n_________________________________\n";
                        std::cout << "Invalid input. Try entering digits!";
                        std::cout << "\n_________________________________\n";
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
                        std::cout << "Exiting to main menu.\n";
                        break;
                    default:
                        std::cout << "\n======================================\n";
                        std::cout << "Invalid choice. Try again.";
                        std::cout << "\n======================================\n";
                    }
                } while (subChoice != 4);
            }
        }
            break;
        case 3:
            flag=false;
            break;
        default:
            std::cout << "\n======================================\n";
            std::cout << "Invalid choice. Try again.";
            std::cout << "\n======================================\n";
        }
    }
}
