////////////////////////////////////////////////////////////////////////////////
// Main File:        main.cpp
// This File:        Transaction.cpp
// Other Files:      User.hpp, User.cpp, Event.hpp, Event.cpp, Transaction.hpp
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

#include "Transaction.hpp"

std::string indent;

/**
 * constrcutor
 * @param user
 * @param event
 * @param balance
 * @param payment
 * @param target
 */
Transaction::Transaction(User *user, Event *event, double balance,
                         double payment, User *target) {
    Transaction::user = user;
    Transaction::event = event;
    Transaction::balance = balance;
    Transaction::payment = payment;
    Transaction::target = target;
    time(&created);
}

/**
 * getter for balance
 *
 * @return balance due
 */
double Transaction::getBalance() {
    return balance;
}

/**
 * getter for payment
 *
 * @return payment made
 */
double Transaction::getPayment() {
    return payment;
}

/**
 * get user
 * @return user
 */
User *Transaction::getUser() {
    return user;
}

/**
 * get event
 * @return event
 */
Event *Transaction::getEvent() {
    return event;
}

/**
 * get target user
 * @return the target user's User object
 */
User *Transaction::getTarget() {
    return target;
}

/**
 * setup the event
 * @param event
 */
void Transaction::setEvent(Event *event) {
    Transaction::event = event;
}

/**
 * print the details of transaction
 * @param indent the indented string
 * @param self decides if program uses "You" or the user's full name
 */
void Transaction::printDetails(std::string indent, bool self) {
    if (target != NULL) {
        std::string targetName = target->getName();
        if (payment > 0) {
            std::cout << indent << "You paid " << targetName << " " << payment
                      << " at the time of " << ctime(&created);
        } else {
            std::cout << indent << targetName << " paid You " << -payment
                      << " at the time of " << ctime(&created);
        }
    } else {
        if (self) {
            std::cout << indent << "You";
        } else {
            std::cout << indent << user->getName();
        }
        std::cout << " paid " << payment << " out of " << balance
                  << " in the event \"" << event->getName()
                  << "\" at the time of " << ctime(&created);
    }
}
