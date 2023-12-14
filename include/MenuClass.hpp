#pragma once
#include <iostream>
#include "ProduceClass.hpp"
#include "CustomerClass.hpp"
class Menu {
    private:
    int choice;
    
    public:
    int welcome();
    int viewShopMenu();
    int viewSubMenu(const std::string &view);
    int viewSubMenu2();
    int viewSubMenu3();
    int shop(Produce &produce);
    int order (Produce &produce);
    int cart(Produce &produce);
    int checkout(Produce &produce, Customer &customer);
};