
#pragma once
#define FMT_HEADER_ONLY
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <cxxabi.h>
#include <array>
#include <fstream>
#include <map>
#include <fmt/format.h>
#include <iomanip>

#include "FreeFunctions.hpp"

// Side Note: I could have done some polishing for these functions:
// showItems(), viewCart(), and calculatTotal()
// If I had time.. I was cutting it close to the deadline :(
class Produce {
    protected:
        struct produce {
            std::string produceName;
            std::string produceType;
            double price;
        } m_produce;

        // flag shared between Produce class & Customer class
        // vector for storing all of produce
        inline static std::vector<produce> m_vectorProduce;
        inline const static char m_filePWeight[] = "./data/ProduceByWeight.txt";
        inline const static char m_filePAmount[] = "./data/ProduceByAmount.txt";

        // used for counting total items for each type of produce 
        // to implement separation
        inline static std::array<int, 2> m_produceTypeSize;
        inline static bool firstTimeCall{true};
        inline static std::map<int, int> m_orders;
        bool m_isMember{false};
        bool m_isManager{false};
    
    public:

        // if time allows, ill implement something here..
        Produce() {
        }
        virtual ~Produce() = default;   // just in case

        void loadFiles();
        void resetFirstTimeCall();

        virtual bool addItem(const std::string &item, const double &price);
        virtual bool removeItem(const std::string &item);
        // show all of the items
        virtual void showItems();

        bool viewCart();

        // invoke when checking out 
        void calculateTotal(int flag);

        // invoke when user choose to place order from main() function
        void placeOrder();

        bool takeOrder();

        // helper function, can be place in private section
        // transfer the produceName & price of each produce in the produce vector to a map
        void transferToMap(std::map<std::string, double> &weight, std::map<std::string, double> &amount);

        // overloaded for weight and amount object
        void transferToMap(std::map<std::string, double> &items, const int &type);
};

class ProduceByWeight : public Produce {
    private:
        inline static std::map<std::string, double> items;
        double discountRate = 0.05;
        const std::string m_filePWeight{"./data/ProduceByWeight.txt"};

    public:
        ProduceByWeight() {

        }
        virtual ~ProduceByWeight() = default;

        bool addItem(const std::string &itemName, const double &price) override; 
        bool removeItem(const std::string &itemName) override;

        std::map<std::string, double> &getItems();

        void loadItems();
        void showItems() override;
        void saveItems();
};

class ProduceByAmount : public Produce {
    private:
        inline static std::map<std::string, double> items;
        double discountRate = 0.10;
        const std::string m_filePAmount{"./data/ProduceByAmount.txt"};

    public:
        ProduceByAmount() {
        }
        virtual ~ProduceByAmount() = default;

        std::map<std::string, double> &getItems();
        void loadItems();
        void showItems() override;
        void saveItems();

        // addItem might not have time to fully implement
        bool addItem(const std::string &itemName, const double &price) override;

        // needed more time to implement this for management
        // when manager logins.. he/she can add/remove inventory
        bool removeItem(const std::string &itemName) override;
};