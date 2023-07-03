#include "Library.h"

#include "InputTools.h"
#include "Account.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <format>
#include <fstream>
#include <filesystem>
#include <random>
#include <array>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::function;
using std::format;

using std::fstream;
using std::ofstream;
using std::ifstream;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::array;

namespace fs = std::filesystem;

Library::Library()
{
    this->_setDirectories();
}

Library::~Library()
{
}

void Library::viewMenu()
{
    system("cls");
    vector<string> menuPrompts;
    menuPrompts.push_back("0. Quit program\n");
    menuPrompts.push_back("1. View Library Catalogue\n");
    menuPrompts.push_back("2. Borrow Book\n");

    vector<int> menuOptions = { 0, 1, 2, 3, 4 };
    vector<function<void()>> funcs = {
        []() { exit(0); },
        [this]() { this->viewLibraryCatalogue(); },
        [this]() { this->viewBorrowMenu(); },
    };
    this->SC.prompt(menuPrompts, menuOptions, funcs);
}

void Library::viewBorrowMenu()
{
    system("cls");
    cout << "*BORROW MENU*\n";
    vector<string>menuPrompts;
    menuPrompts.push_back("0. Return to previous\n");
    menuPrompts.push_back("1. Borrow using name, author and code\n");
    menuPrompts.push_back("2. Borrow using code\n");
    menuPrompts.push_back("3. Borrow using name and author\n");

    vector<int> menuOptions { 0, 1, 2, 3 };
    vector<function<void()>> funcs = {
        [this]() { this->viewMenu(); },
        [this]() { this->borrowBook(); },
        [this]() { this->borrowBookC(); },
        [this]() {this->borrowBookNA(); }
    };
    this->SC.prompt(menuPrompts, menuOptions, funcs);
}

void Library::viewLibraryCatalogue()
{
    cout << "*CATALOGUE*\n";
    for (Book book : this->catalogue)
    {
        printBook(book);
    }
}

void Library::borrowBook()
{
    int bookCode;
    string name;
    string author;

    cout << "Enter Data:\n";
    cout << "BOOK CODE: ";
    bookCode = SC.verifySingleInput();
    cout << "BOOK NAME: ";
    cin >> name;
    cout << "BOOK AUTHOR: ";
    cin >> author;
   
    Book book(bookCode, name, author);
    bool bookFound = false;
    for (Book libBook : this->catalogue)
    {
        if (book.name == libBook.name
            && book.author == libBook.author
            && book.getCode() == libBook.getCode())
        {
            cout << "Book Found!\n";
            cout << "Printing data...\n";
            this->printBook(libBook); // always default to actual book
            bookFound = true;

            if (libBook.status == UNAVALIABLE)
                cout << "BORROW FAILED! Book is unavaliable!\n";
            else if (libBook.status == BORROWED)
                cout << "BORROW FAILED! Book is borrowed!\n";
            else if (libBook.status = TRANSFERED)
                cout << "BORROW FAILED! Book has been transfered!\n";
            else cout << "BORROW SUCCESFUL! Book has been borrowed!\n";

            break;
        }
        else
            cout << "SEARCHING...\n";
    }
    
    if (!bookFound)
    {
        cout << "ERR: NO BOOK FOUND; ENTER TO CONTINUE\n";
        cin.ignore();
        cin.get();
        system("cls");
    }
}

void Library::borrowBookC()
{
    int bookCode;
    cout << "Enter Data:\n";
    cout << "BOOK CODE: ";
    bookCode = SC.verifySingleInput();

    bool bookFound = false;
    for (Book libBook : this->catalogue)
    {
        if (bookCode == libBook.getCode())
        {
            cout << "Book Found!\n";
            cout << "Printing data...\n";
            this->printBook(libBook);
            bookFound = true;

            if (libBook.status == UNAVALIABLE)
                cout << "BORROW FAILED! Book is unavaliable!\n";
            else if (libBook.status == BORROWED)
                cout << "BORROW FAILED! Book is borrowed!\n";
            else if (libBook.status = TRANSFERED)
                cout << "BORROW FAILED! Book has been transfered!\n";
            else cout << "BORROW SUCCESFUL! Book has been borrowed!\n";

            break;
        }
        else
            cout << "SEARCHING...\n";
    }
    
    if (!bookFound)
    {
        cout << "ERR: NO BOOK FOUND; ENTER TO CONTINUE\n";
        cin.ignore();
        cin.get();
        system("cls");
    }
}

