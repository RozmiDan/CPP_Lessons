#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename Allocator = std::allocator<T>>
class MyVector
{
    size_t size = 0;
    size_t capacity = 0;
    T* arr = nullptr;
    Allocator alloc;

public:
    MyVector(size_t val): size(val), capacity(size * 2), arr(new T [capacity])
    {

    }    

private:
    template<bool IsConst>
    class My_base_iterrator
    {
        using refer_conditional = std::conditional<IsConst, const T&, T&>;
        using pointer_conditional = std::conditional<IsConst, const T*, T*>;
        using value_conditional = T;

        friend class MyVector<T>;

    public:
        ~My_base_iterrator() = default;
        My_base_iterrator(const My_base_iterrator& other) = default;
        My_base_iterrator& operator=(const My_base_iterrator& other) = default;

        refer_conditional operator*() const // если на итератор навешен const, то значение под ним изменять можно
        {
            return *m_ptr;
        }

        My_base_iterrator& operator+=(size_t value)
        {
            m_ptr += value;
            return *this;
        }

        My_base_iterrator& operator++()
        {
            m_ptr += 1;
            return *this;
        }

        My_base_iterrator operator++(int)
        {
            My_base_iterrator copy(this);
            m_ptr += 1;
            return copy;
        }

        pointer_conditional operator->() const
        {
            return m_ptr;
        }

        operator My_base_iterrator<true>() const
        {
            return m_ptr;
        }
    private:
        My_base_iterrator(T* ptr) : m_ptr(ptr){}
        pointer_conditional m_ptr;
    };

public:

    using iterator = My_base_iterrator<false>;
    using const_iterator = My_base_iterrator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin()
    {
       return (arr);
    }

    iterator end()
    {
        return (arr + size);
    }

    //если вектор const, то метод должен возвращать const iterator
    const_iterator begin() const
    {
       return (arr);
    }

    const_iterator end() const
    {
        return (arr + size);
    }

    const_iterator cbegin() const
    {
       return (arr);
    }

    const_iterator cend() const
    {
        return (arr + size);
    }

    void reserve(size_t newcap)
    {
        if(newcap <= capacity)
            return;

        //зарезервировали память, try catch не нужен т.к. ничего не сделано еще
        //T* new_arr = reinterpret_cast<T*>(new char [newcap * sizeof(T)]);
        T* new_arr = alloc.allocate(newcap);

        size_t index = 0;
        //перенесли значения
        //обрабатываем если при конструкторе от T исключение
        try {
            for (; index < size; ++index) {
                //new (new_arr + index) T(arr[index]); //placement new
                alloc.construct(new_arr + index, arr[index]);
            }
        } catch (...) {
            //очищаем память если не удалось выполнить placemenew
            for (size_t i = 0; i < index; ++i) {
                //arr[i].~T();
                alloc.destroy(arr[i]);
            }
            //delete [] reinterpret_cast<char*>(new_arr);
            alloc.deallocate(new_arr, newcap);
            //вниз пробрасываем то что поймали
            throw;
        }


        //удалили старый массив
        for (size_t i = 0; i < size; ++i) {
            //arr[i].~T();
            alloc.destroy(arr[i]);
        }
        //delete [] reinterpret_cast<char*>(arr);
        alloc.deallocate(arr, capacity);
        //переназначили поля
        capacity = newcap;
        arr = new_arr;

    }

    void pushback(const T& obj)
    {
        if(size + 1 > capacity)
            reserve();
        arr[size] = obj;
        size++;
    }



    ~MyVector()
    {

    }
};

template <>
class MyVector<bool>
{
    size_t size = 0;
    size_t capacity = 0;
    char* arr = nullptr;

    class BitReference
    {
        char* m_cell;
        uint8_t m_index;

    public:
        BitReference(char* cell, uint8_t index) : m_cell(cell), m_index(index){}
        BitReference operator=(bool val)
        {
            if(val)
                *m_cell |= (1 << m_index);
            else
                *m_cell &= ~(1 << m_index);
            return *this;
        }
    };

public:
    BitReference operator[](size_t index)
    {
        return BitReference(arr + index/8, index % 8);
    }
};

int main()
{
    vector<int>::iterator();
    vector<bool> a(2);
    cout << "Hello World!" << endl;
    return 0;
}
