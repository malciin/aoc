#include <iostream>
#include "Helpers.h"
using namespace std;
int main()
{
    string a("hanna, mala, jest, hehe");
    auto res = h::split(a, " ");
    for(auto x : res)
        cout << x << "\n";
}