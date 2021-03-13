#include <iostream>
#include <signal.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void signalHandler(int signum);

class Node
{
    friend class Graph;

public:
    Node(int value)
    {
        vertex = value;
        next = NULL;
    }
    ~Node() {}

private:
    int vertex;
    Node *next;
};
class Graph
{
public:
    Graph()
    {
        N = 0;
        for (int i = 0; i < 82169; i++)
        {
            result[i] = -1;
        }
    }

    void Add(int src, int dst);
    void Delete(int src);
    void Read(string filename);
    void Output(int K);
    bool IsEmpty();
    void Coreness(int K);
    void Color(int core);
    void Find_Clique(int K);
    void DFS(int vertex, int layer, int number);
    void Output1();

private:
    ///////////////
    Node *head[82169] = {0};
    int N;
    /////////////////////////////
    int deg[82169] = {0};
    int coreness[82169] = {0};
    bool cancel[82169] = {false};
    bool notexist[82169] = {false};
    /////////////////////////////////////
    int color_num = 0;
    int result[82169];
    bool visited[82169] = {false};
    int first_color = 1;

    //////////////////////////////////////
    int max_core = 0;
    int max_complete = 0;
    bool count[82169] = {false};
    bool answer[82169] = {false};
    bool find_max = 0;
};

Graph g;
void signalHandler(int signum)
{
    g.Output1();
    exit(signum);
}
void Graph::Color(int core)
{
    int i = 0;
    Node *currentNode;
    bool available[82169];

    if (first_color == 1)
    {
        while (coreness[i] != core)
        {
            i++;
        }
        result[i] = 0;
        first_color = 0;
    }
    for (; i < N; i++)
    {
        if (coreness[i] == core)
        {
            visited[i] = true;
            for (int j = 0; j < N; j++)
            {
                available[j] = true;
            }
            currentNode = head[i];
            while (currentNode)
            {
                if (result[currentNode->vertex] != -1)
                    available[result[currentNode->vertex]] = false;
                currentNode = currentNode->next;
            }
            for (int cr = 0; cr < N; cr++)
            {
                if (available[cr])
                {
                    result[i] = cr;
                    if (cr > color_num)
                        color_num = cr;
                    break;
                }
            }
        }
    }
}

void Graph::DFS(int vertex, int layer, int number)
{
    int number_tmp = number; // vertex number of a complete graph
    Node *currentNode = head[vertex];
    if (max_complete >= max_core)
    {
        find_max = true;
        max_complete = number;
        return;
    }
    while (currentNode)
    {
        if (count[currentNode->vertex])
        {
            number_tmp--;
        }
        currentNode = currentNode->next;
    }
    if (number_tmp != 0)
    {
        return;
    }
    if (number + 1 > max_complete)
    {
        max_complete = number;
        for (int i = 0; i < N; i++)
        {
            answer[i] = count[i];
        }
    }
    count[vertex] = true;
    int flag = 0;
    for (int i = 0; i < N; i++)
    {
        if (result[i] == layer + 1)
        {
            flag = 1;
            DFS(i, layer + 1, number + 1);

            if (find_max)
            {
                return;
            }
        }
    }
    if (number + 1 > max_complete)
    {
        max_complete = number;
        for (int i = 0; i < N; i++)
        {
            answer[i] = count[i];
        }
    }
    count[vertex] = false;
}
void Graph::Find_Clique(int K)
{
    int max_tmp = 0;

    for (int i = 0; i < N; i++)
    {
        if (coreness[i] > max_core && visited[i] == false)
        {
            max_core = coreness[i];
        }
    }

    while (max_core > max_complete && max_core > 0)
    {
        Color(max_core);
        //////////////////////////////////////////////////////////////////
        for (int i = 0; i < N; i++)
        {
            if (result[i] == 0)
            {
                DFS(i, 0, 0);
            }
        }

        ////////////////////////////////////////////////
        max_core = 0;
        for (int i = 0; i < N; i++)
        {
            if (coreness[i] > max_core && visited[i] == false)
            {
                max_core = coreness[i];
            }
        }
    }
}

void Graph::Read(string filename)
{
    fstream in;
    int src, dst;

    in.open(filename, ios::in);
    while (in >> src >> dst)
    {
        Add(src, dst);
        N = max(N, max(src, dst));
    }
    N++;
    cout << N << endl;
}

void Graph::Add(int src, int dst)
{
    Node *currentNode = head[src];
    Node *newNode1 = new Node(dst);
    Node *newNode2 = new Node(src);

    while (currentNode != NULL)
    {
        if (currentNode->vertex == dst)
        {
            return;
        }
        currentNode = currentNode->next;
    }
    newNode1->next = head[src];
    newNode2->next = head[dst];
    head[src] = newNode1;
    head[dst] = newNode2;
    deg[src]++;
    deg[dst]++;
}
void Graph::Delete(int src)
{
    Node *currentNode;
    Node *preNode = NULL;

    deg[src] = 0;
    currentNode = head[src];
    notexist[src] = true;
    while (currentNode != NULL)
    {
        deg[currentNode->vertex]--;
        currentNode = currentNode->next;
    }
}
bool Graph::IsEmpty()
{
    for (int i = 0; i < N; i++)
    {
        if (deg[i] > 0)
            return false;
    }
    return true;
}

void Graph::Coreness(int K)
{
    int degree = K - 1;
    int flag1 = 1;
    int flag2 = 1;
    int del = 0;
    Node *currentNode;

    while (flag2)
    {
        flag2 = 0;
        for (int i = 0; i < N; i++)
        {
            if (deg[i] < K && !notexist[i])
            {
                flag2 = 1;
                cancel[i] = true;
            }
        }
        for (int i = 0; i < N; i++)
        {
            if (cancel[i] == true)
            {
                currentNode = head[i];
                notexist[i] = true;
                deg[i] = 0;
                del++;
                cancel[i] = false;
                while (currentNode)
                {
                    deg[currentNode->vertex]--;
                    currentNode = currentNode->next;
                }
            }
        }
    }

    while (del < N - 1)
    {
        degree++;
        //       cout << degree << endl;
        flag1 = 1;
        while (flag1)
        {
            flag1 = 0;
            for (int i = 0; i < N; i++)
            {
                if (deg[i] <= degree && !notexist[i])
                {
                    flag1 = 1;
                    del++;
                    cancel[i] = true;
                    coreness[i] = degree;
                }
            }
            for (int i = 0; i < N; i++)
            {
                if (cancel[i] == true)
                {
                    Delete(i);
                    cancel[i] = false;
                }
            }
        }
    }
}
void Graph::Output(int K)
{
    Node *currentNode;
    ofstream MyFile("kcore.txt");
    for (int i = 0; i < N; i++)
    {
        currentNode = head[i];
        if (coreness[i] >= K)
            MyFile << i << ' ' << coreness[i] << endl;
        while (currentNode != NULL)
        {
            currentNode = currentNode->next;
        }
    }
}
void Graph::Output1()
{
    ofstream NewFile("clique.txt");
    for (int i = 0; i < N; i++)
    {
        if (answer[i])
        {
            NewFile << i << endl;
        }
    }
}
int main(int argc, char *argv[])
{
    string filename = string(argv[1]);
    int K = stoi(argv[2]);
    signal(SIGINT, signalHandler);

    g.Read(filename);
    g.Coreness(K);
    g.Output(K);
    g.Find_Clique(K);
    g.Output1();

    return 0;
}

// code by Teng-Hsiang Wang