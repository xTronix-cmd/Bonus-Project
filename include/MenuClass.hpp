#include <iostream>
#include "ProduceClass.hpp"
#include "CustomerClass.hpp"
#include "FreeFunctions.hpp"

class Menu {
    private:
        int choice;
    
    public:
        template <typename T>
        void askForInput(T &c, const std::string &prompt) {
            while (true) {
                std::cout << prompt;
                std::cin >> c;

                if (std::cin.fail()) {  // checks to see if there's any error when trying to extract from input stream
                    std::cin.clear();  // clears the bit to good bit 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush the bad input from the stream
                    std::cout << "Invalid input. Try again.\n";
                    continue; 
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush out any remaining bad input
                // this check to see if we flush more than one character
                // which indicates a possibility of not extracting the input properly
                if (std::cin.gcount() > 1) {
                    std::cout << "Invalid input. Try again.\n";
                    continue;
                }
                break;
            }
            std::cout << std::endl;
        }
        template <typename T>
        void askForInput(T &a, T &b, const std::string &prompt) {
            while (true) {
                std::cout << prompt;
                std::cin >> a >> b;

                if (std::cin.fail()) {  // checks to see if there's any error when trying to extract from input stream
                    std::cin.clear();  // clears the bit to good bit 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush the bad input from the stream
                    continue;
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush out any remaining bad input
                // this check to see if we flush more than one character
                // which indicates a possibility of not extracting the input properly
                if (std::cin.gcount() > 1) {
                    continue;
                }
                break;
            }
        }
        inline int welcome() { // modify this!
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
        inline int viewShopMenu() {
            std::cout << std::endl << std::endl;
            std::cout << fmt::format("1) View Products") << std::endl;
            std::cout << fmt::format("2) View Cart") << std::endl;
            std::cout << std::endl;
            std::cout << fmt::format("3) Back to Main Page") << std::endl;
            std::cout << std::endl << std::endl;
            askForInput<int>(choice, ": ");
            return choice;
        }
        inline int viewSubMenu(const std::string &view) {
            std::cout << std::endl;
            std::cout << "1) " << view << std::endl;
            std::cout << "2) Add/Remove Order" << std::endl << std::endl;
            std::cout << "3) Back to Main page" << std::endl;
            std::cout << std::endl << std::endl;
            askForInput<int>(choice, ": ");
            return choice;
        }
        inline int viewSubMenu2(const std::string&view) {  // this is invoke from shopMenu page
            std::cout << std::endl;
            std::cout << "1) " << view << std::endl;
            std::cout << "2) Back to Shop page" << std::endl;
            std::cout << "3) Back to Main page" << std::endl;
            std::cout << std::endl;
            askForInput<int>(choice, ": ");
            return choice;
        } 
        inline int viewSubMenu3() {
            std::cout << std::endl;
            std::cout << "1) Go back to Main page" << std::endl;
            std::cout << "2) Exit" << std::endl;
            std::cout << std::endl;
            askForInput<int>(choice, ": ");
        }
        // void shop(const Produce &produce, const Menu &menu) {
        //     bool backToMainPage{false};
        //     bool firstTimeOrder{true};
        //     bool inPostOrder{true};
        //     int level{1}
        //     while (!backToMainPage) {
        //         produce.showItems();
        //         if (firstTimeOrder) { 
        //             firstTimeOrder = false;
        //             produce.takeorder();
        //             continue;
        //         }
        //         menu.viewSubMenu("View Cart");
        //         askForInput(choice, ": ");
        //         switch (choice) {
        //             case 1: produce.viewCart();
        //                     menu.viewSubMenu("Checkout");
        //                     break;
        //             case 2: firstTimeOrder = true;
        //                     continue;
        //             case 3: backToMainPage = true;
        //                     continue;
        //         }
        //         askForInput<int>(choice, ": ");
        //         switch (choice) {
        //             case 1: produce.calculateTotal(customer.checkMembership());
        //                     menu.viewSubMenu("Place Order");
        //                     break;
        //             case 2: firstTimeOrder = true;
        //                     continue;
        //             case 3: backToMainPage = true;
        //                     continue;
        //         }
        //         askForInput<int>(choice, ": ");
        //         switch (choice) {
        //             case 1: produce.placeOrder();
        //                     menu.viewSubMenu3();
        //                     break;
        //             case 2: firstTimeOrder = true;
        //                     continue;
        //             case 3: backToMainPage = true;
        //                     continue;
        //         }
        //         askForInput<int>(choice, ": ");
        //         switch (choice) {
        //             case 1: backToMainPage = true;
        //                     continue;
        //             case 2: return 0;
        //         }
        //     }
        // }
        // // im not sure yet what to do with this return values
        
        int shop(const Produce &produce) {
            produce.showItems();
            produce.takeorder();
        }
        int order(const Produce &produce) {
            produce.showItems();
            produce.takeorder();
            return 0;
        }
        void cart(const Produce &produce, const Menu &menu, const Customer &customer) {
            int choice;
            bool backToMainPage{false};
            bool backToShopPage{false};

            menu.viewSubMenu2("Checkout");
            askForInput<int>(choice, ":");
            while (!backToMainPage){
                switch (choice) {
                    case 1: produce.calculateTotal(customer.checkMembership());
                            menu.viewSubMenu2("Place Order");
                            break;
                    case 2: // back to shop page
                            // backToShopPage = true;
                            continue;
                    case 3: // back to main page
                            // backToMainPage = true;
                            continue;
                }
                askForInput<int>(choice, ": ");
                switch (choice) {
                    case 1: menu.viewSubMenu3();
                            produce.placeOrder();
                            break;
                    case 2: // go to add/remove order
                            break;
                    case 3: // back to main page
                            break;
                }
            }
        }
        int checkout(const Produce &produce, const Menu &menu, const Customer &customer) {
            int choice;
            produce.calculateTotal(customer.checkMembership());
            menu.viewSubMenu("Place Order");
            askForInput<int>(choice, ": ");
            if (choice == 1) {
                produce.calculateTotal(customer.checkMembership());
                menu.viewSubMenu2("Place Order");
            }
            return 0;
        }
};