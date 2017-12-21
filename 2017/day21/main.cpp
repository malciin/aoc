#include "../Helpers/Helpers.h"
using namespace std;

// Rotate the current martix
void rotate90(vector<string> & str)
{
    vector<string> newStr = str;
    for(int i = str.size()-1, iInsert = 0; i>=0; i--, iInsert++)
        for(int j = 0, jInsert= 0; j < str.size(); j++, jInsert++)
            newStr[iInsert][jInsert] = str[j][i];
    str = newStr;
}

// Flip the current matrix
void flip(vector<string> & str)
{
    for(int i = 0, n = (str.size()-1)/2; i<=n; i++)
        swap(str[i], str[str.size() - 1 - i]);
}

// Test if 'a' matrix is rotated and/or flipped 'b' matrix
bool same(const vector<string> & a, vector<string> b)
{
    for(int i = 0; i<4; i++){
        if (a == b)
            return true;
        flip(b);
        if (a == b)
            return true;
        flip(b);
        rotate90(b);
    }
    return false;
}

// Main iteratate funcion
void iterate(vector<string> & pattern, const vector<pair<vector<string>, vector<string>>> & input)
{
    vector<string> newPattern;
    int size;
    pattern.size() % 2 == 0 ? size = 2 : size = 3; 

    // Compute the size of newPattern
    newPattern.resize(pattern.size() + pattern.size() / size);
    for(auto & x : newPattern)
        x.resize(pattern.size() + pattern.size() / size);
    
    //cout << "New pattern will be : " << pattern.size() + pattern.size()/ size << "x" << pattern.size() + pattern.size() / size << "\n";

    // For each square
    for(int i = 0; i<pattern.size() / size; i++)
    {
        for(int j = 0; j<pattern.size() / size; j++)
        {
            vector<string> square;
            
            // Get square matrix
            for(int k = 0; k<size; k++)
            {
                string row(pattern[i*size + k].begin()+=(j*size), pattern[i*size + k].begin()+=(j*size + size));
                square.push_back(row);
            }

            // Find the new corresponding matrix to our oryginal square matrix
            for(int k = 0; k<input.size(); k++) 
            {
                if (same(square, input[k].first))
                {
                    square = input[k].second;
                    break;
                }
                if (k == input.size() - 1)
                    throw std::exception();
            }

            // Insert the our new matrix to our map
            for(int x = 0; x<square.size(); x++)
            {
                for(int y = 0; y<square.size(); y++)
                {
                    newPattern[x + i * square.size()][y + j * square.size()] = square[x][y];
                }
            }
        }
    }
    pattern = newPattern;
}

int computePixels(const vector<string> & map)
{
    int x = 0;
    for(auto & line : map)
        for_each(line.begin(), line.end(), [&](char ch){
            if (ch == '#') 
                x++;
        });
    return x;
}

int main()
{
	string line;
    vector<pair<vector<string>, vector<string>>> input;

    // Parse file
    while(getline(cin, line))
    {
        auto splitted = aoc::split(line, " ");
        auto req = aoc::split(splitted[0], '/');
        auto res = aoc::split(splitted[2], '/');
        input.push_back(make_pair(req, res));
    }
    // Parse ended
    vector<string> map;
    map.push_back(".#.");
    map.push_back("..#");
    map.push_back("###");

    for(int i = 0; i < 18; i++)
    {
        iterate(map, input);
        if (i == 4)
            cout << "After 5 iterations: " << computePixels(map) << " pixels\n";
    }
        
    
    cout << "After 18 iterations: " << computePixels(map) << " pixels\n";
}