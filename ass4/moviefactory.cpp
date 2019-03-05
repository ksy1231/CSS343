/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "moviefactory.h"
#include <iostream>

// Will return either a comedy or drama based on thee parameters
Movie* MovieFactory::makeMovie(char genre, const string& directorName,
	const string& movieTitle, int releaseYear) {
	// If it's a comedy 
	if (genre == 'F') {
		return new ComedyMovie(directorName, movieTitle, releaseYear);
	} else if (genre == 'D') {  // If it's a drama
		return new DramaMovie(directorName, movieTitle, releaseYear);
	} else {  // Else print an error
		cout << "ERROR: " << genre << " is not a movie genre!" << endl;
		return nullptr;
	}
}

// Will return either a classic movie
Movie * MovieFactory::makeMovie(char genre, const string & directorName,
	const string & movieTitle, int releaseYear,
	const string & majorActor, int releaseMonth) {
	if (genre == 'C') {  // If it's a classic 
		return new ClassicMovie(directorName, movieTitle, releaseYear,
			majorActor, releaseMonth);
	} else {  // else print an error
		cout << "ERROR: " << genre << " is not a movie genre!" << endl;
		return nullptr;
	}
}
