/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "movieinventory.h"
#include <iostream>

// Constructor for movieInventory
MovieInventory::MovieInventory(Movie* m, int quantity, char mediaType) {
	this->movie = m; 
	if (mediaType == 'D') 
		mediaQuantity[DVD] = quantity;
	else
		cout << "ERROR: " << mediaType << " is an incorrect media type." << endl; 
}

// Destructor
MovieInventory::~MovieInventory() {
	delete movie;
	movie = nullptr;
}

// Increase quantity for the movie based on the given quantity
void MovieInventory::increaseQuantity(int quantity) {
	mediaQuantity[DVD] += quantity;
}

// Decrease quantity for the movie based on the given quantity
void MovieInventory::decreaseQuantity(int quantity) {
	mediaQuantity[DVD] -= quantity;
}

// Getters
int MovieInventory::getQuantity() const {
	return mediaQuantity[DVD];
}

// Getters
Movie * MovieInventory::getMovie() const {
	return this->movie;
}
