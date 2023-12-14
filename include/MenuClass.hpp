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
        int welcome() { // modify this!
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
        int viewShopMenu() {
            std::cout << std::endl << std::endl;
            std::cout << fmt::format("1) View Products") << std::endl;
            std::cout << fmt::format("2) View Cart") << std::endl;
            std::cout << std::endl;
            std::cout << fmt::format("3) Back to Main Page") << std::endl;
            std::cout << std::endl << std::endl;
            askForInput<int>(choice, ": ");
            return choice;
        }
        int viewSubMenu(const std::string &view) {
            std::cout << std::endl;
            std::cout << "1) " << view << std::endl;
            std::cout << "2) Add/Remove Order" << std::endl << std::endl;
            std::cout << "3) Back to Main page" << std::endl;
            std::cout << std::endl << std::endl;
            askForInput<int>(choice, ": ");
            return choice;
        }
        int viewSubMenu2() {  // this is invoke from shopMenu page
            std::cout << std::endl;
            std::cout << "1) Order" << std::endl;
            std::cout << "2) Back to Main page" << std::endl;
            std::cout << "3) Quit" << std::endl;
            std::cout << std::endl;
            askForInput<int>(choice, ": ");
            return choice;
        } 
        int viewSubMenu3() {
            std::cout << std::endl;
            std::cout << "1) Go back to Main page" << std::endl;
            std::cout << "2) Exit" << std::endl;
            std::cout << std::endl;
            askForInput<int>(choice, ": ");
            return choice;
        }
        int shop(Produce &produce) {
            produce.showItems();
            produce.takeOrder();
            produce.showItems();
            return 0; // zero if successfull
        }
        int order (Produce &produce) {
            int choice;
            this->shop(produce);
            choice = this->viewSubMenu("View Cart");
            switch (choice) {
                case 1: return 2;
                case 2: return 1;
                case 3: return -1;
            }
            return 0; // by default exits
        }

        int cart(Produce &produce) {
            int choice;
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

        int checkout(Produce &produce, Customer &customer) {
            int choice;
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
};