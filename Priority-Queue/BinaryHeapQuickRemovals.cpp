#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <initializer_list>
#include <exception>

using namespace std;

template <typename T>
class BinaryHeapQuickRemovals
{

    private:
        // The number of elements currently inside the heap
        int heapSize = 0;

        // A dynamic list to track the elements inside the heap
        vector<T> heap;
        map<T,set<int>> Map;


    public:
        // Construct and initially empty priority queue
        BinaryHeapQuickRemovals(){}
        BinaryHeapQuickRemovals(initializer_list<T> elems);
        ~BinaryHeapQuickRemovals();

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

        // Test if an element is in heap, O(1)
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


        void mapAdd(T value,int index);

        void mapRemove(T value,int index);

        int mapGet(T value);

        void mapSwap(T val1,T val2,int val1Index,int val2Index);

};

template<typename T>
BinaryHeapQuickRemovals<T>::BinaryHeapQuickRemovals(initializer_list<T> elems)
{
    for(T elem:elems)
        add(elem);
}

template<typename T>
BinaryHeapQuickRemovals<T>::~BinaryHeapQuickRemovals()
{

}

template<typename T>
bool BinaryHeapQuickRemovals<T>::isEmpty()
{
    return heapSize==0;
}

template<typename T>
void BinaryHeapQuickRemovals<T>::clear()
{
    heap.clear();
    heapSize=0;
    Map.clear();
    return;
}

template<typename T>
int BinaryHeapQuickRemovals<T>::size()
{
    return heapSize;
}

template<typename T>
T BinaryHeapQuickRemovals<T>::peek()
{
    if(isEmpty())
        throw invalid_argument("Queue is Empty");
    return heap[0];
}

template<typename T>
T BinaryHeapQuickRemovals<T>::poll()
{
    return removeAt(0);
}

template<typename T>
bool BinaryHeapQuickRemovals<T>::contains(T elem)
{
    //this code will take only O(1) time
    return Map.count(elem);


    //below code will take O(n) time
    // for(T element:heap)
    // {
    //     if(element==elem)
    //         return true;
    // }
    // return false;
}

template<typename T>
void BinaryHeapQuickRemovals<T>::add(T elem)
{
    heap.push_back(elem);
    mapAdd(elem,heapSize);
    swim(heapSize);
    heapSize++;
    return;
}

template<typename T>
bool BinaryHeapQuickRemovals<T>::less(int i,int j)
{
    return heap[i]<heap[j];
}

template<typename T>
void BinaryHeapQuickRemovals<T>::swim(int k)
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
void BinaryHeapQuickRemovals<T>::sink(int k)
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
void BinaryHeapQuickRemovals<T>::swap(int i,int j)
{
    T i_elem=heap[i];
    T j_elem=heap[j];
    heap[i]=j_elem;
    heap[j]=i_elem;

    mapSwap(i_elem,j_elem,i,j);
}

template<typename T>
void BinaryHeapQuickRemovals<T>::mapSwap(T val1,T val2,int val1Index,int val2Index)
{
    Map[val1].erase(val1Index);
    Map[val2].erase(val2Index);
    Map[val1].insert(val2Index);
    Map[val2].insert(val1Index);
}

template<typename T>
bool BinaryHeapQuickRemovals<T>::remove(T element)
{
    // Linear removal via search, O(n)
    // for (int i = 0; i < heapSize; i++) {
    //     if (element==heap[i]) {
    //         removeAt(i);
    //         return true;
    //     }
    // }
    // return false;
    int index=mapGet(element);
    if(index==-1)
        return false;
    removeAt(index);
    return true;

}

template<typename T>
T BinaryHeapQuickRemovals<T>::removeAt(int i)
{
    if (isEmpty())
        throw invalid_argument("Queue is Empty");

    heapSize--;
    T removed_data = heap[i];
    swap(i, heapSize);

    // Obliterate the value
    heap.pop_back();
    mapRemove(removed_data,heapSize);

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
void BinaryHeapQuickRemovals<T>::mapAdd(T value,int index)
{
    Map[value].insert(index);
    // for(auto i:Map)
    // {
    //     cout<<"value is "<<i.first<<endl;
    //     for(auto k:i.second)
    //         cout<<k <<" ";
    //     cout<<endl;
    // }
    // cout<<endl;
}

template<typename T>
int BinaryHeapQuickRemovals<T>::mapGet(T value)
{
    if(Map.count(value))
    {
        int nvalue=(*Map[value].rbegin());
        return nvalue;
    }
    else
    {
        return -1;
    }
    
}
template<typename T>
void BinaryHeapQuickRemovals<T>::mapRemove(T value,int index)
{
    
    if(Map.count(value))
    {
        Map[value].erase(index);
    }
    else
        return;
    if(Map[value].size()==0)
        Map.erase(value);
}

template<typename T>
bool BinaryHeapQuickRemovals<T>::isMinHeap(int k)
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
void BinaryHeapQuickRemovals<T>::printAll()
{
    if(heap.size()<=0)
        return;
    cout<<"[ ";
    for(T item:heap)
        cout<<item<<", ";
    cout<<" ]"<<endl;
    return;

}

// int main(int argc, char const *argv[])
// {
//     BinaryHeapQuickRemovals<int> aa;
//     aa.add(4);
//     aa.add(15);
//     aa.add(2);
//     aa.add(15);
//     aa.add(1);
//     aa.add(85);
//     aa.printAll();
//     aa.remove(4);
//     aa.add(77);
//     aa.printAll();
//     aa.add(44);
//     aa.printAll();
//     cout<<aa.size()<<endl;
    
//     return 0;
// }
