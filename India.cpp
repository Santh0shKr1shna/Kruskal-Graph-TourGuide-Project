#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define edge pair<int, int>
string cities[9] = {"Chennai", "Mumbai", "New Delhi", "Kochi", "Kolkata", "Bengaluru", "Hyderabad", "Ahmedabad", "Lucknow"};
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
    void findRoute();
    void makeGraph();
    int minimum_cost();
    void print();
    void pAdjMst();
    void Path();

public:
    Graph(int V);
    void AddCity(int u, int v, int w);
    void FindRoute()
    {
        findRoute();
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
void Graph::findRoute()
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
    cout << "\n\n\tEdge \t\t\t:"
         << "\t\tWeight" << endl;
    cout << "\n";
    for (int i = 0; i < MST.size(); i++)
    {
        cout << cities[MST[i].second.first] << " - " << cities[MST[i].second.second] << " \t\t:\t\t"
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
        if (i % 5 == 0)
        {
            cout << "\n\n";
            MyFile << "\n\n";
        }
        if (i == V - 1)
        {
            cout << path[i];
            MyFile << path[i];
        }
        else if (i == V - 2)
        {
        }
        else if (i == 1)
        {
            cout << path[V - 2] << "------>" << path[i] << "------>";
            MyFile << path[V - 2] << "------>" << path[i] << "------>";
        }
        else
        {
            cout << path[i] << "------>";
            MyFile << path[i] << "------>";
        }
    }
    MyFile << "\n\n\n\n \t\t\t\t\t\t\t\t\tThis is the Travel Path";
    MyFile.close();
}

int main()
{
    // fstream f;
    cout << ifstream("startPage.txt").rdbuf();
    cout << endl;
    cout << ifstream("node1.txt").rdbuf();
    cout << endl;
    cout << "\n\t\t\t******************* TOUR PLANNER FOR INDIAN CITIES ***********************\t\t\n";
    Graph g(9);
    g.AddCity(0, 1, 1030);
    g.AddCity(0, 2, 1750);
    g.AddCity(0, 3, 550);
    g.AddCity(0, 4, 1360);
    g.AddCity(0, 5, 280);
    g.AddCity(0, 6, 510);
    g.AddCity(0, 7, 1370);
    g.AddCity(0, 8, 1530);
    g.AddCity(1, 2, 1160);
    g.AddCity(1, 3, 1070);
    g.AddCity(1, 4, 1660);
    g.AddCity(1, 5, 840);
    g.AddCity(1, 6, 630);
    g.AddCity(1, 7, 450);
    g.AddCity(1, 8, 1210);
    g.AddCity(2, 3, 2080);
    g.AddCity(2, 4, 1300);
    g.AddCity(2, 5, 1740);
    g.AddCity(2, 6, 1260);
    g.AddCity(2, 7, 780);
    g.AddCity(2, 8, 420);
    g.AddCity(3, 4, 1900);
    g.AddCity(3, 5, 370);
    g.AddCity(3, 6, 860);
    g.AddCity(3, 7, 1500);
    g.AddCity(3, 8, 1940);
    g.AddCity(4, 5, 1560);
    g.AddCity(4, 6, 1180);
    g.AddCity(4, 7, 1620);
    g.AddCity(4, 8, 890);
    g.AddCity(5, 6, 500);
    g.AddCity(5, 6, 1230);
    g.AddCity(5, 6, 1580);
    g.AddCity(6, 7, 880);
    g.AddCity(6, 8, 1080);
    g.AddCity(7, 8, 940);
    g.FindRoute();
    cout << endl;
    // g.PrintMst();
    // cout << endl;
    // cout << "\n\n\nMINIMUM COST TO COVER ALL THE CITIES :: \t " << g.Minimum_cost();
    // cout << endl;
    // cout << endl;
    // cout << "PATH FOR THE TRAVEL ::\n\n";
    // g.PathOfCities();
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
