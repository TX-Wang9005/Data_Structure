#include <iostream>
#include <stdio.h>
using namespace std;

class Queue
{
    friend class stack;

public:
    Queue(const int queueCapacity)
    {
        capacity = queueCapacity;
        front = -1;
        rear = -1;
        queue = new char[capacity];
    };
    void Push(char item);
    void Pop(int x);
    int Rear();
    int Front();
    void Input();
    char Output(int position);
    void Print(int first);
    int Judge();

private:
    char *queue;
    int front, rear;
    int capacity;
};
int Queue::Rear()
{
    return rear;
}
int Queue::Front()
{
    return front;
}
int Queue::Judge()
{
    int i = front + 1;
    int previous; // previous character 0 (, 1 +-*/, 2 number, 3 )
    int brackets = 0;
    int invalid = 0;

    previous = queue[i];
    if (queue[i] == '+' || queue[i] == '-' || queue[i] == '*' || queue[i] == '/')
    {
        invalid = 1;
        previous = 1;
    }
    else if (queue[i] >= '0' && queue[i] <= '9')
    {
        invalid = 0;
        previous = 2;
    }
    else if (queue[i] == '(')
    {
        previous = 0;
        invalid = 0;
        brackets = 1;
    }
    else if (queue[i] == ')')
    {
        previous = 3;
        invalid = 1;
    }
    else
        cout << "wrong format";

    if (front < rear)
    {
        for (i = i + 1; i <= rear && invalid == 0; i++)
        {
            if (queue[i] == '+' || queue[i] == '-' || queue[i] == '*' || queue[i] == '/')
            {
                if (previous == 0 || previous == 1)
                    invalid = 1;
                else if (previous == 2 || previous == 3)
                    invalid = 0;
                previous = 1;
            }
            else if (queue[i] >= '0' && queue[i] <= '9')
            {
                if (previous == 2 || previous == 3)
                    invalid = 1;
                else if (previous == 0 || previous == 1)
                    invalid = 0;
                previous = 2;
            }
            else if (queue[i] == '(')
            {
                if (previous == 2)
                    invalid = 1;
                else
                    invalid = 0;
                brackets++;
                previous = 0;
            }
            else if (queue[i] == ')')
            {
                if (previous == 0 || previous == 1)
                    invalid = 1;
                else if (previous == 2 || previous == 3)
                    invalid = 0;
                previous = 3;
                brackets--;
            }
            else
            {
                cout << "wrong format";
            }
        }
    }
    else
    {
        for (i = i + 1; i < capacity && invalid == 0; i++)
        {
            if (queue[i] == '+' || queue[i] == '-' || queue[i] == '*' || queue[i] == '/')
            {
                if (previous == 0 || previous == 1)
                    invalid = 1;
                else if (previous == 2 || previous == 3)
                    invalid = 0;
                previous = 1;
            }
            else if (queue[i] >= '0' && queue[i] <= '9')
            {
                if (previous == 2)
                    invalid = 1;
                else if (previous == 0 || previous == 1 || previous == 3)
                    invalid = 0;
                previous = 2;
            }
            else if (queue[i] == '(')
            {
                invalid = 0;
                brackets++;
                previous = 0;
            }
            else if (queue[i] == ')')
            {
                if (previous == 0 || previous == 1)
                    invalid = 1;
                else if (previous == 2 || previous == 3)
                    invalid = 0;
                previous = 3;
                brackets--;
            }
            else
            {
                cout << "wrong format";
            }
        }
        for (i = 0; i <= rear && invalid == 0; i++)
        {
            if (queue[i] == '+' || queue[i] == '-' || queue[i] == '*' || queue[i] == '/')
            {
                if (previous == 0 || previous == 1)
                    invalid = 1;
                else if (previous == 2 || previous == 3)
                    invalid = 0;
                previous = 1;
            }
            else if (queue[i] >= '0' && queue[i] <= '9')
            {
                if (previous == 2)
                    invalid = 1;
                else if (previous == 0 || previous == 1 || previous == 3)
                    invalid = 0;
                previous = 2;
            }
            else if (queue[i] == '(')
            {
                invalid = 0;
                brackets++;
                previous = 0;
            }
            else if (queue[i] == ')')
            {
                if (previous == 0 || previous == 1 || brackets <= 0)
                    invalid = 1;
                else if (previous == 2 || previous == 3)
                    invalid = 0;
                previous = 3;
                brackets--;
            }
            else
            {
                cout << "wrong format";
            }
        }
    }

    if (brackets != 0 || previous == 1 || previous == 0)
        invalid = 1;
    return invalid;
}
void Queue::Print(int first)
{

    if (first == 0)
        cout << endl;
    if (front < rear)
    {
        for (int i = front + 1; i <= rear; i++)
        {
            cout << queue[i];
        }
    }
    else
    {
        for (int i = front + 1; i < capacity; i++)
        {
            cout << queue[i];
        }
        for (int i = 0; i <= rear; i++)
        {
            cout << queue[i];
        }
    }
    cout << '\n';
}
void Queue::Push(char item)
{

    rear = (rear + 1) % capacity;
    queue[rear] = item;
}
void Queue::Pop(int x)
{
    for (int i = 0; i < x; i++)
    {
        front = (front + 1) % capacity;
        queue[front] = 0;
    }
}
char Queue::Output(int position)
{
    return queue[position];
}
void Queue::Input()
{
    char index;

    while ((index = getchar()) != '\n')
    {
        Push(index);
    }
}