void Library::borrowBookNA()
{
    string name;
    string author;

    cout << "Enter Data: \n";
    cout << "BOOK NAME: ";
    cin >> name;
    cout << "BOOK AUTHOR: ";
    cin >> author;

    bool bookFound = false;
    for (Book libBook: this->catalogue)
    {
        if (name.compare(libBook.name) == 0 && author.compare(libBook.author) == 0)
        {
            cout << "Book Found!\n";
            cout << "Printing data...\n";
            this->printBook(libBook);
            bookFound = true;

            if (libBook.status == UNAVALIABLE)
                cout << "BORROW FAILED! Book is unavaliable!\n\n";
            else if (libBook.status == BORROWED)
                cout << "BORROW FAILED! Book is borrowed!\n\n";
            else if (libBook.status = TRANSFERED)
                cout << "BORROW FAILED! Book has been transfered!\n\n";
            else cout << "BORROW SUCCESFUL! Book has been borrowed!\n\n";

            break;
        }
        else
            cout << "SEARCHING...\n";
    }

    if (!bookFound)
    {
        cout << "ERR: NO BOOK FOUND; ENTER TO CONTINUE\n";
        cin.ignore();
        cin.get();
        system("cls");
    }
}

void Library::printBook(Book book)
{
    string status;
    switch (book.status)
    {
    case BookStatus::AVALIABLE:
        status = "AVALIABLE";
        break;
    case BookStatus::BORROWED:
        status = "BORROWED";
        break;
    case BookStatus::TRANSFERED:
        status = "TRANSFERED";
        break;
    case BookStatus::UNAVALIABLE:
        status = "UNAVALIABLE";
        break;
    default:
        cout << "ERR";
        exit(1);
        break;
    }
    cout << "==========\n";
    cout << "BOOK:\n";
    cout << format("NAME: {};\n", book.name);
    cout << format("AUTHOR: {};\n", book.author);
    cout << format("CODE: {};\n", book.getCode());
    cout << format("STATUS: {};\n", status);
    cout << "==========\n";
    cout << std::endl;
}

void Library::_setDirectories()
{
    this->_dataPath = fs::path(this->_dataDirectory);
    this->_accountPath = fs::path(this->_accountDirectory);
    this->_cataloguePath = fs::path(this->_cataogueDirectory);

    this->_accountFilePath = fs::path(this->_accountFile);
    this->_catalogueFilePath = fs::path(this->_catalogueFile);
}

void Library::createData()
{
    try
    {
        fs::create_directory(this->_dataPath);
        fs::create_directory(this->_accountPath);
        fs::create_directory(this->_cataloguePath);
    }
    catch (const std::exception&)
    {
        cout << "ERR: FAILED TO CREATE DATA DIRECTORY!\n";
        throw;
    }

    ofstream accountTXT(this->_accountFilePath);
    ofstream catalogueTXT(this->_catalogueFilePath);

    // test writing
    if (!accountTXT.is_open())
        cout << "ERR: FILE WRITE ERR";
    if (!catalogueTXT.is_open())
        cout << "ERR: FILE WRITE ERR";

    accountTXT << "OPEN\n";
    catalogueTXT << "OPEN\n";

    accountTXT.close();
    catalogueTXT.close();

}

