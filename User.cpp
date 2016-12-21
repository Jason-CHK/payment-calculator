////////////////////////////////////////////////////////////////////////////////
// Main File:        main.cpp
// This File:        User.cpp
// Other Files:      User.hpp, Event.hpp, Event.cpp, Transaction.hpp,
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

std::vector<User *> User::users;

/**
 * constructor
 * @param username
 * @param name
 */
User::User(std::string username, std::string name) {
    User::username = username;
    User::name = name;
    User::records = std::vector<Transaction *>();
    users.push_back(&*this);
}

/**
 * get the username
 * @return username
 */
std::string User::getUsername() {
    return username;
}

/**
 * get name
 * @return name
 */
std::string User::getName() {
    return name;
}

/**
 * get records
 * @return records
 */
std::vector<Transaction *> *User::getRecords() {
    return &records;
}

/**
 * print all transaction lists
 * @param indent the indented string
 */
void User::printRecords(std::string indent) {
    std::cout << indent << std::endl;
    for (int i = 0; i < records.size(); ++i) {
        records[i]->printDetails(indent, true);
    }
    if (!records.size()) {
        std::cout << indent << "There is no transaction." << std::endl;
    }
}

/**
 * the debt relation between two users in a single event
 * @param selfTrans
 * @param tgtTrans
 * @param print
 * @param indent
 * @return debt
 */
double
singleDebt(Transaction *selfTrans, Transaction *tgtTrans, bool print = false,
           std::string indent = "") {
    double payment = selfTrans->getPayment();
    double balance = selfTrans->getBalance();
    double tgtPayment = tgtTrans->getPayment();
    double tgtBalance = tgtTrans->getBalance();
    std::string name = tgtTrans->getUser()->getName();
    Event *event = selfTrans->getEvent();

    double debt = std::min(fabs(payment - balance),
                           fabs(tgtPayment - tgtBalance));
    if (payment < balance) {
        if (print) {
            std::cout << indent << "You owe " << name << " " << debt;
        }
    } else {
        if (print) {
            std::cout << indent << name << " owes you " << debt;
        }
        debt = -debt;
    }
    if (print) {
        std::cout << " in the event \"" << event->getName()
                  << "\" at the time of "
                  << event->getCreateTime();
    }

    return debt;
}

/**
 * user's total debt for other user
 * @param targetName
 * @param print
 * @param indent
 * @return total debt
 */
double
User::targetDebts(std::string targetName, bool print, std::string indent) {
    if (print) {
        std::cout << indent << std::endl;
    }
    double totalDebts = 0;
    User *target = getUserByUsername(targetName);

    if (target == NULL) {
        if (print) {
            std::cout << indent << "Target user does not exist." << std::endl;
        }
        return 0;
    }

    if (target == this) {
        if (print) {
            std::cout << indent << "No debt for yourself." << std::endl;
        }
        return 0;
    }

    bool hasTransaction = false;
    for (int i = 0; i < records.size(); ++i) {
        // personal transaction
        if (records[i]->getTarget() != NULL) {
            if (target == records[i]->getTarget()) {
                hasTransaction = true;
                totalDebts -= records[i]->getPayment();
                if (print) {
                    records[i]->printDetails(indent, true);
                }
            }
            continue;
        }

        double payment = records[i]->getPayment();
        double balance = records[i]->getBalance();
        if (payment == balance) {
            continue;
        }
        std::vector<Transaction *> *transactions
                = records[i]->getEvent()->getRecords();
        for (int j = 0; j < transactions->size(); ++j) {
            User *user = (*transactions)[j]->getUser();
            if (user == target) {
                Transaction *transaction = (*transactions)[j];
                double tgtPayment = transaction->getPayment();
                double tgtBalance = transaction->getBalance();
                if (tgtPayment == tgtBalance) {
                    continue;
                }

                // there is a one way debt
                if ((payment - balance) * (tgtPayment - tgtBalance) < 0) {
                    hasTransaction = true;
                    totalDebts += singleDebt(records[i], transaction, print,
                                             indent);
                }
            }
        }
    }

    if (hasTransaction && print) {
        std::cout << indent << std::endl;
    }

    if (!hasTransaction || totalDebts == 0) {
        if (print) {
            std::cout << indent << "There is no debt between you and "
                      << target->getName() << "." << std::endl;
        }
        return 0;
    }

    if (totalDebts > 0) {
        if (print) {
            std::cout << indent << "You owe " << target->getName() << " "
                      << totalDebts;
        }
    } else {
        if (print) {
            std::cout << indent << target->getName() << " owes you "
                      << -totalDebts;
        }
    }
    if (print) {
        std::cout << std::endl;
    }
    return totalDebts;
}

/**
 * print details of debts
 * @param indent
 */
void User::printDebts(std::string indent) {
    std::cout << indent << std::endl;
    bool hasDebt = false;
    double totalDebt = 0;
    for (int i = 0; i < users.size(); ++i) {
        User *target = users[i];
        if (target == this) {
            continue;
        }
        double debt = targetDebts(target->getUsername());
        if (debt != 0) {
            totalDebt += debt;
            hasDebt = true;
            if (debt > 0) {
                std::cout << indent << "You owe " << target->getName() << " "
                          << debt;
            } else {
                debt = -debt;
                std::cout << indent << target->getName() << " owes you "
                          << debt;
            }
            std::cout << std::endl;
        }
    }
    if (!hasDebt) {
        std::cout << indent << "There is not any debt." << std::endl;
        return;
    }

    std::cout << indent << std::endl;
    if (totalDebt >= 0) {
        std::cout << indent << "You are owing " << totalDebt << " in total."
                  << std::endl;
    } else {
        std::cout << indent << "You are owned " << -totalDebt << " in total."
                  << std::endl;
    }
}

/**
 * get user by username
 * @param username
 * @return user object, null if there is no user match the input name
 */
User *User::getUserByUsername(std::string username) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            return users[i];
        }
    }
    return NULL;
}