class Stack_int
{

public:
    Stack_int(int stackCapacity)
    {
        stack = new int[stackCapacity];
        top = -1;
    }
    void Push(const int item);
    int Pop();
    int Top();

private:
    int *stack;
    int top;
};
int Stack_int ::Top()
{
    return top;
}
void Stack_int::Push(const int item)
{
    stack[++top] = item;
}
int Stack_int::Pop()
{
    int data = stack[top];
    stack[top--] = 0;
    return data;
}
class Stack
{

public:
    Stack(int stackCapacity)
    {
        stack = new char[stackCapacity];
        top = -1;
    }
    void Push(const char item);
    char Pop();
    int Top();
    int Convert(char index);

private:
    char *stack;
    int top;
};
int Stack ::Top()
{
    return top;
}
void Stack::Push(const char item)
{
    stack[++top] = item;
}
char Stack::Pop()
{
    char data = stack[top];
    stack[top--] = 0;
    return data;
}
int Stack::Convert(char index)
{
    int times = 0;
    int current = top;

    if (top != -1)
    {
        if (index == ')')
        {
            while (stack[current] != '(')
            {
                times++;
                current--;
            }
            times++;
        }
        else if (index == '+' || index == '-')
        {

            while (current >= 0)
            {
                if (stack[current] == '+' || stack[current] == '-' || stack[current] == '*' || stack[current] == '/')
                {
                    times++;
                    current--;
                }
                else
                    break;
            }
        }
        else if (index == '*' || index == '/')
        {
            while (current >= 0)
            {
                if (stack[current] == '*' || stack[current] == '/')
                {
                    times++;
                    current--;
                }
                else
                    break;
            }
        }
    }
    return times;
}

