#include <iostream>

using namespace std;
class Node
{
    friend class Data;

public:
    Node(int value = 0, Node *next = NULL, Node *previous = NULL)
    {
        data = value;
        link_n = next;
        link_p = previous;
    }

private:
    int data;
    Node *link_n;
    Node *link_p;
};
class Data
{
public:
    Data()
    {
        first = NULL;
        last = NULL;
    };
    void InsertBefore(int x, int k);
    void InsertBack(int x, int k);
    void Front(int x);
    void Back(int x);
    void Delete(int k);
    void DeleteFront();
    void DeleteBack();
    void Reverse(int k, int j);
    void Clear();
    void Print();

private:
    Node *first;
    Node *last;
};

int main(void)
{
    Data list;
    string command;
    int x, k, j;

    while (cin >> command)
    {
        if (command == "InsertFront")
        {
            cin >> x;
            list.Front(x);
        }
        else if (command == "InsertBack")
        {
            cin >> x;
            list.Back(x);
        }
        else if (command == "InsertAfter")
        {
            cin >> k;
            cin >> x;
            list.InsertBack(x, k);
        }
        else if (command == "InsertBefore")
        {
            cin >> k;
            cin >> x;
            list.InsertBefore(x, k);
        }
        else if (command == "Delete")
        {
            cin >> x;
            list.Delete(x);
        }
        else if (command == "DeleteFront")
        {
            list.DeleteFront();
        }
        else if (command == "DeleteBack")
        {
            list.DeleteBack();
        }
        else if (command == "Reverse")
        {
            cin >> k;
            cin >> j;
            list.Reverse(k, j);
        }
        else if (command == "Clear")
        {
            list.Clear();
        }
        else if (command == "Print")
        {
            list.Print();
        }
        else
            continue;
    }

    return 0;
}

