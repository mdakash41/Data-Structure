#include <iostream>

#define intsize int //can be used long long int instead of int

using namespace std;

class DynamicArray
{
private:
    intsize arraylength;
    intsize arrayCapacity;
    intsize *array;
    bool hasSpace();
    void allocateNewSpace();

public:
    DynamicArray(intsize size);
    DynamicArray();
    void printAll();
    bool addValue(intsize val);
    intsize hasValue(intsize value);
    intsize valueAt(intsize position);
    bool removeValue(intsize val);
    bool removeFrom(intsize position);
    ~DynamicArray();
};

DynamicArray::DynamicArray(intsize size)
{
    if (size > 0)
    {
        this->array = new intsize[size];
        arrayCapacity = size;
        arraylength = 0;
    }
    else
    {
        this->array = new int[1];
    }
}

DynamicArray::DynamicArray()
{
    this->array = new intsize[1];
    arrayCapacity = 1;
    arraylength = 0;
}

DynamicArray::~DynamicArray()
{
    delete[] array;
}

bool DynamicArray::addValue(intsize val)
{
    if (!hasSpace())
    {
        allocateNewSpace();
    }
    array[arraylength++] = val;
    return true;
}

intsize DynamicArray::hasValue(intsize value)
{
    for (int i = 0; i < arraylength; i++)
    {
        if (array[i] == value)
            return i;
    }
    return -1;
}

intsize DynamicArray::valueAt(intsize position)
{
    if (position > -1 and position < arraylength)
        return array[position];
    throw out_of_range("Index number is wrong");
}

bool DynamicArray::removeValue(intsize value)
{
    bool flag = false;
    for (int i = 0; i < arraylength - 1; i++)
    {
        if (array[i] == value)
        {
            flag = true;
        }
        if (flag)
        {
            array[i] = array[i + 1];
        }
    }
    if (!flag)
    {
        if (array[arraylength - 1] == value)
        {
            array[arraylength - 1] = 0;
            flag = true;
        }
    }
    if (flag)
    {
        arraylength -= 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool DynamicArray::removeFrom(intsize position)
{
    if(position<0 or position>=arraylength)
        return false;
    if(position==(arraylength-1))
    {
        array[position]=0;
        arraylength-=1;
        return true;
    }
    else
    {
        for(int i=position;i<arraylength-1;i++)
        {
            array[position]=array[position+1];
        }
        arraylength--;
        return true;
    }
    
}

bool DynamicArray::hasSpace()
{
    return arrayCapacity > arraylength;
}

void DynamicArray::allocateNewSpace()
{
    intsize *newarray = new intsize[arrayCapacity];
    for (int i = 0; i < arraylength; i++)
        newarray[i] = array[i];
    delete[] array;
    this->array = new int[arrayCapacity * 2];
    copy(newarray, newarray + arrayCapacity, array);
    this->arrayCapacity *= 2;
    return;
}

void DynamicArray::printAll()
{
    cout << "Total Element  : " << arraylength << endl;
    cout << "Total Capacity : " << arrayCapacity << endl;
    for (int i = 0; i < arraylength; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    return;
}

int main()
{

    DynamicArray num(2);
    num.printAll();
    num.addValue(45);
    num.addValue(34);
    num.printAll();
    num.addValue(25);
    num.printAll();

    // int *ar;
    // ar = new int[3];
    // for (int i = 0; i < 3; i++)
    //     ar[i] = i + 1;
    // for (int i = 0; i < 3; i++)
    //     cout << ar[i] << " ";
    // cout << endl;
    // cout << "deleting array" << endl;
    // int *newarray = new int[6];
    // for (int i = 0; i < 3; i++)
    //     newarray[i] = ar[i];
    // delete[] ar;
    // ar = new int[6];
    // copy(newarray, newarray + 3, ar);
    // for (int i = 0; i < 6; i++)
    //     cout << ar[i] << " ";
    // cout << endl;

    return 0;
}