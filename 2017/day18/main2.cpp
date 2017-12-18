/*
    PART TWO
*/

#include "mingw.thread.h"
#include "../Helpers/Helpers.h"
using namespace std;

bool stuck1Thread;
bool stuck2Thread;
bool deadlock()
{
    if (stuck1Thread && stuck2Thread)
        return true;
    return false;
}
void threadProgram(const vector<vector<string>> & program, 
    queue<long long> * input, 
    queue<long long> * output, 
    bool * waiting, 
    int * sended, long long id)
{
    std::unordered_map<string, long long> mapValue;
    mapValue["p"] = id;
    int instruction = 0;
    while(true)
    {
        string var = program[instruction][1];

        // set default value for the variable
        if (mapValue.find(var) == mapValue.end())
            if (isalpha(var[0]))
                mapValue[var] = 0;
            
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
            //cout << var << ": " << mapValue[var] << "\n";
        }
        else if (program[instruction].size() == 2)
        {
            if (program[instruction][0] == "snd")
            {
                (*sended)++;
                output->push(mapValue[var]);
            }
            else if (program[instruction][0] == "rcv")
            {
                while(input->empty())
                {
                    *waiting = true;
                    if (deadlock() && input->empty())
                    {
                        return;
                    }
                }
                *waiting = false;
                long long val = input->front();
                input->pop();
                mapValue[var] = val;
                
            }
            else throw std::exception();
        }
        else throw std::exception();
        instruction++;
    }
}

int main()
{
    stuck1Thread = false;
    stuck2Thread = false;
    int sended1 = 0;
    int sended2 = 0;

	string line;
    vector<vector<string>> program;
    queue<long long> firstQueue;
    queue<long long> secondQueue;

    while(getline(cin, line))
    {
        auto splitted = aoc::split(line, ' ');
        program.push_back(splitted);
    }
    
    thread first(threadProgram, program, &firstQueue, &secondQueue, &stuck1Thread, &sended1, 0);
    thread second(threadProgram, program, &secondQueue, &firstQueue, &stuck2Thread, &sended2, 1);
    
    first.join();
    second.join();

    cout << sended2 << "\n";
}