#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "CircularDynamicArray.cpp"

using namespace std;

template <class type>
class FibHeapNode
{
protected:
    type key;

    FibHeapNode *parent;
    FibHeapNode *child;

    FibHeapNode *left;
    FibHeapNode *right;

    int degree;
    bool mark;

public:
    FibHeapNode()
    {
        key = NULL;

        parent = nullptr;
        child = nullptr;

        left = nullptr;
        right = nullptr;

        degree = 0;
        mark = false;
    }

    FibHeapNode(type k)
    {
        key = k;

        parent = nullptr;
        child = nullptr;

        left = nullptr;
        right = nullptr;

        degree = 0;
        mark = false;
    }
};

template <class type>
class FibHeap
{
protected:
    FibHeapNode<type> *min;
    int numNodes;

public:
    FibHeap()
    {
        numNodes = 0;
        min = nullptr;
    }

    FibHeap(type k[], int s, CircularDynamicArray<FibHeapNode*> &handle)
    {

    }

    ~FibHeap()
    {
        delete min;
    }

    type peekKey()
    {

    }

    type extractMin()
    {

    }

    FibHeapNode* insert(type k)
    {
        FibHeapNode<type> x = new FibHeapNode<type>(k);

        if (min == nullptr)
        {
            min = x;
            x.left = x;
            x.right = x;
        }
        else
        {
            //add to root list
            //  
            if (x.key < min->key)
            {
                min = x;
            }
        }

        numNodes += 1;
    }

    bool decreaseKey(FibHeapNode *h, type k)
    {

    }

    void merge(FibHeap<type> &H2)
    {

    }

    void printKey()
    {

    }
};