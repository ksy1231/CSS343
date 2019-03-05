/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#ifndef ASS4_CLASSICMOVIE_H
#define ASS4_CLASSICMOVIE_H

#include "movie.h"
#include <string>
#include <vector>

class ClassicMovie : public Movie {
public:
	// Constructor
	ClassicMovie(const string& directorName, const string& movieTitle,
				 int releaseYear, const string& majorActor, int releaseMonth);
	// Destructor
	~ClassicMovie() override;
	// Prints out the information about the movie in formated order
	void print() const override;
	// Operator overrides
	bool operator==(const Movie& movieobj) const override;
	bool operator<(const Movie& movieObj) const override;
	bool operator>(const Movie& movieObj) const override;
	// Returns if the actor given in the param is in the major actor vecter
	bool findMajorActor(const string& actor) const;
	// Returns release month
	int getReleaseMonth() const;
	// Returns the first major actor 
	string getMajorActor() const;
	// Allows us to add a new major actor if it is different than currently in
	void addMajorActor(const string& actor);

private:
	vector<string> majorActor;
	int releaseMonth;
	const char CLASSIC = 'F';
};

#endif
