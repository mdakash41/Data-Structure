#include <iostream>
#include<initializer_list>
#include <exception>

using namespace std;

class LinkedList{

    private:

        struct Node
        {
            int value;
            Node *next=nullptr;
        } *llist;

        struct listinfo
        {
            int listsize=0;
            bool isEmpty=true;
            Node *listhead=nullptr;

        } listdetails; 

        bool isIndexValid(int pos);


    public:
        
        LinkedList();
        LinkedList(initializer_list<int> arrays);
        ~LinkedList();
        bool addItem(int value);
        bool addItemAt(int pos,int value);
        int get(int pos);
        bool removeValue(int value);
        bool removeAt(int pos);
        bool removeAll();
        int getSize();
        void printAll()
        {
            Node *cnode=listdetails.listhead;
            while (cnode->next!=nullptr)
            {
                cout<<cnode->value<<" ";
                cnode=cnode->next;
                if(cnode->next==nullptr)
                    cout<<cnode->value;
            }
            cout<<endl;

            return;
            
        }
        
};

LinkedList::LinkedList()
{
    listdetails.listhead=nullptr;
    listdetails.listsize=0;
}

LinkedList::LinkedList(initializer_list<int> values)
{
    for(int i:values)
        addItem(i);
}

LinkedList::~LinkedList()
{

    delete llist;

}

bool LinkedList::isIndexValid(int pos)
{
    return (pos>=0 and pos<listdetails.listsize);
}

bool LinkedList::addItem(int value)
{
    if(listdetails.isEmpty)
    {
        llist=new Node();
        llist->value=value;
        listdetails.isEmpty=false;
        listdetails.listsize++;
        listdetails.listhead=llist;
    }
    else
    {
        Node *temp=listdetails.listhead;
        while (temp->next!=nullptr)
        {
            temp=temp->next;
        }
        Node *newNode=new Node();
        newNode->value=value;
        temp->next=newNode;
        listdetails.listsize++;
    }
    return true;
    

}

bool LinkedList::addItemAt(int pos,int value)
{

    if(!isIndexValid(pos))
        throw out_of_range("Array position is not correct");
    else if(listdetails.isEmpty)
    {
        addItem(value);
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
        temp->next=newNode;
        listdetails.listsize++;
    }
    return true;
}

int LinkedList::get(int pos)
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

bool LinkedList::removeValue(int value)
{
    if(listdetails.isEmpty)
        return false;
    if(listdetails.listhead->value==value)
    {
        Node *deleteit=listdetails.listhead;
        listdetails.listhead=listdetails.listhead->next;
        delete deleteit;
        listdetails.listsize--;
        if(listdetails.listsize==0)
            listdetails.isEmpty=true;
        return true;
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
        delete deleteit;
        listdetails.listsize--;
        if(listdetails.listsize==0)
            listdetails.isEmpty=true;
        return true;
    }
    

}
bool LinkedList::removeAt(int pos)
{

    if(listdetails.isEmpty)
        return false;
    
    if(!isIndexValid(pos))
        throw out_of_range("index not Correct");
    if(pos==0)
    {
        Node *deleteit=listdetails.listhead;
        listdetails.listhead=listdetails.listhead->next;
        delete deleteit;
        listdetails.listsize--;
        if(listdetails.listsize==0)
            listdetails.isEmpty=true;
        return true;
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
        delete deleteit;
        listdetails.listsize--;
        if(listdetails.listsize==0)
            listdetails.isEmpty=true;
        return true;
    }
    
    

}

bool LinkedList::removeAll()
{
    if(listdetails.isEmpty)
        return true;
    while (listdetails.listhead->next!=nullptr)
    {
        Node *currentNode=listdetails.listhead;
        listdetails.listhead=listdetails.listhead->next;
        delete currentNode;
    }

    listdetails.isEmpty=true;
    listdetails.listsize=0;
    return true;
    
}

int LinkedList::getSize()
{
    return listdetails.listsize;
}




int main(int argc, char const *argv[])
{

    LinkedList mynumbers({1,2,3,4,5,2,9});
    mynumbers.printAll();

    cout<<"checking addItemAt function"<<endl;
    mynumbers.addItemAt(0,15);
    mynumbers.printAll();
    mynumbers.addItemAt(4,25);
    mynumbers.printAll();

    cout<<"checking get function"<<endl;  
    cout<<mynumbers.get(0)<<endl;
    cout<<mynumbers.get(4)<<endl;
    cout<<mynumbers.get(mynumbers.getSize()-1)<<endl;
    // cout<<mynumbers.get(mynumbers.getSize())<<endl;
    
    
    cout<<"checking removeValue function"<<endl;
    mynumbers.removeValue(25);
    mynumbers.printAll();
    mynumbers.removeValue(15);
    mynumbers.printAll();
    mynumbers.removeValue(9);
    mynumbers.printAll();

    cout<<"checking removeat function"<<endl;
    mynumbers.removeAt(0);
    mynumbers.printAll();
    mynumbers.removeAt(3);
    mynumbers.printAll();
    mynumbers.removeAt(mynumbers.getSize()-1);
    mynumbers.printAll();

    cout<<"Checking removeAll function"<<endl;
    mynumbers.removeAll();
    if(mynumbers.getSize()==0)
        cout<<"There is no number inside the mynumbers variable"<<endl;
    


    return 0;
}
