#include <iostream>
#include <map>

using namespace std;

template<typename T>
class Set
{
private:
    map<T,int> set;
    
public:
    Set(){}
    ~Set(){}
    void clear();
    int size();
    bool isEmpty();
    bool add(T elem);
    bool remove(T elem);
    bool contains(T elme);
    void printAll();

};

template<typename T>
void Set<T>::clear()
{
    set.clear();
}

template<typename T>
int Set<T>::size()
{
    return set.size();
}

template<typename T>
bool Set<T>::isEmpty()
{
    return set.size()==0;
}

template<typename T>
bool Set<T>::add(T elem)
{
    if(set[elem]==0)
    {
        set[elem]++;
        return true;
    }
    return false;
}

template<typename T>
bool Set<T>::remove(T elem)
{
    if(set[elem])
    {
        set.erase(elem);
        return true;
    }
    return false;
    
}
template<typename T>
bool Set<T>::contains(T elme)
{
    return set[elme]==1;
}

template<typename T>
void Set<T>::printAll()
{
    if(set.size()==0)
        return;
    cout<<"[ ";
    for(auto item:set)
    {
        cout<<item.first<<", ";
    }
    cout<<"]"<<endl;
}