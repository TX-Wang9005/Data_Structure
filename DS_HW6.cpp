#include <iostream>
#include <limits.h>
#include <math.h>

using namespace std;

int first = 1;
class Node
{
    friend class Graph;

public:
    Node(int value, float weight)
    {
        vertex = value;
        this->weight = weight;
        next = NULL;
    }

private:
    int vertex;
    float weight;
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
        D = new float *[N];
        for (int i = 0; i < N; i++)
        {
            D[i] = new float[N];
        }
        ACP = false;
    }
    void Add(int src, int dst, float weight);
    void Delete(int src, int dst);
    bool connect();
    void Floyd_Warshall();
    void MDST(bool AC);
    void Output();
    void DFS(int v);
    void Diameter();
    void SOSPD();

private:
    Node **head;
    int N;
    float ecc;
    bool *visited;
    float **D;
    float d_left;
    float d_right;
    int left;
    int right;
    bool ACP;
};

void Graph::SOSPD()
{
    bool *s;
    float *dist;
    Node *currentNode;
    int u;
    float small = INT_MAX;

    s = new bool[N];
    dist = new float[N];

    for (int i = 0; i < N; i++)
    {
        s[i] = false;
        if (i == left && ACP)
            dist[i] = 0;
        else if (i == left && !ACP)
            dist[i] = d_left;
        else if (i == right && !ACP)
            dist[i] = d_right;
        else
            dist[i] = INT_MAX;
    }

    for (int i = 0; i < N; i++)
    {
        small = INT_MAX;
        for (int j = 0; j < N; j++)
        {
            if (!s[j] && dist[j] < small)
            {
                small = dist[j];
                u = j;
            }
        }
        s[u] = true;
        currentNode = head[u];
        while (currentNode != NULL)
        {
            if (!s[currentNode->vertex] && (dist[u] + currentNode->weight < dist[currentNode->vertex]))
            {
                dist[currentNode->vertex] = dist[u] + currentNode->weight;
            }
            currentNode = currentNode->next;
        }
    }
    float answer = 0;
    for (int i = 0; i < N; i++)
        answer += dist[i];
    cout << answer << endl;
}
void Graph::Diameter()
{
    cout << (ecc * 2) << endl;
}

