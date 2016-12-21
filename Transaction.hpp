////////////////////////////////////////////////////////////////////////////////
// Main File:        main.cpp
// This File:        Transaction.hpp
// Other Files:      User.hpp, User.cpp, Event.hpp, Event.cpp, Transaction.cpp
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

#ifndef CS_368_TRANSACTION_HPP
#define CS_368_TRANSACTION_HPP

#include "User.hpp"
#include "Event.hpp"
#include <iostream>
#include <vector>
#include <ctime>

class User;

class Event;

/**
 * The Transaction class, which stores the information of a transaction, with
 * involved user, event or target user, the amount of money due and paid, and
 * the transaction time.
 */
class Transaction {
private:
    User *user;  // the payer
    Event *event;  // event of event transaction
    double balance;  // how much user should pay
    double payment;  // how much user actually pays
    User *target;  // target user of personal transaction
    time_t created;  // time of transaction

public:
    /**
     * constructor of Transaction object
     *
     * @param user
     * @param event
     * @param balance
     * @param payment
     * @param target
     */
    Transaction(User *user, Event *event, double balance, double payment,
                User *target = NULL);

    /**
     * getter for balance
     *
     * @return balance due
     */
    double getBalance();

    /**
     * getter for payment
     *
     * @return payment made
     */
    double getPayment();

    /**
     * getter for payer
     *
     * @return payer's User object
     */
    User *getUser();

    /**
     * getter for event
     *
     * @return the event of the transaction
     */
    Event *getEvent();

    /**
     * getter for target
     *
     * @return the target user's User object
     */
    User *getTarget();

    /**
     * setter for event
     *
     * @param event the event
     */
    void setEvent(Event *event);

    /**
     * print detail of a transaction
     * @param indent the indent string
     * @param self decides if program uses "You" or the user's full name
     */
    void printDetails(std::string indent, bool self = false);
};

#endif //CS_368_TRANSACTION_HPP
