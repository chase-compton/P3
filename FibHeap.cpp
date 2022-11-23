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
    FibHeapNode<type> *head;
    FibHeapNode<type> *tail;
    int numNodes;

public:
    FibHeap()
    {
        min = nullptr;
        head = nullptr;
        tail = nullptr;
        numNodes = 0;
    }

    FibHeap(type k[], int s, CircularDynamicArray<FibHeapNode<type> *> &handle)
    {
        min = nullptr;
        head = nullptr;
        tail = nullptr;
        numNodes = s;

        for (int i = 0; i < s; i++)
        {
            handle.addEnd(insert(k[i]));
        }
        consolidate();
    }

    type peekKey()
    {
        return *min;
    }

    FibHeapNode<type> *insert(type k)
    {
        FibHeapNode<type> *x = new FibHeapNode<type>(k);

        if (min == nullptr)
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

        return x;
    }

    void insertNode(FibHeapNode<type> *x)
    {
        if (x == nullptr)
        {
            return;
        }
        if (min == nullptr)
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
    }

    type extractMin()
    {
        FibHeapNode<type> *z = min;
        if (z)
        {
            if(z->child)
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
                    cur->parent = nullptr;
                    cur = next;
                    head->left = tail;
                }
                while (cur != first);
            }

            z->right->left = z->left;
            z->left->right = z->right;
            printKey();
            cout << "Head: " << head->key << " Tail: " << tail->key << endl;
            cout << "Head Left: " << head->left->key << " Tail Right: " << tail->right->key << endl;

            if (z == z->right)
            {
                min = nullptr;
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
        return true;
    }

    void merge(FibHeap<type> &H2)
    {
        tail->right = H2.head;
        H2.head->left = tail;
        tail = H2.tail;
        head->left = tail;
        tail->right = head;

        if ((min == nullptr) || (H2.min != nullptr && H2.min->key < min->key))
        {
            min = H2.min;
        }
        numNodes += H2.numNodes;
    }

    void consolidate()
    {
        int maxDegree = log2(numNodes) + 1;
        FibHeapNode<type> *A[maxDegree];
        for (int i = 0; i < maxDegree; i++)
        {
            A[i] = nullptr;
        }
        FibHeapNode<type> *x = head;
        while (1)
        {
            int d = x->degree;
            while (A[d] != nullptr)
            {
                FibHeapNode<type> *y = A[d];
                if (x->key > y->key)
                {
                    FibHeapNode<type> *temp = x;
                    x = y;
                    y = temp;
                }
                fibheapLink(y, x);
                A[d] = nullptr;
                d += 1;
            }
            A[d] = x;
            if(x->right == head)
                break;
            x = x->right;
        }
        min = nullptr;
        for (int i = 0; i < maxDegree; i++)
        {
            if (A[i] != nullptr)
            {
                if(A[i]->key == "C")
                    cout << A[i]->child->right->right->key << endl;
                insertNode(A[i]);
            }
        }
    }

    void fibheapLink(FibHeapNode<type> *y, FibHeapNode<type> *x)
    {
        cout << x->key << y->key << "#" << endl;
        if(y->left)
        {
            cout << y->left->key << endl;
        }
        if(y->right)
        {
            cout << y->right->key << endl;
        }
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (x->child != nullptr)
        {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }
        else
        {
            y->right = y;
            y->left = y;
        }
        x->child = y;
        cout << y->right->key << x->child->right->key << "-" << endl;
        y->mark = false;
        x->degree += 1;
    }
    void printKey()
    {
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
        if (node == nullptr)
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

    void checker()
    {
        cout << head->right->child->right->right->key << endl;
    }
};