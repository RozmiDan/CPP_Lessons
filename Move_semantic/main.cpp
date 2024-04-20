#include <iostream>

using namespace std;

template <typename T>
struct Array
{
    Array(size_t sz) : size_(sz), data_(new T [size_])
    {}

    Array(const Array& other) : size_(other.size_), data_(new T [size_])
    {
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    Array& operator=(Array other)
    {
        if(&other == this)
            return *this;
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);

        return *this;
    }

    ~Array()
    {
        delete [] data_;
    }

    size_t size() const
    {
        return size_;
    }

    T& operator[](size_t index)
    {
        return data_[index];
    }

    const T& operator[](size_t index) const
    {
        return data_[index];
    }

    Array(Array&& other) : data_(other.data_), size_(other.size_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    Array& operator=(Array&& other)
    {
        if(&other == this)
            return *this;

        for(size_t index = 0; index < size_; ++index)
        {
            data_[index].~T();
        }
        delete data_;
        data_ = other.data_;
        other.data_ = nullptr;
        size_ = other.size_;
        other.size_ = 0;
        return *this;
    }

private:
    size_t size_;
    T* data_;
};

template <typename T>
T&& move(T& value)
{
    return static_cast<T&&>(value);
}

template <typename T>
void swap(T lhv, T rhv)
{
    T tmp = std::move(rhv);
    rhv = std::move(lhv);
    lhv = std::move(tmp);
}

template <typename T>
int&& fd(T&& value)
{
    cout << "s" << value;
    return move(value);

}

int main()
{
    int f = 23;
    fd<int>(std::move(f));

//    int&& a = 23;
//    a = 5;
////  int&& b = a; //CE a - lvalue
//    int&& b = move(a);
//    int&& c = static_cast<int&&>(b);
//    c = 10;
//    cout << a << endl; // 10

    int a = 27;
    int const b = 412;
    int * pa = &a;
    int const * const * p4 =(&pa);

    return 0;
}
