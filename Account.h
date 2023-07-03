#pragma once
#include <string>
#include <vector>

#include "Book.h"

using std::string;
using std::vector;

class Account
{
public:
	Account(string username, unsigned int userPassword);
	Account();
	~Account();
private:
	unsigned int _number;
	unsigned int _password;
public:
	string name;
	vector<Book> borrowedBooks;

	unsigned int getNumber();
	void setNumber(unsigned int num);

	unsigned int getPassword();
	void setPassword(unsigned int pass);
};

