#include <iostream>
#include <exception>
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
    T peek();
    int size();
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
        throw invalid_argument("Stack is Empty");
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
T Stack<T>::peek()
{

    if(!isEmpty()){
        return stackdetails.head->value;
    }
    else
    {
        throw invalid_argument("Stack is Empty");
    }


}

template<typename T>
int Stack<T>::size()
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
    cout<<"Total books "<<books.size()<<endl;
    cout<<"The top books on the stack is "<<books.peek()<<endl;
    cout<<"Removing "<<books.pop()<<" from the stack"<<endl;


    return 0;
}
