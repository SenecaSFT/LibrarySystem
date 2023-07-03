#include "Book.h"

#include <string>

using std::string;

Book::Book(unsigned int bookCode, string bookName, string bookAuthor, BookStatus bookStatus)
{
	this->setCode(bookCode);
	this->name = bookName;
	this->author = bookAuthor;
	this->status = bookStatus;
}

Book::Book(unsigned int bookCode, string bookName, string bookAuthor)
{
	this->setCode(bookCode);
	this->name = bookName;
	this->author = bookAuthor;
}

Book::Book()
{
}

Book::~Book()
{
}

int Book::getCode()
{
	return this->_code;
}

void Book::setCode(unsigned int bookCode)
{
	if (bookCode < 0)
		bookCode = 0;
	if (bookCode > 999)
		bookCode = 999;

	this->_code = bookCode;
}
