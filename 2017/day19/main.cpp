/*
    PART ONE
*/
#include "../Helpers/Helpers.h"


using namespace std;
int main()
{
	string line;
    vector<string> maze;

    while(getline(cin, line))
        maze.push_back(line);

    pair<int, int> position;

    enum Direction{
        UP, DOWN, LEFT, RIGHT
    };
    Direction direction = Direction::DOWN;
    string visited;
    position.second = 0;
    for(int i = 0; i< maze[0].size(); i++)
        if (maze[0][i] == '|')
            position.first = i;
    int steps = 0;
    while(true)
    {
        
        //cout << "Pozycja: " << position.first << " " << position.second << ": " << maze[position.second][position.first] << "\n";
        steps++;
        if (maze[position.second][position.first] == '-' || maze[position.second][position.first] == '|' || isalpha(maze[position.second][position.first]))
        {
            if (isalpha(maze[position.second][position.first]))
                visited+= maze[position.second][position.first];
            switch (direction){
            case UP:
                position.second--;
                break;
            case DOWN:
                position.second++;
                break;
            case LEFT:
                position.first--;
                break;
            case RIGHT:
                position.first++;
                break;
            }
        }
        else if (maze[position.second][position.first] == '+')
        {
            if (direction <= 1)
            {
                if (maze[position.second][position.first-1] == '-' || maze[position.second][position.first-1] == '|'|| isalpha(maze[position.second][position.first-1]))
                {
                    direction = LEFT;
                    position.first--;
                }
                    
                else if (maze[position.second][position.first+1] == '-' || maze[position.second][position.first+1] == '|'|| isalpha(maze[position.second][position.first+1]))
                {
                    direction = RIGHT;
                    position.first++;
                }
                    
                else
                    break;
            }
            else
            {
                if (maze[position.second+1][position.first] == '-' || maze[position.second+1][position.first] == '|' || isalpha(maze[position.second+1][position.first]))
                {
                    direction = DOWN;
                    position.second++;
                }
                    
                else if (maze[position.second-1][position.first] == '-' || maze[position.second-1][position.first] == '|' || isalpha(maze[position.second-1][position.first]))
                {
                    direction = UP;
                    position.second--;
                }
                    
                else
                    break;
            }
        }
        else
        {
            steps--;
            break;
        }
            
        
    }
    cout << visited << " " << steps <<"\n";
    
}