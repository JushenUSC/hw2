#include "book.h"

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author)
	: Product(category, name, price, qty) 
{
	ISBN_ = ISBN;
	author_ = author;
}

Book::~Book() {}

std::set<std::string> Book::keywords() const{
	std::string potentialBookKeywords = name_ + " " + ISBN_ + " " + author_;
	return parseStringToWords(potentialBookKeywords);
}

std::string Book::displayString() const {
	return name_ + "\nAuthor: " + author_ + " ISBN: " + ISBN_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const {
	os << category_ << endl << name_ << endl << price_ << endl << qty_ << endl << ISBN_ << endl << author_;
}