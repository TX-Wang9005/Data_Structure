#include <iostream>
#include <string>

using namespace std;
template <class T>
class Stack
{
    friend class Tree;

public:
    Stack(int stackCapacity = 50)
    {
        stack = new T[stackCapacity];
        top = -1;
        capacity = stackCapacity;
    }
    void DoubleCapacity();
    void Push(const T &item);
    void Pop();
    T Top();
    int Gettop();
    bool IsEmpty() const;
    ~Stack() { delete[] stack; }

private:
    T *stack;
    int top;
    int capacity;
};
template <class T>
int Stack<T>::Gettop()
{
    return top;
}
template <class T>
T Stack<T>::Top()
{
    if (top > -1)
        return stack[top];
}
template <class T>
void Stack<T>::Push(const T &item)
{
    if (top == capacity - 1)
    { // if stack is full, double the capacity
        DoubleCapacity();
    }
    stack[++top] = item;
}
template <class T>
void Stack<T>::Pop()
{
    if (top != -1)
        stack[top--].~T();
}
template <class T>
void Stack<T>::DoubleCapacity()
{

    // double capacity
    T *newStack = new T[capacity * 2]; // create newStack

    for (int i = 0; i <= capacity; i++)
    {
        newStack[i] = stack[i];
    }
    T *del = stack;
    stack = newStack; // redirect stack to newStack
    delete[] del;     // release the memory of stack
    capacity *= 2;
}
template <class T>
bool Stack<T>::IsEmpty() const
{
    if (top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Node
{
    friend class Tree;

public:
    Node(int value)
    {
        data = value;
        leftChild = NULL;
        rightChild = NULL;
        cover = false;
        tower = false;
    }

private:
    int data;
    bool cover;
    Node *leftChild;
    Node *rightChild;
    bool tower;
};
class Tree
{
public:
    Tree()
    {
        root = NULL;
    };
    void Construct(string s);
    void Inorder();
    void Preorder();
    void Postorder(Node *currentNode);
    void Traverse();
    int Height(Node *currentNode);
    void High();
    void WeightSum();
    int MaxPathSum(Node *currentNode);
    void Path();
    Node *Delete(Node *currentNode);
    void DeleteLeaf();
    void Clear(Node *currentNode);
    bool Foldable(Node *leftNode, Node *rightNode);
    void Fold();
    int minNode(Node *currentNode);
    void BinaryTower();
    void End();
    ~Tree() { Clear(root); }

private:
    Node *root;
};

void Tree::Construct(string s)
{
    int position = 0;
    string number;
    Stack<Node *> Nd;
    Stack<char> ch;
    Node *newNode;
    Node *right;
    Node *left;

    while (position < s.length())
    {
        if (s[position] == ')')
        {
            if (ch.Top() == '(')
            {
                Nd.Push(NULL);
                ch.Pop();
                position++;
            }
            else
            {
                number.clear();
                if ((ch.Top() <= '9' && ch.Top() >= '0') || ch.Top() == '-')
                {
                    while (ch.Top() != '(')
                    {
                        number = ch.Top() + number;
                        ch.Pop();
                    }
                    newNode = new Node(stoi(number));
                    if (Nd.Gettop() >= 1)
                    {
                        right = Nd.Top();
                        Nd.Pop();
                        left = Nd.Top();
                        Nd.Pop();
                        newNode->leftChild = left;
                        newNode->rightChild = right;
                    }
                    Nd.Push(newNode);
                    ch.Pop();
                }
                position++;
            }
        }
        else
        {
            ch.Push(s[position]);
            position++;
        }
    }
    root = Nd.Top();
    Nd.Pop();
}
void Tree::Inorder()
{
    Stack<Node *> s;
    Node *currentNode = root;

    while (1)
    {
        while (currentNode)
        {
            s.Push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.IsEmpty())
            return;
        currentNode = s.Top();
        s.Pop();
        cout << currentNode->data << " ";
        currentNode = currentNode->rightChild;
    }
}
void Tree::Preorder()
{
    Stack<Node *> s;
    Node *currentNode = root;

    while (1)
    {
        while (currentNode)
        {
            s.Push(currentNode);
            cout << currentNode->data << " ";
            currentNode = currentNode->leftChild;
        }
        if (s.IsEmpty())
            return;
        currentNode = s.Top();
        s.Pop();
        currentNode = currentNode->rightChild;
    }
}
void Tree::Postorder(Node *currentNode)
{
    if (currentNode)
    {
        Postorder(currentNode->leftChild);
        Postorder(currentNode->rightChild);
        cout << currentNode->data << " ";
    }
}
void Tree::Traverse()
{
    if (root != NULL)
        Preorder();
    cout << endl;
    if (root != NULL)
        Inorder();
    cout << endl;
    if (root != NULL)
        Postorder(root);
    cout << endl;
}
void Tree::High()
{
    if (root != NULL)
        cout << Height(root) << endl;
    else
        cout << 0 << endl;
}
int Tree::Height(Node *currentNode)
{
    int leftHeight = 0;
    int rightHeight = 0;

    if (currentNode == NULL)
    {
        return 0;
    }
    else
    {
        leftHeight = Height(currentNode->leftChild);
        rightHeight = Height(currentNode->rightChild);
        if (leftHeight >= rightHeight)
        {
            return leftHeight + 1;
        }
        else
            return rightHeight + 1;
    }
}
void Tree::WeightSum()
{
    Stack<Node *> s;
    Node *currentNode = root;
    int sum = 0;

    while (1)
    {
        while (currentNode)
        {
            s.Push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.IsEmpty())
        {
            cout << sum << endl;
            return;
        }
        currentNode = s.Top();
        s.Pop();
        sum += currentNode->data;
        currentNode = currentNode->rightChild;
    }
}
void Tree::Path()
{
    if (root)
        cout << MaxPathSum(root) << endl;
    else
        cout << '0' << endl;
}
int Tree::MaxPathSum(Node *currentNode)
{
    int leftWeight = 0;
    int rightWeight = 0;

    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL)
    {
        return currentNode->data;
    }
    else
    {
        if (currentNode->leftChild != NULL && currentNode->rightChild == NULL)
        {
            leftWeight = MaxPathSum(currentNode->leftChild);
            return leftWeight + currentNode->data;
        }
        if (currentNode->rightChild != NULL && currentNode->leftChild == NULL)
        {
            rightWeight = MaxPathSum(currentNode->rightChild);
            return rightWeight + currentNode->data;
        }
        leftWeight = MaxPathSum(currentNode->leftChild);
        rightWeight = MaxPathSum(currentNode->rightChild);
        if (leftWeight > rightWeight)
        {
            return leftWeight + currentNode->data;
        }
        else
            return rightWeight + currentNode->data;
    }
}
void Tree::DeleteLeaf()
{
    root = Delete(root);
}
Node *Tree::Delete(Node *currentNode)
{
    if (currentNode == NULL)
    {
        return NULL;
    }

    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL)
    {
        delete currentNode;
        return NULL;
    }
    if (currentNode->leftChild != NULL)
        currentNode->leftChild = Delete(currentNode->leftChild);
    if (currentNode->rightChild != NULL)
        currentNode->rightChild = Delete(currentNode->rightChild);
    return currentNode;
}
void Tree::End()
{
    if (root != NULL)
        Clear(root);
    root = NULL;
}
void Tree::Clear(Node *currentNode)
{
    if (currentNode)
    {
        Clear(currentNode->rightChild);
        Clear(currentNode->leftChild);
        delete currentNode;
    }
}
void Tree::Fold()
{
    if (root != NULL)
    {
        if (Foldable(root->leftChild, root->rightChild))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    else
        cout << "Yes" << endl;
}
bool Tree::Foldable(Node *leftNode, Node *rightNode)
{
    if (leftNode == NULL && rightNode == NULL)
    {
        return true;
    }
    else if ((leftNode == NULL && rightNode != NULL) || (leftNode != NULL && rightNode == NULL))
    {
        return false;
    }
    else
    {
        if (Foldable(leftNode->leftChild, rightNode->rightChild) && Foldable(leftNode->rightChild, rightNode->leftChild))
        {
            return true;
        }
        else
            return false;
    }
}

void Tree::BinaryTower()
{
    Stack<Node *> s;
    Node *currentNode = root;
    int flag = 0;

    while (flag == 0)
    {
        while (currentNode)
        {
            s.Push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.IsEmpty())
        {
            flag = 1;
            break;
        }

        currentNode = s.Top();
        s.Pop();
        currentNode->tower = false;
        currentNode->cover = false;
        currentNode = currentNode->rightChild;
    }
    if (root == NULL)
        cout << "0" << endl;
    else
        cout << minNode(root) << endl;
}

int Tree::minNode(Node *currentNode)
// [Format] can be improved
{
    int leftcover = 0;
    int rightcover = 0;

    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL)
    {
        currentNode->cover = false;
        currentNode->tower = false;
        if (currentNode == root)
        {
            return 1;
        }
        return 0;
    }
    else if (currentNode->leftChild == NULL && currentNode->rightChild != NULL)
    {
        rightcover = minNode(currentNode->rightChild);
        if (currentNode->rightChild->cover == true && currentNode->rightChild->tower == true)
        {
            currentNode->cover = true;
            currentNode->tower = false;
            return rightcover;
        }
        else if (currentNode->rightChild->cover == true && currentNode->rightChild->tower == false)
        {
            if (currentNode == root)
            {
                currentNode->cover = true;
                currentNode->tower = true;
                return rightcover + 1;
            }
            else
            {
                currentNode->cover = false;
                currentNode->tower = false;
                return rightcover;
            }
        }
        else
        {
            currentNode->tower = true;
            currentNode->cover = true;
            return rightcover + 1;
        }
    }
    else if (currentNode->rightChild == NULL && currentNode->leftChild != NULL)
    {
        leftcover = minNode(currentNode->leftChild);
        if (currentNode->leftChild->cover && currentNode->leftChild->tower)
        {
            currentNode->cover = true;
            currentNode->tower = false;
            return leftcover;
        }
        else if (currentNode->leftChild->cover == true && currentNode->leftChild->tower == false)
        {
            if (currentNode == root)
            {
                currentNode->cover = true;
                currentNode->tower = true;
                return leftcover + 1;
            }
            else
            {
                currentNode->cover = false;
                currentNode->tower = false;
                return leftcover;
            }
        }
        else
        {
            currentNode->tower = true;
            currentNode->cover = true;
            return leftcover + 1;
        }
    }
    else
    {
        leftcover = minNode(currentNode->leftChild);
        rightcover = minNode(currentNode->rightChild);
        if (currentNode->leftChild->cover && currentNode->rightChild->cover && (currentNode->leftChild->tower || currentNode->rightChild->tower))
        {
            currentNode->cover = true;
            currentNode->tower = false;
            return leftcover + rightcover;
        }
        else if (currentNode->leftChild->cover && currentNode->rightChild->cover && currentNode->leftChild->tower == false && currentNode->rightChild->tower == false)
        {
            if (currentNode == root)
            {
                currentNode->cover = true;
                currentNode->tower = true;
                return leftcover + rightcover + 1;
            }
            else
            {
                currentNode->cover = false;
                currentNode->tower = false;
                return leftcover + rightcover;
            }
        }
        else
        {
            currentNode->cover = true;
            currentNode->tower = true;
            return leftcover + rightcover + 1;
        }
    }
}

int main(int argc, char *argv[])
{
    Tree BTree;
    string command;
    string s;

    cin >> s;
    BTree.Construct(s);
    s.clear();
    while (cin >> command)
    {
        if (command == "Traverse")
        {
            BTree.Traverse();
        }
        else if (command == "Height")
        {
            BTree.High();
        }
        else if (command == "WeightSum")
        {
            BTree.WeightSum();
        }
        else if (command == "MaximumPathSum")
        {
            BTree.Path();
        }
        else if (command == "Foldable")
        {
            BTree.Fold();
        }
        else if (command == "BinaryTower")
        {
            BTree.BinaryTower();
        }
        else if (command == "DeleteLeaf")
        {
            BTree.DeleteLeaf();
        }
        else if (command == "End")
        {
            if (cin >> s)
            {
                BTree.End();
                BTree.Construct(s);
                s.clear();
            }
            else
            {
                break;
            }
        }
        else
            continue;
    }

    return 0;
}

// code by Teng-Hsiang Wang