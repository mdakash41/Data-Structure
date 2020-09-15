#include <iostream>
#include<initializer_list>
#include <exception>

using namespace std;

class DoubleLinkedList{

    private:

        struct Node
        {
            int value;
            Node *next=nullptr;
            Node *previous=nullptr;
        } *llist;

        struct{
            int listsize=0;
            bool isEmpty=true;
            Node *listhead=nullptr;
            Node *listtail=nullptr;

        } listdetails; 

        bool isIndexValid(int pos);


    public:
        
        DoubleLinkedList();
        DoubleLinkedList(initializer_list<int> arrays);
        ~DoubleLinkedList();
        bool insertAt(int pos,int value);
        int get(int pos);
        int removeAt(int pos);
        int removeValue(int value);
        void clear();
        int getSize();

        int getFirst();//
        int getLast();//
        bool insertFirst(int value);//
        bool insertLast(int value);//
        int removeFirst();//
        int removeLast();//
        void traverseList();
        void traverseBackwardList();
        
};

DoubleLinkedList::DoubleLinkedList()
{
    listdetails.listhead=nullptr;
    listdetails.listsize=0;
}

DoubleLinkedList::DoubleLinkedList(initializer_list<int> values)
{
    for(int i:values)
        insertLast(i);
}

DoubleLinkedList::~DoubleLinkedList()
{
    delete llist;
}

bool DoubleLinkedList::isIndexValid(int pos)
{
    return (pos>=0 and pos<listdetails.listsize);
}

bool DoubleLinkedList::insertLast(int value)
{
    if(listdetails.isEmpty)
    {
        llist=new Node();
        llist->value=value;
        listdetails.isEmpty=false;
        listdetails.listsize++;
        listdetails.listhead=llist;
        listdetails.listtail=llist;
    }
    else
    {
        Node *newNode=new Node();
        newNode->value=value;
        newNode->previous=listdetails.listtail;
        listdetails.listtail->next=newNode;
        listdetails.listtail=newNode;
        listdetails.listsize++;
    }
    return true;
}

bool DoubleLinkedList::insertFirst(int value)
{
    if(listdetails.isEmpty)
    {
        llist=new Node();
        llist->value=value;
        listdetails.isEmpty=false;
        listdetails.listsize++;
        listdetails.listhead=llist;
        listdetails.listtail=llist;
    }
    else
    {
        Node *newNode=new Node();
        newNode->value=value;
        newNode->next=listdetails.listhead;
        listdetails.listhead->previous=newNode;
        listdetails.listhead=newNode;
        listdetails.listsize++;
    }
    return true;
}

bool DoubleLinkedList::insertAt(int pos,int value)
{

    if(!isIndexValid(pos))
        throw out_of_range("Array position is not correct");
    else if(listdetails.isEmpty)
    {
        insertLast(value);
        return true;
    }
    if(pos==0)
    {
        Node *newNode=new Node();
        newNode->value=value;
        newNode->next=listdetails.listhead;
        listdetails.listhead=newNode;
        listdetails.listsize++;
    }
    else
    {
        int ind=0;
        Node *newNode=new Node();
        newNode->value=value;
        Node *temp=listdetails.listhead;
        while (ind!=pos-1)
        {
            temp=temp->next;
            ind++;
        }
        newNode->next=temp->next;
        newNode->previous=temp;
        temp->next=newNode;
        if(newNode->next==nullptr)
            listdetails.listtail=newNode;
        listdetails.listsize++;
    }
    return true;
}

int DoubleLinkedList::get(int pos)
{
    if (!isIndexValid(pos))
    {
        throw out_of_range("index out of range");
    }
    
    Node *currentNode=listdetails.listhead;
    
    while (pos>0)
    {
        currentNode=currentNode->next;
        pos--;
    }
    
    return currentNode->value;
}

int DoubleLinkedList::removeFirst()
{
    if(listdetails.isEmpty)
        return false;
    int removedValue;
    if(listdetails.listhead==listdetails.listtail)
    {
        Node *currentNode=listdetails.listhead;
        removedValue=currentNode->value;
        delete currentNode;
        listdetails.listhead=listdetails.listtail=nullptr;
        listdetails.isEmpty=true;
        listdetails.listsize--;
    }
    else
    {
        Node *currentNode=listdetails.listhead;
        removedValue=currentNode->value;
        listdetails.listhead=listdetails.listhead->next;
        listdetails.listhead->previous=nullptr;
        delete currentNode;
        listdetails.listsize--;
    }
    return removedValue;
}

int DoubleLinkedList::removeValue(int value)
{
    if(listdetails.isEmpty)
        return false;

    int removedValue;
    if(listdetails.listhead->value==value)
    {
        Node *deleteit=listdetails.listhead;
        listdetails.listhead=listdetails.listhead->next;
        if(listdetails.listhead->next!=nullptr)
            listdetails.listhead->previous=nullptr; //removing previous pointer
        else
        {
            listdetails.listtail=listdetails.listhead;
        }
        removedValue=deleteit->value;
        delete deleteit;
        listdetails.listsize--;
        if(listdetails.listsize==0)
            listdetails.isEmpty=true;
        return removedValue;
    }
    else
    {
        Node *currentnode=listdetails.listhead;
        while (currentnode->next->value!=value) 
        {
            if(currentnode->next==nullptr)
                return false;
            currentnode=currentnode->next;
        }

        Node *deleteit=currentnode->next;
        currentnode->next=currentnode->next->next;
        if(currentnode->next!=nullptr)
            currentnode->next->previous=currentnode;
        else
        {
            listdetails.listtail=currentnode;
        }
        removedValue=deleteit->value;
        delete deleteit;
        listdetails.listsize--;
        if(listdetails.listsize==0)
            listdetails.isEmpty=true;
        return removedValue;
    }
}

