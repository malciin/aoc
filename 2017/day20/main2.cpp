#include "../Helpers/Helpers.h"
#include <cmath>
#include <iterator>
using namespace std;

struct pos{
    int x;
    int y;
    int z;
    bool operator==(const pos &other) const
    { 
        return (x == other.x && y == other.y && z == other.z);
    }
};

struct particle{
    pos position;
    pos velocity;
    pos acceleration;
};

namespace std{
template<>
struct hash<pos>
{
    size_t operator()(const pos & x) const
    {
        return x.x * 73856093 ^ x.y * 19349663 ^ x.z * 83492791;
    }
};
};

long long distance3dManhattan(const pos & a)
{
    return labs(a.x) + labs(a.y) + labs(a.z);
}

int main()
{
	string line;
    queue<int> queueVal;
    vector<particle> particles;
    
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


    int howManySeconds = 500;
    int destroyed = 0;
    
    for(int i = 0; i<howManySeconds; i++)
    {
        vector<pos> toRemove;
        unordered_set<pos> collisions;
        for(auto & part : particles)
        {
            part.velocity.x += part.acceleration.x;
            part.velocity.y += part.acceleration.y;
            part.velocity.z += part.acceleration.z;
            part.position.x += part.velocity.x;
            part.position.y += part.velocity.y;
            part.position.z += part.velocity.z;
            
            if(collisions.find(part.position) == collisions.end())
                collisions.insert(part.position);
            else
                toRemove.push_back(part.position);
        }
        int removed = 0;
        
        for(int i = 0, n = particles.size(); i < n - removed; i++)
        {
            if (any_of(toRemove.begin(), toRemove.end(), [&](pos position){
                if (position == particles[i].position)
                    return true;
                return false;
            }))
            {
                swap(particles[i], particles[particles.size() - 1 - removed]);
                i--;
                removed++;
                continue;
         
            }
        }
        if (removed != 0)
            destroyed += removed;
            
    }

    auto min = distance(particles.begin(), min_element(particles.begin(), particles.end(), [](const particle & a, const particle & b){
        if(distance3dManhattan(a.position) < distance3dManhattan(b.position))
            return true;
        return false;
    }));

    cout << min << " Left: " << 1000 - destroyed;
}