#pragma once
#define FMT_HEADER_ONLY
#include <iostream>
#include <fmt/format.h>
#include "ProduceClass.hpp"
#include "CustomerClass.hpp"
#include "FreeFunctions.hpp"
class Menu {
    private:
    int choice;
    
    public:
    int welcome();
    int viewShopMenu();
    int viewSubMenu(const std::string &view);
    int viewSubMenu2();
    int viewSubMenu3();
    void shop(Produce &produce);
    int order (Produce &produce);
    int cart(Produce &produce);
    int checkout(Produce &produce, Customer &customer);
    int viewManagerPage();
    int viewManagerMenu();

};