int DoubleLinkedList::removeLast()
{
    if(listdetails.isEmpty)
        return false;
    int removedValue;
    if(listdetails.listhead==listdetails.listtail)
    {
        Node *currentNode=listdetails.listtail;
        removedValue=currentNode->value;
        delete currentNode;
        listdetails.listhead=listdetails.listtail=nullptr;
        listdetails.isEmpty=true;
        listdetails.listsize--;
    }
    else
    {
        Node *currentNode=listdetails.listtail;
        removedValue=currentNode->value;
        listdetails.listtail=listdetails.listtail->previous;
        listdetails.listtail->next=nullptr;
        delete currentNode;
        listdetails.listsize--;
    }
    return removedValue;
}

int DoubleLinkedList::removeAt(int pos)
{

    if(listdetails.isEmpty)
        return false;
    
    if(!isIndexValid(pos))
        throw out_of_range("index not Correct");

    int removedValue;
    if(pos==0)
    {
        Node *deleteit=listdetails.listhead;
        listdetails.listhead=listdetails.listhead->next;
        listdetails.listhead->previous=nullptr;
        removedValue=deleteit->value;
        delete deleteit;
        listdetails.listsize--;
        if(listdetails.listsize==0)
            listdetails.isEmpty=true;
        return removedValue;
    }
    else
    {
        Node *currentNode=listdetails.listhead;
        int c=0;
        while (c!=(pos-1))
        {
            currentNode=currentNode->next;
            c++;
        }
        Node *deleteit=currentNode->next;
        currentNode->next=currentNode->next->next;
        if(currentNode->next!=nullptr)
            currentNode->next->previous=currentNode;
        else
        {
            listdetails.listtail=currentNode;
        }
        removedValue=deleteit->value;
        delete deleteit;
        listdetails.listsize--;
        if(listdetails.listsize==0)
            listdetails.isEmpty=true;
        return removedValue;
    }
}

void DoubleLinkedList::clear()
{
    if(listdetails.isEmpty)
        return;
    while (listdetails.listhead->next!=nullptr)
    {
        Node *currentNode=listdetails.listhead;
        listdetails.listhead=listdetails.listhead->next;
        delete currentNode;
    }

    listdetails.isEmpty=true;
    listdetails.listsize=0;
    listdetails.listhead=listdetails.listtail=nullptr;
    return;
    
}

int DoubleLinkedList::getSize()
{
    return listdetails.listsize;
}

int DoubleLinkedList::getFirst()
{
    if(listdetails.isEmpty)
        throw out_of_range("List is Empty");
    return listdetails.listhead->value;
}

int DoubleLinkedList::getLast()
{
    if(listdetails.isEmpty)
        throw out_of_range("List is Empty");
    return listdetails.listtail->value;
}

void DoubleLinkedList::traverseList()
{
    Node *currentNode=listdetails.listhead;
    while (currentNode->next!=nullptr)
    {
        cout<<currentNode->value<<" ";
        currentNode=currentNode->next;
        if(currentNode->next==nullptr)
            cout<<currentNode->value;
    }
    cout<<endl;

    return;
}

void DoubleLinkedList::traverseBackwardList()
{
    Node *currentNode=listdetails.listtail;
    while (currentNode->previous!=nullptr)
    {
        cout<<currentNode->value<<" ";
        currentNode=currentNode->previous;
        if(currentNode->previous==nullptr)
            cout<<currentNode->value;
    }
    cout<<endl;

    return;
}




int main(int argc, char const *argv[])
{

    DoubleLinkedList mynumbers({1,2,3,4,5,2,9});
    mynumbers.traverseList();

    cout<<"checking insertAt function"<<endl;
    mynumbers.insertAt(0,15);
    mynumbers.traverseList();
    mynumbers.insertAt(4,25);
    mynumbers.traverseList();
    mynumbers.insertFirst(55);
    mynumbers.insertLast(88);
    mynumbers.traverseList();

    cout<<"checking get function"<<endl;  
    cout<<"getting 0th index value "<<mynumbers.get(0)<<endl;
    cout<<"geting 4th index value "<<mynumbers.get(4)<<endl;
    cout<<"getting last index value "<<mynumbers.get(mynumbers.getSize()-1)<<endl;
    cout<<"getting first vlaue "<<mynumbers.getFirst()<<endl;
    cout<<"getting last value "<<mynumbers.getLast()<<endl;
    // cout<<mynumbers.get(mynumbers.getSize())<<endl;
    
    
    cout<<"checking removeValue function"<<endl;
    cout<<"Successfully removed value "<<mynumbers.removeValue(25)<<endl;
    cout<<"Successfully removed value "<<mynumbers.removeValue(15)<<endl;
    cout<<"Successfully removed value "<<mynumbers.removeValue(9)<<endl;
    cout<<"Successfully removed first value "<<mynumbers.removeFirst()<<endl;
    //cout<<"Successfully removed last value "<<mynumbers.removeLast()<<endl;
    mynumbers.traverseList();

    cout<<"checking removeat function"<<endl;
    mynumbers.removeAt(0);
    mynumbers.traverseList();
    mynumbers.removeAt(3);
    mynumbers.traverseList();
    mynumbers.removeAt(mynumbers.getSize()-1);
    mynumbers.traverseList();

    cout<<"Traversing list"<<endl;
    mynumbers.traverseList();
    mynumbers.traverseBackwardList();


    cout<<"Checking removeAll function"<<endl;
    mynumbers.clear();
    if(mynumbers.getSize()==0)
        cout<<"There is no number inside the mynumbers variable"<<endl;
    return 0;
}
