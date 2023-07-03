#include "InputTools.h"

#include <iostream>
#include <string>
#include <functional>

using std::cout;
using std::cin;
using std::string;

namespace InputTools
{
	Scanner::Scanner()
	{
	}
	Scanner::~Scanner()
	{
	}
	void Scanner::purgeData()
	{
		this->promptStrings.clear();
		this->promptOptions.clear();
	}
	void Scanner::prompt(const vector<string> promptStrings, const vector<int> promptOptions, const vector<function<void()>> funcs)
	{
		bool inputValid = false;

		while (!inputValid)
		{
			for (string promptString : promptStrings)
			{
				cout << promptString;
			}

			cout << "> ";
			string userInput;

			cin >> userInput;

			try
			{
				int userInputConverted = stoi(userInput);

				for (size_t i = 0; i < promptOptions.size(); i++)
				{
					if (userInputConverted == promptOptions[i])
					{
						// input is good
						funcs[i](); // run coresponding function
						break;
					}
				}
			}
			catch (const std::exception&)
			{
				cout << "ERR: BAD INPUT!\n\n";
			}
		}
	}
	int Scanner::verifySingleInput()
	{
		string userInput;
		bool inputValid = false;
		while (!inputValid)
		{
			cin >> userInput;
			try
			{
				int userInputConverted = stoi(userInput);
				return userInputConverted;
			}
			catch (const std::exception&)
			{
				cout << "ERR: BAD INPUT!\n\n";
			}
		}
	}
}