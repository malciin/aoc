#include "../Helpers/Helpers.h"
#include <set>
using namespace std;

struct pairhash {
public:
    size_t operator()(const pair<int, int> &x) const
    {
        return (x.first << 16) + x.second;
    }
};

class Virus
{
    enum Direction{
        UP, RIGHT, DOWN, LEFT
    };
    int dir;
    unordered_set<pair<int, int>, pairhash> weakened;
    unordered_set<pair<int, int>, pairhash> infected;
    unordered_set<pair<int, int>, pairhash> flagged;

    pair<int, int> position;    // first is y pos, second is x pos
    int infectionBurst;
public:
    Virus()
    {
        position = make_pair(0,0);
        dir = UP;
        infectionBurst = 0;
    }

    void setMap(const vector<string> & map)
    {
        int middle = (map.size() + 1)/2 - 1;
        for(int i = 0; i<map.size(); i++)
            for(int j = 0; j<map[0].size(); j++)
            {
                if (map[i][j] == '#')
                    infected.insert(make_pair(i-middle, j-middle));
            }
    }

    int getInfectionBurst()
    {
        return infectionBurst;
    }

    inline void activate()
    {
        // If node is weakened
        if(weakened.find(position) != weakened.end())
        {
            weakened.erase(position);
            infected.insert(position);
            infectionBurst++;
        }
        // If node is infected
        else if(infected.find(position) != infected.end())
        {
            dir++;
            if(dir > 3)
                dir = 0;
            infected.erase(position);
            flagged.insert(position);
        }
        // If node is flagged
        else if(flagged.find(position) != flagged.end())
        {
            flagged.erase(position);
            dir -= 2;
            if (dir < 0)
                dir += 4;
        }
        // Node is clean
        else
        {
            dir--;
            if (dir < 0)
                dir = 3;
            weakened.insert(position);
        }
        switch(dir)
        {
        case UP:
            position.first--;
            break;
        case DOWN:
            position.first++;
            break;
        case LEFT:
            position.second--;
            break;
        case RIGHT:
            position.second++;
            break;
        }
    }
};

int main()
{
    vector<string> map;
	string line;

    // Parse file
    while(getline(cin, line))
        map.push_back(line);
    
    // Parse ended
    Virus virus;
    virus.setMap(map);

    aoc::measureTimeMS();
    for(int i = 0; i<10000000; i++)
        virus.activate();
        
    int time = aoc::measureTimeMS();
        
    cout << "After: " << time << "ms\n"; 
    cout << "Part2: " << virus.getInfectionBurst() << "\n";
}