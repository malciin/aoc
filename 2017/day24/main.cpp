/*
    BOTH PART1 AND PART2 - BRUTEFORCE - TOOK ~6 seconds to compute the result
*/
#include "../Helpers/Helpers.h"
#include <stack>
using namespace std;
typedef pair<int, int> part;

void generateBridges(const vector<part> & parts)
{
    struct Bridge{
        list<part> bridge;
        vector<bool> used;
        int strength;
    };

    vector<bool> used;
    for(auto x : parts)
        used.push_back(false);



    stack<Bridge> buildingBridges;
    vector<Bridge> readyBridges;
    for(int i = 0; i< parts.size(); i++)
    {
        if (parts[i].first == 0)
        {
            Bridge newBridge;
            newBridge.used = used;
            newBridge.used[i] = true;
            newBridge.bridge.push_back(parts[i]);
            newBridge.strength = parts[i].first + parts[i].second;
            buildingBridges.push(newBridge);
        }
    }
    while(!buildingBridges.empty())
    {
        auto currentBridge = buildingBridges.top(); buildingBridges.pop();
        bool readyBridge = true;
        for(int i = 0; i<parts.size(); i++)
        {
            if(!currentBridge.used[i])
            {
                if (currentBridge.bridge.back().second == parts[i].first)
                {
                    auto newBridge = currentBridge;
                    readyBridge = false;
                    newBridge.bridge.push_back(parts[i]);
                    newBridge.used[i] = true;
                    newBridge.strength += parts[i].first + parts[i].second;
                    buildingBridges.push(newBridge);
                }
                else if (currentBridge.bridge.back().second == parts[i].second)
                {
                    auto newBridge = currentBridge;
                    readyBridge = false;
                    newBridge.bridge.push_back(make_pair(parts[i].second, parts[i].first));
                    newBridge.used[i] = true;
                    newBridge.strength += parts[i].first + parts[i].second;
                    buildingBridges.push(newBridge);
                }
            }
        }
        if (readyBridge)
            readyBridges.push_back(currentBridge);
    }

    cout << readyBridges.size() << " generated bridges!\n";
    
    auto & max = *max_element(readyBridges.begin(), readyBridges.end(), [](const Bridge & max, const Bridge & newBr){ 
        if (newBr.strength > max.strength) 
            return true; 
        return false;
    });

    cout << "Max strength bridge: " << max.strength << " with the long of " << max.bridge.size() << "\n";


    for(auto & bridge : readyBridges)
    {
        if (max.bridge.size() < bridge.bridge.size())
            max = bridge;
        else if (max.bridge.size() == bridge.bridge.size())
        {
            if (max.strength < bridge.strength)
                 max = bridge;
        }
    }
    cout << "Longest bridge have " << max.bridge.size() << " elements with " << max.strength << " strength!\n";
}

int main()
{
    
	string line;
    vector<part> parts;
    while(getline(cin, line))
    {
        auto splitted = aoc::split(line, '/');
        parts.push_back(make_pair(stoi(splitted[0]), stoi(splitted[1])));
    }

    generateBridges(parts);
    
}