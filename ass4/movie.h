/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_MOVIE_H
#define ASS4_MOVIE_H

#include <string>

using namespace std;

class Movie {
public:
	// Constructor
	Movie(const Movie& m); 
	Movie(const string& directorName, const string& movieTitle, int releaseYear);
	// Destructor
	virtual ~Movie() = default;
	// override print function
	virtual void print() const = 0;
	// Operator overloading for sorting purposes
	virtual bool operator==(const Movie& movieObj) const = 0;
	virtual bool operator<(const Movie& movieObj) const = 0;
	virtual bool operator>(const Movie& movieObj) const = 0;
	// Getters for operators
    // Returns movie title
	const string getMovieTitle() const;
    // Returns director name
	const string getDirectorName() const;
    // Returns release year
	int getReleaseYear() const;

protected:
	string movieTitle;
	string directorName;
	int releaseYear;
};

#endif
