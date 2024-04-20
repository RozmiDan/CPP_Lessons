#include <iostream>

using namespace std;

class String
{
private:
    char* arr = nullptr;
    size_t size = 0;
    size_t capacity = 0;
public:
    String() = default;
    String(size_t sz);
    String(const String& other); //copy constructor
    ~String();
    String& operator=(String other); //assignment operator
    void swap(String& other);
};

String::String(size_t sz):arr(new char[sz+1])
        , size(sz)
        , capacity(sz + 1)
{}

String::String(const String& other): arr(new char [other.capacity])
        , size(other.size)
        , capacity(other.capacity)
{
    memcpy(arr, other.arr, size + 1);
    arr[size] = '\0';
}

String::~String()
{
    delete [] arr;
}

//copy and swap idiom
String& String::operator= (String other)
{
    swap(other);
    return *this;
}

void String::swap(String& other)
{
    std::swap(arr,other.arr);
    std::swap(size,other.size);
    std::swap(capacity,other.capacity);
}

int main()
{

    return 0;
}
