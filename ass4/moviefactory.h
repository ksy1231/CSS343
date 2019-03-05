/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_MOVIEFACTORY_H
#define ASS4_MOVIEFACTORY_H

#include "movie.h"
#include "classicmovie.h"
#include "comedymovie.h"
#include "dramamovie.h"

using namespace std;

class MovieFactory {
public:
	// Constructor
	MovieFactory() = default;
	// Destructor
	~MovieFactory() = default;
	// For making comedy and drama movies
	Movie* makeMovie(char genre, const string& directorName,
		const string& movieTitle, int releaseYear);
	// For making classic movies 
	Movie* makeMovie(char genre, const string& directorName,
		const string& movieTitle, int releaseYear,
		const string& majorActor, int releaseMonth);
};

#endif // ASS4_MOVIEFACTORY_H
