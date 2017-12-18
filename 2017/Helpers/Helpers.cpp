#include "Helpers.h"
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

};