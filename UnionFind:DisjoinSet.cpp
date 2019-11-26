#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class UF
{
private:
    unordered_map<char, pair<char, int>> nodes;
    int size;

public:
    UF(vector<char> list)
    {
        for (auto i : list)
            nodes[i] = pair<char, int>(i, 1);
        size = list.size();
    }

    int getSize();
    void print();
    char find(char c);
    void unify(char a, char b);
};

int UF::getSize()
{
    return size;
}

void UF::print()
{
    for (auto n : nodes)
    {
        cout << "root: " << n.first << " is mapped to " << n.second.first << " w/ size of nodes " << n.second.second << endl;
    }
}

char UF::find(char c)
{
    if (nodes.find(c) == nodes.end())
    {
        return '-';
    }
    if (c == nodes[c].second)
    {
        return c;
    }

    //get root
    auto temp = c;
    while (temp != nodes[temp].first)
    {
        temp = nodes[temp].first;
    }

    auto root = nodes[temp].first;

    //path compression
    auto temp2 = c;
    while (temp2 != root)
    {
        temp2 = nodes[temp2].first;
        nodes[temp2] = pair<char, int>(root, nodes[temp2].second);
    }

    return root;
}

void UF::unify(char a, char b)
{
    if (nodes.find(a) == nodes.end() || nodes.find(b) == nodes.end())
    {
        cout << "one is undefined" << endl;
        return;
    }

    auto root1 = find(a);
    auto root2 = find(b);

    if (nodes[root1].second > nodes[root2].second)
    {
        nodes[root2].first = root1;
        nodes[root1].second += nodes[root2].second;
    }
    else
    {
        nodes[root1].first = root2;
        nodes[root2].second += nodes[root1].second;
    }
}

int main()
{
    unordered_map<char, pair<char, int>> nodes;
    vector<char> list = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    UF uf(list);
    uf.print();
    cout << "Found from f, root->" << uf.find('f') << endl;
    uf.unify('a', 'b');
    uf.unify('b', 'd');
    uf.unify('g', 'f');
    uf.unify('g', 'a');
    cout << "Found from a, root->" << uf.find('a') << endl;
    uf.print();
}
