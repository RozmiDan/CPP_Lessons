#include <iostream>

using namespace std;

template <typename T>
class allocator
{
    T* allocate(size_t count) // выделяем память размером count
    {
        return reinterpret_cast<T*>(new char [count * sizeof (T)]);      //как в векторе
    }

    void deallocate(T* ptr, size_t count) //count нужен по стандрту, но для обычного алок не нужен
    {
        delete [] reinterpret_cast<char*>(ptr); // очищаем выделенную память
    }

    template<typename U, typename... Args>  // конструируем объект типа U на выделенной памяти
    void construct(U* ptr, const Args&... args) // от переменного числа шаблонных аргументов
    {                                               // для того чтобы вызывать не только станд конструктор
        new (ptr) U(args...);
    }

    template<typename U> // удаление для внутренних типов контейнера по типу Node
    void destroy(U* ptr)
    {
        ptr -> ~U();
    }

    template<typename U>
    allocator(allocator<U>){}

    template<typename U>
    struct rebind
    {
        using value = allocator<U>;
    };
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
