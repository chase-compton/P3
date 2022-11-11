#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "CircularDynamicArray.cpp"

using namespace std;

template <class type>
class Heap
{
protected:
    CircularDynamicArray<type> *heapArray;

public:
    Heap()
    {
        heapArray = new CircularDynamicArray<type>();
    }

    Heap(type k[], int s)
    {
        heapArray = new CircularDynamicArray<type>(s);
        for (int i = 0; i < s; i++)
        {
            (*heapArray)[i] = k[i];
        }
        for (int i = ((heapArray->length() - 1) / 2); i >= 0; i--)
        {
            Heapify(i);
        }
    }

    void Heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heapArray->length() && (*heapArray)[l] < (*heapArray)[i])
            smallest = l;
        if (r < heapArray->length() && (*heapArray)[r] < (*heapArray)[smallest])
            smallest = r;
        if (smallest != i)
        {
            type temp = (*heapArray)[i];
            (*heapArray)[i] = (*heapArray)[smallest];
            (*heapArray)[smallest] = temp;
            Heapify(smallest);
        }
    }

    Heap(const Heap &rhs)
    {
        cout << "Copy Constructor" << endl;
        heapArray = new CircularDynamicArray<type>();
        *heapArray = *rhs.heapArray;
    }

    Heap &operator=(const Heap &rhs)
    {
        cout << "Copy Assignment" << endl;
        *heapArray = *rhs.heapArray;
        return *this;
    }

    ~Heap()
    {
        delete heapArray;
    }

    type peekKey()
    {
        return (*heapArray)[0];
    }

    type extractMin()
    {
        type root = (*heapArray)[0];

        if (heapArray->length() == 1)
        {
            heapArray->delFront();
            return root;
        }

        (*heapArray)[0] = (*heapArray)[heapArray->length() - 1];
        heapArray->delEnd();
        Heapify(0);

        return root;
    }

    void insert(type k)
    {
        heapArray->addEnd(k);
        int i = heapArray->length() - 1;
        while (i != 0 && (*heapArray)[parent(i)] > (*heapArray)[i])
        {
            type temp = (*heapArray)[i];
            (*heapArray)[i] = (*heapArray)[parent(i)];
            (*heapArray)[parent(i)] = temp;
            i = parent(i);
        }
    }

    void printKey()
    {
        heapArray->printArray();
    }   

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return (2 * i + 1);
    }

    int right(int i)
    {
        return (2 * i + 2);
    }

};
