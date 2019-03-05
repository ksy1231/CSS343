/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_CUSTOMER_H
#define ASS4_CUSTOMER_H

#include "history.h"
#include <string>

using namespace std;

class Customer {
public:
	// Constructor
	Customer(int ID, string customerName);
	// Empty destructor
	virtual ~Customer();
	// Print this customer's history
	void printHistory() const;
	// Add a new transaction into this customer history
	void addIntoHistory(const string& customerTransaction);
	// Get customerID
	int getID() const;

private:
	int ID; 
	// Composite string of customer's firstname and last name
	string customerName; 
	History history;
};

#endif // ASS4_CUSTOMER_H
