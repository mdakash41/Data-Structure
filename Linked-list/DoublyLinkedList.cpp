#include <iostream>
#include <initializer_list>
#include <exception>

using namespace std;

template <typename T>
class DoubleLinkedList
{

private:
    struct Node
    {
        T value;
        Node *next = nullptr;
        Node *previous = nullptr;
    } * linkedlist;

    struct
    {
        int size = 0;
        Node *head = nullptr;
        Node *tail = nullptr;

    } listdetails;

    bool isIndexValid(int index);

public:
    DoubleLinkedList();
    DoubleLinkedList(initializer_list<T> arrays);
    ~DoubleLinkedList();

    void clear();
    int getSize();
    bool isEmpty();
    void add(T value);
    void addFirst(T value);
    void addLast(T value);
    T peekFirst();
    T peekLast();
    T removeFirst();
    T removeLast();
    T remove(T value);
    T removeAt(int index);
    void addAt(int index, T value);
    int indexOf(T value);
    T get(int index);
    bool contains(T value);
    void traverseList();
    void traverseBackwardList();
};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
    listdetails.head = nullptr;
    listdetails.size = 0;
}
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(initializer_list<T> values)
{
    for (T value : values)
        addLast(value);
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    delete linkedlist;
}
template <typename T>
bool DoubleLinkedList<T>::isIndexValid(int index)
{
    return (index >= 0 and index < listdetails.size);
}
template <typename T>
void DoubleLinkedList<T>::addLast(T value)
{
    if (isEmpty())
    {
        linkedlist = new Node();
        linkedlist->value = value;
        listdetails.size++;
        listdetails.head = linkedlist;
        listdetails.tail = linkedlist;
    }
    else
    {
        Node *newNode = new Node();
        newNode->value = value;
        newNode->previous = listdetails.tail;
        listdetails.tail->next = newNode;
        listdetails.tail = newNode;
        listdetails.size++;
    }
    return;
}

template <typename T>
void DoubleLinkedList<T>::add(T value)
{
    addLast(value);
    return;
}

template <typename T>
void DoubleLinkedList<T>::addFirst(T value)
{
    if (isEmpty())
    {
        linkedlist = new Node();
        linkedlist->value = value;
        listdetails.size++;
        listdetails.head = linkedlist;
        listdetails.tail = linkedlist;
    }
    else
    {
        Node *newNode = new Node();
        newNode->value = value;
        newNode->next = listdetails.head;
        listdetails.head->previous = newNode;
        listdetails.head = newNode;
        listdetails.size++;
    }
    return;
}
template <typename T>
void DoubleLinkedList<T>::addAt(int index, T value)
{

    if (!isIndexValid(index))
        throw invalid_argument("index number is invalid");
    else if (isEmpty())
    {
        addLast(value);
        return;
    }
    if (index == 0)
    {
        Node *newNode = new Node();
        newNode->value = value;
        newNode->next = listdetails.head;
        listdetails.head = newNode;
        listdetails.size++;
    }
    else
    {
        int ind = 0;
        Node *newNode = new Node();
        newNode->value = value;
        Node *temp = listdetails.head;
        while (ind != index - 1)
        {
            temp = temp->next;
            ind++;
        }
        newNode->next = temp->next;
        newNode->previous = temp;
        temp->next = newNode;
        if (newNode->next == nullptr)
            listdetails.tail = newNode;
        listdetails.size++;
    }
    return;
}
template <typename T>
T DoubleLinkedList<T>::get(int index)
{
    if (!isIndexValid(index))
    {
        throw invalid_argument("index number is invalid");
    }
    Node *currentNode = listdetails.head;
    while (index > 0)
    {
        currentNode = currentNode->next;
        index--;
    }
    return currentNode->value;
}
template <typename T>
bool DoubleLinkedList<T>::contains(T value)
{
    return indexOf(value) != -1;
}
template <typename T>
T DoubleLinkedList<T>::removeFirst()
{
    if (isEmpty())
        throw invalid_argument("List is Empty");
    T removedValue;
    if (listdetails.head == listdetails.tail)
    {
        Node *currentNode = listdetails.head;
        removedValue = currentNode->value;
        delete currentNode;
        listdetails.head = listdetails.tail = nullptr;
        listdetails.size--;
    }
    else
    {
        Node *currentNode = listdetails.head;
        removedValue = currentNode->value;
        listdetails.head = listdetails.head->next;
        listdetails.head->previous = nullptr;
        delete currentNode;
        listdetails.size--;
    }
    return removedValue;
}
template <typename T>
T DoubleLinkedList<T>::remove(T value)
{
    if (isEmpty())
        throw invalid_argument("List is Empty");

    T removedValue;
    if (listdetails.head->value == value)
    {
        Node *deleteit = listdetails.head;
        listdetails.head = listdetails.head->next;
        if (listdetails.head->next != nullptr)
            listdetails.head->previous = nullptr; //removing previous pointer
        else
        {
            listdetails.tail = listdetails.head;
        }
        removedValue = deleteit->value;
        delete deleteit;
        listdetails.size--;
        return removedValue;
    }
    else
    {
        Node *currentnode = listdetails.head;
        while (currentnode->next->value != value)
        {
            if (currentnode->next == nullptr)
                return false;
            currentnode = currentnode->next;
        }

        Node *deleteit = currentnode->next;
        currentnode->next = currentnode->next->next;
        if (currentnode->next != nullptr)
            currentnode->next->previous = currentnode;
        else
        {
            listdetails.tail = currentnode;
        }
        removedValue = deleteit->value;
        delete deleteit;
        listdetails.size--;
        return removedValue;
    }
}

