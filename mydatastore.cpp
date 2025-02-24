#include "mydatastore.h"
#include "util.h"

MyDataStore::~MyDataStore() {
	for (std::set<Product*>::iterator it = productsSet.begin(); it != productsSet.end(); it++) {
		delete (*it);
	}
	productsSet.clear();
	for (std::set<User*>::iterator it = usersSet.begin(); it != usersSet.end(); it++) {
		delete (*it);
	}
	usersSet.clear();
	keywordsAndProducts.clear();
	usersAndCarts.clear();
}

void MyDataStore::addProduct(Product* p) {

	//gets the keywords from the specific product
	std::set<std::string> productKeywords = p->keywords();

	//iterates through each keyword for that product, find that keyword in the mapping and add this product to that set
	for (std::set<std::string>::iterator it = productKeywords.begin(); it != productKeywords.end(); it++) {
		//find the key and value pair given the key
		if (keywordsAndProducts.find(*it) != keywordsAndProducts.end()) {
			std::map<std::string, std::set<Product*>>::iterator iteratorFoundKeyword = keywordsAndProducts.find(*it);
			(iteratorFoundKeyword->second).insert(p);
		}
		//if it doesnt exist (the keyword is new) then create a new pair and add it
		else {
			std::set<Product*> newKeywordsProducts;
			newKeywordsProducts.insert(p);
			std::pair<std::string, std::set<Product*>> newKeywordAndItsProductPair(*it, newKeywordsProducts);
			keywordsAndProducts.insert(newKeywordAndItsProductPair);
		}
	}

	//add product to productsSet as well
	productsSet.insert(p);
	
}

void MyDataStore::addUser(User* u) {
	usersSet.insert(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	//we have a mapping with keywords and associated products
	std::vector<Product*> resultsVector;
	if (terms.empty()) {
        return resultsVector;
    }
	if (type == 0) {
		std::map<std::string, std::set<Product*>>::iterator firstKeywordPair = keywordsAndProducts.find(convToLower(terms[0]));
		if (firstKeywordPair == keywordsAndProducts.end()) {
            return resultsVector; 
        }
		std::set<Product*> matchingProducts = firstKeywordPair->second;
		for (int i = 1; i < terms.size(); i++) {
			std::map<std::string, std::set<Product*>>::iterator nextKeywordPair = keywordsAndProducts.find(convToLower(terms[i]));
			if (nextKeywordPair == keywordsAndProducts.end()) {
                return resultsVector; // No match, AND fails
            }
			matchingProducts = setIntersection(matchingProducts, nextKeywordPair->second);
		}
		resultsVector = vector<Product*>(matchingProducts.begin(), matchingProducts.end());
	}
	else {
		std::set<Product*> matchingProducts;
		for (int i = 0; i < terms.size(); i++) {
			std::map<std::string, std::set<Product*>>::iterator keywordPair = keywordsAndProducts.find(convToLower(terms[i]));
			if (keywordPair != keywordsAndProducts.end()) {
                matchingProducts = setUnion(matchingProducts, keywordPair->second);
            }
		}
		resultsVector = vector<Product*>(matchingProducts.begin(), matchingProducts.end());
	}
	return resultsVector;
}

void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>\n";
	for (std::set<Product*>::iterator productsSetIterator = productsSet.begin(); productsSetIterator != productsSet.end(); productsSetIterator++) {
		(*productsSetIterator)->dump(ofile);
	}
	ofile << "</products>\n";

	ofile << "<users>\n";
	for (std::set<User*>::iterator userSetIterator = usersSet.begin(); userSetIterator != usersSet.end(); userSetIterator++) {
		(*userSetIterator)->dump(ofile);
	}
	ofile << "</users>\n";
}

std::set<User*> MyDataStore::getAllUsers() {
	return usersSet;
}

User* MyDataStore::usernameToUser(std::string username) const {
	for (std::set<User*>::iterator it = usersSet.begin(); it != usersSet.end(); it++) {
		if (convToLower((*it)->getName()) == convToLower(username)) {
			return (*it);
		}
	}
	return nullptr;
}

void MyDataStore::addToCart(User* user, Product* p) {
	if (usersAndCarts.find(user) == usersAndCarts.end()) {
		//create new deque for user because they have yet to have one created
		usersAndCarts[user] = std::deque<Product*>();
	}
	usersAndCarts[user].push_back(p);
}

void MyDataStore::viewCart(const std::string username) const {
	User* foundUser = usernameToUser(username);
	if (!foundUser) {
		cout << "Invalid username" << endl;
		return;
	}
	//print the associated cart to the console
	std::map<User*, std::deque<Product*>>::const_iterator it = (usersAndCarts.find(foundUser));
	if (it == usersAndCarts.end()) {
		return;
	}
	const std::deque<Product*>& usersCart = it->second;
	int itemIndex = 1;
	for (std::deque<Product*>::const_iterator it = usersCart.begin(); it != usersCart.end(); it++) {
		cout << "Item " << itemIndex << endl;
		cout << (*it)->displayString() << endl;
		cout << endl;
		itemIndex++;
	}
}

void MyDataStore::buyCart(const std::string username) {
	User* foundUser = usernameToUser(username);
	if (!foundUser) {
		cout << "Invalid username" << endl;
	}
	std::map<User*, std::deque<Product*>>::iterator it = (usersAndCarts.find(foundUser));
	if (it == usersAndCarts.end()) {
		return;
	}
	std::deque<Product*>& usersCart = it->second;
	while (!(usersCart.empty())) {
		Product* currProduct = usersCart.front();
		if (currProduct->getQty() > 0 && foundUser->getBalance() >= currProduct->getPrice()) {
			currProduct->subtractQty(1);
			foundUser->deductAmount(currProduct->getPrice());
			usersCart.pop_front();
		}
		else {
			break;
		}
	}
}