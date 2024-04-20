#include <iostream>

using namespace std;

template <typename T>
class List{

public:
    List();
    ~List();
    int get_size() const;
    void pop_front();
    void pop_back();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int index);
    void removeAt(int index);
    void clear();
    T& operator [](int index);

private:

    template<typename Type>
    class Node{
    public:
        Node(Type data = Type(), Node* pnext = nullptr)
        {
            this->_pNext = pnext;
            this->m_data = data;
        }

        Type m_data;
        Node* _pNext;
    };

    int m_size;
    Node<T>* head;

};

int main()
{
    List<int> lst;
    lst.push_front(9);
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(8);
    lst.push_front(6);
    //lst.pop_back();

    for (int i = 0; i < lst.get_size(); i++)
    {
        cout << lst[i] << " ";
    }
    cout << endl;

    lst.insert(64,2);
    lst.removeAt(2);
    lst.pop_back();

    for (int i = 0; i < lst.get_size(); i++)
    {
        cout << lst[i] << " ";
    }
    cout << endl;

    return 0;
}

template <typename T>
List<T>::List()
{
    this->head = nullptr;
    this->m_size = 0;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
int List<T>::get_size() const
{
    return m_size;
}

template<typename T>
void List<T>::pop_front()
{
    Node<T>* tmp = head;
    head = head->_pNext;
    delete tmp;
    m_size--;
}

template<typename T>
void List<T>::pop_back()
{
    removeAt(m_size - 1);
}

template<typename T>
void List<T>::push_front(T data)
{
    if(head == nullptr)
    {
        head = new Node<T>(data);
    }
    else
    {
        Node<T>* tmp = head;
        head = new Node<T>(data,tmp);
    }
    m_size++;
}

template<typename T>
void List<T>::clear()
{
    while (m_size)
    {
        pop_front();
    }
}

template <typename T>
void List<T>::push_back(T data)
{
    if(head == nullptr)
    {
        head = new Node<T>(data);
    }

    else
    {
        Node<T>* current = head;
        while (current->_pNext != nullptr) {
            current = current->_pNext;
        }
        current->_pNext = new Node<T>(data);
    }
    m_size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
    if(head == nullptr)
    {
        push_front(data);
    }
    else
    {
        Node<T>* tmp = head;
        int counter = 0;
        while (counter != index - 1)
        {
            counter++;
            tmp = tmp->_pNext;
        }
        tmp->_pNext = new Node<T>(data,tmp->_pNext);
    }
    m_size++;
}

template<typename T>
void List<T>::removeAt(int index)
{
    if(index == 0)
    {
        pop_front();
    }
    else
    {
        Node<T>* tmp = head;
        int counter = 0;
        while (counter != index - 1)
        {
            counter++;
            tmp = tmp->_pNext;
        }
        Node<T>* nodeForDell = tmp->_pNext;
        tmp->_pNext = nodeForDell->_pNext;
        delete nodeForDell;
        m_size--;
    }
}

template<typename T>
T &List<T>::operator [](int index)
{
    if(index <= m_size)
    {
        int counter = 0;
        Node<T>* current = head;
        while (counter != index)
        {
            current = current->_pNext;
            counter++;
        }
        return current->m_data;
    }
}
