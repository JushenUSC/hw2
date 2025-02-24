#include "movie.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) : Product(category, name, price, qty) {
	genre_ = genre;
	rating_ = rating;
}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
	std::string keywordsToIndex = name_ + " " + genre_;
	return parseStringToWords(keywordsToIndex);
}

std::string Movie::displayString() const {
	return name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const {
	os << category_ << endl << name_ << endl << price_ << endl << qty_ << endl << genre_ << endl << rating_ << endl;
}