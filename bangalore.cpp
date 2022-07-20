#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define edge pair<int, int>
string cities[12] = {"Basavanagudi", "IndiraNagar", "Jayanagar", "Koromangala", "Malleshwaram", "RajajiNagar", "FrazerTown", "SadashivaNagar", "HSRLayout", "BTMLayout", "Bellandur", "WilsonGarden"};
// string cities[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
class Graph
{
private:
    vector<pair<int, edge>> CITY;
    vector<pair<int, edge>> MST;
    int *cycle_checker;
    int V;
    vector<int> *adj;
    vector<string> path;
    int Find_City(int i);
    void Union_City(int u, int v);
    void DFS();
    void DFS1(int s, vector<bool> &visited);
    void kruskal();
    void makeGraph();
    int minimum_cost();
    void print();
    void pAdjMst();
    void Path();

public:
    Graph(int V);
    void AddCity(int u, int v, int w);
    void Kruskal()
    {
        kruskal();
    }
    void PrintMst()
    {
        print();
    }
    int Minimum_cost()
    {
        return minimum_cost();
    }
    void PathOfCities()
    {
        Path();
    }
    void PrintAdjMst()
    {
        pAdjMst();
    }
};
Graph::Graph(int V)
{
    this->V = V;
    cycle_checker = new int[V];
    adj = new vector<int>[V];
    for (int i = 0; i < V; i++)
        cycle_checker[i] = i;
    CITY.clear();
    MST.clear();
}
void Graph::AddCity(int u, int v, int w)
{
    CITY.push_back(make_pair(w, edge(u, v)));
}
int Graph::Find_City(int i)
{
    if (i == cycle_checker[i])
        return i;
    else
        return Find_City(cycle_checker[i]);
}

void Graph::Union_City(int u, int v)
{
    cycle_checker[u] = cycle_checker[v];
}
void Graph::kruskal()
{
    int i, u, v;
    sort(CITY.begin(), CITY.end());
    for (i = 0; i < CITY.size(); i++)
    {
        u = Find_City(CITY[i].second.first);
        v = Find_City(CITY[i].second.second);
        if (u != v)
        {
            MST.push_back(CITY[i]);
            Union_City(u, v);
        }
    }
    makeGraph();
}

void Graph::print()
{
    cout << "\n\n\n";
    cout << "Edge :"
         << " Weight" << endl;
    for (int i = 0; i < MST.size(); i++)
    {
        cout << cities[MST[i].second.first] << " - " << cities[MST[i].second.second] << " : "
             << MST[i].first;
        cout << endl;
    }
}
int Graph::minimum_cost()
{
    int sum = 0;
    for (int i = 0; i < MST.size(); i++)
    {
        sum += MST[i].first;
    }
    return sum;
}
void Graph::makeGraph()
{
    for (int i = 0; i < MST.size(); i++)
    {
        int u = MST[i].second.first;
        int v = MST[i].second.second;
        adj[u].push_back(v);
    }
}
void Graph::pAdjMst()
{
    cout << "v =" << V << endl;
    for (int i = 0; i < V; i++)
    {
        cout << "i outside " << i << endl;
        for (int j = 0; j < adj[i].size(); j++)
        {
            cout << "i---" << i << "--" << adj[i][j] << " ";
        }
        cout << endl;
    }
}
void Graph::DFS1(int s, vector<bool> &visited)
{
    stack<int> stack;
    stack.push(s);
    while (!stack.empty())
    {
        int s = stack.top();
        stack.pop();
        if (!visited[s])
        {
            path.push_back(cities[s]);
            visited[s] = true;
        }
        for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
            if (!visited[*i])
                stack.push(*i);
    }
}
void Graph::DFS()
{
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++)
        if (!visited[i])
            DFS1(i, visited);
}
void Graph::Path()
{
    DFS();
    ofstream MyFile("ans.txt");
    MyFile << "\t\t\t\t\t\t\t\t\tPATH FOR THE TRAVEL ::\n\n";

    for (int i = 0; i < V; i++)
    {
        if (i == V - 3)
        {
            cout << endl;
            cout << endl;
            MyFile << "\n\n";
        }
        if (i % 5 == 0 && i != V - 2)
        {
            cout << endl;
            cout << endl;
            MyFile << "\n\n";
        }
        if (i == V - 2)
        {
            cout << path[i + 1];
            MyFile << path[i + 1];
        }
        else if (i == V - 1)
        {
        }
        else if (i == V / 2)
        {
            cout << path[V - 2] << "---->" << path[i] << "---->";
            MyFile << path[V - 2] << "---->" << path[i] << "---->";
        }
        else
        {
            cout << path[i] << "---->";
            MyFile << path[i] << "---->";
        }
        // if (i == 0)
        // {
        //     cout << path[i] << "----->";
        // }
        // else if (i != V - 1 && i % 5 != 0)
        //     cout << path[i] << "----->";
        // else if (i % 5 == 0 && i != 0)
        // {
        //     cout << "\n\n"
        //          << path[i] << "----->";
        // }
        // else
        //     cout << path[i];
    }
    MyFile << "\n\n **********************This is the Travel Path*************************";
    MyFile.close();
}

