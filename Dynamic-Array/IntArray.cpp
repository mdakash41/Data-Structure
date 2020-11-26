#include <iostream>
#include <algorithm>

using namespace std;

class IntArray
{
private:
    int *arr;
    int len = 0;
    int capacity = 0;
public:
    IntArray();
    IntArray(int capacity);
    IntArray(initializer_list<int> array);
    int size();
    bool isEmpty();
    int get(int index);
    void set(int index, int elem);
    void add(int elem);
    void removeAt(int index);
    bool remove(int elem);
    void reverse();
    void sort();
    ~IntArray();
};

IntArray::IntArray()
{
    IntArray(10);
}

IntArray::IntArray(int capacity)
{
    this->capacity=capacity;
    arr=new int[capacity];
}

IntArray::IntArray(initializer_list<int> array)
{
    int array_size=array.size();
    arr=new int[array_size];
    for(int value:array)
    {
        arr[len++]=value;
    }
    capacity=array_size;
}

int IntArray::size()
{
    return len;
}
bool IntArray::isEmpty()
{
    return len==0;
}
int IntArray::get(int index)
{
    if (index>=len)
    {
        throw invalid_argument("index is not correct");
    }
    return arr[index];
    
}
void IntArray::set(int index,int elem)
{
    if (index>=len)
    {
        throw invalid_argument("index is not correct");
    }
    arr[index]=elem;
}
void IntArray::add(int elem)
{
    if(len==capacity){
        capacity*=2;
        int temp[len];
        copy(arr,arr+len,temp);
        delete arr;
        arr=new int[capacity];
        copy(temp,temp+len,arr);
    }
    arr[len++]=elem;
}
void IntArray::removeAt(int index)
{
    for(int i=index;i<len-1;i++)
    {
        arr[index]=arr[index+1];
    }
    len--;
    capacity--;
}
bool IntArray::remove(int elem)
{
    for (int i = 0; i < len; i++) {
        if (arr[i] == elem) {
            removeAt(i);
            return true;
        }
    }
    return false;
}
void IntArray::reverse()
{
    std::reverse(arr,arr+len);
    
}
void IntArray::sort()
{
    std::sort(arr,arr+len);
}

IntArray::~IntArray()
{
    delete arr;
}

int main(int argc, char const *argv[])
{
    IntArray ar(50);
    ar.add(3);
    ar.add(7);
    ar.add(6);
    ar.add(-2);

    ar.sort(); // [-2, 3, 6, 7]

    // Prints [-2, 3, 6, 7]
    for (int i = 0; i < ar.size(); i++) 
        cout<<ar.get(i)<<" ";

    return 0;
}
