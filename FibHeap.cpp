#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;

template <class type>
class FibHeapNode
{
public:
    type key;

    FibHeapNode *parent;
    FibHeapNode *child;

    FibHeapNode *left;
    FibHeapNode *right;

    int degree;
    bool mark;

    FibHeapNode()
    {
        key = NULL;

        parent = NULL;
        child = NULL;

        left = NULL;
        right = NULL;

        degree = 0;
        mark = false;
    }

    FibHeapNode(type k)
    {
        key = k;

        parent = NULL;
        child = NULL;

        left = NULL;
        right = NULL;

        degree = 0;
        mark = false;
    }
};

template <class type>
class FibHeap
{
protected:
    FibHeapNode<type> *min;
    FibHeapNode<type> *head;
    FibHeapNode<type> *tail;
    int numNodes;
    int rootListSize;

public:
    FibHeap()
    {
        min = NULL;
        head = NULL;
        tail = NULL;
        numNodes = 0;
        rootListSize = 0;
    }

    FibHeap(type k[], int s, CircularDynamicArray<FibHeapNode<type> *> &handle)
    {
        min = NULL;
        head = NULL;
        tail = NULL;
        numNodes = s;

        for (int i = 0; i < s; i++)
        {
            handle.addEnd(insert(k[i]));
        }
        consolidate();
    }

    type peekKey()
    {
        return min->key;
    }

    FibHeapNode<type> *insert(type k)
    {
        FibHeapNode<type> *x = new FibHeapNode<type>(k);

        if (min == NULL)
        {
            min = x;
            x->left = x;
            x->right = x;
            head = x;
            tail = x;
        }
        else
        {
            tail->right = x;
            x->left = tail;
            x->right = head;
            tail = x;
            head->left = tail;
            if (x->key < min->key)
            {
                min = x;
            }
        }

        numNodes += 1;
        rootListSize += 1;

        return x;
    }

    void insertNode(FibHeapNode<type> *x)
    {
        if (x == NULL)
        {
            return;
        }
        if (min == NULL)
        {
            min = x;
            x->left = x;
            x->right = x;
            head = x;
            tail = x;
        }
        else
        {
            tail->right = x;
            x->left = tail;
            x->right = head;
            tail = x;
            head->left = tail;
            if (x->key < min->key)
            {
                min = x;
            }
        }
        rootListSize += 1;
    }

    type extractMin()
    {
        FibHeapNode<type> *z = min;
        if (z)
        {
            if (z->child)
            {
                FibHeapNode<type> *cur = z->child;
                FibHeapNode<type> *next;
                FibHeapNode<type> *first = z->child;
                do
                {
                    next = cur->right;
                    tail->right = cur;
                    cur->left = tail;
                    cur->right = head;
                    tail = cur;
                    cur->parent = NULL;
                    cur = next;
                    head->left = tail;
                    rootListSize += 1;
                } while (cur != first);
            }
            if (z == head)
            {   head = z->right;
                tail->right = head;
            }
            if (z == tail)
            {
                tail = z->left;
                head->left = tail;
            }
            z->right->left = z->left;
            z->left->right = z->right;
            rootListSize -= 1;
            if (z == z->right)
            {
                min = NULL;
            }
            else
            {
                min = z->right;
                consolidate();
            }

            numNodes -= 1;
        }

        return z->key;
    }

    bool decreaseKey(FibHeapNode<type> *h, type k)
    {
        if (k > h->key)
        {
            return false;
        }

        h->key = k;
        FibHeapNode<type> *y = h->parent;
        if (y != NULL && h->key < y->key)
        {
            cut(h,y);
            cascadingCut(y);
        }
        if (h->key < min->key)
        {
            min = h;
        }
        return true;
    }

    void cut(FibHeapNode<type> *x, FibHeapNode<type> *y)
    {
        if(y->child == x)
            if(x == x->right)
                y->child = NULL;
            else
                y->child = x->right;
        x->right->left = x->left;
        x->left->right = x->right;
        tail->right = x;
        x->left = tail;
        x->right = head;
        tail = x;
        head->left = tail;
        x->parent = NULL;
        x->mark = false;
        y->degree -= 1;
        rootListSize += 1;
    }

    void cascadingCut(FibHeapNode<type> *y)
    {
        FibHeapNode<type> *z = y->parent;
        if (z != NULL)
        {
            if(y->mark == false)
            {
                y->mark = true;
            }
            else
            {
                cut(y,z);
                cascadingCut(z);
            }
        }
    }

    void merge(FibHeap<type> &H2)
    {
        tail->right = H2.head;
        H2.head->left = tail;
        tail = H2.tail;
        head->left = tail;
        tail->right = head;

        if ((min == NULL) || (H2.min != NULL && H2.min->key < min->key))
        {
            min = H2.min;
        }
        numNodes += H2.numNodes;
        rootListSize += H2.rootListSize;

        H2.head = NULL;
        H2.tail = NULL;
        H2.min = 0;
        H2.rootListSize = 0;
        H2.numNodes = 0;
    }

    void consolidate()
    {
        int maxDegree = log2(numNodes) + 1;
        FibHeapNode<type> *A[maxDegree];
        for (int i = 0; i < maxDegree; i++)
        {
            A[i] = NULL;
        }
        FibHeapNode<type> *x = head;
        for (int i = 0; i < rootListSize; i++)
        {
            FibHeapNode<type> *next = x->right;
            int d = x->degree;
            while (A[d] != NULL)
            {
                FibHeapNode<type> *y = A[d];
                if (x == y)
                {
                    break;
                }
                if (x->key > y->key)
                {
                    FibHeapNode<type> *temp = x;
                    x = y;
                    y = temp;
                }
                fibheapLink(y, x);
                A[d] = NULL;
                d += 1;
            }
            A[d] = x;
            x = next;
        }
        min = NULL;
        head = NULL;
        tail = NULL;
        rootListSize = 0;
        for (int i = 0; i < maxDegree; i++)
        {
            if (A[i] != NULL)
            {
                insertNode(A[i]);
            }
        }
    }

    void fibheapLink(FibHeapNode<type> *y, FibHeapNode<type> *x)
    {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        x->degree += 1;
        y->mark = false;
        if (x->child != NULL)
        {
            FibHeapNode<type> *child = x->child;
            x->child = y;
            y->right = child;
            y->left = child->left;
            child->left->right = y;
            child->left = y;
        }
        else
        {
            y->right = y;
            y->left = y;
            x->child = y;
        }
    }
    void printKey()
    {
        if (min == NULL)
            return;
        FibHeapNode<type> *cur = head;
        do
        {
            cout << "Rank " << cur->degree << endl;
            cout << cur->key << " ";
            printHelper(cur->child);
            cur = cur->right;
            cout << endl;
            cout << endl;
        } while (cur != head);
    }

    void printHelper(FibHeapNode<type> *node)
    {
        if (node == NULL)
            return;
        cout << node->key << " ";
        printHelper(node->child);
        FibHeapNode<type> *cur = node->right;
        while (cur != node)
        {
            cout << cur->key << " ";
            printHelper(cur->child);
            cur = cur->right;
        }
    }
};