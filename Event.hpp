////////////////////////////////////////////////////////////////////////////////
// Main File:        main.cpp
// This File:        Event.hpp
// Other Files:      User.hpp, User.cpp, Event.cpp, Transaction.hpp,
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

#ifndef CS_368_EVENT_HPP
#define CS_368_EVENT_HPP

#include "User.hpp"
#include "Transaction.hpp"
#include <string>
#include <vector>
#include <ctime>

class User;

class Transaction;

/**
 * The Event class, which stores the information of an event, with the event
 * name, creation time and transaction list of each involved user.
 */
class Event {
private:
    std::string name;  // name of event
    time_t created;  // time of event
    std::vector<Transaction *> records;  // list of transactions

public:
    /**
     * constructor
     *
     * @param name name of event
     * @param records transaction list
     */
    Event(std::string name, std::vector<Transaction *> records);

    /**
     * getter for creation time
     *
     * @return formatted creation time
     */
    std::string getCreateTime();

    /**
     * getter for event name
     *
     * @return event name
     */
    std::string getName();

    /**
     * getter for transaction list
     *
     * @return transaction list of the event
     */
    std::vector<Transaction *> *getRecords();
};

#endif //CS_368_EVENT_HPP
