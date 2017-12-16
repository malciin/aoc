#include <string>
#include <iostream>
using namespace std;

pair<int, int> score(const string & stream)
{
    int depth = 0;
    int score = 0;
    bool skip = false;
    int skipped = 0;
    for(int i = 0; i<stream.size(); i++)
    {
        if (stream[i] == '!')
        {
            i++;
            continue;
        }
        if (stream[i] == '>')
            skip = false;
        if (stream[i] == '<' && !skip)
        {
            skip = true;
            continue;
        }
        if (skip)
        {
            skipped++;
            continue;
        }
        if (stream[i] == ',')
            continue;
        if (stream[i] == '{')
            depth++;
        if (stream[i] == '}')
        {
            score += depth;
            depth--;
        }
    }
    return make_pair(score, skipped);
}

int main()
{
	string program;
    
    string line;
    getline(cin, line);
    
    cout << "Score: " << score(line).first << "\tSkipped: " << score(line).second << "\n";
    return 0;
}