/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "store.h"
#include <string>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void runStore() {
	Store store;
	string movieData = "data4movies.txt";
	string customerData = "data4customers.txt";
	string commandData = "data4commands.txt";
	store.populateCustomer(customerData);
	store.populateMovie(movieData);
	store.commandHandler(commandData);
}

int main() {
	runStore();
	return 0;
}
