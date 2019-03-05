/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "customerlist.h"
#include <iostream>

using namespace std;

// Default constructor
CustomerList::CustomerList() = default;

// Destructor that will delete all customers. Loop through each bucket
// and delete each customer object there
CustomerList::~CustomerList() {
	// Delete each Customer
	// for each bucket in the array
	for (auto &arrayIndex : custList) {
		for (auto &vectorIndex : arrayIndex) {
			// Delete the *newed* customer
			delete vectorIndex;
			// Don't have to set nullptr since we passed it in directly
		}
	}
}

// Adding a new customer into the list
// Handles duplications and ID validation
bool CustomerList::addCustomer(int ID, const string& customerName) {
	// Make sure ID is 4 digits
	if (ID > 999 && ID < 10000) {
		int index = hash(ID);
		// Find if customer exists first
		for (auto &i : custList[index]) {
			// if the ID exists, return false
			if (i->getID() == ID)
				cout << "ERROR: Customer " << ID << " already exists." << endl;
			return false;
		}
		// Push the new customer into the correct bucket
		custList[index].push_back(new Customer(ID, customerName));
		return true;
	}
	cout << "ERROR: " << ID << " is invalid. Needs to be 4 digits." << endl;
	return false;
}

// Hashing the customer based off of the hash value
int CustomerList::hash(int ID) const {
	return ID % HASH_MOD;
}

// Get a customer by ID, will return nullptr if ID does not exist
Customer* CustomerList::getCustomer(int ID) {
	int index = hash(ID);
	// Find if customer exists first
	for (auto &i : custList[index]) {
		if (i->getID() == ID)  // If the bucket has ID
			return i;  // Return Customer*
	}
	return nullptr;
}
