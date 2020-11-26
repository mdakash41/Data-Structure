#include <iostream>


using namespace std;

template<typename T>
class MinDHeap
{
private:
    T *heap;
    int d,n,sz;
    int *child,*parent;
public:
    MinDHeap(int degree,int maxNodes);
    int size();
    bool isEmpty();
    void clear();
    T peek();
    T poll();
    void add(T elem);
    void sink(int i);
    void swim(int i);
    int minChild(int i);
    bool less(int i,int j);
    void swap(int i,int j);
    void printAll()
    {
        if(heap==nullptr)
            return;
        for(int i=0;i<sz;i++)
            cout<<heap[i]<<" ";
        cout<<endl;
    }

    ~MinDHeap();

};

template<typename T>
MinDHeap<T>::MinDHeap(int degree,int maxNodes)
{
    d=max(2,degree);
    n=max(d,maxNodes);
    sz=0;
    heap=new T[n];
    child=new int[n];
    parent=new int[n];
    for (int i = 0; i < n; i++) 
    {
        parent[i] = (i - 1) / d;
        child[i] = i * d + 1;
    }

}

template<typename T>
int MinDHeap<T>::size()
{
    return sz;
}
template<typename T>
bool MinDHeap<T>::isEmpty()
{
    return sz==0;
}
template<typename T>
void MinDHeap<T>::clear()
{
    for(int i=0;i<n;i++)
        heap[i]='\0';
    sz=0;

}
template<typename T>
T MinDHeap<T>::peek()
{
    if(isEmpty())
        throw out_of_range("Heap is Empty");
    return heap[0];
}
template<typename T>
T MinDHeap<T>::poll()
{
    if(isEmpty())
        throw out_of_range("Heap is Empty");
    T root=heap[0];
    heap[0]=heap[--sz];
    heap[sz]='\0';
    sink(0);
    return root;
}
template<typename T>
void MinDHeap<T>::add(T elem)
{
    if(sz>=n)
        throw out_of_range("array is full");
    heap[sz]=elem;
    swim(sz++);
}
template<typename T>
void MinDHeap<T>::sink(int i)
{
    for (int j = minChild(i); j != -1; ) 
    {
        swap(i, j);
        i = j;
        j = minChild(i);
    }
}
template<typename T>
void MinDHeap<T>::swim(int i)
{
    while (less(i, parent[i])) 
    {
        swap(i, parent[i]);
        i = parent[i];
    }
}
template<typename T>
int MinDHeap<T>::minChild(int i)
{
    int index,from,to;
    index = -1;
    from = child[i];
    to = min(sz, from + d);
    for (int j = from; j < to; j++) 
    {
        if (less(j, i)) 
            index = i = j;
    }
    return index;
}
template<typename T>
bool MinDHeap<T>::less(int i,int j)
{
    return heap[i]<heap[j];
}
template<typename T>
void MinDHeap<T>::swap(int i,int j)
{
    T tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;
}

template<typename T>
MinDHeap<T>::~MinDHeap()
{
    delete[] heap;
    delete[] child;
    delete[] parent;
}


// int main(int argc, char const *argv[])
// {
//     MinDHeap<int> dd(2,20);
//     dd.add(34);
//     dd.add(34);
//     dd.add(14);
//     dd.add(2);
//     dd.add(66);
//     dd.poll();
//     dd.clear();
//     dd.printAll();
//     return 0;
// }
