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
    CircularDynamicArray()
    {
        size = 0;
        cap = 2;
        array = new type[cap];
        front = 0;
    }

    CircularDynamicArray(int s)
    {
        size = s;
        cap = s;
        array = new type[cap];
        front = 0;
    }

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

    ~CircularDynamicArray()
    {
        delete[] array;
    }

    type &operator[](int i)
    {
        if (i >= 0 && i < size)
        {
            return *(array + ((front + i) % cap));
        }
        cout << "Error: Index is out of bounds." << endl;
        return outOfbounds;
    }

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
            for (int j = size; j < cap; j++)
            {
                newArray[j] = 0;
            }
            delete[] array;
            array = newArray;
            front = 0;
        }
        array[(front + size) % cap] = value;
        size++;
    }

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
            for (int j = size; j < cap; j++)
            {
                newArray[j] = 0;
            }
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
            for (int j = size; j < cap; j++)
            {
                newArray[j] = 0;
            }
            delete[] array;
            array = newArray;
            front = 0;
        }
    }

    void delFront()
    {
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
            for (int j = size; j < cap; j++)
            {
                newArray[j] = 0;
            }
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
        //temp solution because my QS is wack rn
        type *tempArray = new type[cap];
        for (int i = 0; i < size; i++)
        {
            tempArray[i] = *(array + ((front + i) % cap));
        }
        return WCkthSmallest(tempArray, 0, size - 1, k);
    }

    type QSkthSmallest(int l, int r, int k)
    {
        if (k > 0 && k <= r - l + 1)
        {
            int index = QSpartition(l, r);
            if (index - l == k - 1)
            {
                return *(array + ((front + index) % cap));
            }
            if (index - l > k - 1)
            {
                return QSkthSmallest(l, index - 1, k);
            }
            return QSkthSmallest(index + 1, r, k - index + l - 1);
        }

        return -1;
    }

    type QSpartition(int l, int r)
    {
        type x = *(array + ((front + r) % cap));
        int i = l;
        for (int j = l; j <= r - 1; j++)
        {
            if (*(array + ((front + j) % cap)) <= x)
            {
                swap(*(array + ((front + i) % cap)), *(array + ((front + j) % cap)));
                i++;
            }
        }
        swap(*(array + ((front + i) % cap)), *(array + ((front + r) % cap)));
        return i;
    }

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
            type median[(n + 4) / 5];
            for (i = 0; i < n / 5; i++)
            {
                median[i] = findMedian(arr + l + i * 5, 5);
            }
            if (i * 5 < n)
            {
                median[i] = findMedian(arr + l + i * 5, n % 5);
                i++;
            }
            type medOfMeds = (i == 1) ? median[i - 1] : WCkthSmallest(median, 0, i - 1, i / 2);

            int pos = WCpartition(arr, l, r, medOfMeds);

            if (pos - l == k - 1)
            {
                return arr[pos];
            }
            if (pos - l > k - 1)
            {
                return WCkthSmallest(arr, l, pos - 1, k);
            }
            return WCkthSmallest(arr, pos + 1, r, k - pos + l - 1);
        }
        return -1;
    }

    type findMedian(type arr[], int n)
    {
        sort(arr, arr + n);
        return arr[n / 2];
    }

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
};