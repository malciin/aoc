#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class day16container
{
	// better if we used than string the Boost.Circular, 
	// but this need boost, or the own buffer implementation
	string programs;
	bool _foundPeriod;
	unordered_set<string> memory;
	unordered_map<char, int> programsPos;
public:
	day16container() : programs("abcdefghijklmnop")
	{
		_foundPeriod = false;
		for_each(programs.cbegin(), programs.cend(), 
			[&](const char ch){ 
				programsPos[ch] = programs[programs.size()-1]; 
			});
	}

	void exchange(int a, int b)
	{
		programsPos[programs[a]] = b;
		programsPos[programs[b]] = a;
		auto temp = programs[a];
		programs[a] = programs[b];
		programs[b] = temp;

	}

	void partner(char a, char b)
	{
		exchange(programsPos[a], programsPos[b]);
	}

	void spin(int howMuch)
	{
		int n = programs.size();
		int input = 0;

		string programsNew = programs;
		int i = howMuch - 1;
		for(int n = programs.size(); i>=0; i--, input++)
		{
			programsNew[input] = programs[n-1-i];
			programsPos[programsNew[input]] = input;
		}
		for(i = 0 ;input < n; input++, i++)
		{
			programsNew[input] = programs[i];
			programsPos[programsNew[input]] = input;
		}
		programs = programsNew;
	}
	int foundPeriod()
	{
		if (_foundPeriod)
			return memory.size();
		else
			return 0;
	}
	void memorizePos()
	{
		if (memory.find(programs) != memory.end())
		{
			_foundPeriod = true;
		}
		else
			memory.insert(programs);
	}
	void print()
	{
		for(auto x : programs)
			cout << x;
		cout << "\n";
	}
};

int main()
{
	day16container day16;


	string line;
	getline(cin, line);
	const int howMuchDances = 1000000000;
	bool periodFound = false;
	for(int i = 0; i<howMuchDances; i++)
	{
		int period = day16.foundPeriod();
		if (period != 0 && !periodFound)
		{
			periodFound = true;
			i = (howMuchDances / period * period);

			cout << "Found period after " << period << "\n";
			continue;
		}
		auto it = line.begin();
		auto itHelper = it;

		while(it != line.end())
		{
			char cmd = *it;
			it++;
			itHelper = it;
			
			if (cmd == 's')
			{
				while((*itHelper) != ',' && (*itHelper) != '\0')
					itHelper++;
				string arg(it, itHelper);
				if (itHelper != line.end())
					itHelper++;
				day16.spin(stoi(arg));
			}
			else if (cmd == 'x' || cmd == 'p')
			{
				while((*itHelper) != '/')
					itHelper++;
				string arg1(it, itHelper);
				itHelper++;
				it = itHelper;

				while((*itHelper) != ',' && (*itHelper) != '\0')
					itHelper++;
				string arg2(it, itHelper);
				if (itHelper != line.end())
					itHelper++;
				
				if (cmd == 'x')
					day16.exchange(stoi(arg1), stoi(arg2));
				else
					day16.partner(arg1[0], arg2[0]);
			}
			
			it = itHelper;
			
		}
		day16.memorizePos();
	}
	day16.print();
	
	return 0;
}