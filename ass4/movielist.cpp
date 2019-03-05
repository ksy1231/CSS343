/**
 * Authors: Will Hwang, Soo Yun Kim
 */

#include "movielist.h"
#include <iostream>
#include <iomanip>

// Empty movieList
MovieList::MovieList() {
	movieList.resize(3);
}

// Empty destructor
MovieList::~MovieList() {
	// We newed movie list, delete that shit
	for (auto &i : movieList) {
		for (auto it = i.begin(); it != i.end(); ++it) {
			delete *it;
		}
	}
}

// Add movie for comedy and drama
bool MovieList::addMovie(char genre, const string& directorName,
	const string& movieTitle, int releaseYear, int quantity) {
	// Check if genre is valid
	if (genre != 'F' && genre != 'D') {
		cout << "ERROR: " << genre << " is not a valid genre." << endl;
		return false;
	}

	// The index of the correct movieList based on the genre
	int index;
	if (genre == 'F') index = F;
	else if (genre == 'D') index = D;

	// Make new movie from the given parameters
	Movie* movieToAdd = factory.makeMovie(genre, directorName, movieTitle,
			releaseYear);
	
	// If first in list
	if (movieList[index].empty()) {
		movieList[index].push_back(new MovieInventory(movieToAdd, quantity,
				'D'));
		return true;
	}
	
	for (auto it = movieList[index].begin(); it != movieList[index].end();
			++it) {
		Movie* movieToCheck = (*it)->getMovie();
		// If movie already exists in the list
		if (*movieToAdd == *movieToCheck) {
			delete movieToAdd;
			(*it)->increaseQuantity(quantity);
			return true;
		} else if (*movieToAdd < *movieToCheck) {
			movieList[index].insert(it, new MovieInventory(movieToAdd, quantity,
					'D'));
			return true;
		}
	}
	// broke out of for loop,
	// means the movie is not in the list and it's the biggest
	movieList[index].push_back(new MovieInventory(movieToAdd, quantity, 'D'));
	return true;
}

// Add movie for classic movie
bool MovieList::addMovie(char genre, const string & directorName,
						const string & movieTitle, int releaseYear,
						const string & majorActor, int releaseMonth,
						int quantity) {
	// Check if genre is valid
	if (genre != 'C') {
		cout << "ERROR: " << genre << " is not a valid genre." << endl;
		return false;
	}

	// The index of the correct movieList based on the genre
	int index = C;

	// Make new movie from the given parameters
	Movie* movieToAdd = factory.makeMovie(genre, directorName, movieTitle,
			releaseYear, majorActor, releaseMonth);

	// If first in list
	if (movieList[index].empty()) {
		movieList[index].push_back(new MovieInventory(movieToAdd, quantity,
				'D'));
		return true;
	}

	for (auto it = movieList[index].begin(); it != movieList[index].end();
			++it) {
		Movie* movieToCheck = (*it)->getMovie();
		// If movie already exists in the list
		if (*movieToAdd == *movieToCheck) {
			delete movieToAdd;
			auto * classicMovie = dynamic_cast<ClassicMovie*>(movieToCheck);
			// If the major actor is not recorded in the existing classic movie,
			// record it
			if (!classicMovie->findMajorActor(majorActor))
				classicMovie->addMajorActor(majorActor);
			// Increase quantity based on parameter
			(*it)->increaseQuantity(quantity);
			return true;
		} else if (*movieToAdd < *movieToCheck) {
			movieList[index].insert(it, new MovieInventory(movieToAdd, quantity,
					'D'));
			return true;
		}
	}
	// broke out of for loop, means the movie is not in the list
	// and it's the biggest
	movieList[index].push_back(new MovieInventory(movieToAdd, quantity, 'D'));
	return true;
}

// Incrementing classic movie
bool MovieList::incrementMovie(char mediaType, int releaseMonth,
	int releaseYear, const string& majorActor) {
	if (!isDVD(mediaType)) return false;
	// Loop through the classic movie bucket
	for (auto &it : movieList[C]) {
		Movie* classicM = it->getMovie();
		// Dynamic cast so it knows what to call 
		const auto * classicMovie = dynamic_cast<const ClassicMovie*>(classicM);

		// If the values match, increase quantity by 1
		if (classicM->getReleaseYear() == releaseYear &&
			classicMovie->getReleaseMonth() == releaseMonth &&
			classicMovie->findMajorActor(majorActor)) {
			it->increaseQuantity(1);
			return true;
		}
	}
	cout << "ERROR:" << releaseMonth << " " << releaseYear << " "
		<< majorActor << " movie does not exist in the store." << endl;
	return false;
}

