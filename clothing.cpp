#include "clothing.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : Product(category, name, price, qty) {
	size_ = size;
	brand_ = brand;
}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
	return parseStringToWords(name_ + " " + brand_);
}

std::string Clothing::displayString() const {
	return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n " + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const {
	os << category_ << endl << name_ << endl << price_ << endl << qty_ << endl << size_ << endl << brand_ << endl;
}