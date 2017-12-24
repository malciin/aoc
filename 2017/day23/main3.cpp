/*
    PART2 - I rewrite input.txt code to be C++ code (look 'helper.txt' file), and after analize that algorithm and some computations
    I get that input.txt compute the number of not prime numbers from B to C, and I just simplify that
    algo
*/
#include "../Helpers/Helpers.h"
#include <cmath>
using namespace std;

bool isPrime (int num)
{
    if (num <=1)
        return false;
    else if (num == 2)         
        return true;
    else if (num % 2 == 0)
        return false;
    else
    {
        bool prime = true;
        int divisor = 3;
        double num_d = static_cast<double>(num);
        int upperLimit = static_cast<int>(sqrt(num_d) +1);
        
        while (divisor <= upperLimit)
        {
            if (num % divisor == 0)
                prime = false;
            divisor +=2;
        }
        return prime;
    }
}


int main()
{
    long long a,b,c,d,e,f,g,h;
    b = c = d = e = f = g = h = 0;
    a = 1;

    b = 109300;
    c = 126300;
    /* // Upper is equal below 
    c = b;
    if (a != 0){
        b = b * 100;
        b = b + 100000;			
        c = b;
        c = b + 17000;
    }
    */
    while(true){
        f = 1;
        d = 2;
        /*
        do {
            e = 2;       
            do {
                g = d;
                g = g * e;
                g = g - b;
                if (g == 0)
                    f = 0;
                e = e + 1;
                g = e;
                g = g - b;
            } while(g != 0);
            cout << "A:" <<  a << " B:" << b << " C:" << c << " D:" << d << " E:" << e << " F:" << f << " G:" << g << " H:" << h << "\n";
            
            d = d + 1;
            g = d;
            g = g - b;
            
        } while (g != 0);
        */
        if (!isPrime(b))
            h = h + 1;
            
        //cout << "A:" <<  a << " B:" << b << " C:" << c << " D:" << d << " E:" << e << " F:" << f << " G:" << g << " H:" << h << "\n";
        g = b;
        g = g - c;
        if ( g != 0)
            b = b + 17;
        else 
            break;
    }
    cout << h << "\n";
}