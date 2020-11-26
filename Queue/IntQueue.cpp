 #include <iostream>
 #include <stdexcept>

 using namespace std;

 class IntQueue {

    private:
        int *ar;
        int front, end, sz;

    public:
        // maxSize is the maximum number of items
        // that can be in the queue at any given time
        IntQueue(int maxSize) {
            front = end = 0;
            sz = maxSize + 1;
            ar = new int[sz];
        }

        bool isEmpty();
        int size();
        int peek();
        void enqueue(int vlue);
        int dequeue();
};


// Return true/false on whether the queue is empty
bool IntQueue::isEmpty() {
    return front == end ;
}

// Return the number of elements inside the queue
int IntQueue::size() {
    if (front > end) return (end + sz - front);
    return end - front;
}

int IntQueue::peek() {
    return ar[front];
}

// Add an element to the queue
void IntQueue::enqueue(int value) {
    ar[end] = value;
    if (++end == sz) end = 0;
    if (end == front) 
        throw invalid_argument("Queue too small!");
}

// Make sure you check is the queue is not empty before calling dequeue!
int IntQueue::dequeue() {
    int ret_val = ar[front];
    if (++front == sz) front = 0;
    return ret_val;
}

// Example usage
int main(int argc, char const *argv[]) {

    IntQueue q(5);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    cout<<q.dequeue()<<endl; // 1
    cout<<q.dequeue()<<endl; // 2
    cout<<q.dequeue()<<endl; // 3
    cout<<q.dequeue()<<endl; // 4

    if(q.isEmpty()) // false
    {
        cout<<"q is Empty"<<endl;
    }
    else
    {
        cout<<"q is not Empty"<<endl;
    }

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout<<q.dequeue()<<endl; // 5
    cout<<q.dequeue()<<endl; // 1
    cout<<q.dequeue()<<endl; // 2
    cout<<q.dequeue()<<endl; // 3

    if(q.isEmpty()) // true
    {
        cout<<"q is Empty"<<endl;
    }
    else
    {
        cout<<"q is not Empty"<<endl;
    }
    return 1;
  }