//============================================================================
//
// Name : Marty Grefiel
// Student #: 301572130
// Student userid (email): mga137 (mga137@sfu.ca)
//
//============================================================================
// Project name:    Produce Market
// Date:            12/11/2023 
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  cplusplus.com, cppreference.com, and stackoverflow.com
// Note: Files are read and written from/to the "data" directory.
//
//============================================================================

// #include <iostream>

#include "CustomerClass.hpp"
#include "ProduceClass.hpp"
// #include "FreeFunctions.hpp"
#include "MenuClass.hpp"
#include "ManagerClass.hpp"

int main() {

    ProduceByWeight objProduceWeight;
    ProduceByAmount objProduceAmount;
    Produce produce;
    Customer customer;
    Menu menu;
    Manager manager;

    customer.loadCustomersDatabase();

    manager.setManagerInfo("Marty", "Tigz", "Locker1");

    produce.loadFiles();

    bool backToMainPage;
    bool leaveMarket{false};
    int choice; 

// this menu implementation could have done better by using
// functions to pass inputs and take outputs
// would have been less clunky
    while (!leaveMarket) {
        // this is to reset the flag when it's set somewhere to go back to main page
        backToMainPage = false;
        choice = menu.welcome();
        switch (choice) {
            case 1: // show shop page
                    choice = menu.viewShopMenu();
                    if (choice )
                    break;
            case 2: // sign up
                    customer.signUp();
                    continue; // after signup back to main page
            case 3: // login
                    customer.login();
                    continue; // after login back to main page
            case 4: // quit
                    leaveMarket = true;
                    continue;
            case 7: if (manager.managerLogin()) {
                        bool backToManagerMenu{false};
                        while (!backToMainPage && !backToManagerMenu) {
                            choice = menu.viewManagerMenu();
                            switch (choice) {
                                case 1: manager.saveManagerInfo("data/man.dat");
                                        continue;
                                case 2: manager.loadManagerInfo("data/man.dat"); 
                                        continue;
                                case 3: manager.viewManagerInfo();
                                        continue;
                                case 4: choice = menu.viewManagerPage();
                                        switch (choice) {
                                            case 1: ; // add item
                                            case 2: ;// remove item
                                            case 3: ;// add member
                                            case 4: std::string name;
                                                    std::cout << "Enter member name to remove: ";
                                                    std::cin >> name;
                                                    manager.deleteMember(name);
                                                    break;
                                        }
                                        continue;
                                case 5: backToMainPage = true;
                                        backToManagerMenu = true;
                                        continue;
                            }
                        }
                    }
            default: continue; // back to main page
        }
        while (!backToMainPage) {
            switch (choice) {
                // case 1: order chosen
                case 1: choice = menu.order(produce);
                        break;
                // case 2: cart chosen
                case 2: choice = menu.cart(produce);
                        break;
                // case 3: checkout chosen
                case 3: choice = menu.checkout(produce, customer);
                        break;
                // default: continue; // back to menu page
            }
            if (choice == -1) { 
                backToMainPage = true;
            } else if (choice == 0) { 
                backToMainPage = true;
                leaveMarket = true;
            } else { continue; }
        }
    }
    std::cout << "Thank you! Come again." << std::endl;
    return 0;
}