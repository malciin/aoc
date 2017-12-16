#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
using namespace std;

int main()
{
	vector<int> instructions;
	int jumpBy;
	while (cin >> jumpBy)
	{
		instructions.push_back(jumpBy);
	}
	
	int instr = 0;
	int clock = 0;
	int jumpLines = instructions.size();
	while(instr >= 0 && instr < jumpLines)
	{
		clock++;
		jumpBy = instructions[instr];
		if(instructions[instr] >= 3)
			instructions[instr]--;
		else
			instructions[instr]++;
		instr += jumpBy; 
	}
	
	cout << "Wyszedlem po " << clock << " instrukcjach\n";
	return 0;
}