/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_MOVIELIST_H
#define ASS4_MOVIELIST_H

#include <vector>
#include <list>
#include <string>
#include "movieinventory.h"
#include "moviefactory.h"
#include "movie.h"

using namespace std;

class MovieList {
public:
	// Constructor
	MovieList();
	// Destructor
	virtual ~MovieList();
	// Adding a comedy or drama: will handle duplications and sorting
	bool addMovie(char genre, const string& directorName,
		const string& movieTitle, int releaseYear, int quantity);
	// Adding a classic: will handle duplications and sorting
	bool addMovie(char genre, const string& directorName,
		const string& movieTitle, int releaseYear,
		const string& majorActor, int releaseMonth, int quantity);
	// Incrementing a classic movie
	bool incrementMovie(char mediaType, int releaseMonth,
		int releaseYear, const string& majorActor);
	// Incrementing comedy movies
	bool incrementMovie(char mediaType, const string& title, int releaseYear);
	// Incrementing drama movies
	bool incrementMovie(char mediaType, const string& director,
	                    const string& title);
	// Decrement a classic movie
	bool decrementMovie(char mediaType, int releaseMonth,
		int releaseYear, const string& majorActor);
	// Decrement comedy movies
	bool decrementMovie(char mediaType, const string& title, int releaseYear);
	// Decrement  drama movies
	bool decrementMovie(char mediaType, const string& director,
	                    const string& title);
	// For printing all movies out
	void printMovies() const;

private:
	// Index 0: Comedy (F)
	const static int F = 0;
	// Index 1: Drama (D)
	const static int D = 1;
	// Index 2: Classics (C)
	const static int C = 2;
	const static char DVD = 'D';
	vector<list<MovieInventory*>> movieList;
	MovieFactory factory;
	// Checks if media type is a DVD
	bool isDVD(char mediaType) const;
};

#endif // ASS4_MOVIELIST_H
