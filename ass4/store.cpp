/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "store.h"
#include <iostream>
#include <sstream>
#include <string>

Store::Store() = default;

Store::~Store() = default;

// Helper method for populateMovie
// This method will extract each token and send it to the movie list
void Store::addMovieToMovieList(vector<string> tokens) {
	char genre;
	string director, title, majorActor;
	int quantity, year, month;
	// vector guarantees consistent numbering, index 0 = genre, 1 = quantity
	// 2 = director, 3 = title, and based on genre, index 4 is handled below
	genre = tokens[0][0];
	quantity = stoi(tokens[1]);
	director = tokens[2];
	title = tokens[3];
	// Check if classic movie, if so need to extract additional data
	// Major actor and month

	// Create vector to hold tokens of element 4
	vector<string> elementToken;
	string cToken;
	char delimeter = ' ';
	istringstream tokenStream(tokens[4]);
	// Break token up using space as delimeter
	while (getline(tokenStream, cToken, delimeter)) {
		elementToken.push_back(cToken);
	}
	if (elementToken.size() > 1) {
		// Getting major actor first and last name
		majorActor = elementToken[0] + " " + elementToken[1];
		// Getting month and convert to int
		month = stoi(elementToken[2]);
		// Get year and convert to int
		year = stoi(elementToken[3]);

		// Adding the movie to the movie list
		movieList.addMovie(genre, director,
			title, year, majorActor, month, quantity);
	}

	// Either a comedy or drama movie
	else {
		year = stoi(elementToken[0]);

		// Adding the movie to the movie list
		movieList.addMovie(genre, director, title, year, quantity);
	}

}

// Populate the movie list from the given file
void Store::populateMovie(string& filename) {
	// Opening movie source
	ifstream infile;
	infile.open(filename);
	// Check to make sure the file exists
	if (infile.fail()) {
		cout << "The file was not found." << endl;
		return;
	}
	// Creaating the delimeter to break up the string
	string delimiter = ", ";
	// String to catch the line
	string line;

	// Loop through each line in the file
	while (getline(infile, line)) {
		if (line.back() == '\r') {
			line = line.substr(0, line.length() - 1);
		}
		// Create a sstream on the line
		istringstream iss(line);
		// Keep track of position in the line
		size_t pos = 0;
		// Hold the current token
		string token;
		// Vector to hold all of the tokens found
		vector<string> tokenList;

		// Loop through each element in the line
		while ((pos = line.find(delimiter)) != string::npos) {
			token = line.substr(0, pos);
			// Adding token to vector
			tokenList.push_back(token);
			line.erase(0, pos + delimiter.length());
		}
		// Catching last token
		tokenList.push_back(line);
		// Calling helper to add movie to movielist
		addMovieToMovieList(tokenList);
		// Clear vector for next movie
		tokenList.clear();
	}
}

// Reads in the customer list from a file and adds it to the
// customer list object
void Store::populateCustomer(string & filename) {
	ifstream infile;
	infile.open(filename);
	// Check to make sure the file exists
	if (infile.fail()) {
		cout << "The file was not found." << endl;
		return;
	}
	string line;
	// Loop through each line in the file
	while (getline(infile, line)) {
		if (line.back() == '\r') {
			line = line.substr(0, line.length() - 1);
		}
		vector<string> tokenList;
		string token;
		char delimeter = ' ';
		istringstream tokenStream(line);
		// Break line up using space as delimeter
		while (getline(tokenStream, token, delimeter)) {
			tokenList.push_back(token);
		}
		int customerID = stoi(tokenList[0]);
		string customerName = tokenList[1] + " " + tokenList[2];
		customerList.addCustomer(customerID, customerName);
	}
}

