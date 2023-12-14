#include <iostream>
#include "ProduceClass.hpp"
#include "CustomerClass.hpp"
#include "FreeFunctions.hpp"

int Menu::welcome() { // modify this!
    std::cout << std::endl;
    std::cout << fmt::format("\n{:^63}\n", "Welcome to Marty's Produce Market") << std::endl;
    std::cout << fmt::format("1) Shop") << std::endl;
    std::cout << fmt::format("2) Sign Up for membership discount") << std::endl;
    std::cout << fmt::format("3) Login") << std::endl;
    std::cout << fmt::format("4) Quit") << std::endl;
    std::cout << std::endl;
    askForInput<int>(choice, ": ");
    return choice;
}
int Menu::viewShopMenu() {
    std::cout << std::endl << std::endl;
    std::cout << fmt::format("1) View Products") << std::endl;
    std::cout << fmt::format("2) View Cart") << std::endl;
    std::cout << std::endl;
    std::cout << fmt::format("3) Back to Main Page") << std::endl;
    std::cout << std::endl << std::endl;
    askForInput<int>(choice, ": ");
    return choice;
}
int Menu::viewSubMenu(const std::string &view) {
    std::cout << std::endl;
    std::cout << "1) " << view << std::endl;
    std::cout << "2) Add/Remove Order" << std::endl << std::endl;
    std::cout << "3) Back to Main page" << std::endl;
    std::cout << std::endl << std::endl;
    askForInput<int>(choice, ": ");
    return choice;
}
int Menu::viewSubMenu2() {  // this is invoke from shopMenu page
    std::cout << std::endl;
    std::cout << "1) Order" << std::endl;
    std::cout << "2) Back to Main page" << std::endl;
    std::cout << "3) Quit" << std::endl;
    std::cout << std::endl;
    askForInput<int>(choice, ": ");
    return choice;
} 
int Menu::viewSubMenu3() {
    std::cout << std::endl;
    std::cout << "1) Go back to Main page" << std::endl;
    std::cout << "2) Exit" << std::endl;
    std::cout << std::endl;
    askForInput<int>(choice, ": ");
    return choice;
}
void Menu::shop(Produce &produce) {
    produce.showItems();
    produce.takeOrder();
    produce.showItems();
}
int Menu::order (Produce &produce) {
    this->shop(produce);
    choice = this->viewSubMenu("View Cart");
    switch (choice) {
        case 1: return 2;
        case 2: return 1;
        case 3: return -1;
    }
    return 0; // by default exits
}

int Menu::cart(Produce &produce) {
    if (produce.viewCart()) {
        choice = this->viewSubMenu("Checkout");
        switch (choice) {
            case 1: return 3;  // checkout is chosen
            case 2: return 1;  // add/remove order chosen
            case 3: return -1; // back to main page
        }
    }
    else {
        choice = this->viewSubMenu2();
        switch (choice) {
            case 1: return 1;  // add/remove order chosen
            case 2: return -1; // back to main page
            case 3: return 0;  // exits program
        }
    }
    return 0; // by default exits
}

int Menu::checkout(Produce &produce, Customer &customer) {
    produce.calculateTotal(customer.checkMembership());
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
    }
    return 0; // by default exits
}