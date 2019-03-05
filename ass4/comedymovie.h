/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_COMEDYMOVIE_H
#define ASS4_COMEDYMOVIE_H

#include "movie.h"
#include <string>

using namespace std;

class ComedyMovie : public Movie {
public:
	// Comedy movie constructor
	ComedyMovie(const string& directorName, const string& movieTitle,
				int releaseYear);
	// Destructor
	~ComedyMovie() override;
	// Prints the movie information
	void print() const override;
	// Operator overloads
	bool operator==(const Movie& movieObj) const override;
	bool operator<(const Movie& movieObj) const override;
	bool operator>(const Movie& movieObj) const override;

private:
	const char COMEDY = 'F';
};

#endif 