bool Library::verifyData()
{
    if (!fs::exists(this->_dataPath) && !fs::is_directory(this->_dataPath))
    {
        cout << "ERR: NO DATA DIRECTORY\n\n";
        return false;
    }
    else if (!fs::exists(this->_accountFilePath) && !fs::is_directory(this->_accountFilePath))
    {
        cout << "ERR: NO ACCOUNT FILE\n\n";
        return false;
    }
    else if (!fs::exists(this->_catalogueFilePath) && !fs::is_directory(this->_catalogueFilePath))
    {
        cout << "ERR: NO CATALOGUE FILE\n\n";
        return false;
    }
    else
    {
        return true;
    }
}

bool Library::verifyAccount()
{
    ifstream accountFile(this->_accountFilePath);

    if (accountFile.peek() == ifstream::traits_type::eof())
    {
        cout << "WRN: ACCOUNT FILE IS EMPTY!\n";
        cout << "REQUESTING NEW DATA...\n";
        return false;
    }
    else
    {
        return true;
    }
    
    accountFile.close();
}

void Library::createAccount()
{
    string accountName;
    cout << "*ACCOUNT CREATION*\n";
    cout << "Enter Account Name:\n";
    cout << "> ";
    cin >> accountName;

    cout << "Enter Password:\n";
    int userPass = SC.verifySingleInput();

    Account userAccount(accountName, userPass);

    this->activeAccount = userAccount;
}

void Library::saveAccount(Account account)
{
    // check if file is empty
    ifstream accountTXT(this->_accountFilePath);

    if (!accountTXT.is_open())
    {
        cout << "ERR: FAILED TO OPEN DATA FILE\n"; 
        exit(1);
    }
    else
    {
        ofstream clearAccountTXT(this->_accountFilePath, std::ios::trunc);

        string passwordString = std::to_string(account.getPassword());
        string numberString = std::to_string(account.getNumber());
        clearAccountTXT << account.name << endl;
        clearAccountTXT << passwordString << endl;
        clearAccountTXT << numberString << endl;

        clearAccountTXT.close();
    }
    accountTXT.close();
}

//Account Library::getAccount()
//{
//    ifstream accountFile(this->_accountFilePath);
//
//    if (!accountFile.is_open())
//    {
//        cout << "ERR: FAILED TO OPEN ACCOUNT FILE!"; exit(1);
//    }
//    else
//    {
//        string accountName;
//        string accountPassword;
//        string accountNumber;
//
//        std::getline(accountFile, accountName);
//        std::getline(accountFile, accountPassword);
//        std::getline(accountFile, accountNumber);
//
//        // convert values
//        unsigned int accPass = std::stoul(accountPassword);
//        unsigned int accNum = std::stoul(accountNumber);
//
//        Account account(accountName, accPass);
//        account.setNumber(accNum);
//    }
//    accountFile.close();
//}

bool Library::verifyCatalogue()
{
    ifstream catalogueFile(this->_catalogueFilePath);

    if (catalogueFile.peek() == ifstream::traits_type::eof())
    {
        cout << "WRN: CATALOGUE FILE IS EMPTY!\n";
        cout << "REQUESTING NEW DATA...\n";
        return false;
    }
    else
    {
        return true;
    }

    catalogueFile.close();
}

void Library::createCatalogue()
{
    // a default book
    Book book(000, "name", "author", BookStatus::UNAVALIABLE);

    this->catalogue.push_back(book);

    array<string, 10> names = {
        "Book1",
        "Book2",
        "Book3",
        "Book4",
        "Book5",
        "Book6",
        "Book7",
        "Book8",
        "Book9",
        "Book10"
    };

    array<string, 10> authors = {
        "Author1",
        "Author2",
        "Author3",
        "Author4",
        "Author5",
        "Author6",
        "Author7",
        "Author8",
        "Author9",
        "Author10"
    };

    array<BookStatus, 4> statuses = {
        AVALIABLE,
        BORROWED,
        TRANSFERED,
        UNAVALIABLE
    };


    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<int> codeDist(000, 999);
    uniform_int_distribution<int> nameDist(0, names.size() - 1);
    uniform_int_distribution<int> authorDist(0, authors.size() - 1);
    uniform_int_distribution<int> statusDist(0, statuses.size() - 1);

    for (size_t i = 0; i < 100; i++)
    {

        Book book(codeDist(rng), names[nameDist(rng)], authors[authorDist(rng)],
            statuses[statusDist(rng)]);

        this->catalogue.push_back(book);
    }
}

