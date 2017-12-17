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



int main()
{
	const int puzzle = 394;
	list<int> puzzleList;
	puzzleList.push_back(0);
	auto it = puzzleList.begin();
	int insertVal = 1;
	// while(*it != 49999999)
	// bruteforce solution for part2. It takes around ~10 minutes to give correct answer
	// smarter way is in part2.cpp file


	while(*it != 2017)
	{
		int howMuchSkip = puzzle % puzzleList.size();
		while(howMuchSkip > 0)
		{
			howMuchSkip--;
			it++;
			if (it == puzzleList.end())
				it = puzzleList.begin();
		}
		it = puzzleList.insert(++it, insertVal);
		insertVal++;
		if (*it == 2017)
		{
			cout << "After " << *it << " we have " << *++it <<"\n";
			it--;
		}
	}



	it = puzzleList.begin();
	while(it != puzzleList.end())
	{
		if(*it == 0)
		{
			cout << "After zero we have " << *++it;
			break;
		}
		it++;
	}
	return 0;
}