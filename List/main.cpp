#include <iostream>
//#include "list.h"

using namespace std;

//template<typename T>
//class List;

template <typename T>
class List
{
public:
    List();
    void push_back(T data);
    void dispList();
    int getSize();
    T& operator [](const int index);
private:

    template<typename Y>
    class Node
    {
    public:
        Node(T data = Y(), Node* pNext = nullptr)
        {
            this->_data = data;
            this->_pNext = pNext;
        }

        Y _data;
        Node *_pNext;

    };

    int counter;
    Node<T>* head;
};

template<typename T>
List<T>::List()
{
    counter = 0;
    head = nullptr;
}

template<typename T>
void List<T>::push_back(T data)
{
    if(head == nullptr)
    {
        head = new Node<T>(data);
    }
    else
    {
        Node<T>* current = head;
        while(current->_pNext != nullptr)
        {
            current = current->_pNext;
        }
        current->_pNext = new Node<T>(data);
    }
    counter++;
}

template<typename T>
void List<T>::dispList()
{
    Node<T>* runner = head;
    while (runner->_pNext != nullptr)
    {
        cout << runner->_data << "\t";
        runner = runner->_pNext;
    }
    cout << runner->_data << "\n";
}

template<typename T>
int List<T>::getSize()
{
    return counter;
}

template<typename T>
T &List<T>::operator [](const int index)
{
    int counter = 0;
    Node<T>* current = head;
    while(counter != index)
    {
        current = current->_pNext;
        counter++;
    }
    return current->_data;
}



int main()
{
    List<int> lst;
    //cout << lst.getSize();
    lst.push_back(3);
    lst.push_back(7);
    cout << lst[0] << endl;
    lst.push_back(1);
    lst.push_back(9);
    cout << lst[3] << endl;
    lst.push_back(8);
    lst.dispList();
    cout << lst.getSize() << endl;
    cout << lst[2];
    return 0;
}
