#pragma once
#include <string>

using std::string;

enum BookStatus
{
	AVALIABLE,
	BORROWED,
	TRANSFERED,
	UNAVALIABLE
};


class Book
{
public:
	Book(unsigned int bookCode, string bookName, string bookAuthor, BookStatus bookStatus);
	Book(unsigned int bookCode, string bookName, string bookAuthor);
	Book();
	~Book();

private:
	int _code;
public:
	string name;
	string author;
	BookStatus status;

public:
	int getCode();
	void setCode(unsigned int bookCode);
};

