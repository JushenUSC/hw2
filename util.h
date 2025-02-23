#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>

using namespace std;

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	//set up both iterators that point to beginning of respective sets
	typename set<T>::iterator setOneIterator = s1.begin();
	typename set<T>::iterator setTwoIterator = s2.begin();
	//create the intersection set
	set<T> intersectionSet;
	while (setOneIterator != s1.end() && setTwoIterator != s2.end()) {
		if (*setOneIterator > *setTwoIterator) {
			setTwoIterator++;
		}
		if (*setOneIterator < *setTwoIterator) {
			setOneIterator++;
		}
		if (*setOneIterator == *setTwoIterator) { 
			intersectionSet.insert(*setOneIterator);
			setOneIterator++;
			setTwoIterator++;
		}
	}
	return intersectionSet;
}


template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	//copy s1 into union set
	set<T> setUnion(s1);

	//create an iterator to traverse the s2 set
	typename set<T>::iterator setTwoIterator = s2.begin();

	//while loop runs from beginning to end of s2 set
	while (setTwoIterator != s2.end()) {
		//insert second set
		setUnion.insert(*setTwoIterator);
		setTwoIterator++;
	}
	return setUnion;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
