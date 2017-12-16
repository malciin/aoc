#include <iostream>
#include <algorithm>
using namespace std;
unsigned long long generator1()
{
    static long long value = 512;
    do{
        value = (value * 16807) % 2147483647;
    } while(value % 4 != 0);
    return value;
}
unsigned long long generator2()
{
    static long long value = 191;
    do{
        value = (value * 48271) % 2147483647;
    } while(value % 8 != 0);
    return value;
}

bool match16lastbit(unsigned long long val1, unsigned long long val2)
{
    for(int i = 0; i<16; i++)
    {
        if ((val1 & 1) != (val2 & 1))
            return false;
        val1 = val1 >> 1;
        val2 = val2 >> 1;
    }
    return true;
}

int main()
{
    int sameBits = 0;
    for(int i = 0; i<5000000; i++)
    {
        if (match16lastbit(generator1(), generator2()))
            sameBits++;
    }
    
    cout << sameBits;
}