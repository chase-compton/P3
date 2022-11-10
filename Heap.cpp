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
        for (int i = 0, i < s; i++)
        {
            heapArray->addEnd(k[i])
        }
        for (int i = (heapArray->length / 2), i > 0; i--)
        {
            Heapify(i)
        }

//         A:heap-size D A:length
// 2 for i D bA:length=2c downto 1
// 3 MAX-HEAPIFY.A; i /
    }

    void Heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heapArray->length() && heapArray[l] < heapArray[i])
            smallest = l;
        if (r < heapArray->length() && heapArray[r] < heapArray[smallest])
            smallest = r;
        if (smallest != i)
        {
            swap(&heapArray[i], &heapArray[smallest]);
            Heapify(smallest);
        }
    }

    Heap(const Heap &rhs)
    {

    }

    Heap &operator=(const Heap &rhs)
    {
        return *this;
    }

    ~Heap()
    {

    }

    type peekKey()
    {

    }

    type extractMin()
    {

    }

    void insert(type k)
    {
        
    }

    void printKey()
    {

    }
};


template <class type>
void swap(type *x, type *y)
{
    type temp = *x;
    *x = *y;
    *y = temp;
}