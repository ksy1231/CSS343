/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "history.h"
#include <iostream>

// Prints out the whole transaction history for a customer
void History::print() const {
	// For each transaction in history, cout it
	for (int i = static_cast<int>(history.size() - 1); i >= 0; --i)
		cout << history[i] << endl;
}

// Adds an additional history entry for the customer
void History::add(const string& customerTransaction) {
	history.push_back(customerTransaction);
}
