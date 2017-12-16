#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <tuple>
using namespace std;

// Split the string by " "
vector<string> split(const string & str)
{
	typedef istream_iterator<string> stringIterator;
	typedef back_insert_iterator<vector<string>> vectorIterator;
	
	vector<string> words;
	vectorIterator insertIterator(words);

	istringstream buffer(str);
	stringIterator strIn(buffer);

	copy(strIn, stringIterator(), insertIterator);
	return words;
}

int sumLine(const string & line)
{
	auto words = split(line);
	vector<int> values;
	back_insert_iterator<vector<int>> insertIterator(values);
	transform(words.begin(), words.end(), insertIterator, [](const string & word) {return stoi(word);});
	int max = *max_element(values.begin(), values.end());
	int min = *min_element(values.begin(), values.end());
	return max - min;
}

int evenlyDividesLine(const string & line)
{
	auto words = split(line);
	vector<int> values;
	back_insert_iterator<vector<int>> insertIterator(values);
	transform(words.begin(), words.end(), insertIterator, [](const string & word) {return stoi(word);});
	for(int i = 0, n = values.size(); i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			if ((values[i] % values[j]) == 0)
				return values[i]/values[j];
		}
	return 0;
}

int main()
{
	string line;
	
	int sum = 0;
	while (getline(cin, line))
		sum += evenlyDividesLine(line);
	cout << "Evenly sum: " << sum << "\n";
	return 0;
}