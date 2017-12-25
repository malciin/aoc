/*
    BOTH PART1 AND PART2 - BRUTEFORCE - TOOK ~6 seconds to compute the result
*/
#include "../Helpers/Helpers.h"
#include <bitset>
#include <regex>
using namespace std;

enum Direction{
    Left = -1, Right = 1
};

struct Instruction
{
    int writeValue;
    Direction direction;
    char nextState;
};

struct State
{
    Instruction instr0;
    Instruction instr1;
};

int main()
{
    
    unordered_map<char, State> states;
    unordered_map<int, int> tape;

    int currPos = 0;
    char currState;
    int steps;

    string line;

    // PARSING...
    getline(cin, line);
    auto splitted = aoc::split(line, ' ');
    currState = splitted[splitted.size() - 1][0];

    getline(cin, line);
    splitted = aoc::split(line, ' ');
    steps = stoi(splitted[splitted.size() - 2]);

    while(getline(cin, line))
    {
        if (!getline(cin, line))
            break;
        splitted = aoc::split(line, ' ');
        State newState;
        char stateId = splitted[splitted.size() - 1][0];

        getline(cin, line);

        getline(cin, line);
        splitted = aoc::split(line, ' ');
        newState.instr0.writeValue = stoi(splitted[splitted.size() - 1]);

        getline(cin, line);
        splitted = aoc::split(line, ' ');
        if (splitted[splitted.size() - 1] == "left.")
            newState.instr0.direction = Direction::Left;
        else
            newState.instr0.direction = Direction::Right;

        getline(cin, line);
        splitted = aoc::split(line, ' ');
        newState.instr0.nextState = splitted[splitted.size() - 1][0];

        getline(cin, line);

        getline(cin, line);
        splitted = aoc::split(line, ' ');
        newState.instr1.writeValue = stoi(splitted[splitted.size() - 1]);

        getline(cin, line);
        splitted = aoc::split(line, ' ');
        if (splitted[splitted.size() - 1] == "left.")
            newState.instr1.direction = Direction::Left;
        else
            newState.instr1.direction = Direction::Right;

        getline(cin, line);
        splitted = aoc::split(line, ' ');
        newState.instr1.nextState = splitted[splitted.size() - 1][0];

        states[stateId] = newState;
    }
    // END PARSING...

    int clock = 0;
    while(clock < steps)
    {
        if (tape[currPos] == 0)
        {
            tape[currPos] = states[currState].instr0.writeValue;
            if (tape[currPos] == 0)
                tape.erase(currPos);
            currPos += states[currState].instr0.direction;
            currState = states[currState].instr0.nextState;
        }
        else if (tape[currPos] == 1)
        {
            tape[currPos] = states[currState].instr1.writeValue;
            if (tape[currPos] == 0)
                tape.erase(currPos);
            currPos += states[currState].instr1.direction;
            currState = states[currState].instr1.nextState;
        }
        else
            throw std::exception();
        clock++;
    }

    cout << tape.size() << "!\n";
}