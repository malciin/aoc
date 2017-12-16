#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>
#include <list>

class KnotHasher{
    std::list<int> _list;
    std::list<int> _initialState;

    int skipSize;
    std::list<int>::iterator position;

    void iteratorIncr(std::list<int>::iterator & position, int howMuch = 1)
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
    void reverse(int length)
    {
        std::list<int>::iterator beginPosition = position;
        std::list<int>::iterator backPosition = position;
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
public:
    // Part2 Constructor
    KnotHasher()
    {
        for(int i = 0; i<256; i++)
            _list.push_back(i);
        _initialState = _list;
        skipSize = 0;
        position = _list.begin();
    }

    

    std::string operator()(const std::string& sequence)
    {
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
        
        std::string result;
        std::ostringstream sout;
        for(int i = 0; i<16; i++)
            sout << std::setfill('0') << std::setw(2)<< std::hex << (int)denseHash[i];
        result = sout.str();


        _list = _initialState;
        skipSize = 0;
        position = _list.begin();

        return result;
    }
};