#include <iostream>
#include <memory>

template <typename T>
class my_shared_ptr
{
public:
    my_shared_ptr(T* ptr): data(ptr), counter(new size_t (1)){}

    ~my_shared_ptr(){
        if(!counter) //if share_ptr doesn't point anywhere
            return;
        *--counter;
        if(*counter == 0)
        {
            delete data;
            delete counter;
        }
    }

    my_shared_ptr(const my_shared_ptr& other) : data(other.data), counter(other.counter){
        ++(*counter);
    }

    my_shared_ptr& operator=(const my_shared_ptr& other){
        --*counter;
        if(*counter == 0)
        {
            delete data;
            delete counter;
        }
        data = other.data;
        counter = other.counter;
        ++(*counter);
        return *this;
    }

    my_shared_ptr(my_shared_ptr&& other) noexcept {
        data = nullptr;
        counter = nullptr;
        other.swap(*this);
    }

    my_shared_ptr operator=(my_shared_ptr&& other) noexcept {
        --*counter;
        if(*counter == 0)
        {
            delete data;
            delete counter;
        }
        data = other.data;
        counter = other.counter;
        other.data = nullptr;
        other.counter = nullptr;
    }

    void swap(my_shared_ptr& other)
    {
        std::swap(data, other.data);
        std::swap(counter, other.counter);
    }

private:

    template <typename ...Args>
    my_shared_ptr<T> make_my_shared_ptr(Args&&... args); // делаем другом, чтобы уметь создавать
                                                         // sh_ptr из ф-ии make_shared()
    struct ControlBlock
    {
        T data;
        size_t counter;
    };

    my_shared_ptr(ControlBlock* ptr):cbl(ptr){} // заприваченный конструктор, который может
                                                // вызвать только make_shared()
    ControlBlock* cbl;
    T* data;
    size_t* counter;
};

template <typename T, typename ...Args>
my_shared_ptr<T> make_my_shared_ptr(Args&&... args)
{
    auto* cntrl_blck = new typename my_shared_ptr<T>::ControlBlock(T(std::forward<Args>(args)...), 1); // выделяем память под ControlBlock
    return my_shared_ptr<T>(cntrl_blck);                                                              // создаемся от приватного констр.
}

int main()
{
//    auto p = ControlBloc<int>{int(23),1};
//    std::cout << p.data;

    auto p = std::shared_ptr<int>(new int (234));
    auto q(p);
    auto o = q;                 // p = q = o -> 234
    *o = 23;                    // p = q = o -> 23
    auto j(std::move(o));       // p = q = j -> 23, o -> nullptr

    std::cout << *p <<' '<< *q << ' ' << *j << ' ' << *o;

    auto a = std::make_shared<int>(4);


    return 0;
}
