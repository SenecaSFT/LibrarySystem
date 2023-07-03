#pragma once
#include <vector>
#include <string>
#include <filesystem>

#include "InputTools.h"

#include "Book.h"
#include "Account.h"

using std::vector;
using std::string;

namespace fs = std::filesystem;

class Library
{
public:
	Library();
	~Library();

private:
	const string _dataDirectory = "DATA/";
	const string _accountDirectory = "DATA/ACCOUNT";
	const string _cataogueDirectory = "DATA/CATALOGUE";

	const string _accountFile = "DATA/ACCOUNT/ACCOUNT.txt";
	const string _catalogueFile = "DATA/CATALOGUE/CATALOGUE.txt";

	fs::path _dataPath;
	fs::path _accountPath;
	fs::path _cataloguePath;
	fs::path _accountFilePath;
	fs::path _catalogueFilePath;

public:
	InputTools::Scanner SC;
	//vector<Account> accounts;
	Account activeAccount;
	vector<Book> catalogue;

private:
	void _setDirectories();

public:
	// main functions
	void viewMenu();
	void viewBorrowMenu();
	void viewLibraryCatalogue();
	void borrowBook();
	void borrowBookC();
	void borrowBookNA();

	// other
	void printBook(Book book);

	// filesystem
	void createData();
	bool verifyData();

	// account
	bool verifyAccount();
	void createAccount();
	void saveAccount(Account account);
	//Account getAccount();

	// catalogue
	bool verifyCatalogue();
	void createCatalogue();
	void saveCatalogue(vector<Book> catalogue);
	//vector<Book> getCatalogue();
};
