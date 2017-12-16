#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Naive? version. Just step circles
pair<int, int> steps(int n)	// return point coordinates
{
    int lastXPos, xPos, lastYPos, yPos, realXPos, realYPos;
    lastXPos = xPos = lastYPos = yPos = realXPos = realYPos = 0;
    bool xTravel = true;
    bool sign = false;

    int tick = 1;
    while(tick != n)
    {
        if (xTravel)
        {
            if (xPos <= lastXPos)
            {
                realXPos += sign ? -1 : 1;
                xPos++;
            }
                
            if (xPos > lastXPos)
            {
                xTravel = !xTravel;
                lastXPos = xPos;
                yPos = 0;
            }
        }
        else
        {
            if (yPos <= lastYPos)
            {
                realYPos += sign ? -1 : 1;
                yPos++;
            }
            if (yPos > lastYPos)
            {
                xTravel = !xTravel;
                lastYPos = yPos;
                xPos = 0;
                sign = !sign;
            }
        }
        tick++;
    }
    return make_pair(realXPos, realYPos);
    
}
int max(int a, int b, int c)
{
    int max = a;
    max = max < b ? b : max;
    return max < c ? c : max;
}

// Naive version - get the position from the step function, make 2D table
// and just add values around specific index
int generateTo(int value)
{
    vector<vector<int>> tab;
    tab.resize(50);
    for(int i = 0; i<50; i++)
        tab[i].resize(50);
    for(int i = 0; i<50; i++)
        for(int j = 0; j<50; j++)
            tab[i][j] = 0;

    pair<int, int> pos = make_pair(0, 0);
    tab[pos.second+25][pos.first+25] = 1;

    int tick = 1;
    while(tab[pos.second+25][pos.first+25] < value)
    {
        cout << tab[pos.second+25][pos.first+25] << "\n";
        tick++;
        pos = steps(tick);
        for(int i = -1; i<= 1; i++)
            for(int j = -1; j<= 1; j++)
            {
                if (i == 0 && j == 0)
                    continue;
                tab[pos.second+25][pos.first+25] += tab[pos.second+25+i][pos.first+25+j];
            }
    }
    return tab[pos.second+25][pos.first+25];
}

int main()
{
    int n = 2;
    auto position = steps(289326);
    int odleglosc = abs(position.first) + abs(position.second);
    cout << "Distance: " << odleglosc;
    cout << "\nGenerate to: " << generateTo(289326);

    return 0;
}