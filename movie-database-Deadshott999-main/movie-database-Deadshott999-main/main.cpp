#include "moviedb.h"
#include <iostream>

using namespace std;

int main()
{
	MovieDatabase db;
	Movie movie1 = {"Spider-Man 3", 2007};
	Movie movie2 = {"Vampires Suck", 2010};
	Movie movie3 = {"Lovelace", 2013};
	cout << "test";
    db.addBack(movie1);
    db.addBack(movie2);
    db.addBack(movie3);
	
	return EXIT_SUCCESS;
}
