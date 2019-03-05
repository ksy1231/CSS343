/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "customer.h"
#include <iostream>

// Constructor for a customer
Customer::Customer(int ID, string customerName)
	: ID(ID), customerName(std::move(customerName)) { }

// Destructor
Customer::~Customer() = default;

// Print the customer history
void Customer::printHistory() const {
	cout << "History of " << this->ID << " " << this->customerName << endl;
	history.print();
	cout << endl;
}

// Add history for the customer
void Customer::addIntoHistory(const string& customerTransaction) {
	// Call the History class add() function to add a new customer transaction
	history.add(customerTransaction);
}

// Get customerID
int Customer::getID() const {
	return this->ID;
}
