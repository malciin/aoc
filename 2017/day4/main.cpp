#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
using namespace std;


vector<string> split(const string & str)
{
	typedef istream_iterator<string> stringIterator;
	typedef back_insert_iterator<vector<string>> vectorIterator;
	
	// Split the string by " "
	vector<string> words;
	vectorIterator insertIterator(words);

	istringstream buffer(str);
	stringIterator strIn(buffer);

	copy(strIn, stringIterator(), insertIterator);
	return words;
}

bool goodPassword(const string & password)
{
	auto words = split(password);
	set<string> wordsSet;
	for(int i = 0; i<words.size(); i++)
	{
		// comment next line for part 1
		sort(words[i].begin(), words[i].end());
		auto iterator = wordsSet.find(words[i]);
		if (iterator==wordsSet.end())
			wordsSet.insert(iterator, words[i]);
		else
			return false;
	}
	return true;
}

int main()
{
	string line;
	
	int properPasswords = 0;
	while (getline(cin, line))
	{
		bool proper = goodPassword(line);
		properPasswords = properPasswords + int(proper);
	}
	cout << "Proper Passwords: " << properPasswords << "\n";
	return 0;
}