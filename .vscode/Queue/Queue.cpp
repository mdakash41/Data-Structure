#include <iostream>

using namespace std;

template<typename T>
class Queue{

    private:
        struct Node
        {
            T element;
            Node *next=nullptr;
            Node *previous=nullptr;
        }*queue;

        struct{
            int queuesize=0;
            Node *head=nullptr,*tail=nullptr;
        }queueDetails;
    
    public:
        Queue(){
            queue=new Node();
        }
        ~Queue(){
            delete queue;
        }
        void enQueue(T value);
        T deQueue();
        T front();
        int getSize();
        bool isEmpty();
};

template<typename T>
void Queue<T>::enQueue(T value)
{
    if(isEmpty())
    {
        queue->element=value;
        queueDetails.queuesize++;
        queueDetails.head=queue;
        queueDetails.tail=queue;
    }
    else
    {
        Node *newNode=new Node();
        newNode->element=value;
        newNode->next=queueDetails.head;
        queueDetails.head->previous=newNode;
        queueDetails.head=newNode;
        queueDetails.queuesize++;
    }
    return;
}

template<typename T>
T Queue<T>::deQueue()
{
    if(isEmpty())
        throw -1;
    T removedValue;
    if(queueDetails.head==queueDetails.tail)
    {
        Node *currentNode=queueDetails.tail;
        removedValue=currentNode->element;
        delete currentNode;
        queueDetails.head=queueDetails.tail=nullptr;
        queueDetails.queuesize--;
    }
    else
    {
        Node *currentNode=queueDetails.tail;
        removedValue=currentNode->element;
        queueDetails.tail=queueDetails.tail->previous;
        queueDetails.tail->next=nullptr;
        delete currentNode;
        queueDetails.queuesize--;
    }
    return removedValue;
}

template<typename T>
T Queue<T>::front()
{
    if(isEmpty())
        throw -1;
    return queueDetails.tail->element;
}

template<typename T>
int Queue<T>::getSize()
{
    return queueDetails.queuesize;
}

template<typename T>
bool Queue<T>::isEmpty()
{
    return queueDetails.queuesize==0;
}

int main(){

    Queue<int> myNumbers;
    for(int i=0;i<5;i++)
        myNumbers.enQueue(i+1);
    cout<<"Size of the queue is "<<myNumbers.getSize()<<endl;
    cout<<"Front value of the queue is "<<myNumbers.front()<<endl;
    while(!myNumbers.isEmpty()){
        cout<<myNumbers.deQueue()<<" Item Pop "<<endl;
    }
    return 0;
}