bool Graph::connect()
{
    for (int i = 0; i < N; i++)
    {
        visited[i] = false;
    }
    DFS(0);
    for (int i = 0; i < N; i++)
    {
        if (visited[i] == false)
        {
            return false;
        }
    }
    return true;
}
void Graph::DFS(int v)
{
    Node *currentNode;
    visited[v] = true;
    currentNode = head[v];
    while (currentNode != NULL)
    {
        if (!visited[currentNode->vertex])
        {
            DFS(currentNode->vertex);
        }
        currentNode = currentNode->next;
    }
}
void Graph::Floyd_Warshall()
{
    Node *currentNode;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                D[i][j] = 0;
            else
                D[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < N; i++)
    {
        currentNode = head[i];
        while (currentNode != NULL)
        {
            D[i][currentNode->vertex] = currentNode->weight;
            currentNode = currentNode->next;
        }
    }
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (D[i][j] > (D[i][k] + D[k][j]))
                    D[i][j] = D[i][k] + D[k][j];
            }
        }
    }
}
void Graph::MDST(bool AC)
{
    int **r;
    float ecc_vertex = INT_MAX;
    float length;
    int vertex;
    Node *currentNode;

    ACP = false;
    r = new int *[N];
    for (int i = 0; i < N; i++)
    {
        r[i] = new int[N];
    }
    Floyd_Warshall();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            r[i][j] = j;
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = N - 1; j > 0; j--)
        {
            for (int k = 0; k < j; k++)
            {
                if (D[i][r[i][k]] < D[i][r[i][k + 1]])
                {
                    int tmp = r[i][k];
                    r[i][k] = r[i][k + 1];
                    r[i][k + 1] = tmp;
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (ecc_vertex > D[i][r[i][0]])
        {
            ecc_vertex = D[i][r[i][0]];
            vertex = i;
        }
    }
    ecc = INT_MAX;
    for (int i = 0; i < N; i++)
    {
        currentNode = head[i];
        while (currentNode != NULL)
        {
            int j = currentNode->vertex;
            length = currentNode->weight;
            for (int a = 0, b = 1; b < N; b++)
            {
                if (D[j][r[i][b]] > D[j][r[i][a]])
                {
                    if (ecc > (D[i][r[i][b]] + D[j][r[i][a]] + length) / 2)
                    {
                        ecc = (D[i][r[i][b]] + D[j][r[i][a]] + length) / 2;
                        left = i;
                        right = j;
                        d_left = ecc - D[i][r[i][b]];
                        d_right = ecc - D[j][r[i][a]];
                    }
                    a = b;
                }
            }
            currentNode = currentNode->next;
        }
    }
    if (ecc_vertex == ecc)
    {
        left = vertex;
        ecc = ecc_vertex;
        ACP = true;
    }
    if (AC)
    {
        if (ACP == true)
            cout << left << endl;
        else
            cout << left << " " << right << endl;
    }
}

void Graph::Add(int src, int dst, float weight)
{
    Node *currentNode1 = head[src];
    Node *currentNode2 = head[dst];
    Node *newNode1 = new Node(dst, weight);
    Node *newNode2 = new Node(src, weight);

    while (currentNode1 != NULL)
    {
        if (currentNode1->vertex == dst)
        {
            currentNode1->weight = weight;
            while (currentNode2 != NULL)
            {
                if (currentNode2->vertex == src)
                {
                    currentNode2->weight = weight;
                    return;
                }
                currentNode2 = currentNode2->next;
            }
            return;
        }
        currentNode1 = currentNode1->next;
    }

    newNode1->next = head[src];
    newNode2->next = head[dst];
    head[src] = newNode1;
    head[dst] = newNode2;
}

void Graph::Delete(int src, int dst)
{
    Node *currentNode1;
    Node *currentNode2;
    Node *preNode1 = NULL;
    Node *preNode2 = NULL;

    currentNode1 = head[src];
    currentNode2 = head[dst];
    while (currentNode1 != NULL)
    {
        if (currentNode1->vertex == dst)
        {
            if (preNode1 == NULL)
            {
                head[src] = currentNode1->next;
            }
            else
            {
                preNode1->next = currentNode1->next;
            }
            delete currentNode1;
            currentNode1 = preNode1;
            while (currentNode2 != NULL)
            {
                if (currentNode2->vertex == src)
                {
                    if (preNode2 == NULL)
                    {
                        head[dst] = currentNode2->next;
                    }
                    else
                    {
                        preNode2->next = currentNode2->next;
                    }
                    delete currentNode2;
                    currentNode2 = preNode2;
                }
                preNode2 = currentNode2;
                if (currentNode2 == NULL)
                    currentNode2 = head[dst];
                else
                    currentNode2 = currentNode2->next;
            }
        }
        preNode1 = currentNode1;
        if (currentNode1 == NULL)
            currentNode1 = head[src];
        else
            currentNode1 = currentNode1->next;
    }
}

void Graph::Output()
{
    Node *currentNode;
    for (int i = 0; i < N; i++)
    {
        currentNode = head[i];
        while (currentNode != NULL)
        {
            cout << '(' << i << ',' << currentNode->vertex << ',' << currentNode->weight << ')' << endl;
            currentNode = currentNode->next;
        }
    }
}

int main(int argc, char *argv[])
{
    int number;
    string command;
    cin >> number;
    Graph g(number);

    while (cin >> command)
    {
        if (command == "Add")
        {
            int src, dst, weight;
            cin >> src >> dst >> weight;
            g.Add(src, dst, weight);
        }
        else if (command == "Delete")
        {
            int src, dst;
            cin >> src >> dst;
            g.Delete(src, dst);
        }
        else if (command == "print")
        {
            g.Output();
        }
        else if (command == "AC")
        {
            if (number == 1)
            {
                cout << 0 << endl;
            }
            else
            {
                if (g.connect())
                {
                    g.MDST(true);
                }
                else
                {
                    cout << "Not connected graph" << endl;
                }
            }
        }
        else if (command == "Diameter")
        {
            if (number == 1)
            {
                cout << 0 << endl;
            }
            else
            {
                if (g.connect())
                {
                    g.MDST(false);
                    g.Diameter();
                }
                else
                {
                    cout << "Not connected graph" << endl;
                }
            }
        }
        else if (command == "SOSPD")
        {
            if (number == 1)
            {
                cout << 0 << endl;
            }
            else
            {
                if (g.connect())
                {
                    g.MDST(false);
                    g.SOSPD();
                }
                else
                {
                    cout << "Not connected graph" << endl;
                }
            }
        }

        else
            continue;
    }
    return 0;
}

// code by Teng-Hsiang Wang