void Library::saveCatalogue(vector<Book> catalogue)
{
    // this is only going to be run once, ideally
    ofstream catalogueTXT(this->_catalogueFilePath);

    for (Book book : catalogue)
    {
        string bookName = book.name;
        string bookAuthor = book.author;
        BookStatus bookStatus = book.status;
        string bookStatusSTR;
        string bookCode = std::to_string(book.getCode());

        // set status into string
        switch (bookStatus)
        {
        case AVALIABLE:
            bookStatusSTR = "Avaliable";
            break;
        case BORROWED:
            bookStatusSTR = "BORROWED";
            break;
        case TRANSFERED:
            bookStatusSTR = "TRANSFERED";
            break;
        case UNAVALIABLE:
            bookStatusSTR = "UNAVALIABLE";
            break;
        default: // something terrible has occured
            cout << "Errrr?\n";
            break;
        }

        // write
        catalogueTXT << bookName << endl;
        catalogueTXT << bookAuthor << endl;
        catalogueTXT << bookStatusSTR << endl;
        catalogueTXT << bookCode << endl;
    }
    catalogueTXT.close();
}

//vector<Book> Library::getCatalogue() // should be only called once certain data exists
//{
//    ifstream catalogueTXT(this->_catalogueFilePath);
//
//
//    if (!catalogueTXT.is_open())
//    {
//        cout << "ERR: FAILED TO OPEN CATALOGUE FILE!"; exit(1);
//    }
//    else
//    {
//        vector<Book> catalogue;
//
//        string line;
//        bool bookBegin = true;
//        while (std::getline(catalogueTXT, line))
//        {
//            //cout << line;
//            string bookName;
//            string bookAuthor;
//            string bookStatus;
//            string bookCode;
//            std::getline(catalogueTXT, bookAuthor);
//            std::getline(catalogueTXT, bookStatus);
//            std::getline(catalogueTXT, bookCode);
//            bookName = line;
//
//            //cout << "NAME: " << bookName << endl;
//            //cout << "AUTHOR: " << bookAuthor << endl;
//            //cout << "STATUS: " << bookStatus << endl;
//            //cout << "CODE: " << bookCode << endl;
//
//            // convert values
//            unsigned int bkINT = std::stoul(bookCode);
//            BookStatus bkStat = BookStatus::AVALIABLE;
//
//            //cout << bookStatus;
//
//            if (bookStatus.compare("AVALIABLE") == 0) // evil, but works
//                bkStat = BookStatus::AVALIABLE;
//            else if (bookStatus.compare("BORROWED") == 0)
//                bkStat = BookStatus::BORROWED;
//            else if (bookStatus.compare("TRANSFERED") == 0)
//                bkStat = BookStatus::TRANSFERED;
//            else if (bookStatus.compare("UNAVALIABLE") == 0)
//                bkStat = BookStatus::UNAVALIABLE;
//            else
//                cout << "FATAL ERR IN DATA\n"; exit(1);
//
//            // make book
//            Book book(bkINT, bookName, bookAuthor, bkStat);
//            catalogue.push_back(book);
//        }
//        cout << "Catalogue size: " << catalogue.size() << endl;
//        catalogueTXT.close();
//
//        for (Book b : catalogue)
//        {
//            cout << b.name << endl;
//            cout << b.author << endl;
//            cout << b.status << endl;
//            cout << b.getCode() << endl;
//        }
//
//
//        cout << "RRRRRRRRRRRRRRRR";
//        return catalogue;
//    }
//
//
//}
