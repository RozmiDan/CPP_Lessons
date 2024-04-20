#include "mystringclass.h"

MyStringClass::MyStringClass(const char* str): m_size(std::strlen(str))
                , m_capacity(m_size * 2 + 1)
                , m_string(new char[m_capacity])
{
    memcpy(m_string, str, m_size + 1);
    m_string[m_size + 1] = '\0';
}

MyStringClass::MyStringClass(size_t number, char value): m_size(number)
                , m_capacity(m_size * 2 + 1)
                , m_string(new char [m_capacity])
{
    std::memset(m_string, value, number); //faster then cycle, bcz used machine word instead 1 byte in cycle
}

MyStringClass::MyStringClass(const MyStringClass& other): m_size(other.m_size)
                , m_capacity(other.m_capacity)
                , m_string(new char[m_capacity])
{
    memcpy(m_string, other.m_string, m_size + 1); //faster then cycle, bcz used machine word instead 1 byte in cycle
}

MyStringClass::~MyStringClass()
{
    delete[] m_string;
}

//copy and swap
MyStringClass& MyStringClass::operator=(MyStringClass other)
{
    swap(other); //destructor will delete memory of other object
    return *this;
}

char& MyStringClass::operator[](int index)
{
    return m_string[index];
}

const char& MyStringClass::operator[](int index) const
{
    return m_string[index];
}

void MyStringClass::swap(MyStringClass &other)
{
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_string, other.m_string);
}

MyStringClass& MyStringClass::operator+=(const MyStringClass &other)
{
    if(m_capacity <= m_size + other.m_size)
    {
        char* new_str = new char [(m_size + other.m_size) * 2 + 1];
        memcpy(new_str, m_string, m_size);
        delete [] m_string;
        m_string = new_str;
    }
    memcpy(m_string + m_size, other.m_string, other.m_size);
    m_size += other.m_size;
    m_string[m_size+1] = '\0';
    return *this;
}

MyStringClass operator+(const MyStringClass& a, const MyStringClass& b)
{
    MyStringClass res = a; //no copy res in return bcz RVO(return value optimiz-n)
    res += b;
    return res;
}

bool operator<(const MyStringClass& a, const MyStringClass& b)
{
    return (a.m_size < b.m_size);
}

bool operator>(const MyStringClass& a, const MyStringClass& b)
{
    return (b < a);
}

bool operator==(const MyStringClass& a, const MyStringClass& b)
{
    return (a.m_size == b.m_size);
}

std::ostream& operator<<(std::ostream& out, const MyStringClass& str)
{
    return (out << str.m_string);
}

std::istream& operator>>(std::istream& in, MyStringClass& str)
{
    //TODO
    return in;
}
