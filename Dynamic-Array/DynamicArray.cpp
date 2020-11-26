#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class IntArray
{
private:
    T *arr;
    int len = 0;
    int capacity = 0;
public:
    IntArray();
    IntArray(int capacity);
    IntArray(initializer_list<int> array);
    int size();
    bool isEmpty();
    T get(int index);
    void set(int index, T elem);
    void add(T elem);
    void removeAt(int index);
    bool remove(T elem);
    void reverse();
    void sort();
    ~IntArray();
};

template<typename T>
IntArray<T>::IntArray()
{
    IntArray(10);
}
template<typename T>
IntArray<T>::IntArray(int capacity)
{
    this->capacity=capacity;
    arr=new T[capacity];
}
template<typename T>
IntArray<T>::IntArray(initializer_list<int> array)
{
    int array_size=array.size();
    arr=new int[array_size];
    for(int value:array)
    {
        arr[len++]=value;
    }
    capacity=array_size;
}
template<typename T>
int IntArray<T>::size()
{
    return len;
}
template<typename T>
bool IntArray<T>::isEmpty()
{
    return len==0;
}
template<typename T>
T IntArray<T>::get(int index)
{
    if (index>=len)
    {
        throw invalid_argument("index is not correct");
    }
    return arr[index];
    
}
template<typename T>
void IntArray<T>::set(int index,T elem)
{
    if (index>=len)
    {
        throw invalid_argument("index is not correct");
    }
    arr[index]=elem;
}
template<typename T>
void IntArray<T>::add(T elem)
{
    if(len==capacity){
        capacity*=2;
        T temp[len];
        copy(arr,arr+len,temp);
        delete arr;
        arr=new T[capacity];
        copy(temp,temp+len,arr);
    }
    arr[len++]=elem;
}
template<typename T>
void IntArray<T>::removeAt(int index)
{
    for(int i=index;i<len-1;i++)
    {
        arr[index]=arr[index+1];
    }
    len--;
    capacity--;
}
template<typename T>
bool IntArray<T>::remove(T elem)
{
    for (int i = 0; i < len; i++) {
        if (arr[i] == elem) {
            removeAt(i);
            return true;
        }
    }
    return false;
}
template<typename T>
void IntArray<T>::reverse()
{
    std::reverse(arr,arr+len);
    
}
template<typename T>
void IntArray<T>::sort()
{
    std::sort(arr,arr+len);
}
template<typename T>
IntArray<T>::~IntArray()
{
    delete arr;
}
