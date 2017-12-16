#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>
#include <list>
using namespace std;

struct coords{
    int x;
    int y;
    int z;
};

void move (coords & xyz, const string & direction)
{
    if (direction == "n")
    {
        xyz.x++;
        xyz.z--;
    }
        
    else if (direction == "s")
    {
        xyz.x--;
        xyz.z++;
    }
        
    else if (direction == "ne")
    {
        xyz.y--;
        xyz.x++;
    }
        
    else if (direction == "sw")
    {
        xyz.y++;
        xyz.x--;
    }
        
    else if (direction == "se")
    {
        xyz.z++;
        xyz.y--;
    }
        
    else if (direction == "nw")
    {
        xyz.z--;
        xyz.y++;
    }
}



int setMaxDinstance(int & actualDistance, coords xyz)
{
    auto iabs = [](int a){
        return a < 0 ? (-a) : a;
    };
    actualDistance = actualDistance < iabs(xyz.x) ? iabs(xyz.x) : actualDistance;
    actualDistance = actualDistance < iabs(xyz.y) ? iabs(xyz.y) : actualDistance;
    actualDistance = actualDistance < iabs(xyz.z) ? iabs(xyz.z) : actualDistance;
}

int main()
{
    coords position {0,0,0};
    string directions;
    getline(cin, directions);

    auto begin = directions.begin();
    auto back = directions.begin();
    int maxDistance = 0;
    while(back != directions.end())
    {
        if (*back == ',' || *back == '\0')
        {
            //cout << string(begin, back) << " ";
            move(position, string(begin,back));
            setMaxDinstance(maxDistance, position);
            back++;
            begin = back;
            continue;
        }
        back++;
    }
    //cout << string(begin, back) << " ";
    move(position, string(begin,back));
    setMaxDinstance(maxDistance, position);

    cout << position.x << " " << position.y << " " << position.z << "\n";
    cout << "Max distance : " << maxDistance;
    return 0;
}