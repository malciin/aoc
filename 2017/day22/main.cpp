#include "../Helpers/Helpers.h"
using namespace std;

class Virus
{
    enum Direction{
        UP, RIGHT, DOWN, LEFT
    };
    int dir;
    set<pair<int, int>> infected;
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

    void activate()
    {
        if(infected.find(position) != infected.end())
        {
            dir++;
            if(dir > 3)
                dir = 0;
            infected.erase(position);
        }
        else
        {
            dir--;
            if (dir < 0)
                dir = 3;
            infected.insert(position);
            infectionBurst++;
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

    for(int i = 0; i<10000; i++)
        virus.activate();
        
    cout << "Part1: " << virus.getInfectionBurst() << "\n";
}