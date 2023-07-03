#pragma once
#include <vector>
#include <string>
#include <functional>

using std::vector;
using std::string;
using std::function;

namespace InputTools
{
	class Scanner
	{
	public:
		Scanner();
		~Scanner();

	private:
		vector<string> promptStrings;
		vector<int> promptOptions;

	public:
		void purgeData();
		void prompt(const vector<string> promptStrings, const vector<int> promptOptions, const vector<function<void()>> funcs);;
		int verifySingleInput();
	};

}