#include <iostream>
#include <exception>

using namespace std;

class UnionFind
{
private:
    // The number of elements in this union find
    int totalItem;

    // Used to track the size of each of the component
    int *sz;

    // id[i] points to the parent of i, if id[i] = i then i is a root node
    int *id;

    // Tracks the number of components in the union find
    int numComponents;

    //this will throw error if index is not valid
    //else run the rest of the code.
    void indexIsValid(int index);

public:
    UnionFind(int size);
    ~UnionFind();
    // Find which component/set 'p' belongs to, takes amortized constant time.
    int find(int p);
    // Return whether or not the elements 'p' and
    // 'q' are in the same components/set.
    bool connected(int p, int q);
    // Return the size of the components/set 'p' belongs to
    int componentSize(int p);
    // Return the number of elements in this UnionFind/Disjoint set
    int size();
    // Returns the number of remaining components/sets
    int components();
    // Unify the components/sets containing elements 'p' and 'q'
    void unify(int p, int q);
};

UnionFind::UnionFind(int size)
{
    if(size<=0)
        throw invalid_argument("Size cannot be less than or equal to 0");
    totalItem=numComponents=size;
    sz=new int[size];
    id=new int[size];
    for (int i = 0; i < size; i++)
    {
        id[i]=i;
        sz[i]=1;
    }
    
}

void UnionFind::indexIsValid(int index)
{
    if (totalItem<=index && index<0)
        throw invalid_argument("Index number is not valid"); 
}

int UnionFind::find(int p)
{
    indexIsValid(p);
    int root=p;
    while (root!=id[root])
    {
        root=id[root];
    }

    while (p!=root)
    {
        int temp=id[p];
        id[p]=root;
        p=temp;
    }

    return root;
}

bool UnionFind::connected(int p,int q)
{
    return find(p)==find(q);
}

int UnionFind::componentSize(int p)
{
    indexIsValid(p);
    return sz[find(p)];
}

int UnionFind::size()
{
    return totalItem;
}

int UnionFind::components()
{
    return numComponents;
}

void UnionFind::unify(int p,int q)
{
    indexIsValid(p);
    indexIsValid(q);
    int root1=find(p);
    int root2=find(q);
    if(root1==root2)
        return;
    if(sz[root1]<sz[root2]){
        sz[root1]+=sz[root1];
        id[root1]=root2;
    }
    else
    {
        sz[root1]+=sz[root2];
        id[root2]=root1;
    }
    numComponents--;
}

UnionFind::~UnionFind()
{
    delete[] sz;
    delete[] id;
}

// int main(int argc, char const *argv[])
// {
//     UnionFind aa(10);
//     aa.unify(2,3);
//     cout<<aa.connected(2,3)<<endl;
//     cout<<aa.connected(1,2)<<endl;
//     cout<<aa.componentSize(2)<<endl;
//     cout<<aa.size()<<endl;
//     return 0;
// }