// Help action for borrowing, returning, and printing
void Store::commandHandler(string& filename) {
	ifstream infile;
	infile.open(filename);
	// Check to make sure the file exists
	if (infile.fail()) {
		cout << "The file was not found." << endl;
		return;
	}
	string line;
	while (getline(infile, line)) {
		if (line.back() =='\r') {
			line = line.substr(0, line.length() - 1);
		}
		char command = line[0];
		switch (command) {
		case 'B':
			borrowMovie(line);
			break;
		case 'R':
			returnMovie(line);
			break;
		case 'I':
			printInventory();
			break;
		case 'H':
			printCustomerHistory(line);
			break;
		default:
			cout << "ERROR: '" << command << "' is not a valid command."
			    << endl;
			break;
		}
	}
}

// Print all customers' history
void Store::printCustomerHistory(const string & customer) {
	vector<string> tokenList;
	string token;
	char delimeter = ' ';
	istringstream tokenStream(customer);
	// Break line up using space as delimeter
	while (getline(tokenStream, token, delimeter)) {
		tokenList.push_back(token);
	}
	int customerID = stoi(tokenList[1]);

	Customer* customerPtr = customerList.getCustomer(customerID);
	// getCustomer() will return nullptr if it couldn't find it
	if (customerPtr == nullptr) {
		cout << "Customer with ID#" << customerID << " could not be found."
		    << endl;
		return;
	} else {  // else it did find it, print the history
		customerPtr->printHistory();
	}
}

// Calls printMovies which will print out the inventory
void Store::printInventory() {
	movieList.printMovies();
}

// Help customer to borrow movie
bool Store::borrowMovie(const string & command) {
	// Parse string
	vector<string> tokenList;
	string token;
	char delimeter = ' ';
	istringstream tokenStream(command);
	// Get the first four tokens, then proceed accordingly
	int count = 0;
	while (count < 4) {
		getline(tokenStream, token, delimeter);
		tokenList.push_back(token);
		++count;
	}
	// Grab movie information
	// and add to vector for further parsing depending on the movie type
	getline(tokenStream, token);
	tokenList.push_back(token);

	// Store information from vector
	string borrowCommand = tokenList[0];
	int customerId = stoi(tokenList[1]);
	char mediaType = tokenList[2][0];
	char genre = tokenList[3][0];
	// Need to check movie type before extracting information
	string movieInformation = tokenList[4];

	//Grab customer from customer ID
	Customer* customer = customerList.getCustomer(customerId);
	// Check if customer is in the system
	if (!customer) {
		cout << "ERROR: Customer '" << customerId << "' does not exist."
		    << endl;
		return false;
	}
	// Check if the media type is valid,
	// currently DVD 'D' is the only accepted type
	else if (mediaType != 'D') {
		cout << "ERROR: Type of media '" << mediaType << "' does not exist."
		    << endl;
		return false;
	}

	// Variables for drama and comedy
	string title;
	string director;
	int year;
	// Variables for classic
	vector<string> tList;
	string majorActor;
	int month;
	string tToken;
	char tDelimeter = ' ';
	istringstream tss(movieInformation);

	bool result;

	switch (genre) {
	case 'F':
		title = movieInformation.substr(0, movieInformation.find(", "));
		year = stoi(movieInformation.substr(movieInformation.find(", ") + 2));

		result = movieList.decrementMovie(mediaType, title, year);
		// Add transaction to customer history
		// if movie was removed from inventory
		if (result) {
			customer->addIntoHistory(borrowCommand + " " + mediaType + " "
			+ genre + " " + title + " " + to_string(year));
		} else {
			return false;
		}
		break;
	case 'D':
		director = movieInformation.substr(0, movieInformation.find(", "));
		title = movieInformation.substr(movieInformation.find(", ") + 2);
		title = title.substr(0, title.length() - 1);

		result = movieList.decrementMovie(mediaType, director, title);
		// Add transaction to customer history
		if (result) {
			customer->addIntoHistory(borrowCommand + " " + mediaType + " "
			+ genre + " " + director + " " + title);
		} else {
			return false;
		}
		break;
	case 'C':
		// Break line up using space as delimeter
		while (getline(tss, tToken, tDelimeter)) {
			tList.push_back(tToken);
		}

		month = stoi(tList[0]);
		year = stoi(tList[1]);
		majorActor = tList[2] + " " + tList[3];

		// Remove one movie from movie inventory
		result = movieList.decrementMovie(mediaType, month, year, majorActor);
		// Add transaction to customer history
		if (result) {
			customer->addIntoHistory(borrowCommand + " " + mediaType + " "
			+ genre + " " + to_string(month) + " " + to_string(year) + " "
			+ majorActor);
		} else {
			return false;
		}
		break;
	default:
		cout << "ERROR: '" << genre << "' is not a valid genre." << endl;
		break;
	}
	return true;
}

