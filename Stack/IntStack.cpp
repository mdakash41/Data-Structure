#include <iostream>
#include <exception>

using namespace std;

class IntStack {

    private:
        int *ar;
        int pos = 0;

    // maxSize is the maximum number of items
    // that can be in the queue at any given time
    public:
        IntStack(int maxSize)
        {
            ar = new int[maxSize];
        }
        ~IntStack(){}
        int size();
        bool isEmpty();
        int peek();
        void push(int value);
        int pop();

};
// Returns the number of elements insize the stack
int IntStack::size() {
return pos;
}

// Returns true/false on whether the stack is empty
bool IntStack::isEmpty() {
return pos == 0;
}

// Returns the element at the top of the stack
int IntStack::peek() {
return ar[pos - 1];
}

// Add an element to the top of the stack
void IntStack::push(int value) {
ar[pos++] = value;
}

// Make sure you check that the stack is not empty before calling pop!
int IntStack::pop() {
return ar[--pos];
}

// Example usage
int main(int argc,char const *argv[]) {

    IntStack s(5);

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    cout<<s.pop()<<endl; // 5
    cout<<s.pop()<<endl; // 4
    cout<<s.pop()<<endl; // 3

    s.push(3);
    s.push(4);
    s.push(5);

    while (!s.isEmpty())
        cout<<s.pop()<<endl;
    return 1;
  }