// Decrement for classic movie
bool MovieList::decrementMovie(char mediaType, int releaseMonth,
	int releaseYear, const string & majorActor) {
	if (!isDVD(mediaType)) return false;
	// Loop through the classic movie bucket
	for (auto &it : movieList[C]) {
		Movie* classicM = it->getMovie();
		// Dynamic cast so it knows what to call 
		const auto * classicMovie = dynamic_cast<const ClassicMovie*>(classicM);
		// If the values match
		if (classicM->getReleaseYear() == releaseYear &&
			classicMovie->getReleaseMonth() == releaseMonth &&
			classicMovie->findMajorActor(majorActor)) {
			if (it->getQuantity() > 0) {  // if quantity is bigger than 0
				it->decreaseQuantity(1);
				return true;
			} else {  // quantity is 0
				cout << "ERROR:" << releaseMonth << " " << releaseYear << " "
					<< majorActor << " movie is out of stock." << endl;
				return false;
			}
		} 
	}
	cout << "ERROR:" << releaseMonth << " " << releaseYear << " "
		<< majorActor << " movie does not exist in the store." << endl;
	return false;
}

// Increment for comedymovies
bool MovieList::incrementMovie(char mediaType, const string& title,
		int releaseYear) {
	if (!isDVD(mediaType)) return false;
	// For each movie in the comedy movie bucket
	for (auto &it : movieList[F]) {
		Movie* comedyM = it->getMovie();
		// if the values match, we found the movie in the bucket
		if (comedyM->getMovieTitle() == title &&
			comedyM->getReleaseYear() == releaseYear) {
			it->increaseQuantity(1);
			return true;
		}
	}
	cout << "ERROR: " << title << ", " << releaseYear <<
		" movie does not exist in the store." << endl;
	return false;
}

//Decrement for comedy movies
bool MovieList::decrementMovie(char mediaType, const string & title,
		int releaseYear) {
	if (!isDVD(mediaType)) return false;
	// For each movie in the comedy movie bucket
	for (auto &it : movieList[F]) {
		Movie* comedyM = it->getMovie();
		// if the values match
		if (comedyM->getMovieTitle() == title &&
			comedyM->getReleaseYear() == releaseYear) {
			// Values match and it's in stock
			if (it->getQuantity() > 0) {
				it->decreaseQuantity(1);
				return true;
			} else { // else quantity is 0
				cout << "ERROR: " << title << ", " << releaseYear <<
					" movie is out of stock." << endl;
				return false;
			}
		}
	}
	cout << "ERROR: " << title << ", " << releaseYear <<
		" movie does not exist in the store." << endl;
	return false;
}

// Increment for drama movies
bool MovieList::incrementMovie(char mediaType, const string& director,
	const string& title) {
	// Check if media type is valid, which is just DVD right now
	if (!isDVD(mediaType)) return false;

	// For each movie in the comedy movie bucket
	for (auto &it : movieList[D]) {
		Movie* dramaM = it->getMovie();
		// if the values match, we found the movie in the bucket
		if (dramaM->getDirectorName() == director &&
			dramaM->getMovieTitle() == title) {
			it->increaseQuantity(1);
			return true;
		}
	}
	cout << "ERROR: " << director << ", " << title <<
		" movie does not exist in the store." << endl;
	return false;
}

// Decrement for drama movies
bool MovieList::decrementMovie(char mediaType, const string & director,
								const string & title) {
	if (!isDVD(mediaType)) return false;
	
	// For each movie in the comedy movie bucket
	for (auto &it : movieList[D]) {
		Movie* dramaM = it->getMovie();
		// if the values match
		if (dramaM->getDirectorName() == director &&
			dramaM->getMovieTitle() == title) {
			// Values match and it's in stock
			if (it->getQuantity() > 0) {
				it->decreaseQuantity(1);
				return true;
			} else { // else quantity is 0
				cout << "ERROR: " << director<< ", " << title <<
					" movie is out of stock." << endl;
				return false;
			}
		}
	}
	cout << "ERROR: " << director << ", " << title <<
		" movie does not exist in the store." << endl;
	return false;

}

// For printing all movies out
void MovieList::printMovies() const {
	// For the comedy movie bucket
	for (auto it : movieList[F]) {
		Movie* currMovie = it->getMovie();
		cout << it->getQuantity() << setw(20)
			<< currMovie->getDirectorName() << setw(40) 
			<< currMovie->getMovieTitle()<< setw(10) 
			<< currMovie->getReleaseYear() << endl;
	}
	cout << endl;

	// For the drama movie bucket
	for (auto it : movieList[D]) {
		Movie* currMovie = it->getMovie();
		cout << it->getQuantity() << setw(20)
			<< currMovie->getDirectorName() << setw(40)
			<< currMovie->getMovieTitle() << setw(10)
			<< currMovie->getReleaseYear() << endl;
	}
	cout << endl;

	// For classic movies bucket
	for (auto it : movieList[C]) {
		Movie* currMovie = it->getMovie();
		auto * classicMovie = dynamic_cast<ClassicMovie*>(currMovie);
		cout << it->getQuantity() << setw(20)
			<< currMovie->getDirectorName() << setw(40)
			<< currMovie->getMovieTitle() << setw(20)
			<< classicMovie->getMajorActor() << setw(7)
			<< classicMovie->getReleaseMonth() << setw(10)
			<< currMovie->getReleaseYear() << endl;
	}
	cout << endl;
}

// Checks if media type is a DVD
bool MovieList::isDVD(char mediaType) const {
	if (mediaType != DVD) {
		cout << "ERROR: " << mediaType << " is an invalid media type." << endl;
		return false;
	} else {
		return true;
	}
}
