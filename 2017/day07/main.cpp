// Shitty Way to solve that program. A lot of unnecessary computing
// Better approach is that we must noticed that the disc with the biggest whole weight is the bottom disc (XD)
// This simplify a lot! 
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <list>
using namespace std;
class Node
{
	int getChildWeight(Node * node)
	{
		int sum = 0;

		for(auto x : childrens)
			sum += x->getWeight();
		return sum;
	}
public:
    string name;
    int weight;
	list<Node *> childrens;
	
	int getWeight()
	{
		return weight + getChildWeight(this);
	}

	bool isBalanced()
	{
		int weight = 0;
		for(auto x : childrens)
		{
			if (weight == 0)
				weight = x->getWeight();
			else if (weight != x->getWeight())
				return false;
		}
		return true;
	}

	Node * getUnbalancedNode()
	{
		for(auto x : childrens)
		{
			if (!x->isBalanced())
				return x->getUnbalancedNode();
		}
		return this;
	}
};
class TreeContainer
{
	unordered_map<string, int> discs; // disc name with its weight
	unordered_map<string, list<string>> discChildrens;

	vector<string> split(const string & str)
	{
		typedef istream_iterator<string> stringIterator;
		typedef back_insert_iterator<vector<string>> vectorIterator;
		
		// Split the string by " "
		vector<string> words;
		vectorIterator insertIterator(words);
	
		istringstream buffer(str);
		stringIterator strIn(buffer);
	
		copy(strIn, stringIterator(), insertIterator);
		return words;
	}
public:
	TreeContainer() {}
	void parseLine(const string & line)
	{
		auto words = split(line);
		auto weight = stoi(string(words[1].begin() + 1, words[1].end()- 1));
			
		discs[words[0]] = weight;
		if (words.size() == 2)
			return;
		
		int i;
		for(i = 3; i<words.size() - 1; i++)
			discChildrens[words[0]].push_back(string(words[i].begin(), words[i].end()-1));			
		discChildrens[words[0]].push_back(string(words[i].begin(), words[i].end()));
	}

	Node * setRoot()
	{
        Node * root = nullptr;
        unordered_set<Node *> nodes;
        unordered_map<string, Node *> map;
        unordered_map<Node *, Node *> parentMap;

        for(auto x: discs)
        {
            Node * pt = new Node{x.first, x.second};
            if (root == nullptr)
                root = pt;
            map[x.first] = pt;
            nodes.insert(pt);
        }


        for(auto x: discChildrens)
        {
            for(auto child : x.second)
            {
                map[x.first]->childrens.push_back(map[child]);
                parentMap[map[child]] = map[x.first];
            }
        }

        while(parentMap[root] != nullptr)
        {
            root = parentMap[root];
		}
		return root;
	}

	void print()
	{
		cout << "Loaded " << discs.size() << "tokens\n";
		for(auto x : discs)
			cout << x.first << " (" << x.second << ")\n";

		for(auto x : discChildrens)
		{
			cout << x.first << " -> ";
			for(auto child : x.second)
				cout << child << " " ;
			cout << "\n";
		}
	}
};

int main()
{
	string line;

	TreeContainer treeContainer;	
	int sum = 0;
	while (getline(cin, line))
	{
		treeContainer.parseLine(line);
	}
	treeContainer.print();
	auto*pt = treeContainer.setRoot();
	if (pt != nullptr)
		cout << "Bottom program: " << pt->name << "\n";

	pt = pt->getUnbalancedNode();
	cout << pt << "unbalanced!\n";
	
	for(auto x : pt->childrens)
	{
		cout << x->name << "\tWeight:" << x->weight << "\tWholeDiscWeight: " << x->getWeight() << "\n";
	}

	return 0;
}