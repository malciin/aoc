#include "KnotHash.h"
#include <algorithm>
using namespace std;
#include <queue>

const char* hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch(c)
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'a': return "1010";
        case 'b': return "1011";
        case 'c': return "1100";
        case 'd': return "1101";
        case 'e': return "1110";
        case 'f': return "1111";
    }
}

void printDisk(const vector<vector<bool>> & disk)
{
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            if (disk[i][j])
                cout << "#";
            else
            cout << ".";
        }
        cout << "\n";
    }
}


int regions(vector<vector<bool>> disk)
{
    auto validate = [](const pair<int, int> & pos){
        if (pos.first < 0 || pos.second < 0 || pos.first >= 128 || pos.second >= 128)
            return false;
        return true;
    };
    int numberRegions = 0;
    queue<pair<int, int>> toVisit;
    for(int i = 0; i < disk.size(); i++)
    {
        cout << i << "\n";
        for(int j = 0; j<disk.size(); j++)
        {
            if (disk[i][j])
            {
                numberRegions++;
                disk[i][j] = false;
                toVisit.push(make_pair(i, j));
            }
                
            while(!toVisit.empty())
            {
                auto currentPos = toVisit.front();
                toVisit.pop();
                for(int k = -1; k<=1; k+=1)
                {
                    auto pair = make_pair(currentPos.first + k, currentPos.second);
                    if (validate(pair))
                    {
                        if (disk[pair.first][pair.second])
                            toVisit.push(pair);
                        disk[pair.first][pair.second] = false;
                    }
                    pair = make_pair(currentPos.first, currentPos.second + k);
                    if (validate(pair))
                    {
                        if (disk[pair.first][pair.second])
                            toVisit.push(pair);
                        disk[pair.first][pair.second] = false;
                    }
                }
            }
        }
    }
    return numberRegions;
}



int main()
{
    KnotHasher knotHash;
    vector<vector<bool>> disk(128);
    for(auto & x:disk)
        x.resize(128,false);
    
    string inputHash("hfdlxzhv");
    for(int i = 0; i<128; i++)
    {
        auto hash = knotHash(inputHash + "-" + to_string(i));
        
        for(int j = 0; j<32; j++)
        {
            auto * bits = hex_char_to_bin(hash[j]);
            for(int k = 0; k<4; k++)
                if (bits[k] == '1')
                    disk[i][j*4 + k] = true;
        }
    }
    int used = 0;
    for(auto & row : disk)
        for_each(row.begin(), row.end(), [&](bool a){if (a) used++;});
    cout << used << " Regions: " << regions(disk) << "\n";

}