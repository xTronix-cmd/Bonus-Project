#include "MenuClass.hpp"

int Menu::welcome() { // modify this!
    std::cout << std::endl;
    std::cout << fmt::format("\n{:^63}\n", "Welcome to Marty's Produce Market") << std::endl;
    std::cout << fmt::format("1) Shop") << std::endl;
    std::cout << fmt::format("2) Sign Up for membership discount") << std::endl;
    std::cout << fmt::format("3) Login") << std::endl;
    std::cout << std::endl;
    std::cout << fmt::format("4) Quit") << std::endl;
    std::cout << std::endl;
    askForInput<int>(choice, ": ");
    return choice;
}
int Menu::viewShopMenu() {
    while (true) {
        std::cout << std::endl << std::endl;
        std::cout << fmt::format("1) View Products") << std::endl;
        std::cout << fmt::format("2) View Cart") << std::endl;
        std::cout << std::endl;
        std::cout << fmt::format("3) Back to Main Page") << std::endl;
        std::cout << std::endl << std::endl;
        askForInput<int>(choice, ": ");
        if (choice >= 1 && choice <= 3) { return choice; }
        
    }
}
int Menu::viewSubMenu(const std::string &view) {
    while (true) {
        std::cout << std::endl;
        std::cout << "1) " << view << std::endl;
        std::cout << "2) Add/Remove Order" << std::endl;
        std::cout << std::endl;
        std::cout << "3) Back to Main page" << std::endl;
        std::cout << std::endl << std::endl;
        askForInput<int>(choice, ": ");
        if (choice >= 1 && choice <= 3) { return choice; }
    }
}
int Menu::viewSubMenu2() {  // this is invoke from shopMenu page
    while (true) {
        std::cout << std::endl;
        std::cout << "1) Order" << std::endl;
        std::cout << std::endl;
        std::cout << "2) Back to Main page" << std::endl;
        std::cout << "3) Quit" << std::endl;
        std::cout << std::endl;
        askForInput<int>(choice, ": ");
        if (choice >= 1 && choice <= 3) { return choice; }
    }
} 
int Menu::viewSubMenu3() {
    while (true) {
        std::cout << std::endl;
        std::cout << "1) Go back to Main page" << std::endl;
        std::cout << "2) Exit" << std::endl;
        std::cout << std::endl;
        askForInput<int>(choice, ": ");
        if (choice == 1 || choice == 2) { return choice; }
    }
    return 0;
}
void Menu::shop(Produce &produce) {
    produce.showItems();
    produce.takeOrder();
    produce.showItems();
}
int Menu::order (Produce &produce) {
    this->shop(produce);
    while (true) {
        choice = this->viewSubMenu("View Cart");
        switch (choice) {
            case 1: return 2;
            case 2: return 1;
            case 3: return -1;
            default: continue;
        }
    }
    return 0; // by default exits
}

int Menu::cart(Produce &produce) {
    while (true) {
        if (produce.viewCart()) {
            choice = this->viewSubMenu("Checkout");
            switch (choice) {
                case 1: return 3;  // checkout is chosen
                case 2: return 1;  // add/remove order chosen
                case 3: return -1; // back to main page
                default: continue;
            }
        }
        else {
            choice = this->viewSubMenu2();
            switch (choice) {
                case 1: return 1;  // add/remove order chosen
                case 2: return -1; // back to main page
                case 3: return 0;  // exits program
                default: continue;
            }
        }
        return 0; // by default exits
    }
}

int Menu::checkout(Produce &produce, Customer &customer) {
    produce.calculateTotal(customer.checkMembership());
    while (true) {
        choice = this->viewSubMenu("Place Order");
        switch (choice) {
            case 1: // place order
                    produce.placeOrder();
                    choice = this->viewSubMenu3();
                    if (choice == 1) {
                        return -1;  // back to main page
                    }
                    return 0;  // exits program
            case 2: // add/remove order
                    return 1;
            case 3:
                    return -1;  // back to main page
            default: continue;
        }
    }
    return 0; // by default exits
}
int Menu::viewManagerMenu() {
    while (true) {
        std::cout << std::endl;
        std::cout << "1) Save manager info" << std::endl;
        std::cout << "2) Load manager info" << std::endl;
        std::cout << "3) View manager info" << std::endl;
        std::cout << "4) Manager Task" <<std::endl;
        std::cout << std::endl;
        std::cout << "5) Back to Main page" << std::endl;
        std::cout << std::endl;
        askForInput(choice, ": ");
        if (choice >= 1 && choice <= 5) { return choice; }
    }
}
int Menu::viewManagerPage() {
    while (true) {
        std::cout << std::endl;
        std::cout << "1) Add Item" << std::endl;
        std::cout << "2) Remove Item" << std::endl;
        std::cout << "3) Add member" << std::endl;
        std::cout << "4) Remove member" << std::endl;
        std::cout << std::endl;
        std::cout << "5) Back to manager menu" << std::endl;
        std::cout << std::endl;
        askForInput(choice, ": ");
        if (choice >= 1 && choice <= 5) { return choice; }
    }
}