/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "classicmovie.h"
#include <iostream>

// Constuctor that will create the movie based on the given parameters
ClassicMovie::ClassicMovie(const string& directorName, const string& movieTitle,
						   const int releaseYear, const string & majorActor, 
						   int releaseMonth)
						   : Movie(directorName, movieTitle, releaseYear) {
	this->majorActor.push_back(majorActor);
	this->releaseMonth = releaseMonth;
}

// Destructor
ClassicMovie::~ClassicMovie() { }

// Prints out the information about the movie
void ClassicMovie::print() const {
	cout << CLASSIC << ", " << this->directorName << ", " << this->movieTitle
		<< ", ";
	for (const auto &i : this->majorActor) {
		cout << i << ", ";
	}
	cout << this->releaseMonth << " " << this->releaseYear << endl;
}

// Checks to see if the specified major actor has been added to the movie
bool ClassicMovie::findMajorActor(const string& actor) const {
	for (const auto &i : majorActor) {
		if (i == actor) {
			return true;
		}
	}
	return false;
}

// Returns release month
int ClassicMovie::getReleaseMonth() const {
	return releaseMonth;
}

// Return major actor
string ClassicMovie::getMajorActor() const {
	return majorActor[0];
}

// Allows us to add a new major actor if it is different than currently in
void ClassicMovie::addMajorActor(const string & actor){
	majorActor.push_back(actor);
}

// Does not check for major actors since it's an array
bool ClassicMovie::operator==(const Movie& movieObjOrig) const {
	const auto & movieObj = dynamic_cast<const ClassicMovie&>
		(movieObjOrig);
	if (this == &movieObj) return true;
	// Check if all fields are equal to each other
	return (this->directorName == movieObj.getDirectorName() &&
		this->movieTitle == movieObj.getMovieTitle() &&
		this->releaseYear == movieObj.getReleaseYear() &&
		this->releaseMonth == movieObj.getReleaseMonth());
}

// Operator <, uses operator > for functionality
bool ClassicMovie::operator<(const Movie& movieObjOrig) const{
	// Cast the Movie* into classic movie so we have access to its data
	const auto & movieObj = dynamic_cast<const ClassicMovie&>
		(movieObjOrig);
	// Check if year is equal
	if (this->releaseYear < movieObj.getReleaseYear()) {  
		return true;
	} else if (this->releaseYear > movieObj.getReleaseYear()) {
		return false;
	} else { // Years are equal, move to months
		if (this->releaseMonth < movieObj.getReleaseMonth()) {
			return true;
		} else if (this->releaseMonth > movieObj.getReleaseMonth()) {
			return false;
		} else { // Months are equal, check actor
			if (this->majorActor[0] < movieObj.majorActor[0]) {
				return true;
			} else if (this->majorActor[0] > movieObj.majorActor[0]) {
				return false;
			}
		}
	}
	return false;
}

// Operator >, uses operator < for functionality
bool ClassicMovie::operator>(const Movie& movieObj) const{
	return !(*this < movieObj);
}
