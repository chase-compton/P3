#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

template <class type>
class Heap
{
protected:
    CircularDynamicArray<type> *heapArray;

public:
    //Default Constructor
    Heap()
    {
        heapArray = new CircularDynamicArray<type>();
    }
    //Array with bottom up heap construction
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
    // Bottom Up method in order to verify/restore heap order. Used in the array constructor
    void Heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        //checks for a child being smaller than parent (violation of heap order)
        if (l < heapArray->length() && (*heapArray)[l] < (*heapArray)[i])
            smallest = l;
        if (r < heapArray->length() && (*heapArray)[r] < (*heapArray)[smallest])
            smallest = r;
        //swpas if new smallest is found
        if (smallest != i)
        {
            type temp = (*heapArray)[i];
            (*heapArray)[i] = (*heapArray)[smallest];
            (*heapArray)[smallest] = temp;
            Heapify(smallest);
        }
    }
    //Copy constructor
    Heap(const Heap &rhs)
    {
        heapArray = new CircularDynamicArray<type>();
        *heapArray = *rhs.heapArray;
    }
    //Assignment Op
    Heap &operator=(const Heap &rhs)
    {
        *heapArray = *rhs.heapArray;
        return *this;
    }
    //Destructor
    ~Heap()
    {
        delete heapArray;
    }
    //returns min value without extraction
    type peekKey()
    {
        return (*heapArray)[0];
    }
    //returns and extracts the min 
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
    //insertion function
    //adds to end and node swims up if needed
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
    //print function for heap
    void printKey()
    {
        heapArray->printArray();
    }   
    //helper function to locate relations easier
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
