#ifndef MYSTRINGCLASS_H
#define MYSTRINGCLASS_H

#include <cstring>
#include <string>

class MyStringClass
{
public:
    MyStringClass() = default;
    MyStringClass(const char* str);
    MyStringClass(size_t number, char value);
    ~MyStringClass();
    MyStringClass(const MyStringClass& other);
    MyStringClass &operator=(MyStringClass other);
    char& operator[](int index);
    const char& operator[](int index) const;
    MyStringClass& operator+=(const MyStringClass& other);

    friend MyStringClass operator+(const MyStringClass& a, const MyStringClass& b);
    friend bool operator<(const MyStringClass& a, const MyStringClass& b);
    friend bool operator>(const MyStringClass& a, const MyStringClass& b);
    friend bool operator==(const MyStringClass& a, const MyStringClass& b);

    friend std::ostream& operator<<(std::ostream& out, const MyStringClass& str);
    friend std::istream& operator>>(std::istream& in, MyStringClass& str);

private:
    void swap(MyStringClass& other);

private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    char* m_string = nullptr;
};



#endif // MYSTRINGCLASS_H
