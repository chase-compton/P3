#include <cstdlib>
#include <algorithm>
#include <iostream>


using namespace std;

template <class type>
class CircularDynamicArray
{
protected:
    int size;
    int cap;
    int front;
    type *array;
    type outOfbounds;

public:
    //Default Constructor
    CircularDynamicArray()
    {
        size = 0;
        cap = 2;
        array = new type[cap];
        front = 0;
    }
    //Size Constructor
    CircularDynamicArray(int s)
    {
        size = s;
        cap = s;
        array = new type[cap];
        front = 0;
    }
    //Copy Contructor
    CircularDynamicArray(const CircularDynamicArray &rhs)
    {
        size = rhs.size;
        cap = rhs.cap;
        array = new type[cap];
        for (int i = 0; i < size; i++)
        {
            array[i] = *(rhs.array + ((rhs.front + i) % cap));
        }
        front = 0;
    }
    //Assignment Op
    CircularDynamicArray &operator=(const CircularDynamicArray &rhs)
    {
        size = rhs.size;
        cap = rhs.cap;
        type *tempArray = new type[cap];
        for (int i = 0; i < size; i++)
        {
            tempArray[i] = *(rhs.array + ((front + i) % cap));
        }
        delete[] array;
        array = tempArray;
        front = 0;
        return *this;
    }
    //Destructor
    ~CircularDynamicArray()
    {
        delete[] array;
    }
    //[] op in order to access like a normal array
    type &operator[](int i)
    {
        if (i >= 0 && i < size)
        {
            return *(array + ((front + i) % cap));
        }
        cout << "Error: Index is out of bounds." << endl;
        return outOfbounds;
    }
    //adds value to the end and doubles if needed
    void addEnd(type value)
    {
        if (size == cap)
        {
            type *newArray;
            cap = cap * 2;
            newArray = new type[cap];
            for (int i = 0; i < size; i++)
            {
                newArray[i] = *(array + ((front + i) % (cap / 2)));
            }
            // for (int j = size; j < cap; j++)
            // {
            //     newArray[j] = NULL;
            // }
            delete[] array;
            array = newArray;
            front = 0;
        }
        array[(front + size) % cap] = value;
        size++;
    }
    //adds front and doubles if needed
    void addFront(type value)
    {
        if (size == cap)
        {
            type *newArray;
            cap = cap * 2;
            newArray = new type[cap];
            for (int i = 0; i < size; i++)
            {
                newArray[i] = *(array + ((front + i) % (cap / 2)));
            }
            // for (int j = size; j < cap; j++)
            // {
            //     newArray[j] = NULL;
            // }
            delete[] array;
            array = newArray;
            front = 0;
        }
        front = (front - 1 + cap) % cap;
        array[front] = value;
        size++;
    }

    void delEnd()
    {
        // removes the last value and reduces capacity if needed
        size--;
        if (size <= cap / 4)
        {
            type *newArray;
            cap = cap / 2;
            newArray = new type[cap];
            for (int i = 0; i < size; i++)
            {
                newArray[i] = *(array + ((front + i) % (cap * 2)));
            }
            // for (int j = size; j < cap; j++)
            // {
            //     newArray[j] = NULL;
            // }
            delete[] array;
            array = newArray;
            front = 0;
        }
    }

    void delFront()
    {
        // deletes at the front and reduces the capacity if needed
        size--;
        front = (front + 1 + cap) % cap;
        if (size <= cap / 4)
        {
            type *newArray;
            cap = cap / 2;
            newArray = new type[cap];
            for (int i = 0; i < size; i++)
            {
                newArray[i] = *(array + ((front + i) % (cap * 2)));
            }
            // for (int j = size; j < cap; j++)
            // {
            //     newArray[j] = NULL;
            // }
            delete[] array;
            array = newArray;
            front = 0;
        }
    }

    int length()
    {
        return size;
    }

    int capacity()
    {
        return cap;
    }
    //clears out the array
    void clear()
    {
        delete[] array;
        size = 0;
        cap = 2;
        array = new type[cap];
        front = 0;
    }

    type QuickSelect(int k)
    {
        type *tempArray = new type[cap];
        for (int i = 0; i < size; i++)
        {
            tempArray[i] = *(array + ((front + i) % cap));
        }
        return QSkthSmallest(tempArray, 0, size - 1, k - 1);
    }

    type QSkthSmallest(type arr[], int l, int r, int k)
    {
        if (l == r)
        {
            return arr[l];
        }
        int index = arr[(r + l) / 2];
        index = QSpartition(arr, l, r, index);
        if (index == k)
        {
            return arr[k];
        }
        if (index > k)
        {
            return QSkthSmallest(arr, l, index - 1, k);
        }
        return QSkthSmallest(arr, index + 1, r, k);
    }

