// https://www.reddit.com/r/dailyprogrammer/comments/7fvy7z/20171127_challenge_342_easy_polynomial_division/
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <tuple>
#include <unordered_set>
using namespace std;

class int_vector_hasher {
public:
	std::size_t operator()(std::vector<int> const& vec) const {
		std::size_t seed = vec.size();
		for(auto i : vec) {
			seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

// VEEERY UGLY SOLUTION!
int detectLoop(vector<int> & memory)
{
    unordered_set<vector<int>, int_vector_hasher> arrangements;
    
    vector<pair<vector<int>, int>> insertedInCycle;
    int memorySize = memory.size();
    
    int id = 0;
	int cycles = 0;

	auto findIterator = arrangements.find(memory);
	insertedInCycle.push_back(make_pair(memory, cycles));
	do
	{
		findIterator = arrangements.insert(findIterator, memory);
		

		int insertIndex = distance(memory.begin(), max_element(memory.begin(), memory.end()));
		int howMuch = memory[insertIndex];
		memory[insertIndex] = 0;
		insertIndex++;
		for(;howMuch > 0; howMuch--, insertIndex++)
		{
			if (insertIndex == memorySize)
				insertIndex -= memorySize;
			memory[insertIndex]++;
		}
		
        cycles++;
        insertedInCycle.push_back(make_pair(memory, cycles));
		findIterator = arrangements.find(memory);
	} while(findIterator == arrangements.end());
    
    int cycleFirst;
    for(int i = 0; i<insertedInCycle.size(); i++)
    {
        if (insertedInCycle[i].first == insertedInCycle[insertedInCycle.size()-1].first)
        {
            cycleFirst = insertedInCycle[i].second;
            break;
        }
    }
	return cycles-cycleFirst;
}


// In my opinion better than upper solution (less memory)
int detectLoop2(vector<int> & memory)
{
	unordered_set<vector<int>, int_vector_hasher> arrangements;

	int memorySize = memory.size();
	int cycles = 0;

	auto findIterator = arrangements.find(memory);
	
	do
	{
		arrangements.insert(findIterator, memory);
		

		int insertIndex = distance(memory.begin(), max_element(memory.begin(), memory.end()));
		int howMuch = memory[insertIndex];
		memory[insertIndex] = 0;
		insertIndex++;
		for(;howMuch > 0; howMuch--, insertIndex++)
		{
			if (insertIndex == memorySize)
				insertIndex -= memorySize;
			memory[insertIndex]++;
		}
		
		cycles++;
		findIterator = arrangements.find(memory);
    } while(findIterator == arrangements.end());
    
    arrangements.clear();
    cycles = 0;
    do
	{
		arrangements.insert(findIterator, memory);
		

		int insertIndex = distance(memory.begin(), max_element(memory.begin(), memory.end()));
		int howMuch = memory[insertIndex];
		memory[insertIndex] = 0;
		insertIndex++;
		for(;howMuch > 0; howMuch--, insertIndex++)
		{
			if (insertIndex == memorySize)
				insertIndex -= memorySize;
			memory[insertIndex]++;
		}
		
		cycles++;
		findIterator = arrangements.find(memory);
    } while(findIterator == arrangements.end());
	
	return cycles;
}

// In my opinion better than upper solution (less code, 
// little more memory (just for pointers and intigers)). Dont need to rerun loop like upper function

int main()
{
	vector<int> memoryBlocks;
	int input;
	while(cin >> input)
		memoryBlocks.push_back(input);
	
	cout << "Loop after: " << detectLoop2(memoryBlocks);
	return 0;
}