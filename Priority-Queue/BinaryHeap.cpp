#include <iostream>
#include <vector>
#include <initializer_list>
#include <exception>

using namespace std;

template <typename T>
class BinaryHeap
{

    private:
        // The number of elements currently inside the heap
        int heapSize = 0;

        // A dynamic list to track the elements inside the heap
        vector<T> heap;


    public:
        // Construct and initially empty priority queue
        BinaryHeap(){}
        BinaryHeap(initializer_list<T> elems);
        ~BinaryHeap();

        // Returns true/false depending on if the priority queue is empty
        bool isEmpty();

        // Clears everything inside the heap, O(n)
        void clear();

        // Return the size of the heap
        int size();

        // Returns the value of the element with the lowest priority in this priority queue.
        // If the priority queue is empty null is returned.
        T peek();

        // Removes the root of the heap, O(log(n))
        T poll();

        // Test if an element is in heap, O(n)
        bool contains(T elem);

        // Adds an element to the priority queue, the
        // element must not be null, O(log(n))
        void add(T elem);

        // Removes a particular element in the heap, O(n)
        bool remove(T element);
        
        // Recursively checks if this heap is a min heap
        // This method is just for testing purposes to make
        // sure the heap invariant is still being maintained
        // Called this method with k=0 to start at the root
        bool isMinHeap(int k);

        //print All the element in the list
        void printAll();

        private:
            // Tests if the value of node i <= node j
            // This method assumes i & j are valid indices, O(1)
            bool less(int i, int j);

            // Perform bottom up node swim, O(log(n))
            void swim(int k);

            // Top down node sink, O(log(n))
            void sink(int k);

            // Swap two nodes. Assumes i & j are valid, O(1)
            void swap(int i, int j);


            // Removes a node at particular index, O(log(n))
            T removeAt(int i);

};

template<typename T>
BinaryHeap<T>::BinaryHeap(initializer_list<T> elems)
{
    for(T elem:elems)
        add(elem);
}

template<typename T>
BinaryHeap<T>::~BinaryHeap()
{

}

template<typename T>
bool BinaryHeap<T>::isEmpty()
{
    return heapSize==0;
}

template<typename T>
void BinaryHeap<T>::clear()
{
    heap.clear();
    heapSize=0;
    return;
}

template<typename T>
int BinaryHeap<T>::size()
{
    return heapSize;
}

template<typename T>
T BinaryHeap<T>::peek()
{
    if(isEmpty())
        throw invalid_argument("Queue is Empty");
    return heap[0];
}

template<typename T>
T BinaryHeap<T>::poll()
{
    return removeAt(0);
}

template<typename T>
bool BinaryHeap<T>::contains(T elem)
{
    for(T element:heap)
    {
        if(element==elem)
            return true;
    }
    return false;
}

template<typename T>
void BinaryHeap<T>::add(T elem)
{
    heap.push_back(elem);
    swim(heapSize);
    heapSize++;
    return;
}

template<typename T>
bool BinaryHeap<T>::less(int i,int j)
{
    return heap[i]<heap[j];
}

template<typename T>
void BinaryHeap<T>::swim(int k)
{
     // Grab the index of the next parent node WRT to k
    int parent = (k - 1) / 2;
    // Keep swimming while we have not reached the
    // root and while we're less than our parent.
    while (k > 0 && less(k, parent)) {
        
      // Exchange k with the parent
      swap(parent, k);
      k = parent;
      

      // Grab the index of the next parent node WRT to k
      parent = (k - 1) / 2;
    }
}

template<typename T>
void BinaryHeap<T>::sink(int k)
{
    while (true) {
        int left = 2 * k + 1; // Left  node
        int right = 2 * k + 2; // Right node
        int smallest = left; // Assume left is the smallest node of the two children

        // Find which is smaller left or right
        // If right is smaller set smallest to be right
        if (right < heapSize && less(right, left))
            smallest = right;

        // Stop if we're outside the bounds of the tree
        // or stop early if we cannot sink k anymore
        if (left >= heapSize || less(k, smallest)) 
            break;

        // Move down the tree following the smallest node
        swap(smallest, k);
        k = smallest;
    }
}

template<typename T>
void BinaryHeap<T>::swap(int i,int j)
{
    T temp=heap[i];
    heap[i]=heap[j];
    heap[j]=temp;
}

template<typename T>
bool BinaryHeap<T>::remove(T element)
{
    // Linear removal via search, O(n)
    for (int i = 0; i < heapSize; i++) {
        if (element==heap[i]) {
            removeAt(i);
            return true;
        }
    }
    return false;
}

template<typename T>
T BinaryHeap<T>::removeAt(int i)
{
    if (isEmpty())
        throw invalid_argument("Queue is Empty");

    heapSize--;
    T removed_data = heap[i];
    swap(i, heapSize);

    // Obliterate the value
    heap.pop_back();

    // Check if the last element was removed
    if (i == heapSize)
        return removed_data;
    T elem = heap[i];

    // Try sinking element
    sink(i);

    // If sinking did not work try swimming
    if (heap[i]==elem)
        swim(i);
    return removed_data;
}

template<typename T>
bool BinaryHeap<T>::isMinHeap(int k)
{
    // If we are outside the bounds of the heap return true
    if (k >= heapSize) return true;

    int left = 2 * k + 1;
    int right = 2 * k + 2;

    // Make sure that the current node k is less than
    // both of its children left, and right if they exist
    // return false otherwise to indicate an invalid heap
    if (left < heapSize && !less(k, left)) return false;
    if (right < heapSize && !less(k, right)) return false;

    // Recurse on both children to make sure they're also valid heaps
    return isMinHeap(left) && isMinHeap(right);
}

template<typename T>
void BinaryHeap<T>::printAll()
{
    if(heap.size()<=0)
        return;
    cout<<"[ ";
    for(T item:heap)
        cout<<item<<", ";
    cout<<" ]"<<endl;
    return;

}