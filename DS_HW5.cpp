#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Swap(vector<int> &A, int a, int b)
{
    int tmp = A[a];
    A[a] = A[b];
    A[b] = tmp;
}
void insertionSort(vector<int> &A)
{
    for (int i = 1; i < A.size(); i++)
    {
        int key = A[i];
        int j;
        for (j = i - 1; j >= 0 && A[j] > key; j--)
        {
            A[j + 1] = A[j];
        }
        A[j + 1] = key;
    }
}

int Merge(vector<int> &A, int start, int mid, int end)
{
    vector<int> C;
    int i, j, k;
    int QQ = 0;
    int point;
    int N = mid - start + 1;

    i = start;   // for pre
    j = mid + 1; // for back
    k = start;   // for c
    point = start;

    while (i <= mid && j <= end)
    {
        if (A[i] <= A[j])
        {
            C.push_back(A[i]);
            i++;
        }
        else
        {
            while (A[point] <= 2 * A[j] && N > 0)
            {
                point++;
                N--;
            }
            QQ += N;
            C.push_back(A[j]);
            j++;
        }
    }
    while (i <= mid)
    {
        C.push_back(A[i]);
        i++;
    }
    while (j <= end)
    {
        C.push_back(A[j]);
        j++;
    }
    k = 0;
    for (int p = start; p <= end; p++)
    {
        A[p] = C[k];
        k++;
    }
    return QQ;
}

int MergeSort(vector<int> &A, int start, int end)
{
    int QQ = 0;
    if (start < end)
    {
        int mid = (start + end) / 2;
        QQ += MergeSort(A, start, mid);
        QQ += MergeSort(A, mid + 1, end);
        QQ += Merge(A, start, mid, end);
    }
    return QQ;
}

int select(vector<int> &A)
{
    int n = A.size();
    if (n == 1)
    {
        return A[0];
    }
    vector<int> M;
    vector<int> B;
    for (int i = 0; i < n; i++)
    {
        B.push_back(A[i]);
        if (B.size() == 5 || i == n - 1)
        {
            insertionSort(B);
            M.push_back(B[B.size() / 2]);
            B.clear();
        }
    }
    return select(M);
}
int find(vector<int> &A, int k)
{
    int median = select(A);
    vector<int> large, small;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] < median)
            small.push_back(A[i]);
        else if (A[i] > median)
            large.push_back(A[i]);
    }

    if (large.size() == k - 1)
        return median;
    else if (large.size() > k - 1)
        return find(large, k);
    else
        return find(small, k - large.size() - 1);
}
int main(int argc, char *argv[])
{
    int number;
    int op;
    int num;
    vector<int> A;

    while (cin >> number)
    {
        cin >> op;
        A.clear();
        for (int i = 0; i < number; i++)
        {
            cin >> num;
            A.push_back(num);
        }
        if (op == 0)
        {
            cout << MergeSort(A, 0, number - 1) << endl;
        }
        else if (op > 0)
        {
            cout << find(A, op) << endl;
        }
    }
    return 0;
}

// code by Teng-Hsiang Wang