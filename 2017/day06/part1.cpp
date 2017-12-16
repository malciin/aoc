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
		for(auto& i : vec) {
			seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};


int detectLoop(vector<int> & memory)
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
	
	return cycles;
}

int main()
{
	vector<int> memoryBlocks;
	int input;
	while(cin >> input)
		memoryBlocks.push_back(input);
	
	cout << "Loop after: " << detectLoop(memoryBlocks);
	return 0;
}