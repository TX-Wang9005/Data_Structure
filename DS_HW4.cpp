#include <iostream>

using namespace std;

class Node
{
    friend class Graph;

public:
    Node(int value, int price, int air)
    {
        city = value;
        airline = air;
        cost = price;
        next = NULL;
    }

private:
    int city;
    int cost;
    int airline;
    Node *next;
};

class Graph
{
public:
    Graph(int number)
    {
        N = number;
        head = new Node *[N];
        for (int i = 0; i < N; i++)
        {
            head[i] = NULL;
        }
        visited = new bool[N];
    }
    void Add(int src, int dst, int cost, int airline);
    void Request(int src, int dst, int price);
    int DFS(int vertex, int dst, int price, int airline);
    void Delete(int src, int dst, int airline);

private:
    Node **head;
    int N;
    bool *visited;
    int maxprice;
};

void Graph::Add(int src, int dst, int cost, int airline)
{
    Node *currentNode = head[src];
    Node *preNode;
    Node *newNode = new Node(dst, cost, airline);

    while (currentNode != NULL)
    {
        if (currentNode->city == dst && currentNode->airline == airline)
        {
            if (currentNode->cost > newNode->cost)
                currentNode->cost = cost;
            return;
        }
        currentNode = currentNode->next;
    }
    newNode->next = head[src];
    head[src] = newNode;
}

void Graph::Delete(int src, int dst, int airline)
{
    Node *currentNode;
    Node *preNode = NULL;

    currentNode = head[src];
    while (currentNode != NULL)
    {
        if (currentNode->city == dst && currentNode->airline == airline)
        {
            if (preNode == NULL)
            {
                head[src] = currentNode->next;
            }
            else
            {
                preNode->next = currentNode->next;
            }
            delete currentNode;
            currentNode = preNode;
        }
        preNode = currentNode;
        if (currentNode == NULL)
            currentNode = head[src];
        else
            currentNode = currentNode->next;
    }
}
void Graph::Request(int src, int dst, int price)
{
    int ans;

    for (int i = 0; i < N; i++)
    {
        visited[i] = false;
    }
    maxprice = -1;
    ans = DFS(src, dst, price, -1);
    if (ans == -1)
        cout << -1 << endl;
    else
        cout << ans << endl;
}
int Graph::DFS(int vertex, int dst, int price, int lastairline)
{
    Node *currentNode = head[vertex];
    int edgecost;
    int cost;
    int minprice = -1;

    if (vertex == dst)
    {
        if (price >= maxprice)
            maxprice = price;
        return 0;
    }

    visited[vertex] = true;
    while (currentNode != NULL)
    {
        if (currentNode->airline == lastairline || lastairline == -1)
            edgecost = currentNode->cost;
        else
            edgecost = currentNode->cost + 5;
        if (!visited[currentNode->city] && edgecost <= price && (price - edgecost >= maxprice))
        {
            cost = DFS(currentNode->city, dst, (price - edgecost), currentNode->airline);
            if (cost != -1)
                cost += edgecost;
            if ((cost < minprice && cost > 0) || minprice == -1)
                minprice = cost;
        }
        currentNode = currentNode->next;
    }
    visited[vertex] = false;
    return minprice;
}
int main(int argc, char *argv[])
{
    int number;
    string command;
    int src, dst, cost, airline;
    cin >> number;
    Graph graph(number);

    while (cin >> command)
    {
        if (command == "Add")
        {
            cin >> src;
            cin >> dst;
            cin >> cost;
            cin >> airline;
            graph.Add(src, dst, cost, airline);
        }
        else if (command == "Delete")
        {
            cin >> src;
            cin >> dst;
            cin >> airline;
            graph.Delete(src, dst, airline);
        }
        else if (command == "Request")
        {
            cin >> src;
            cin >> dst;
            cin >> cost;
            graph.Request(src, dst, cost);
        }
    }
    return 0;
}

// code by Teng-Hsiang Wang