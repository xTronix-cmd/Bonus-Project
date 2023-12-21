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
//
// Resources:  cplusplus.com, cppreference.com, and stackoverflow.com
//
// File:              ProduceClass.cpp
// Description:       class member function definitions to process item produce
//
//============================================================================
#include "ProduceClass.hpp"

// Side Note: I could have done some polishing for these functions:
// showItems(), viewCart(), and calculatTotal()
// If I had time more time.. :)
void Produce::loadFiles() {
    double price;
    std::string itemName;
    bool duplicate{false};
    // must  open produce by weight first before by amount
    // so that we can read them in sorted manner later
    if (std::ifstream weightFile{m_filePWeight, std::ios::in}) {
        while (weightFile >> itemName >> price) {
            duplicate = false;
            m_produce.produceName = itemName;
            m_produce.price = price;
            m_produce.produceType = "weight";
            if  (!m_vectorProduce.empty()){
                for (const produce &p : m_vectorProduce) {
                    if (p.produceName == m_produce.produceName) {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate) {
                    continue;
                }
            }
            m_vectorProduce.push_back(m_produce);
            // this is to count the number of weight items
            m_produceTypeSize.at(0)++;  
        }
        // std::cout << "ProduceByWeight.txt loaded\n";
    } else { std::cout << "Could not load ProduceByWeight.txt file\n"; }


    if (std::ifstream amountFile{m_filePAmount, std::ios::in}) {
        while (amountFile >> itemName >> price) {
            duplicate = false;
            m_produce.produceName = itemName;
            m_produce.price = price;
            m_produce.produceType = "amount";
            if  (!m_vectorProduce.empty()){
                // gets rid of duplicate items
                for (const produce &p : m_vectorProduce) {
                    if (p.produceName == m_produce.produceName) {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate) {
                    continue;
                }
            }
            m_vectorProduce.push_back(m_produce);
            // this is to count the number of weight items
            m_produceTypeSize.at(1)++;
        }
    } else { std::cout << "Could not load ProduceByAmount.txt file\n"; }
    // omitted closing the files since once ifstream object goes out scope
    // its destructor will close them for us

    std::cout << std::endl;
    
}

void Produce::resetFirstTimeCall() {
    firstTimeCall = true;
}

bool Produce::addItem(const std::string &item, const double &price) {
    //
    return false;
}

bool Produce::removeItem(const std::string &item) {
    //
    return false;
}

// show all of the items
void Produce::showItems() {

    std::map<int, int> *orders;

    // when no orders made yet; first time calling showItems to  just show items
    if (firstTimeCall) {
        orders = nullptr;
        firstTimeCall = false;
    }
    // when orders been made
    else { orders = &m_orders; }

    std::map<std::string, double> weight;
    std::map<std::string, double> amount;

    transferToMap(weight, amount);

    std::map<std::string, double>::iterator itWeight, itAmount;
    std::map<int, int>::iterator itOrderAmount1, itOrderAmount2;

    itWeight = weight.begin();
    itAmount = amount.begin();
    // determines which map has less value, so we can use it to iterate through them
    int boundary = std::min(weight.size(), amount.size());

    std::cout << std::endl << std::endl;
    std::cout << fmt::format("{:-<28}{:^10}{:->28}", "", "", "") << std::endl;
    std::cout << fmt::format("{:^14}{:>14}", "Items", "$/lb");
    std::cout << fmt::format("{:^10}", "");
    std::cout << fmt::format("{:^14}{:>14}", "Items", "$ each") << std::endl;
    std::cout << fmt::format("{:-<28}{:^10}{:->28}\n", "", "", "") << std::endl;

    std::string orderAmount1, orderAmount2;

    for (size_t index{1}; index <= boundary; index++) {
        orderAmount1 = "";
        orderAmount2 = "";
        if (orders != nullptr) {
            // assigns the iterators of the corresponding item
            itOrderAmount1 = orders->find(index);

            itOrderAmount2 = orders->find(weight.size()+index);

            if (itOrderAmount1 != orders->end()) {
                orderAmount1 = std::to_string(itOrderAmount1->second);
                orderAmount1 = "x" + orderAmount1;
            }
            if (itOrderAmount2 != orders->end()) {
                orderAmount2 = std::to_string(itOrderAmount2->second);
                orderAmount2 = "x" + orderAmount2;
            }
        }
        std::cout << fmt::format("{:<2}) {:<10}{:^3}{:>11.2f}",  index, itWeight->first,
                                orderAmount1, itWeight->second);
        std::cout << fmt::format("{:^10}", "");
        std::cout << fmt::format("{:<2}) {:<10}{:^3}{:>11.2f}", weight.size()+index, itAmount->first,
                                orderAmount2, itAmount->second) << std::endl;
        
        itWeight++;
        itAmount++;
    }

    // if weight map object is larger, print the remaining items of produce charge by weight
    if (weight.size() > amount.size()) { 
        // algorithm for properly numbering the remaining items
        size_t index{1}; 
        while (itWeight != weight.end()) {
            orderAmount1 = "";
            if (orders != nullptr) {
                itOrderAmount1 = orders->find(boundary+index);
                if (itOrderAmount1 != orders->end()) {
                    orderAmount1 = std::to_string(itOrderAmount1->second);
                    orderAmount1 = "x" + orderAmount1;
                }
            }
            std::cout << fmt::format("{:<2}) {:<10}{:^3}{:>11.2f}\n", boundary+index, itWeight->first,
                                    orderAmount1, itWeight->second);

            itWeight++;
            index++;
        } // algorithm
    }
    // if amount map object is larger, print the remaining items of produce charge for each
    else if (amount.size() > weight.size()) {
        // algorithm for properly numbering the remaining items
        size_t index{1};
        while (itAmount != amount.end()) {
            orderAmount2 = "";
            if (orders != nullptr) {
                itOrderAmount2 = orders->find(boundary*2+index);
                if (itOrderAmount2 != orders->end()) {
                    orderAmount2 = std::to_string(itOrderAmount2->second);
                    orderAmount2 = "x" + orderAmount2;
                }
            }
            std::cout << fmt::format("{:^38}", "");
            std::cout << fmt::format("{:2<}) {:<10}{:^3}{:>11.2f}", boundary*2+index, itAmount->first, 
                                    orderAmount2, itAmount->second) << std::endl;
            
            itAmount++;
            index++;
        } // algorithm
    }
    std::cout << std::endl << std::endl;
}

bool Produce::viewCart() {

            if (m_orders.empty()) {
                std::cout << fmt::format("Cart is empty\n");
                return false;
            }
            std::map<std::string, double> weight;
            std::map<std::string, double> amount;

            // to separate the items by amount and weight into two map objects
            transferToMap(weight, amount);

            std::map<std::string, double>:: iterator itWeight{weight.begin()}, itAmount{amount.begin()};
            size_t boundary = std::min(weight.size(), amount.size());

            double weightCost, amountCost, subtotal;

            std::cout << std::endl << std::endl;
            std::cout << fmt::format("Item(s){:^13}{:>8}", "Qty", "Price Ea") << std::endl;
            std::cout << fmt::format("{:-<28}", "") << std::endl << std::endl;
            
            // this big block is just for printing the result nicely
            for (size_t index{1}; index <= boundary; index++) {
                if (m_orders.find(index) != m_orders.end()) {
                    weightCost += m_orders[index] * itWeight->second;
                    std::cout << fmt::format("{:<10}{:^8} {:>9.2f}\n", itWeight->first, m_orders[index], itWeight->second);
                }
                if (m_orders.find(weight.size()+index) != m_orders.end()) {
                    amountCost += m_orders[weight.size()+index] * itAmount->second;
                    std::cout << fmt::format("{:<10}{:^8} {:>9.2f}\n", itAmount->first, m_orders[weight.size()+index], itAmount->second);
                }
                itWeight++;
                itAmount++;
            }
            if (weight.size() > amount.size()) {
                size_t index{1};
                while (itWeight != weight.end()) {
                    if (m_orders.find(boundary+index) != m_orders.end()) {
                        weightCost += m_orders[boundary+index] * itWeight->second;
                        std::cout << fmt::format("{:<10}{:^8} {:>9.2f}\n", itWeight->first, m_orders[boundary+index], itWeight->second);
                    }
                    itWeight++;
                    index++;
                }
            }
            else if (amount.size() > weight.size()) {
                size_t index{1};
                while (itAmount != amount.end()) {
                    if (m_orders.find(boundary*2+index) != m_orders.end()) {
                        amountCost = m_orders[boundary*2+index] * itAmount->second;
                        std::cout << fmt::format("{:<10}{:^8} {:>9.2f}\n", itAmount->first, m_orders[boundary*2+index], itAmount->second);

                    }
                    itAmount++;
                    index++;
                }
            } /* end block for print items ordered*/

            subtotal = weightCost + amountCost;
            std::cout << fmt::format("{:^16}{:->12}", "", "") << std::endl; 
            std::cout << fmt::format("Sub Total{:^9}{:>10.2f}", "", subtotal) << std::endl;
            std::cout << std::endl << std::endl;

            return true;
        }

void Produce::calculateTotal(int flag) {
    std::map<std::string, double>::iterator itWeight, itAmount;
    std::map<std::string, double> weight;
    std::map<std::string, double> amount;

    transferToMap(weight, amount);

    itWeight = weight.begin();
    itAmount = amount.begin();

    size_t boundary = std::min(weight.size(), amount.size());

    double cost, discount, subtotal;
    const double GST{0.05}, PST{0.07};
    
    std::cout << std::endl << std::endl;
    // discount for over 10 lbs or 5 peices of item
    // index has been found in orders, do something
    for (size_t index{1}; index <= boundary; index++) {
        if (m_orders.find(index) != m_orders.end()) {
            cost = m_orders[index] * itWeight->second;
            std::cout << fmt::format("{:<10}{:^45} {:>10.2f}", itWeight->first, "", cost) << std::endl;
            std::cout << fmt::format(" {} lb(s) @ {:.2f}/lb", m_orders[index], itWeight->second) << std::endl;
            if (m_orders[index] >= 10) {
                discount = -(cost * 0.10);
                std::cout << fmt::format(" {:^3} off over 10 lbs{:>46.2f}", R"(10%)", discount) << std::endl;
            }
            subtotal += cost + discount;
        }
        if (m_orders.find(weight.size()+index) != m_orders.end()) {
            cost = m_orders[weight.size()+index] * itAmount->second;
            std::cout << fmt::format("{:<10}{:^45} {:>10.2f}", itAmount->first, "", cost) << std::endl;
            std::cout << fmt::format(" {} @ {}", m_orders[weight.size()+index], itAmount->second) << std::endl;
            if (m_orders[weight.size()+index] >= 5) {
                discount = -(cost * 0.05);
                std::cout << fmt::format(" {:^3}off over 5 pcs{:>48.2f}", R"(5%)", discount) << std::endl;
            }
            subtotal += cost + discount;
        }
        itWeight++;
        itAmount++;
    }
    if (weight.size() > amount.size()) {
        size_t index{1};
        while (itWeight != weight.end()) {
            if (m_orders.find(boundary+index) != m_orders.end()) {
                cost = m_orders[boundary+index] * itWeight->second;
                std::cout << fmt::format("{:<10}{:^45} {:>10.2f}", itWeight->first, "", cost) << std::endl;
                std::cout << fmt::format(" {} lb(s) @ {}/lb", m_orders[boundary+index], itWeight->second) << std::endl;
                if (m_orders[boundary+index] >= 10) {
                    discount = -(cost * 0.10);
                    std::cout << fmt::format(" {:<3} off over 10 lbs{:>46.2f}", "10%", discount) << std::endl;
                }
                subtotal += cost + discount; 
            }
            itWeight++;
            index++;
        }
    }
    else if (amount.size() > weight.size()) {
        size_t index{1};
        while (itAmount != amount.end()) {
            if (m_orders.find(boundary*2+index) != m_orders.end()) {
                cost = m_orders[boundary*2+index] * itAmount->second;
                std::cout << fmt::format("{:<10}{:^45} {:>10.2f}", itAmount->first, "", cost) << std::endl;
                std::cout << fmt::format(" {} @ {}", m_orders[boundary*2+index], itAmount->second) << std::endl;
                if (m_orders[boundary*2+index] >= 5) {
                    discount = -(cost * 0.05);
                    std::cout << fmt::format(" {:^3}off over 5 pieces{:>45.2f}", "5%", discount) << std::endl;
                }
                subtotal += cost + discount; 
            }
            itAmount++;
            index++;
        }
    }

    if (flag != 0) {
        double percentDiscount;
        std::string mDiscount;
        if (flag == membershipFlag::MEMBER) {
            percentDiscount = 7.0;
            mDiscount = "Member";
        } else if (flag == membershipFlag::MANAGER) {
            percentDiscount = 10.0;
            mDiscount = "Manager";
        }
        discount = -(subtotal * (percentDiscount/100));
        subtotal += discount;
        std::cout << std::endl;
        std::cout << fmt::format("{:<16}{}% off{:^25}{:>18.2f}", mDiscount + " discount ", percentDiscount, "", discount);
        std::cout << std::endl;
    }
    else { std::cout << fmt::format("{:<50}{:>16}", "No member discount", "") << std::endl; }

    std::cout << fmt::format("{:^50}{:->16}", "", "") << std::endl; 
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << fmt::format("Sub Total{:^49}", "");
    std::cout << fmt::format("{:<2}", "") << "$" << subtotal << std::endl;
    std::cout << std::endl;
    


    double taxGST = GST * subtotal;
    double taxPST = PST * subtotal;
    double total = subtotal + taxGST + taxPST;

    std::cout << fmt::format("Tax-Code{:^34}{:>24}", "", "Tax-Value") << std::endl;
    std::cout << fmt::format("GST{:^53}{:>10.2f}", "", taxGST) << std::endl;
    std::cout << fmt::format("PST{:^53}{:>10.2f}", "", taxPST) << std::endl;
    std::cout << fmt::format("{:^50}{:->16}", "", "") << std::endl;
    
    std::cout << fmt::format("Total{:^53}", "");
    std::cout << fmt::format("{:<2}", "")<< "$" << total << std::endl;
    std::cout << std::endl << std::endl;
}

// placing the order and printing the receipt
void Produce::placeOrder(int flag) {
    std::cout << std::endl << std::endl;
    std::cout << fmt::format("{:^63}", "Marty's") << std::endl;
    std::cout << fmt::format("{:^65}", "Produce Market Project") << std::endl;
    std::cout << fmt::format("{:^65}", "Purchase #: _____") << std::endl;
    std::cout << fmt::format("{:^65}", "Reciept") << std::endl;
    std::cout << fmt::format("{:^65}", "-----------") << std::endl;
    std::cout << std::endl;

    calculateTotal(flag);

    std::cout << std::endl;
    std::cout << fmt::format("{:^65}", "Thank You!!") << std::endl;
    m_orders.clear();
    resetFirstTimeCall();
}

bool Produce::takeOrder() {

    int amountOrder, itemNumber;
    bool inputInvalid;
    size_t totalItems = m_vectorProduce.size();

    std::cout << std::endl << std::endl;
    std::cout << fmt::format("To order, [item number] [amount]. eg. 1 2\n");
    std::cout << fmt::format("Enter a negative amount to take off order\n");
    std::cout << fmt::format("To finish ordering, enter an item number not on list.\n");

    while (true) {
        askForInput(itemNumber, amountOrder, ": ");

        if (itemNumber <= 0 || itemNumber > totalItems) {
                break;
        }
        // add another condition if user input a number greater than total items 
        // update: (fixed!)
        else {
            // if key not found in map or total amount ordered is less zero, set amount to zero
            // in short, so we won't have a negative qty of order
            // just incase user enter really large negative number
            if ((m_orders.find(itemNumber) == m_orders.end() && amountOrder < 0) || 
                (m_orders[itemNumber] + amountOrder) < 0) {  
                m_orders[itemNumber] = 0;
                // std::cout << "m_orders.erase() invoked\n";
                m_orders.erase(itemNumber);
            }
            else {
                m_orders[itemNumber] += amountOrder;  // did this so you can subtract a qty of your order
            }
        }
    }
    // This is to prevent showItems() from printing zero when there's a zero order
    // after first time calling it.
    for (auto itOrders = m_orders.begin(); itOrders != m_orders.end(); itOrders++) {
        if (itOrders->second == 0) {
            itOrders = m_orders.erase(itOrders); 
        //    std::cout << "Key got deleted!\n";
        }
    }
    return !m_orders.empty();
}

// helper function, can be place in private section
// transfer the items & price of each produce into their corresponding types
void Produce::transferToMap(std::map<std::string, double> &weight, std::map<std::string, double> &amount) { 
    size_t posIndex{1};

    for (const produce &p : m_vectorProduce) {
        if (posIndex <= m_produceTypeSize.at(0)) {
            weight[p.produceName] = p.price;
        }
        if (posIndex > m_produceTypeSize.at(0) && posIndex <= m_vectorProduce.size()) {
            amount[p.produceName] = p.price;
        } 
        posIndex++;
    }
}

// overloaded for weight and amount object
void Produce::transferToMap(std::map<std::string, double> &items, const int &type) { 
    size_t posIndex{1};

    for (const produce &p : m_vectorProduce) {
        // by weight
        if (type == 0) {
            if (posIndex <= m_produceTypeSize.at(0)) {
                items[p.produceName] = p.price;
            }
        }
        // by amount
        if (type == 1) {
            if (posIndex > m_produceTypeSize.at(0) && posIndex <= m_vectorProduce.size()) {
                items[p.produceName] = p.price;
            } 
        }
        posIndex++;
    }
}

void ProduceByWeight::loadItems() {
    transferToMap(items, 0);
}
bool ProduceByWeight::addItem(const std::string &itemName, const double &price) {
    std::vector<produce>::iterator produceIt = m_vectorProduce.begin();
    m_produce.produceName = itemName;
    m_produce.produceType = "weight";
    m_produce.price = price;

    // insert newly created weight item in the begging of vector
    m_vectorProduce.insert(produceIt, m_produce);  
    m_produceTypeSize.at(0)++;  // might conflict later
    items[itemName] = price;
    saveItems();
    return true;
}

bool ProduceByWeight::removeItem(const std::string &itemName) {
    std::map<std::string, double>::iterator it{items.begin()};
    while (it != items.end()) {
        
        if (caseInsStringCmp(it->first, itemName)) {
        // if (it->first == itemName) {
            // do something
            items.erase(it);
            std::cout << std::endl;
            saveItems();
            return true;
        }
        it++;
    }
    return false;
}

void ProduceByWeight::showItems() {

    transferToMap(items, 0);
    std::cout << "Items charge by weight." << std::endl;
    std::cout << std::endl;
    std::map<std::string, double>::iterator it = items.begin();

    std::cout << fmt::format("{:-<20}", "") << std::endl;
    std::cout << fmt::format("{:<10}{:>10}", "Items", "$/lb") << std::endl;
    std::cout << fmt::format("{:-<20}", "");
    std::cout << std::endl;

    while (it != items.end()) {
        std::cout << fmt::format("{:<10}{:>10}", it->first, it->second) << std::endl;
        it++;
    }
    std::cout << std::endl;
}

void ProduceByWeight::saveItems() {
    std::ofstream outputFile;
    outputFile.open(m_filePWeight, std::ios::out);
    if (outputFile.is_open()) {
        for (const auto &[key, value]: items) {
            outputFile << fmt::format("{:<10}{:>5}", key, value) << std::endl;
        }
    } else { std::cout << fmt::format("file {} couldn't be open\n", m_filePWeight); }
}
std::map<std::string, double> & ProduceByAmount::getItems() {
    return items;
}

void ProduceByAmount::loadItems() {
    transferToMap(items, 1);
}

void ProduceByAmount::showItems() {

    transferToMap(items, 1);
    std::cout << "Items charge by amount." << std::endl;
    std::cout << std::endl;
    std::map<std::string, double>::iterator it = items.begin();

    std::cout << fmt::format("{:-<20}", "") << std::endl;
    std::cout << fmt::format("{:<10}{:>10}", "Items", "$ each") << std::endl;
    std::cout << fmt::format("{:-<20}", "");
    std::cout << std::endl;

    while (it != items.end()) {
        std::cout << fmt::format("{:<10}{:>10}", it->first, it->second) << std::endl;
        it++;
    }
}

void ProduceByAmount::saveItems() {
    std::ofstream outputFile;
    outputFile.open(m_filePAmount, std::ios::out);
    if (outputFile.is_open()) {
        for (const auto &[key, value]: items) {
            outputFile << fmt::format("{:<10}{:>5}", key, value) << std::endl;
        }
    } else { std::cout << fmt::format("file {} couldn't be open\n", m_filePAmount); }
}

// addItem might not have time to fully implement
bool ProduceByAmount::addItem(const std::string &itemName, const double &price) {
    m_produce.produceName = itemName;
    m_produce.produceType = "amount";
    m_produce.price = price;
    m_vectorProduce.push_back(m_produce);
    m_produceTypeSize.at(1)++; // might conflict later
    items[itemName] = price;
    saveItems();
    return true;
}

// needed more time to implement this for management
// when manager logins.. he/she can add/remove inventory
bool ProduceByAmount::removeItem(const std::string &itemName) {
    // std::vector<produce>::iterator produceIt = m_vectorProduce.begin();
    // size_t index = m_vectorProduce.size() - m_produceTypeSize.at(1);

    // while (produceIt != m_vectorProduce.end()) {
    std::map<std::string, double>::iterator it{items.begin()};
    while (it != items.end()) {
        
        if (caseInsStringCmp(it->first, itemName)) {
        // if (it->first == itemName) {
            // do something
            items.erase(it);
            std::cout << std::endl;
            saveItems();
            return true;
        }
        it++;
    }
    return false;
}