/*
    UNNECESSARY PROGRAM - I thought part2 can just do with bruteforce, and I optimize everything to be quickest,
    but this still wasn't enough
*/
#include "../Helpers/Helpers.h"
using namespace std;

class Program{
    const char * REGISTERS = "abcdefgh";
    int registersNumber;
    
    enum Instructions{
        set, jnz, mul, sub
    };
    
    struct Line{
        union arg1union{
            int val;
            char reg;
        };
        union arg2union{
            int val;
            char reg;
        };
        
        bool varArg1;
        bool varArg2;
        Instructions instruction;
        arg1union arg1;
        arg2union arg2;
    };

    vector<Line> program;   // optimized program

    unordered_map<char, long long> registers;

    int i;
    int instructionsNumber;
public:
    Program()
    {
        registersNumber = char_traits<char>::length(REGISTERS);
        for(int i = 0; i<registersNumber; i++)
            registers[REGISTERS[i]] = 0;
        registers['a'] = 1;
    }

    void part2(){
        cout << registers['h'] << endl;
    }

    void run()
    {
        i = 0;
        while(i < instructionsNumber)
        {
            switch(program[i].instruction)
            {
            case set:
                if (program[i].varArg2)
                    registers[program[i].arg1.reg] = registers[program[i].arg2.reg];
                else
                    registers[program[i].arg1.reg] = program[i].arg2.val;
                break;
            case sub:
                if (program[i].varArg2)
                    registers[program[i].arg1.reg] -= registers[program[i].arg2.reg];
                else
                    registers[program[i].arg1.reg] -= program[i].arg2.val;
                break;
            case mul:
                if (program[i].varArg2)
                    registers[program[i].arg1.reg] *= registers[program[i].arg2.reg];
                else
                    registers[program[i].arg1.reg] *= program[i].arg2.val;
                break;
            case jnz:
                if(program[i].varArg1)
                {
                    if (registers[program[i].arg1.reg] != 0)
                    {
                        i += program[i].arg2.val;
                        continue;
                    }
                }
                else
                {
                    if (program[i].arg1.val != 0)
                    {
                        i += program[i].arg2.val;
                        continue;
                    }
                }
                break;
            }
            i++;
        }
    }

    void parseProgram(const vector<vector<string>> & _program)
    {
        program.clear();
        for(auto & line : _program)
        {
            Line lineProg;
            for(int i = 0; i<3; i++)
            {
                if (line[0] == "set")
                    lineProg.instruction = set;
                else if (line[0] == "sub")
                    lineProg.instruction = sub;
                else if (line[0] == "mul")
                    lineProg.instruction = mul;
                else if (line[0] == "jnz")
                    lineProg.instruction = jnz;

                if (isalpha(line[1][0]))
                {
                    lineProg.varArg1 = true;
                    lineProg.arg1.reg = line[1][0];
                }
                else
                {
                    lineProg.varArg1 = false;
                    lineProg.arg1.val = stoi(line[1]);
                }

                if (isalpha(line[2][0]))
                {
                    lineProg.varArg2 = true;
                    lineProg.arg2.reg = line[2][0];
                }
                else
                {
                    lineProg.varArg2 = false;
                    lineProg.arg2.val = stoi(line[2]);
                }
            }
            program.push_back(lineProg);
        }
        instructionsNumber = program.size();
        cout << "Rozmiar programu: " << instructionsNumber << "\n";
    }
};

int main()
{
	string line;
    vector<vector<string>> program;

    // Parse
    while(getline(cin, line))
    {
        auto splitted = aoc::split(line, ' ');
        program.push_back(splitted);
    }
    // End parsing
    Program programRunner;
    programRunner.parseProgram(program);
    programRunner.run();
}