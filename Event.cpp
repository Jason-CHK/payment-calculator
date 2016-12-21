////////////////////////////////////////////////////////////////////////////////
// Main File:        main.cpp
// This File:        Event.cpp
// Other Files:      User.hpp, User.cpp, Event.hpp, Transaction.hpp,
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

#include "Event.hpp"

/**
 * constructor
 * @param name
 * @param records
 *
 */
Event::Event(std::string name, std::vector<Transaction *> records) {
    Event::name = name;
    Event::records = records;
    time(&created);
}

/**
 * get the time the event created
 * @return time as string
 */
std::string Event::getCreateTime() {
    return ctime(&created);
}

/**
 * get name of the event
 * @return name of event
 */
std::string Event::getName() {
    return name;
}

/**
 * get records of the event
 * @return records
 */
std::vector<Transaction *> *Event::getRecords() {
    return &records;
}
