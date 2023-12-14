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

#include <iostream>
#include <map>

#include "CustomerClass.hpp"
#include "ProduceClass.hpp"
#include "FreeFunctions.hpp"
#include "MenuClass.hpp"

int main() {

    ProduceByWeight objProduceWeight;
    ProduceByAmount objProduceAmount;
    Produce produce;
    Customer customer;
    Menu menu;

    produce.loadFiles();

    bool backToMainPage{false};
    bool backToShopMenu{false};
    bool backToShopPage{false};
    bool fromViewProducts{false};
    bool fromShopPage{false};
    std::string strInput;
    double price;
    int choice; 

// this menu implementation could have done better by using
// functions to pass inputs and take outputs
// would have been less clunky
    while (true) {
        backToMainPage = false;
        choice = menu.welcome();
        switch (choice) {
            case 1: // show shop page
                    choice = menu.viewShopMenu();
                    break;
            case 2: // sign up
                    customer.signUp();
                    continue; // after signup back to main page
            case 3: // login
                    customer.login();
                    continue; // after login back to main page
            case 4: // quit
                    return 0;
        }
        while (!backToMainPage) {
            // if order chosen
            if (choice == 1) {  // view product chosen
                menu.shop(produce);
                choice = menu.viewSubMenu("View Cart");
                switch (choice) {
                    case 1: // view cart chosen
                            choice = 2;
                            continue;
                    case 2: // add/remove chosen
                            choice = 1;
                            continue;
                    case 3: // back to main page chosen
                            backToMainPage = true;
                            continue;
                }
            }
            // if view chart chosen
            if (choice == 2) {
                if (produce.viewCart()) {
                    choice = menu.viewSubMenu("Checkout");
                    switch (choice) {
                        case 1: // checkout chosen
                                // something
                                choice = 3; // to choose checkout
                                continue;
                        case 2: // add/remove order chosen
                                choice = 1;
                                continue;
                        case 3: backToMainPage = true;
                                continue;
                    }
                }
                else {
                    choice = menu.viewSubMenu2();
                    if (choice == 2) {
                        backToMainPage = true; // back to welcome()
                    } else if (choice == 3) {
                        return 0;
                    }
                    // this is implicitly saying that go to ordering process 
                    continue;
                }
            }
            // if checkout chosen
            if (choice == 3 ) {
                produce.calculateTotal(customer.checkMembership());
                choice = menu.viewSubMenu("Place Order");
                switch (choice) {
                    case 1: // place order
                            produce.placeOrder();
                            choice = menu.viewSubMenu3();
                            if (choice == 1) {
                                backToMainPage = true;
                                continue;
                            }
                            return 0;   // if choice != 1, exit program
                    case 2: // add/remove order
                            choice = 1;
                            continue;
                    case 3: // retur to main page
                            backToMainPage = true;
                            continue;
                }
            }
        }
    }
    return 0;
}