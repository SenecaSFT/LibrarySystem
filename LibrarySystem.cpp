#include <iostream>
#include <string>

#include "Library.h"
#include "Book.h"

using std::cout;
using std::cin;
using std::string;

namespace fs = std::filesystem;

void verifyData(Library* library);

int main()
{
    cout << "Hello World!\n";
    cout << "Library Management System Loaded!\n";
    cout << "Loading Menu...\n";


    Library* lib = new Library();
    verifyData(lib); // verify data
    lib->viewMenu();


    delete lib;
}

void verifyData(Library* library)
{
    cout << "VERIFYING DATA...";

    if (!library->verifyData())
    {
        library->createData();

        library->createAccount();
        library->saveAccount(library->activeAccount);

        library->createCatalogue();
        library->saveCatalogue(library->catalogue); // 

    }
    else
    {
        cout << "data verified!";
        if (!library->verifyAccount())
        {
            library->createAccount();
            library->saveAccount(library->activeAccount);        
        }
        if (!library->verifyCatalogue())
        {
            library->createCatalogue();
            library->saveCatalogue(library->catalogue); // 
        }
        library->createCatalogue();
    }
}

//void vefDat(Library library)
//{
//    cout << "VERIFYING DATA...";
//
//    if (!library.verifyData())
//    {
//        library.createData();
//
//        library.createAccount();
//        library.saveAccount(library.activeAccount);
//
//        library.createCatalogue();
//        library.saveCatalogue(library.catalogue); // 
//
//    }
//    else
//    {
//        cout << "data verified!";
//        if (!library.verifyAccount())
//        {
//            library.createAccount();
//            library.saveAccount(library.activeAccount);
//        }
//        if (!library.verifyCatalogue())
//        {
//            library.createCatalogue();
//            library.saveCatalogue(library.catalogue); // 
//        }
//        library.activeAccount = library.getAccount();
//        //library->getCatalogue();
//
//    }
//}