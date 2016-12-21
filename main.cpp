////////////////////////////////////////////////////////////////////////////////
// Main File:        main.cpp
// This File:        main.cpp
// Other Files:      User.hpp, User.cpp, Event.hpp, Event.cpp, Transaction.hpp,
//                   Transaction.cpp
//
// Author:           Jason Cheng & Zhifeng Shi
// CS email:         jcheng@cs.wisc.edu & zhifeng@cs.wisc.edu
//
// Course:           CS 368 (C++)
// Section:          1
// Instructor:       Gerald
//
// Description:      A payment calculator and recording tool that can take
//                   payment information and calculate debts between users.
//
// Sources:
//
// URL(s) of sources:
//////////////////////////// 80 columns wide ///////////////////////////////////

#include "User.hpp"
#include "Event.hpp"
#include "Transaction.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

const int DIVIDE_LINE_WIDTH = 40;

int level;
extern std::string indent;

/**
 * update indent for format "|"
 *
 */
void updateIndent() {
    indent = "";
    for (int i = 0; i < level; i++) {
        indent += "| ";
    }
}

/**
 * remove spaces in front and end
 * @param str
 * @return string with no space
 */
std::string trim(std::string const &str) {
    if (str.empty())
        return str;

    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first =
            firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

/**
 * format
 * @param text
 * @param line
 * @param width
 * @return string
 */
std::string
divideLine(std::string text, char line = '-', int width = DIVIDE_LINE_WIDTH) {
    std::string formattedText = "";
    int lineWidth = (width - (int) text.length()) / 2 - 1;
    for (int i = 0; i < lineWidth; i++) {
        formattedText += line;
    }
    if (text.length() < width - 3) {
        formattedText += ' ';
    }
    formattedText += text;
    if (text.length() < width - 3) {
        formattedText += ' ';
    }
    if ((width - (int) text.length()) % 2 && text.length() < width - 3) {
        formattedText += line;
    }
    for (int i = 0; i < lineWidth; i++) {
        formattedText += line;
    }
    return formattedText;
}

/**
 * get string from user input which has been "trimed"
 *
 * @return string
 */
std::string getString() {
    std::string input;
    getline(std::cin, input);
    return trim(input);
}

/**
 * get the number for command
 *
 * @param prompt
 * @param min
 * @param max
 * @return int number
 */
int getInt(std::string prompt, int min = -1, int max = -1) {
    std::cout << indent << prompt;

    std::string str = "";
    int input = -1;
    bool success = false;
    while (!success) {
        success = true;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cout << indent << "Invalid input, must be integer: ";
            success = false;
        } else if ((min != -1 && input < min) || (max != -1 && input > max)) {
            std::cout << indent << "Invalid input, must in range " << min << "~"
                      << max << ": ";
            success = false;
        }
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }
    return input;
}

/**
 * get the double number for money amount
 *
 * @param prompt
 * @param min
 * @param max
 * @return double amount
 */
double getDouble(std::string prompt, double min = -1, double max = -1) {
    std::cout << indent << prompt;

    std::string str = "";
    double input = -1;
    bool success = false;
    while (!success) {
        success = true;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cout << indent << "Invalid input, must be double: ";
            success = false;
        } else if (min != -1 && max != -1 && (input < min || input > max)) {
            std::cout << indent << "Invalid input, must in range " << min
                      << " ~ " << max << ": ";
            success = false;
        } else if (min != -1 && input < min) {
            std::cout << indent << "Invalid input, must larger than " << min
                      << ": ";
            success = false;
        } else if (max != -1 && input > max) {
            std::cout << indent << "Invalid input, must smaller than " << max
                      << ": ";
            success = false;
        }
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }
    return input;
}

/**
 * the mean for user
 *
 * @return user's choice
 */
int menu() {
    std::string prompt = "\n";
    prompt += indent + divideLine("Menu", '=') + "\n";
    prompt += indent + "1. Create an event\n";
    prompt += indent + "2. Create a user\n";
    prompt += indent + "3. Login\n";
    prompt += indent + "4. Load data from file\n";
    prompt += indent + "5. Save data to file\n";
    prompt += indent + "6. Exit\n";
    prompt += indent + "Your choice: ";
    return getInt(prompt, 1, 6);
}

/**
 * create user instance
 * @param username
 * @return newly created user
 */
