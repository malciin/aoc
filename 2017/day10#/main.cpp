#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>
#include <list>
using namespace std;

class Z10Container{
    list<int> _list;

    int skipSize;
    list<int>::iterator position;

    void iteratorIncr(list<int>::iterator & position, int howMuch = 1)
    {
        if (abs(howMuch) > _list.size())
            throw std::logic_error("Cannot decrement more than list size");
        
        if (howMuch > 0)
        for(int i = 0; i<howMuch; i++)
        {
            position++;
            if (position == _list.end())
                position = _list.begin();
        }

        else
        for(int i = 0; i>howMuch; i--)
        {
            if (position == _list.begin())
            {
                position = _list.end();
                position--;
                continue;
            }
            position--;                
        }
    }

public:
    // Part2 Constructor
    Z10Container()
    {
        skipSize = 0;
        position = _list.begin();
    }

    // Part1 constructor
    Z10Container(int size)
    {
        for(int i = 0; i<size; i++)
            _list.push_back(i);
        skipSize = 0;
        position = _list.begin();
    }

    void reverse(int length)
    {
        list<int>::iterator beginPosition = position;
        list<int>::iterator backPosition = position;
        
        iteratorIncr(backPosition, length - 1);
        
        for(int i = 0, n = length/2; i<n; i++)
        {
            //std::swap(*position, *backPosition);
            int temp = *backPosition;
            //cout << "Zamieniam wartosc " << *position << " z " << *backPosition << "\n";
            *backPosition = *position;
            *position = temp;
            iteratorIncr(position);
            iteratorIncr(backPosition, -1);
        }

        position = beginPosition;
        iteratorIncr(position, length);
        int skipped = 0;
        while(skipped < skipSize)
        {
            skipped++;
            iteratorIncr(position);
        }


        skipSize++;
    }
    void print()
    {
        for(auto x : _list)
            cout << x << " ";
        cout << "\n";
    }

    int z2()
    {
        auto it = _list.begin();
        return *it * (*(++it));
    }

    void hash(const string& sequence)
    {
        cout << "Sequence: ";
        for(int i = 0; i<sequence.size(); i++)
            cout << (int)sequence[i] << ", ";
        cout << "17, 31, 73, 47, 23\n";
        for(int i = 0; i<64; i++)
        {
            for(int j = 0; j<sequence.size(); j++)
                reverse(sequence[j]);
            reverse(17);
            reverse(31);
            reverse(73);
            reverse(47);
            reverse(23);
        }
        
        unsigned char denseHash[16];
        for(int i = 0; i<16; i++)
            denseHash[i] = 0;
        
        int i, j, k = 0;
        auto it = _list.begin();
        
        for(i = 0; i<256; i+=16, k++)
            for(j = 0; j<16; j++, it++)
            {
                denseHash[k] ^= *it;
            }
                
        for(int i = 0; i<16; i++)
            // cout << hex << (int)denseHash[i]; (!) WRONG! SPENT 2H DEBUG THAT!!!!!!
            // if hex is like 0x0a (first 4 bits are equal 0) then cout will print it 'a' not '0a'
            cout << setfill('0') << setw(2)<< hex << (int)denseHash[i];
    }
};

int main()
{
    string howMuch;

    /*
    Z10Container list(256);

    while(cin >> howMuch)
    {
        list.reverse(stoi(howMuch));
        cout << stoi(howMuch) << " ";
    }
    cout << endl;
    cout << list.z2();
    */
    Z10Container list(256);
    unsigned char a;
    string str;
    while(cin >> a)
        str += a;
    list.hash(str);
    return 0;
}