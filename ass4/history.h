/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_HISTORY_H
#define ASS4_HISTORY_H

#include <string>
#include <vector>

using namespace std;

class History {
public:
	// Constructor
	History() = default;;
	// Destructor
	virtual ~History() = default;;
	// Prints the history vector
	void print() const;
	// Adds a new customer transaction, passed in as a string
	void add(const string& customerTransaction);

private:
	vector<string> history; 
};

#endif // ASS4_HISTORY_H
