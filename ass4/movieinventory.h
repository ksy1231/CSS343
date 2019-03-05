/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_MOVIEINVENTORY_H
#define ASS4_MOVIEINVENTORY_H

#include "movie.h"

class MovieInventory {
public:
	// Constructor
	MovieInventory(Movie* m, int quantity, char mediaType);
	// Destructor
	virtual ~MovieInventory();
    // Increase quantity for the movie based on the given quantity
	void increaseQuantity(int quantity);
    // Decrease quantity for the movie based on the given quantity
	void decreaseQuantity(int quantity);
	// Return quantity of DVD
	int getQuantity() const;
	// Return movie
	Movie* getMovie() const;

private:
	// This is the index of DVD
	// Can easily add new media types in the future
	const static int DVD = 0;
	Movie* movie;
	// Size of 1 currently because we only have 1 media type
	int mediaQuantity[1];
};

#endif // ASS4_MOVIEINVENTORY_H
