#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
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


class Firewall
{
    int position;   // position on the local depth
    int depth;
    bool negativeDirection;
public:
    Firewall(){}
    Firewall(int _depth){
        position = 0;
        depth = _depth;
        negativeDirection = false;
    }
    bool colliding(int pos)
    {
        return pos == position;
    }
    int getDepth()
    {
        return depth;
    }
    int getPos()
    {
        return position;
    }
    void step()
    {
        if (!negativeDirection)
        {
            if (position + 1 >= depth)
            {
                position--;
                negativeDirection = true;
            }
            else
                position++;
        }
        else
        {
            if (position - 1 < 0)
            {
                position++;
                negativeDirection = false;
            }
            else
                position--;
        }
    }
    // Optimalization for part 2
    void skipBy(int picoSeconds)
    {
        if (depth == 1)
        {
            position = 0;
            return;
        }
        position += picoSeconds;
        int cycle = depth * 2;
        position = position % (cycle - 2);
        if (position >= depth)
        {
            position = depth - position + depth - 2;
            negativeDirection = true;
        }
    }
};

// Part2 - Bruteforce with skipBy optimization
// Possible optimizations:  use vector instead unordered_map
//                          compute only one firewall position per loop by skipBy method for delay - next Firewall will have position skippedBy ++delay
int main()
{
    string line;
    unordered_map<int, Firewall> firewallStructure;
    
    Firewall fire(1);
    Firewall fireCopy = fire;
    int i = 0;
    while(i < 50)
    {
        fire.skipBy(i);
        cout << fire.getPos() << " ";
        i++;
        fire = fireCopy;
    }
    cout << "\n";


    int lastPosition = 0;
    while(getline(cin, line))
    {
        auto words = split(line);
        words[0].resize(words[0].size() - 1);
        int position = stoi(words[0]);
        int depth = stoi(words[1]);
        firewallStructure[position] = Firewall(depth);
        lastPosition = position;
    }
    unordered_map<int, Firewall> firewallStructureCopy = firewallStructure;
    int packetPosition = -1;
    int severity = 0;
    int delay = 0;
    while(true)
    {
        int packetPosition = -1;
        unordered_map<int, Firewall>::iterator find;
        
        for (auto & x : firewallStructure)
            x.second.skipBy(delay);

        while(packetPosition < lastPosition)
        {
            find = firewallStructure.find(packetPosition + 1);
            if (find != firewallStructure.end())
                if (find->second.colliding(0))
                    break;
            packetPosition++;
            for(auto & x : firewallStructure)
                x.second.step();
            
        }
        if (find->second.colliding(0))
        {
            if (delay % 1000 == 999)
                cout << delay << "\n";
            delay++;
            firewallStructure = firewallStructureCopy;
            continue;
        }
        break;
    }
    
    cout << "Delay: " << delay << endl;
    return 0;
}