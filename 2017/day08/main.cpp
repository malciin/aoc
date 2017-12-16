#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;
vector<string> split(const string & str)
{
    typedef istream_iterator<string> stringIterator;
    typedef back_insert_iterator<vector<string>> vectorIterator;
    
    // Split the string by " "
    vector<string> words;
    vectorIterator insertIterator(words);

    istringstream buffer(str);
    stringIterator strIn(buffer);

    copy(strIn, stringIterator(), insertIterator);
    return words;
}
class CPUProgram
{
    class BooleanOperator
    {
    public:
        bool operator()(int a, const std::string & boolOperator, int b)
        {
            if (boolOperator == ">")
                return a > b;
            if (boolOperator == "<")
                return a < b;
            if (boolOperator == ">=")
                return a >= b;
            if (boolOperator == "<=")
                return a <= b;
            if (boolOperator == "!=")
                return a != b;
            if (boolOperator == "==")
                return a == b;
            throw std::logic_error("Unknown operator");
        }
    };
    BooleanOperator evalBool;
    int highestEver = 0;
    unordered_map<string, int> vars;
    
public:
    int & getVariable(const std::string & var)
    {
        auto variable = vars.find(var);
        if (variable == vars.end())
            vars[var] = 0;
        return vars[var];
    }
    void runProgram(const std::string & program)
    {
        auto instruction = split(program);
        for(int i = 0; i<instruction.size(); i+=7)
        {
            if (evalBool(getVariable(instruction[i+4]), instruction[i+5], stoi(instruction[i+6])))
            {
                int value = stoi(instruction[i+2]);
                getVariable(instruction[i]) +=
                    instruction[i+1] == "inc" ?
                    value : -value;
                if (highestEver < getVariable(instruction[i]))
                    highestEver = getVariable(instruction[i]);
            }
        }
    }

    int getMaxVariable()
    {
        return max_element(vars.begin(), vars.end(), 
        [](const pair<string, int> & a, const pair<string, int> & b){if (a.second < b.second) return true; return false;})->second;
    }
    int getMaxEver()
    {
        return highestEver;
    }
};

int main()
{
	string program;
    
    string line("");
	while (getline(cin, line))
	{
        if (program.empty())
            program.append(line);
        else
            program.append(" " + line);
	}
    CPUProgram cpuProgram;
    cpuProgram.runProgram(program);
    cout << "max : " << cpuProgram.getMaxVariable();
    cout << "max ever: " << cpuProgram.getMaxEver();
    return 0;
}