    type QSpartition(type arr[], int l, int r, int pIndex)
    {
        type x = arr[pIndex];
        swap(arr[pIndex], arr[r]);
        pIndex = l;
        for (int j = l; j < r; j++)
        {
            if (arr[j] <= x)
            {
                swap(arr[j], arr[pIndex]);
                pIndex++;
            }
        }
        swap(arr[pIndex], arr[r]);
        return pIndex;
    }

    //WC Select in order to guarentee O(n)
    type WCSelect(int k)
    {
        type *tempArray = new type[cap];
        for (int i = 0; i < size; i++)
        {
            tempArray[i] = *(array + ((front + i) % cap));
        }
        return WCkthSmallest(tempArray, 0, size - 1, k);
    }

    type WCkthSmallest(type arr[], int l, int r, int k)
    {
        if (k > 0 && k <= r - l + 1)
        {
            int n = r - l + 1;
            int i;
            //Median array to store the median of each group of 5
            type median[(n + 4) / 5];
            for (i = 0; i < n / 5; i++)
            {
                median[i] = findMedian(arr + l + i * 5, 5);
            }
            //for last group if needed
            if (i * 5 < n)
            {
                median[i] = findMedian(arr + l + i * 5, n % 5);
                i++;
            }
            //if median has one element then we are done otherwise continue
            type medOfMeds = (i == 1) ? median[i - 1] : WCkthSmallest(median, 0, i - 1, i / 2);

            //Partition around the medOfMeds
            int pos = WCpartition(arr, l, r, medOfMeds);

            if (pos - l == k - 1)
            {
                return arr[pos];
            }
            //recur left
            if (pos - l > k - 1)
            {
                return WCkthSmallest(arr, l, pos - 1, k);
            }
            //recur right
            return WCkthSmallest(arr, pos + 1, r, k - pos + l - 1);
        }
        return -1;
    }
    //used to find the median in WC Select
    type findMedian(type arr[], int n)
    {
        sort(arr, arr + n);
        return arr[n / 2];
    }
    //Partitions array around x
    int WCpartition(type arr[], int l, int r, type x)
    {
        int i;
        for (i = l; i < r; i++)
        {
            if (arr[i] == x)
            {
                break;
            }
        }
        swap(arr[i], arr[r]);

        i = l;
        for (int j = l; j <= r - 1; j++)
        {
            if (arr[j] <= x)
            {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[r]);
        return i;
    }

    void stableSort()
    {
        mergeSort(0, size - 1);
    }
    //O(log(n)) stable sort. Essentailly divides the array into equal parts recursivley until single comparisons can be made and built back up
    void mergeSort(int begin, int end)
    {
        if (begin >= end)
        {
            return;
        }
        int mid = begin + (end - begin) / 2;
        mergeSort(begin, mid);
        mergeSort(mid + 1, end);
        merge(begin, mid, end);
    }
    //function used during merge sort in order to recombine the divided arrays. Goes through two arrays comparing values in order to combine them in order
    void merge(int left, int mid, int right)
    {
        int subOne = mid - left + 1;
        int subTwo = right - mid;

        type *leftArray = new type[subOne];
        type *rightArray = new type[subTwo];

        for (int i = 0; i < subOne; i++)
        {
            leftArray[i] = *(array + ((front + i + left) % cap));
        }
        for (int j = 0; j < subTwo; j++)
        {
            rightArray[j] = *(array + ((front + mid + 1 + j) % cap));
        }

        int indexOne = 0, indexTwo = 0;
        int indexMerged = left;

        while (indexOne < subOne && indexTwo < subTwo)
        {
            if (leftArray[indexOne] <= rightArray[indexTwo])
            {
                *(array + ((front + indexMerged) % cap)) = leftArray[indexOne];
                indexOne++;
            }
            else
            {
                *(array + ((front + indexMerged) % cap)) = rightArray[indexTwo];
                indexTwo++;
            }
            indexMerged++;
        }
        while (indexOne < subOne)
        {
            *(array + ((front + indexMerged) % cap)) = leftArray[indexOne];
            indexOne++;
            indexMerged++;
        }
        while (indexTwo < subTwo)
        {
            *(array + ((front + indexMerged) % cap)) = rightArray[indexTwo];
            indexTwo++;
            indexMerged++;
        }
        delete[] leftArray;
        delete[] rightArray;
    }

    
    int linearSearch(type e)
    {
        for (int i = 0; i < size; i++)
        {
            if (*(array + ((front + i) % cap)) == e)
            {
                return i;
            }
        }
        return -1;
    }
    //Binary Search assumes sorted
    int binSearch(type e)
    {
        int left =  0;
        int right = size - 1;
        int mid;
        while (left <= right)
        {
            mid = (left + (right - left) / 2);
            if ( *(array + ((front + mid) % cap)) == e)
            {
                return mid;
            }
            else if ( *(array + ((front + mid) % cap)) > e)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return -1;
    }
    //hepful print function I used with heap class
    void printArray()
    {
        for (int i = 0; i < size; i++)
        {
            cout << *(array + ((front + i) % cap)) << " ";
        }
        cout << endl;
    }
};