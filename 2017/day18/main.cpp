/*
    PART ONE
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
    int instruction = 0;
    long long lastPlayed;
    while(true)
    {
        string var = program[instruction][1];
        if (mapValue.find(var) == mapValue.end())
        {
            if (isalpha(var[0]))
                mapValue[var] = 0;
        }
            
        if (program[instruction].size() == 3)
        {
            
            long long val;
            if (isalpha(program[instruction][2][0]))
                val = mapValue[program[instruction][2]];
            else
                val = stoi(program[instruction][2]);
            if (program[instruction][0] == "set")
                mapValue[var] = val;
            else if (program[instruction][0] == "add")
                mapValue[var] += val;
            else if (program[instruction][0] == "mul")
                mapValue[var] *= val;
            else if (program[instruction][0] == "mod")
                mapValue[var] = mapValue[var] % val;
            else if (program[instruction][0] == "jgz")
            {
                long long val2;
                if (isalpha(var[0]))
                    val2 = mapValue[var];
                else
                    val2 = stoi(var);
                if (val2 > 0)
                {
                    instruction += val;
                    continue;
                }
            }
            else throw std::exception();
        }
        else if (program[instruction].size() == 2)
        {
            if (program[instruction][0] == "snd")
                lastPlayed = mapValue[var];
            else if (program[instruction][0] == "rcv")
            {
                if (mapValue[var] != 0)
                {
                    cout << lastPlayed << "!\n";
                    break;
                } 
            }
            else throw std::exception();
        }
        else throw std::exception();
        instruction++;
    }
    
}