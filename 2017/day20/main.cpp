/*
    PART ONE - FIND THE PARTICLES WITH MINIMAL ACCELERATION AND THEN SIMULATE ONLY THEM
*/
#include "../Helpers/Helpers.h"
#include <cmath>
using namespace std;

struct pos{
    int x;
    int y;
    int z;
    pos & operator += (const pos & oth)
    {
        x += oth.x;
        y += oth.y;
        z += oth.z;
        return *this;
    }

    pos operator * (const long long oth)
    {
        x *= oth;
        y *= oth;
        z *= oth;
        return *this;
    }
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

    // Parse file
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
            switch(i) {
            case 0:
                part.position = {x,y,z}; break;
            case 1:
                part.velocity = {x,y,z}; break;
            case 2:
                part.acceleration = {x,y,z};
            }
        }
        if (!queueVal.empty()) throw std::exception();
        particles.push_back(part);
    }
    // Parsing end

    // We find minimal acceleration value
    auto min = distance(particles.begin(), min_element(particles.begin(), particles.end(), [](const particle & a, const particle & b){
        if (distance3dManhattan(a.acceleration) < distance3dManhattan(b.acceleration))
            return true;
        return false;
    }));

    // We get indexes of all particles that have acceleration equal particles[min].acceleration
    vector<int> minimalIndexParts;
    for(int i = 0; i<particles.size(); i++)
        if (distance3dManhattan(particles[min].acceleration) == distance3dManhattan(particles[i].acceleration))
            minimalIndexParts.push_back(i);

    int howMuchStep = 1000; // adjust this
    for(auto x : minimalIndexParts)
    {
        // We set position of particles that have the minimum acceleration by formula for speed and position
        pos v0 = particles[x].velocity;
        pos s0 = particles[x].position;
        particles[x].velocity += particles[x].acceleration * howMuchStep;
        particles[x].position += particles[x].velocity * (howMuchStep/2) * howMuchStep;
        particles[x].position += v0 * howMuchStep;
    }

    // We now find the the closest particle to (0,0) from our minimals
    int minElement = minimalIndexParts[0];
    for(auto x : minimalIndexParts)
        if (distance3dManhattan(particles[x].position) < distance3dManhattan(particles[minElement].position))
            minElement = x;

    cout << minElement << "\n";
}