int main()
{
    // fstream f;
    cout << ifstream("startPage.txt").rdbuf();
    cout << endl;
    cout << "\n\t\t\t******************* TOUR PLANNER FOR BANGLORE CITY ***********************\t\t\n";
    Graph g(12);
    cout << ifstream("node.txt").rdbuf();
    g.AddCity(0, 1, 6);
    g.AddCity(0, 2, 6);
    g.AddCity(0, 3, 6);
    g.AddCity(1, 2, 1);
    g.AddCity(1, 4, 2);
    g.AddCity(2, 3, 2);
    g.AddCity(2, 4, 7);
    g.AddCity(2, 6, 2);
    g.AddCity(4, 5, 4);
    g.AddCity(5, 6, 11);
    g.AddCity(5, 7, 10);
    g.AddCity(6, 8, 2);
    g.AddCity(7, 6, 22);
    g.AddCity(7, 8, 12);
    g.AddCity(7, 10, 25);
    g.AddCity(10, 11, 3);
    g.AddCity(10, 8, 16);
    g.AddCity(8, 9, 1);
    g.AddCity(3, 9, 18);
    g.AddCity(9, 11, 8);
    g.Kruskal();
    cout << endl;
    //
    int n = 1, a;
    while (n == 1)
    {
        cout << "\n\n1 DISPLAY LIST OF CITIES\n2 PRINT MINIMUM SPANNING TREE \n3 DISPlAY PATH \n4 MINIMUM COST \n5 Display ALL \nEnter : ";
        cin >> a;
        switch (a)
        {
        case 1:
            cout << "\n\n LIST OF CITIES :\n";
            for (int i = 0; i < 9; i++)
            {
                cout << i + 1 << " " << cities[i] << endl;
            }
            break;
        case 2:
            g.PrintMst();
            break;

        case 3:
            cout << "\n\n\nMINIMUM COST TO COVER ALL THE CITIES :: \t " << g.Minimum_cost();
            cout << endl;
            cout << endl;
            cout << "PATH FOR THE TRAVEL ::\n\n";
            g.PathOfCities();
            break;
        case 4:
            cout << "\n\n\nMINIMUM COST TO COVER ALL THE CITIES :: \t " << g.Minimum_cost();
            cout << endl;
            cout << endl;
            break;
        case 5:
            g.PrintMst();
            cout << endl;
            cout << endl;
            cout << "\n\n\nMINIMUM COST TO COVER ALL THE CITIES :: \t " << g.Minimum_cost();
            cout << endl;
            cout << endl;
            cout << "PATH FOR THE TRAVEL ::\n\n";
            g.PathOfCities();
            break;
        }

        cout << "\n\nEnter 1 to continue 0 to exit \n\n";
        cin >> n;
    }
    cout << endl;
    cout << ifstream("exitPage.txt").rdbuf();

    return 0;
}
