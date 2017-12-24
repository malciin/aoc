/*
    PART ONE COPIED FROM DAY18 JUST WITH SOME MINOR CHANGES
*/
#include "../Helpers/Helpers.h"


using namespace std;
int main()
{
	string line;
    vector<vector<string>> program;

    while(getline(cin, line))
    {
        auto splitted = aoc::split(line, ' ');
        program.push_back(splitted);
    }

    std::unordered_map<string, long long> mapValue;
    string registers("abcdefgh");
    for(auto reg : registers)
        registers[reg] = 0;
    mapValue["a"] = 0;
    int instruction = 0;
    long long lastPlayed;
    int mul = 0;
    while(instruction < program.size())
    {
        string var = program[instruction][1];
        if (mapValue.find(var) == mapValue.end())
        {
            if (isalpha(var[0]))
                mapValue[var] = 0;
        }
            
        long long val;
        if (isalpha(program[instruction][2][0]))
            val = mapValue[program[instruction][2]];
        else
            val = stoi(program[instruction][2]);
        if (program[instruction][0] == "set")
            mapValue[var] = val;
        else if (program[instruction][0] == "add")
            mapValue[var] += val;
        else if (program[instruction][0] == "sub")
            mapValue[var] -= val;
        else if (program[instruction][0] == "mul")
        {
            mapValue[var] *= val;
            mul++;
        }
            
        else if (program[instruction][0] == "mod")
            mapValue[var] = mapValue[var] % val;
        else if (program[instruction][0] == "jnz")
        {
            long long val2;
            if (isalpha(var[0]))
                val2 = mapValue[var];
            else
                val2 = stoi(var);
            if (val2 != 0)
            {
                instruction += val;
                continue;
            }
        }
        else throw std::exception();
        instruction++;
    }
    cout << "MUL: " << mul << "\n";
}