User *createUser(std::string username = "") {
    std::cout << indent << std::endl;

    std::cout << indent << '+' << divideLine("Creating User") << std::endl;

    ++level;
    updateIndent();

    if (username == "") {
        std::cout << indent << "Please enter username: ";
        username = getString();
        User *user = User::getUserByUsername(username);
        if (user != NULL) {
            std::cout << indent << "User already exists." << std::endl;

            --level;
            updateIndent();

            std::cout << indent << '+' << divideLine("User Not Created")
                      << std::endl;
            return user;
        }
    }
    std::cout << indent << "Please enter full name: ";
    std::string fullName = getString();

    --level;
    updateIndent();

    std::cout << indent << '+' << divideLine("User Created") << std::endl;

    return new User(username, fullName);
}

/**
 * create transaction instance
 *
 * @return newly created transaction
 */
Transaction *createTransaction() {
    std::cout << indent << std::endl;

    std::cout << indent << '+' << divideLine("Creating Transaction")
              << std::endl;

    ++level;
    updateIndent();

    std::string username;
    User *user = NULL;
    while (user == NULL) {
        std::cout << indent << "Which username? ";
        username = getString();
        user = User::getUserByUsername(username);
        if (user == NULL) {
            std::cout << indent << "Username " << username
                      << " does not exist, do you want to create one? (y/N) ";
            std::string choice = getString();
            if (choice[0] == 'y' || choice[0] == 'Y') {
                user = createUser(username);
                std::cout << indent << std::endl;
            } else {
                --level;
                updateIndent();

                std::cout << indent << '+'
                          << divideLine("Transaction Not Created") << std::endl;
                return NULL;
            }
        }
    }
    double balance = getDouble("How much should you pay? ", 0);
    double payment = getDouble("How much did you pay? ", 0);

    Transaction *transaction = new Transaction(user, NULL, balance, payment);

    --level;
    updateIndent();

    std::cout << indent << '+' << divideLine("Transaction Created")
              << std::endl;

    return transaction;
}

/**
 * create event instance
 *
 * @return newly created event
 */
Event *createEvent() {
    std::cout << indent << std::endl;
    std::cout << indent << '+' << divideLine("Creating Event") << std::endl;

    ++level;
    updateIndent();

    // get event name
    std::cout << indent << "What's the name of the event?" << std::endl;
    std::string name;
    while (true) {
        std::cout << indent;
        name = getString();
        if (name != "") {
            break;
        }
        std::cout << indent << "Invalid name, cannot be empty: " << std::endl;
    }

    // get transactions
    bool hasCreatedTransaction = false;
    int choice = -1, totalPayment = 0, totalBalance = 0;
    std::vector<Transaction *> records = std::vector<Transaction *>();
    while (choice != 2) {
        std::string prompt = "\n";
        prompt += indent + "Please select your choice:\n";
        prompt += indent + "1. Add a transaction\n";
        prompt += indent + "2. Finish\n";
        prompt += indent + "Your choice: ";
        choice = getInt(prompt, 1, 2);
        switch (choice) {
            case 1: {
                Transaction *newTransaction = createTransaction();
                if (newTransaction != NULL) {
                    records.push_back(newTransaction);
                    totalPayment += newTransaction->getPayment();
                    totalBalance += newTransaction->getBalance();
                    hasCreatedTransaction = true;
                }
                break;
            }
            default: {
                bool shouldCreateEvent = true;
                if (!hasCreatedTransaction) {
                    std::cout << indent << std::endl;
                    std::cout << indent << "Did not add any transaction."
                              << std::endl;
                    shouldCreateEvent = false;
                }
                if (totalBalance != totalPayment) {
                    std::cout << indent
                              << "Total balance does not equal to total "
                              << "payment. Abort? (y/N) ";
                    std::string tmp = getString();
                    if (tmp[0] == 'y' || tmp[0] == 'Y') {
                        shouldCreateEvent = false;
                    } else {
                        choice = -1;
                    }
                }
                if (!shouldCreateEvent) {
                    --level;
                    updateIndent();

                    std::cout << indent << '+'
                              << divideLine("Event not created.") << std::endl;
                    return NULL;
                }
                break;
            }
        }
    }

    Event *event = new Event(name, records);
    for (int i = 0; i < records.size(); ++i) {
        records[i]->setEvent(event);
        records[i]->getUser()->getRecords()->push_back(records[i]);
    }

    --level;
    updateIndent();

    std::cout << indent << '+' << divideLine("Event Created") << std::endl;

    return event;
}

/**
 * print menu for user
 * @return user's choice
 */
int userMenu() {
    std::string prompt = "\n";
    prompt += indent + divideLine("User Menu", '=') + "\n";
    prompt += indent + "1. List transaction history\n";
    prompt += indent + "2. List user debts list\n";
    prompt += indent + "3. Show detail with specific user\n";
    prompt += indent + "4. Make transaction\n";
    prompt += indent + "5. Logout\n";
    prompt += indent + "Your choice: ";
    return getInt(prompt, 1, 6);
}

