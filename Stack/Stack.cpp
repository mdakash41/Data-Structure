#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Stack
{
private:

    struct Node{
        T value;
        Node *next;

        Node(){
            next=nullptr;
        }
    }*item;

    struct{
        int stacksize;
        Node *head=nullptr;
        bool isEmpty=true;
    }stackdetails;

public:
    Stack();
    ~Stack();
    void push(T value);
    T pop();
    T front();
    int getSize();
    bool isEmpty();
};

template<typename T>
Stack<T>::Stack()
{
    stackdetails.stacksize=0;
}

template<typename T>
Stack<T>::~Stack()
{
    delete item;
    stackdetails.head=nullptr;
}

template<typename T>
void Stack<T>::push(T value)
{

    if(stackdetails.isEmpty)
    {
        item=new Node();
        item->value=value;
        stackdetails.head=item;
        stackdetails.stacksize++;
    }
    else
    {
        Node *newNode=new Node();
        newNode->value=value;
        newNode->next=stackdetails.head;
        stackdetails.head=newNode;
        stackdetails.stacksize++;
    }

    return;
}

template<typename T>
T Stack<T>::pop()
{
    if(stackdetails.stacksize==0)
        throw -1;
    else
    {
        T popitem=stackdetails.head->value;
        Node *deleteit=stackdetails.head;
        stackdetails.head=stackdetails.head->next;
        delete deleteit;
        stackdetails.stacksize--;
        return popitem;
    }

}

template<typename T>
T Stack<T>::front()
{

    if(!isEmpty()){
        return stackdetails.head->value;
    }
    else
    {
        throw -1;
    }


}

template<typename T>
int Stack<T>::getSize()
{
    return stackdetails.stacksize;
}

template<typename T>
bool Stack<T>::isEmpty()
{
    return stackdetails.stacksize==0;
}

int main(int argc, char const *argv[])
{
    Stack<string> books;
    if (books.isEmpty())  
    {
        cout<<"There is no books in the stack"<<endl;
    }
    books.push("Bangla");
    books.push("English");
    books.push("Math");
    cout<<"Total books "<<books.getSize()<<endl;
    cout<<"The top books on the stack is "<<books.front()<<endl;
    cout<<"Removing "<<books.pop()<<" from the stack"<<endl;


    return 0;
}
