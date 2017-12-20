#include "../Helpers/Helpers.h"
#include <cmath>
#include <iterator>
using namespace std;

struct pos{
    int x;
    int y;
    int z;
};

struct particle{
    pos position;
    pos velocity;
    pos acceleration;
};


long long distance3dManhattan(const pos & a)
{
    return labs(a.x) + labs(a.y) + labs(a.z);
}

int main()
{
	string line;
    vector<particle> particles;
    queue<int> queueVal;
    while(getline(cin, line))
    {
        auto it = line.begin();
        while(it != line.end())
        {
            while(!isdigit(*it) && *it != '-' && it != line.end())
                it++;
            if (it == line.end())
                break;
            auto itHelper = it;
            while(*itHelper != ',' && *itHelper != '>')
                itHelper++;

            string value(it, itHelper);
            queueVal.push(stoi(value));
            it = itHelper;
        }

        particle part;
        for(int i = 0; i<3; i++)
        {
            int x, y, z;
            x = queueVal.front(); queueVal.pop();
            y = queueVal.front(); queueVal.pop();
            z = queueVal.front(); queueVal.pop();
            switch(i)
            {
            case 0:
                part.position = {x,y,z};
                break;
            case 1:
                part.velocity = {x,y,z};
                break;
            case 2:
                part.acceleration = {x,y,z};
            }
        }
        if (!queueVal.empty())
            throw std::exception();

        particles.push_back(part);
        //cout << "p=<" << part.position.x << "," << part.position.y << "," << part.position.z << ">, ";
        //cout << "p=<" << part.velocity.x << "," << part.velocity.y << "," << part.velocity.z << ">, ";
        //cout << "p=<" << part.acceleration.x << "," << part.acceleration.y << "," << part.acceleration.z << ">, ";
    }

    auto min = distance(particles.begin(), min_element(particles.begin(), particles.end(), [](const particle & a, const particle & b){
        if (distance3dManhattan(a.acceleration) > distance3dManhattan(b.acceleration))
            return false;
        else if (distance3dManhattan(a.acceleration) < distance3dManhattan(b.acceleration))
            return true;
        if (distance3dManhattan(a.velocity) > distance3dManhattan(b.velocity))
            return false;
        else if (distance3dManhattan(a.velocity) < distance3dManhattan(b.velocity))
            return true;
        return false;
    }));
    cout << min << "\n\n";
}