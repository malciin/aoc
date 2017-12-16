#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Day12
{
    vector<bool> discovered;
    const vector<list<int>> * connections;

    int bfs(int pos)
    {
        queue<int> toVisit;
        toVisit.push(pos);
        int currentProgram;
        int connectedPrograms = 0;
        while(!toVisit.empty())
        {
            currentProgram = toVisit.front(); 
            toVisit.pop();

            connectedPrograms++;

            for(auto x : (*connections)[currentProgram])
                if (discovered[x] == false)
                {
                    toVisit.push(x);
                    discovered[x] = true;
                }
        }
        return connectedPrograms;
    }
public:
    void operator()(const vector<list<int>> * _connections)
    {
        connections = _connections;
        discovered = vector<bool>(connections->size(), false);
        cout << "There is " << bfs(0) - 1 << " programs connected to 0 program\n";
        
        int c = 1;  // 1, because we already found one group!
        for(int i = 0; i<connections->size(); i++)
            if(discovered[i] == false)
            {
                c++;
                bfs(i);
            }
        cout << "There is " << c << " program groups!\n";
    }
};

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

int main()
{
    string line;

    vector<list<int>> connections(2000);
    
    while(getline(cin, line))
    {
        auto words = split(line);
        int program = stoi(words[0]);
        for(int i = 2; i<words.size(); i++)
        {
            if (words[i][words[i].size() - 1] == ',')
                words[i].resize(words[i].size() - 1);
            connections[program].push_back(stoi(words[i]));
        }
    }
    Day12 bfs;
    bfs(&connections);
    return 0;
}