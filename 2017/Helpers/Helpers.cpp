#include "Helpers.h"
#include <chrono>
using namespace std;
namespace aoc{

vector<string> split(const string & str, const string & splitBy)
{
    vector<string> result;
    auto it = str.cbegin();
    string::const_iterator itHelper;
    string::const_iterator itSplit;
    while(it != str.end())
    {
        itHelper = it;
        while(*itHelper != splitBy[0] && itHelper != str.end())
        {
            itHelper++;
        }
        result.push_back(string(it, itHelper));

        it = itHelper;
        itSplit = splitBy.begin();
        while (it!=str.end() && itSplit != splitBy.end())
        {
            it++;
            itSplit++;
        }
            
    }
    return result;
}

vector<string> split(const string & str, const char splitBy)
{
    string _splitBy;
    _splitBy += splitBy;
    return split(str, _splitBy);
}

int measureTimeMS()
{
    static chrono::steady_clock::time_point start, end;
    start = end;
    end = chrono::steady_clock::now();


    chrono::duration<float> elapsedD = end - start;
    chrono::milliseconds elapsed = chrono::duration_cast<chrono::milliseconds>(elapsedD);

    return elapsed.count();
}

int measureTimeUS()
{
    static chrono::steady_clock::time_point start, end;
    start = end;
    end = std::chrono::steady_clock::now();


    chrono::duration<float> elapsedD = end - start;
    chrono::microseconds elapsed = chrono::duration_cast<chrono::microseconds>(elapsedD);

    return elapsed.count();
}

};