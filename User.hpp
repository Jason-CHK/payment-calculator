////////////////////////////////////////////////////////////////////////////////
// Main File:        main.cpp
// This File:        User.hpp
// Other Files:      User.cpp, Event.hpp, Event.cpp, Transaction.hpp,
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

#ifndef CS_368_USER_HPP
#define CS_368_USER_HPP

#include "Event.hpp"
#include "Transaction.hpp"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>

class Transaction;

class Event;

/**
 * The User class, which stores user's username, full name and full transaction
 * list, as well as a full list of users.
 */
class User {
private:
    std::string username;  // username
    std::string name;  // full name
    std::vector<Transaction *> records;  // full transaction history
    static std::vector<User *> users; // all user list

public:
    /**
     * Constructor for the User class
     *
     * @param username username
     * @param name full name
     */
    User(std::string username, std::string name);

    /**
     * getter for username
     *
     * @return username
     */
    std::string getUsername();

    /**
     * getter for full name
     *
     * @return full name
     */
    std::string getName();

    /**
     * getter for transaction list
     *
     * @return transaction list
     */
    std::vector<Transaction *> *getRecords();

    /**
     * display all transaction list
     *
     * @param indent the indent string
     */
    void printRecords(std::string indent);

    /**
     * calculate and optionally display user's debt with specific target
     *
     * @param targetName target's username
     * @param print specify if print out details, default not to print
     * @param indent the indent string, only useful when printing details
     * @return the debt user own target, can be negative
     */
    double targetDebts(std::string targetName, bool print = false,
                       std::string indent = "");

    /**
     * print out all the debts between every other user
     *
     * @param indent the indent string
     */
    void printDebts(std::string indent);

    /**
     * get user object by username
     *
     * @param username username
     * @return the user object
     */
    static User *getUserByUsername(std::string username);
};

#endif //CS_368_USER_HPP
