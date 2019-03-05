/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_STORE_H
#define ASS4_STORE_H

#include "movielist.h"
#include "customerlist.h"
#include <iostream>
#include <fstream>

using namespace std;

class Store {
public:
	// Constructor
	Store();
	// Destructor
	virtual ~Store();
	// Populate the movie list from the given file
	void populateMovie(string& file);
	// Reads in the customer list from a file and adds it to the
	// customer list object
	void populateCustomer(string& file);
	// Help action for borrowing, returning, and printing
	void commandHandler(string& file);
	// Print all customers' history
	void printCustomerHistory(const string& customer);
	// Prints out the inventory in a *FAnCy* format
	void printInventory();
	// Help customer to borrow movie
	bool borrowMovie(const string& command);
	// Help customer to return movie
	bool returnMovie(const string& command);

private:
	CustomerList customerList; 
	MovieList movieList;
	// Helper method for populateMovie
	// This method will extract each token and send it to the movie list
	void addMovieToMovieList(vector<string> tokens);
};

#endif // ASS4_STORE_H
