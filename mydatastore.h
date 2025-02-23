#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {
public:
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	std::set<User*> getAllUsers();
	User* usernameToUser(std::string username) const;
	void addToCart(User* user, Product* p);
	void viewCart(const std::string username) const;
	void buyCart(const std::string username);
protected:
	//need a set of all user's 
	std::set<User*> usersSet;

	//need a set of all Products available
	std::set<Product*> productsSet;

	//need a map to store user with their cart
	//username, vector of their products (cart)
	std::map<User*, std::deque<Product*>> usersAndCarts;

	//need a map of keywords and products
	std::map<std::string, std::set<Product*>> keywordsAndProducts;
};

#endif