// Help customer to return movie
bool Store::returnMovie(const string & command) {
	// Parse string
	vector<string> tokenList;
	string token;
	char delimeter = ' ';
	istringstream tokenStream(command);
	// Get the first four tokens, then proceed accordingly
	int count = 0;
	while (count < 4) {
		getline(tokenStream, token, delimeter);
		tokenList.push_back(token);
		++count;
	}
	// Grab movie information
	// and add to vector for further parsing depending on the movie type
	getline(tokenStream, token);
	tokenList.push_back(token);

	// Store information from vector
	string returnCommand = tokenList[0];
	int customerId = stoi(tokenList[1]);
	char mediaType = tokenList[2][0];
	char genre = tokenList[3][0];
	// Need to check movie type before extracting information
	string movieInformation = tokenList[4];

	//Grab customer from customer ID
	Customer* customer = customerList.getCustomer(customerId);
	// Check if customer is in the system
	if (!customer) {
		cout << "ERROR: Customer '" << customerId << "' does not exist."
		    << endl;
		return false;
	}
	// Check if the media type is valid,
	// currently DVD 'D' is the only accepted type
	else if (mediaType != 'D') {
		cout << "ERROR: Type of media '" << mediaType << "' does not exist."
		    << endl;
		return false;
	}

	// Variables for drama and comedy
	string title;
	string director;
	int year;
	// Variables for classic
	vector<string> tList;
	string majorActor;
	int month;
	string tToken;
	char tDelimeter = ' ';
	istringstream tss(movieInformation);

	bool result;

	switch (genre) {
	case 'F':
		title = movieInformation.substr(0, movieInformation.find(", "));
		year = stoi(movieInformation.substr(movieInformation.find(", ") + 2));

		result = movieList.incrementMovie(mediaType, title, year);
		// Add transaction to customer history
		// if movie was removed from inventory
		if (result) {
			customer->addIntoHistory(returnCommand + " " + mediaType + " "
			+ genre + " " + title + " " + to_string(year));
		} else {
			return false;
		}
		break;
	case 'D':
		director = movieInformation.substr(0, movieInformation.find(", "));
		title = movieInformation.substr(movieInformation.find(", ") + 2);
		title = title.substr(0, title.length() - 1);

		result = movieList.incrementMovie(mediaType, director, title);
		// Add transaction to customer history
		if (result) {
			customer->addIntoHistory(returnCommand + " " + mediaType + " "
			+ genre + " " + director + " " + title);
		} else {
			return false;
		}
		break;
	case 'C':
		// Break line up using space as delimeter
		while (getline(tss, tToken, tDelimeter)) {
			tList.push_back(tToken);
		}

		month = stoi(tList[0]);
		year = stoi(tList[1]);
		majorActor = tList[2] + " " + tList[3];

		// Remove one movie from movie inventory
		result = movieList.incrementMovie(mediaType, month, year, majorActor);
		// Add transaction to customer history
		if (result) {
			customer->addIntoHistory(returnCommand + " " + mediaType + " "
			+ genre + " " + to_string(month) + " " + to_string(year) + " "
			+ majorActor);
		} else {
			return false;
		}
		break;
	default:
		cout << "ERROR: '" << genre << "' is not a valid genre." << endl;
		break;
	}
	return true;
}
