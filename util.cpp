#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	//trim the word first before turning it into a set
	rawWords = trim(rawWords);

	//turn input into stringstream to read from it like cin...
	stringstream inputWords = stringstream(rawWords);
	string currentWord;

	//create the set that will be returned
	set<string> keywordSet;

	while (inputWords >> currentWord) {
		int currentWordLength = currentWord.size();

		//ISBN Number check
		if (currentWordLength == 15 && currentWord[4] == '-' && currentWord[14] == '-') {
			keywordSet.insert(currentWord);
			continue;
		}
		//if length is greater than 2, then its eligible to be added as keyWord
		if (currentWordLength > 2) {

			bool firstKeyWord = true;
			int beginningOfWord = 0;

			for (int i = 0; i < currentWordLength; i++) {
				if (ispunct(currentWord[i]) == true && firstKeyWord == true) { //for first keyword, if there is more than one keyword separated by punctuation
					//create substring from 0 to i
					string newSetWord = currentWord.substr(0, i);
					//add to set only if substring length is greater than two
					if (newSetWord.size() > 2) {
						newSetWord = convToLower(newSetWord);
						keywordSet.insert(newSetWord);
					}
					//set beginningOfWord to i
					beginningOfWord = i + 1;
					firstKeyWord = false;
					continue;
				}
				if (ispunct(currentWord[i]) == true && firstKeyWord == false) { //for second keyword, if there is more than one
					//create substring from beginningOfWord to i
					string newSetWord = currentWord.substr(beginningOfWord, i-beginningOfWord);
					//add to set only if substring length is greater than 2
					if (newSetWord.size() > 2) {
						newSetWord = convToLower(newSetWord);
						keywordSet.insert(newSetWord);
					}
					//set beginningOfWord to i
					beginningOfWord = i+1;
					continue;
				}
				if (i==currentWordLength) { //general case for last word, or first word if there is no punctuation
					//create substring from beginningOfWord to i
					string newSetWord = currentWord.substr(beginningOfWord);
					//add to set only if the substring length is greater than 2
					if (newSetWord.size() > 2) {
						newSetWord = convToLower(newSetWord);
						keywordSet.insert(newSetWord);
					}
					//loop will end as i is at last iteration, so no need for continue
				}
			}
		}
		
	}
	
	return keywordSet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

/*

std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

*/