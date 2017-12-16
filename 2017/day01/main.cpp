#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int part1(const string & str)
{
	int sum = 0;
	int i = 0;
	for(int n = str.size() - 1; i<n; i++)
		if (str[i] == str[i+1])
			sum+= str[i] - '0';

	if (str[i] == str[0])
				sum+= str[i] - '0';
	return sum;
}

int part2(const string & str)
{
	int sum = 0;
	// assume the str.size is even
	for(int i = 0, n = str.size(); i<n; i++)
	{
		int index = i + n/2;
		if (index >= n)
			index -= n;
		if (str[i] == str[index])
			sum += str[i] - '0';
			
	}
	return sum;
}

int main()
{
	string line;
	while (getline(cin, line))
	{
		std::cout << "Sum: " << part2(line);
		std::cout << "\n";
	}
	
	return 0;
}