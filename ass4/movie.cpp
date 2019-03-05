/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "movie.h"

// Copy constructor
Movie::Movie(const Movie& m) {
	this->directorName = m.directorName; 
	this->movieTitle = m.movieTitle; 
	this->releaseYear = m.releaseYear; 
}

// Constructor that takes in a director name, movie and release year
Movie::Movie(const string& directorName, const string& movieTitle,  
	int releaseYear) {
	this->movieTitle = movieTitle;
	this->directorName = directorName;
	this->releaseYear = releaseYear;
}

// Returns movie title
const string Movie::getMovieTitle() const{
	return movieTitle;
}

// Returns director name
const string Movie::getDirectorName() const{
	return directorName;
}

// Returns release year
int Movie::getReleaseYear() const{
	return releaseYear;
}
