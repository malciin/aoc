// Just notice that 0 ALWAYS be at the first position!!
#include <iostream>
using namespace std;
int main()
{
    const int puzzle = 394;
    int listSize = 1;
    int position = 0;
    int afterZero;
    int skipSize;
    while(listSize != 50000000)
    {
        skipSize = puzzle % listSize;
        position += skipSize;
        if (position >= listSize)
            position -= listSize;

        if (position == 0)
            afterZero = listSize;
        position++; // added value is now our position so we increment the position
        listSize++;
        
    }
    cout << "After zero is " << afterZero << "!\n";
}