void Data::InsertBefore(int x, int k)
{
    Node *current = first;
    Node *Newnode = new Node(x, NULL, NULL);
    int flag = 0;

    while (flag == 0 && current != NULL)
    {
        if (current->data == k)
        {
            if (current == first)
            {
                Newnode->link_n = current;
                current->link_p = Newnode;
                first = Newnode;
            }
            else
            {
                Newnode->link_p = current->link_p;
                Newnode->link_n = current;
                current->link_p->link_n = Newnode;
                current->link_p = Newnode;
            }
            flag = 1;
        }
        else
        {
            current = current->link_n;
        }
    }
}
void Data::InsertBack(int x, int k)
{
    Node *current = first;
    Node *Newnode = new Node(x, NULL, NULL);
    int flag = 0;

    while (flag == 0 && current != NULL)
    {
        if (current->data == k)
        {
            if (current == last)
            {
                Newnode->link_p = current;
                current->link_n = Newnode;
                last = Newnode;
            }
            else
            {
                Newnode->link_p = current;
                Newnode->link_n = current->link_n;
                current->link_n->link_p = Newnode;
                current->link_n = Newnode;
            }
            flag = 1;
        }
        else
        {
            current = current->link_n;
        }
    }
}
void Data::Front(int x)
{
    Node *Newnode = new Node(x, NULL, NULL);
    if (first == NULL || last == NULL)
    {
        first = Newnode;
        last = Newnode;
    }
    else
    {
        first->link_p = Newnode;
        Newnode->link_n = first;
        first = Newnode;
    }
}
void Data::Back(int x)
{
    Node *Newnode = new Node(x, NULL, NULL);
    if (first == NULL || last == NULL)
    {
        first = Newnode;
        last = Newnode;
    }
    else
    {
        last->link_n = Newnode;
        Newnode->link_p = last;
        last = Newnode;
    }
}
void Data::Delete(int k)
{
    Node *current = first;
    int flag = 0;

    while (flag == 0 && current != NULL)
    {
        if (current->data == k)
        {
            if (current == first)
                first = first->link_n;
            else if (current == last)
            {
                last = last->link_p;
                last->link_n = NULL;
            }
            else
            {
                current->link_p->link_n = current->link_n;
                current->link_n->link_p = current->link_p;
            }
            flag = 1;
            delete current;
        }
        else
        {
            current = current->link_n;
        }
    }
}
void Data::DeleteFront()
{
    Node *current = first;
    if (first != NULL)
    {
        if (first != last)
        {
            first = first->link_n;
            first->link_p = NULL;
        }
        else
        {
            first = NULL;
            last = NULL;
        }

        delete current;
    }
}
void Data::DeleteBack()
{
    Node *current = last;
    if (first != NULL)
    {
        if (first != last)
        {
            last = last->link_p;
            last->link_n = NULL;
        }
        else
        {
            last = NULL;
            first = NULL;
        }
        delete current;
    }
}
void Data::Clear()
{
    Node *current = first;

    while (first != NULL)
    {
        first = first->link_n;
        delete current;
        current = first;
    }
}
void Data::Print()
{
    Node *current = first;
    int flag = 0;
    if (current == NULL)
        cout << "\n";
    else
    {
        while (flag == 0)
        {
            cout << current->data << " ";
            current = current->link_n;
            if (current == NULL)
            {
                cout << "\n";
                flag = 1;
            }
        }
    }
    delete current;
}
void Data::Reverse(int k, int j)
{
    Node *start = first;
    Node *end = 0;
    Node *previous = 0;
    Node *current = 0;
    Node *next = 0;
    Node *start_n = 0;
    Node *start_p = 0;
    Node *end_n = 0;
    Node *end_p = 0;
    int flag = 0;
    int right = 0;
    int stop = 0;

    while (flag == 0 && start != NULL)
    {
        if (start->data == k)
        {
            end = start;
            while (right == 0 && end != NULL)
            {
                if (end->data == j)
                {
                    ///////////////////////////

                    // inside
                    if (start->link_n == end)
                    {
                        if (start == first)
                        {
                            end_n = end->link_n;
                            first = end;
                            start->link_p = end;
                            end->link_p = NULL;
                            end->link_n = start;
                            if (end == last)
                            {
                                last = start;
                                start->link_n = NULL;
                            }
                            else
                            {
                                start->link_n = end_n;
                            }
                        }
                        else
                        {
                            start_p = start->link_p;
                            end_n = end->link_n;
                            start->link_p = end;
                            end->link_p = start_p;
                            end->link_n = start;
                            start_p->link_n = end;
                            if (end == last)
                            {
                                last = start;
                                start->link_n = NULL;
                            }
                            else
                            {
                                start->link_n = end_n;
                            }
                        }
                    }
                    else
                    {
                        current = start->link_n;
                        previous = start;
                        next = start->link_n->link_n;
                        while (stop == 0)
                        {
                            current->link_n = previous;
                            current->link_p = next;
                            if (next == end)
                                stop = 1;
                            else
                            {
                                previous = current;
                                current = current->link_p;
                                next = current->link_n;
                            }
                        }
                        if (start == first)
                        {
                            end_p = end->link_p;
                            start_n = start->link_n;
                            end_n = end->link_n;
                            first = end;
                            if (end == last)
                            {
                                last = start;
                                start->link_n = NULL;
                            }
                            else
                            {
                                start->link_n = end->link_n; // not last
                                end_n->link_p = start;
                            }
                            start->link_p = start_n;
                            end->link_p = NULL; // first
                            end->link_n = end_p;
                        }
                        else
                        {
                            end_p = end->link_p;
                            end_n = end->link_n;
                            start_n = start->link_n;
                            start_p = start->link_p;

                            if (end == last)
                            {
                                last = start;
                                start->link_n = NULL;
                            }
                            else
                            {
                                start->link_n = end_n; // not last
                                end_n->link_p = start;
                            }
                            end->link_p = start_p; // first
                            start->link_p = start_n;
                            end->link_n = end_p;
                            start_p->link_n = end;
                        }
                    }
                    // end

                    ////////////////////
                    right = 1;
                }
                else
                {
                    end = end->link_n;
                }
            }
            flag = 1;
        }
        else
        {
            start = start->link_n;
        }
    }
}

// code by Teng-Hsiang Wang