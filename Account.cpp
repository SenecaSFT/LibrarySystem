#include "Account.h"

#include <random>

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

Account::Account(string userName, unsigned int userPassword)
{
	this->name = userName;
	// set account number
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<int> dist(0000, 9999);
	this->_number = dist(rng);
	this->setPassword(userPassword);
}

Account::Account()
{
}

Account::~Account()
{
}

unsigned int Account::getNumber()
{
	return this->_number;
}

void Account::setNumber(unsigned int num)
{
	this->_number = num;
}

unsigned int Account::getPassword()
{
	return this->_password;
}

void Account::setPassword(unsigned int pass)
{
	this->_password = pass;
}
