#include "ManagerClass.hpp"


managerInfo Manager::getManagerInfo() const {
    return m_managerInfo;
}

void Manager::setManagerInfo(const std::string &name, const std::string &username, const std::string &password) {
    m_managerInfo.m_name = name;
    m_managerInfo.loginInfo[username] = password;
}
// process password input
std::string Manager::inputPassword() {
    std::string password{};
    char input;

    do {
        input = getch();
        if (input == BACKSPACE) {
            if (password.length() > 0) {
                std::cout << "\b \b";
                password = password.substr(0, password.length() - 1);
            }
        } else if (input != ENTER) {  // to prevent the \r char from being add to password
            password.push_back(input);
            std::cout << "*";
        }
    }
    while(input != ENTER);

    input = 0; // clears the remaining char of input

    if (password.find_first_of(" !#$%^&*()-=_+") != std::string::npos) {
        std::cout << fmt::format("\nSorry, password: {} contains invalid character(s)\n", password);
    }
    std::cout << std::endl;
    return password;
}

bool Manager::managerLogin() {
    std::string username, password;
    char choice;

    std::cout << "Username: ";
    std::cin >> username;
    for (const auto &[key, value] : m_managerInfo.loginInfo) {
        if (username == key) {
            for (size_t tries{1}; tries <= 3; tries++){
                std::cout << "Password: ";
                password = inputPassword();
                if (password == value) { break; }
                std::cout << "Incorrect password. Try again\n";
            }
        }
    }
    // }
    //     else {
    //         std::cout << "Sorry, you're not in managers list" << std::endl;
    //         return false;
    //     }
    return true;
}

// change existing user password
void Manager::changePassword() {
    std::string password;
    std::string username;
    bool match{false};
    std::cout << "Username: ";
    std::cin >> username;
    size_t index{0};
    for (const auto &[key, value] : m_managerInfo.loginInfo) {
        if (username == key) {
            std::cout << "Enter old password: ";
            password = inputPassword();
            if (password == value) {
                std::cout << "Enter new password: ";
                password = inputPassword();
                std::string confirmPass = inputPassword();
                if (password == confirmPass) {
                    m_managerInfo.loginInfo[key] = password;
                }
            }
        } else { std::cout << "Incorrect password. Try again" << std::endl; }
    }
}
void Manager::saveManagerInfo(const std::string &filename) {
    std::ofstream outputFile;

    outputFile.open(filename, std::ios::out | std::ios::binary);
    if (outputFile.is_open()) {
        for (char c : m_managerInfo.m_name) {
            c += 127;
            outputFile.write(&c, sizeof(char));
        }
        outputFile << '\0';

        for (MSS::iterator i = m_managerInfo.loginInfo.begin(); i != m_managerInfo.loginInfo.end(); ++i)
        {
            for (char c : i->first) {
                c += 127;
                outputFile.write(&c, sizeof(char)); 
            }
            outputFile << '\0';

            for (char c : i->second) {
                c += 127;
                outputFile.write(&c, sizeof(char));
            }
            outputFile << '\0';
        }
    }
    else {
        std::cout << "Could not create file " + filename + "\n";
    }
}
void Manager::loadManagerInfo(const std::string &filename) {
    std::string name, username, password;
    std::ifstream inputFile;
    char c;
    bool nullFound{false};
    enum field { NAME, USERNAME, PASSWORD };

    int posField = field::NAME;

    std::cout << sizeof(MSS) << std::endl;
    inputFile.open(filename, std::ios::in | std::ios::binary);
    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            inputFile.read(&c, sizeof(char));
            if (c == '\0') {
                posField++;
                continue;
            }
            else if (posField == field::NAME) {
                name.push_back(c-127);
            } else if (posField == field::USERNAME) {
                username.push_back(c-127);
            } else if (posField == field::PASSWORD) { password.push_back(c-127); }
        }
    }
    else {
        std::cout << "Could not read file " + filename + "\n";
    }
    m2_managerInfo.m_name = name;
    m2_managerInfo.loginInfo[username] = password;
}

void Manager::viewManagerInfo() {
    std::cout << "Name: " << m2_managerInfo.m_name << std::endl;
    for (const auto &[key, value] : m2_managerInfo.loginInfo) {
        std::cout << "Username: " << key << std::endl;
        std::cout << "Password: " << value << std::endl;
    }
}

bool Manager::deleteMember(const std::string &name) {
    std::string firstName;
    for (auto itCustomerInfo{m_customersDatabase.begin()}; itCustomerInfo != m_customersDatabase.end();) {
        size_t firstNameLocation = itCustomerInfo->fullName.find_first_of(" ");
        firstName = itCustomerInfo->fullName.substr(0, firstNameLocation);
        if (caseInsStringCmp(name, firstName)) {
            m_customersDatabase.erase(itCustomerInfo);
            saveCustomersDatabase();
            return true;
        }
        itCustomerInfo++;
    }
    return true;
}

// void addItemWeight(ProduceByWeight &weight, std::string itemToAdd, double price) {
//     m_isManager = true;
//     weight.addItem(itemToAdd, price);
// }

// void addItemAmount(ProduceByAmount &amount, std::string itemToAdd, double price) {
//     m_isManager = true;
//     amount.addItem(itemToAdd, price);
// }

const std::array<std::string, 3> Manager::processAddItems(const std::string &command) {
    int wordCounter{1};
    std::string word;
    std::array<std::string, 3> commandLine;

    for (const char &c : command) {
        if (c == ' ') {
            commandLine.at(wordCounter-1) = word;
            wordCounter++;
            word.clear();
            continue;
        }
        word += c; 
    }
    commandLine.at(wordCounter-1) = word;
    return commandLine;
}
void Manager::removeItems(ProduceByAmount &amount, ProduceByWeight &weight, const std::string &itemToDel) {
    if (amount.removeItem(itemToDel)) {
        std::cout << fmt::format("Item {} removed from amount", itemToDel) << std::endl;

    } else if (weight.removeItem(itemToDel)) {
        std::cout << fmt::format("Item {} removed from weight", itemToDel) << std::endl;
    }
}