/**
 * create a transaction for user
 *
 * @param self
 */
void createPersonalTransaction(User *self) {
    std::cout << indent << std::endl;

    std::cout << indent << '+' << divideLine("Creating Personal Transaction")
              << std::endl;

    ++level;
    updateIndent();

    std::string username;
    User *target = NULL;
    while (target == NULL) {
        std::cout << indent << "Which username? ";
        username = getString();
        target = User::getUserByUsername(username);
        if (target == NULL) {
            std::cout << indent << "Username " << username
                      << " does not exist, do you want to create one? (y/N) ";
            std::string choice = getString();
            if (choice[0] == 'y' || choice[0] == 'Y') {
                target = createUser(username);
                std::cout << indent << std::endl;
            } else {
                --level;
                updateIndent();

                std::cout << indent << '+'
                          << divideLine("Transaction Not Created") << std::endl;
                return;
            }
        }
        if (target == self) {
            std::cout << indent << "Cannot make transaction to yourself."
                      << std::endl;

            --level;
            updateIndent();

            std::cout << indent << '+'
                      << divideLine("Transaction Not Created") << std::endl;
            return;
        }
    }
    std::string targetName = target->getName();
    double balance = 0;
    double payment = getDouble("How much did you pay " + targetName + "? ", 0);

    Transaction *selfTrans = new Transaction(self, NULL, balance, payment,
                                             target);
    Transaction *tgtTrans = new Transaction(target, NULL, balance, -payment,
                                            self);

    self->getRecords()->push_back(selfTrans);
    target->getRecords()->push_back(tgtTrans);

    --level;
    updateIndent();

    std::cout << indent << '+' << divideLine("Transaction Created")
              << std::endl;

    return;
}

/**
 * enter menu for user after login
 *
 */
void userMode() {
    std::cout << indent << std::endl;

    std::cout << indent << '+' << divideLine("User Mode") << std::endl;

    ++level;
    updateIndent();

    std::string username;
    User *user = NULL;
    while (user == NULL) {
        std::cout << indent << "Which username? ";
        username = getString();

        user = User::getUserByUsername(username);
        if (user == NULL) {
            std::cout << indent << "Username " << username
                      << " does not exist, do you want to create one? (y/N) ";
            std::string choice = getString();
            if (choice[0] == 'y' || choice[0] == 'Y') {
                user = createUser(username);
                std::cout << indent << std::endl;
            } else {
                --level;
                updateIndent();
                std::cout << indent << '+' << divideLine("User Mode Ends")
                          << std::endl;
                return;
            }
        }
    }

    // in user mode
    int choice = -1;
    while (choice != 5) {
        choice = userMenu();
        switch (choice) {
            case 1: {
                user->printRecords(indent);
                break;
            }
            case 2: {
                user->printDebts(indent);
                break;
            }
            case 3: {
                std::cout << indent << std::endl;
                std::cout << indent << "Which username? ";
                std::string target = getString();
                user->targetDebts(target, true, indent);
                break;
            }
            case 4: {
                createPersonalTransaction(user);
                break;
            }
            default: {
                break;
            }
        }
    }

    --level;
    updateIndent();

    std::cout << indent << '+' << divideLine("User Mode Ends") << std::endl;
}

/**
 * read data from file
 */
void readFromFile() {
    // TODO
    std::cout << indent << "Data file successfully read" << std::endl;
}

/**
 * write data to file
 */
void writeToFile() {
    // TODO
    std::cout << indent << "Successfully wrote to data file." << std::endl;
}

/**
 * main method for the payment calculator, displays menu and interact with user
 * @param argc
 * @param argv
 * @return 0 if succeed
 */
int main(int argc, char *argv[]) {
    level = 0;
    updateIndent();

    std::cout << indent << "Welcome to the payment calculator!" << std::endl;

    int choice = -1;

    while (choice != 6) {
        choice = menu();
        switch (choice) {
            case 1: {
                createEvent();
                break;
            }
            case 2: {
                createUser();
                break;
            }
            case 3: {
                userMode();
                break;
            }
            case 4: {
                readFromFile();
                break;
            }
            case 5: {
                writeToFile();
                break;
            }
            default: {
                std::cout << indent << std::endl;
                std::cout << indent
                          << "Thank you for using the payment calculator."
                          << std::endl;
                break;
            }
        }
    }
    return 0;
}