template <typename T>
int DoubleLinkedList<T>::indexOf(T value)
{
    if (isEmpty())
        throw invalid_argument("List is Empty");
    else
    {
        Node *currentNode = listdetails.head;
        int index = 0;
        while (currentNode->value != value)
        {
            if (currentNode->next == nullptr)
            {
                return -1;
            }
            currentNode = currentNode->next;
            index++;
        }
        return index;
    }
}

template <typename T>
T DoubleLinkedList<T>::removeLast()
{
    if (isEmpty())
        throw invalid_argument("List is Empty");
    T removedValue;
    if (listdetails.head == listdetails.tail)
    {
        Node *currentNode = listdetails.tail;
        removedValue = currentNode->value;
        delete currentNode;
        listdetails.head = listdetails.tail = nullptr;
        listdetails.size--;
    }
    else
    {
        Node *currentNode = listdetails.tail;
        removedValue = currentNode->value;
        listdetails.tail = listdetails.tail->previous;
        listdetails.tail->next = nullptr;
        delete currentNode;
        listdetails.size--;
    }
    return removedValue;
}
template <typename T>
T DoubleLinkedList<T>::removeAt(int index)
{

    if (isEmpty())
        throw invalid_argument("List is Empty");

    if (!isIndexValid(index))
        throw invalid_argument("index number is invalid");

    T removedValue;
    if (index == 0)
    {
        Node *deleteit = listdetails.head;
        listdetails.head = listdetails.head->next;
        listdetails.head->previous = nullptr;
        removedValue = deleteit->value;
        delete deleteit;
        listdetails.size--;
        return removedValue;
    }
    else
    {
        Node *currentNode = listdetails.head;
        int c = 0;
        while (c != (index - 1))
        {
            currentNode = currentNode->next;
            c++;
        }
        Node *deleteit = currentNode->next;
        currentNode->next = currentNode->next->next;
        if (currentNode->next != nullptr)
            currentNode->next->previous = currentNode;
        else
        {
            listdetails.tail = currentNode;
        }
        removedValue = deleteit->value;
        delete deleteit;
        listdetails.size--;
        return removedValue;
    }
}
template <typename T>
void DoubleLinkedList<T>::clear()
{
    if (isEmpty())
        return;
    while (listdetails.head->next != nullptr)
    {
        Node *currentNode = listdetails.head;
        listdetails.head = listdetails.head->next;
        delete currentNode;
    }
    listdetails.size = 0;
    listdetails.head = listdetails.tail = nullptr;
    return;
}
template <typename T>
int DoubleLinkedList<T>::getSize()
{
    return listdetails.size;
}
template <typename T>
bool DoubleLinkedList<T>::isEmpty()
{
    return listdetails.size == 0;
}
template <typename T>
T DoubleLinkedList<T>::peekFirst()
{
    if (isEmpty())
        throw invalid_argument("List is Empty");
    return listdetails.head->value;
}
template <typename T>
T DoubleLinkedList<T>::peekLast()
{
    if (isEmpty())
        throw invalid_argument("List is Empty");
    return listdetails.tail->value;
}
template <typename T>
void DoubleLinkedList<T>::traverseList()
{
    if (isEmpty())
    {
        cout << "[]" << endl;
        return;
    }
    Node *currentNode = listdetails.head;
    cout << "[ ";
    while (currentNode->next != nullptr)
    {
        cout << currentNode->value << ", ";
        currentNode = currentNode->next;
        if (currentNode->next == nullptr)
            cout << currentNode->value;
    }
    cout << " ]" << endl;
    return;
}
template <typename T>
void DoubleLinkedList<T>::traverseBackwardList()
{
    if (isEmpty())
    {
        cout << "[]" << endl;
        return;
    }
    Node *currentNode = listdetails.tail;
    cout << "[ ";
    while (currentNode->previous != nullptr)
    {
        cout << currentNode->value << " ";
        currentNode = currentNode->previous;
        if (currentNode->previous == nullptr)
            cout << currentNode->value;
    }
    cout << " ]" << endl;
    return;
}