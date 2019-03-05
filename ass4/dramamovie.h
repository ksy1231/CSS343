/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_DRAMAMOVIE_H
#define ASS4_DRAMAMOVIE_H

#include "movie.h"
#include <string>

using namespace std; 

class DramaMovie : public Movie {
public:
	// Constructor
	DramaMovie(const string& directorName, const string& movieTitle,
			   int releaseYear);
	// Destructor
	~DramaMovie() override;
	// Operator overloads
	bool operator==(const Movie& obj) const override;
	bool operator<(const Movie& movieObj) const override;
	bool operator>(const Movie& movieObj) const override;
	// Prints out the information about the movie
	void print() const override;

private:
	// Setting the genre for customer for easy access
	const char DRAMA = 'D'; 
};

#endif 
