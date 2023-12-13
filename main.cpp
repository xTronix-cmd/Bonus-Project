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
#include "MenuClasses.hpp"

int main() {

    ProduceByWeight objProduceWeight;
    ProduceByAmount objProduceAmount;
    Produce objProduce;
    Customer customer;
    Menu menu;

    objProduce.loadFiles();

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
    while (!backToMainPage) {
        choice = welcome();
        switch (choice) {
            case 1: // show shop page
                    choice = viewShopMenu();
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
        while (!backToShopMenu) {
            switch (choice) {
                case 1: // view products
                        while (true) {
                            menu.shop();
                            choice = menu.viewSubMenu("View Cart");
                            // view cart from view products
                            if (choice == 1) {
                                fromViewProducts = true;
                                break;
                            } else if (choice == 3) {
                                backToMainPage = true;
                                backToShopMenu = true;
                                break;
                            }
                        } 
                case 2: // view cart
                        produce.viewCart();
                        if (fromViewProducts) {
                            choice = menu.viewSubMenu("Checkout");
                        } else if (fromShopPage) {
                            choice = menu.viewSubMenu2("Checkout");
                        }
                        break;
                case 3: // back to main page
                        continue;
            }
        }
        switch (choice) {
            case 1: 
                    produce.checkout();
                    if (fromViewProducts) {
                        choice = menu.viewSubMenu("Place Order");
                    } else if (fromShopPage) {
                        choice = menu.viewSubMenu2("Checkout");
                    }
                    break;
            case 3: // back to main page
                    continue;
        }
        switch (choice) {
            case 1: // calculatetotal
                    produce.calculateTotal(customer.checkMembership());
                    choice = menu.viewSubMenu2("Place Order");
                    break;
            case 2: //go to add/remove order
                    break;
            case 3: // back to main page
                    continue;
        }
        switch (choice) {
            case 1: // place order
                    produce.placeOrder();
                    choice = menu.viewSubMenu3();
                    break;
            case 2: // go to add/remove order
                    break;
            case 3: // back to main page
                    continue;
        }
        switch (choice) {
            case 1: // back to main page
                    continue;
            case 2: // exit program
                    return 0;
        }
    }
    std::cout << "Press Enter to exit program.." << std::endl;
    std::cin.get();
    // init();
    return 0;
}