int main(int argc, char *argv[])
{
    Queue list(30);
    Stack convert(30);
    Stack_int calculate(30);
    string command;
    char postfix[30];
    char infix;
    int first = 1;
    int x;
    char y;
    int a, b;
    int j = 0;
    int invalid;
    int times = 0;
    int tmp = 0;
    int number = 0;

    list.Input();
    while (cin >> command)
    {
        if (command == "Print")
        {
            invalid = list.Judge();
            if (invalid == 1)
            {
                list.Print(first);
                if (first == 1)
                {
                    first = 0;
                }
                cout << "Invalid";
            }
            else
            {
                ////////////////////////////////////////////////////////////////////////////////
                list.Print(first);
                if (first = 1)
                {
                    first = 0;
                }
                j = 0;
                if (list.Front() < list.Rear())
                {
                    for (int i = list.Front() + 1; i <= list.Rear(); i++)
                    {
                        infix = list.Output(i);
                        if (infix >= '0' && infix <= '9')
                        {
                            postfix[j] = infix;
                            j++;
                        }
                        else if (infix == '+' || infix == '-' || infix == '*' || infix == '/' || infix == '(' || infix == ')')
                        {
                            times = convert.Convert(infix);
                            for (; times > 0; times--)
                            {
                                tmp = convert.Pop();
                                if (tmp != '(')
                                {
                                    postfix[j] = tmp;
                                    j++;
                                }
                            }
                            if (infix != ')')
                                convert.Push(infix);
                        }
                        else
                            cout << "wrong format";
                    }
                    while (convert.Top() >= 0)
                    {
                        tmp = convert.Pop();
                        if (tmp != '(')
                        {
                            postfix[j] = tmp;
                            j++;
                        }
                    }
                }
                else
                {
                    for (int i = list.Front() + 1; i < 30; i++)
                    {
                        infix = list.Output(i);
                        if (infix >= '0' && infix <= '9')
                        {
                            postfix[j] = infix;
                            j++;
                        }
                        else if (infix == '+' || infix == '-' || infix == '*' || infix == '/' || infix == '(' || infix == ')')
                        {
                            times = convert.Convert(infix);
                            for (; times > 0; times--)
                            {
                                tmp = convert.Pop();
                                if (tmp != '(')
                                {
                                    postfix[j] = tmp;
                                    j++;
                                }
                            }
                            if (infix != ')')
                                convert.Push(infix);
                        }
                        else
                            cout << "wrong format";
                    }
                    for (int i = 0; i <= list.Rear(); i++)
                    {
                        infix = list.Output(i);
                        if (infix >= '0' && infix <= '9')
                        {
                            postfix[j] = infix;
                            j++;
                        }
                        else if (infix == '+' || infix == '-' || infix == '*' || infix == '/' || infix == '(' || infix == ')')
                        {
                            times = convert.Convert(infix);
                            for (; times > 0; times--)
                            {

                                tmp = convert.Pop();
                                if (tmp != '(')
                                {
                                    postfix[j] = tmp;
                                    j++;
                                }
                            }
                            if (infix != ')')
                                convert.Push(infix);
                        }
                        else
                            cout << "wrong format";
                    }
                    while (convert.Top() >= 0)
                    {
                        tmp = convert.Pop();
                        if (tmp != '(')
                        {
                            postfix[j] = tmp;
                            j++;
                        }
                    }
                }
                for (int i = 0; i < j; i++)
                    cout << postfix[i];
                cout << '\n';
                //////////////////////////////////////////////////////////////////////////////////////
                for (int i = 0; i < j; i++)
                {
                    if (postfix[i] >= '0' && postfix[i] <= '9')
                    {
                        number = postfix[i] - '0';
                        calculate.Push(number);
                    }
                    else if (postfix[i] == '+')
                    {
                        b = calculate.Pop();
                        a = calculate.Pop();
                        calculate.Push(a + b);
                    }
                    else if (postfix[i] == '-')
                    {
                        b = calculate.Pop();
                        a = calculate.Pop();
                        calculate.Push(a - b);
                    }
                    else if (postfix[i] == '*')
                    {
                        b = calculate.Pop();
                        a = calculate.Pop();
                        calculate.Push(a * b);
                    }
                    else if (postfix[i] == '/')
                    {
                        b = calculate.Pop();
                        a = calculate.Pop();
                        calculate.Push(a / b);
                    }
                }
                cout << calculate.Pop();
            }
        }
        else if (command == "Enqueue")
        {
            cin >> y;
            list.Push(y);
        }
        else if (command == "Dequeue")
        {
            cin >> x;
            list.Pop(x);
        }
        else
            cout << "wrong\n";
    }
    return 0;
}

// code by Teng-Hsiang Wang