#include <iostream>
#include <memory>

template<typename T>
struct default_delete
{
    void operator()(T* ptr) const
    {
        delete ptr;
    }
};

template<typename T, class Deleter = std::default_delete<T>>
class my_unique_ptr
{
public:
    my_unique_ptr(T* ptr) : ptr_(ptr){}
    my_unique_ptr(T* ptr, Deleter del) : ptr_(ptr), del_(del){}
    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;
    ~my_unique_ptr(){
        del_(ptr_);
    }
    my_unique_ptr(my_unique_ptr&& other) noexcept
        : ptr_(nullptr){
        this->swap(other);
    }

    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept
    {
        other.swap(*this);
        return *this;
    }

    void swap(my_unique_ptr& other) noexcept
    {
        std::swap(ptr_, other.ptr_);
        std::swap(del_, other.del_);
    }

    T& operator*() const
    {
        return *ptr_;
    }

    T* operator->() const
    {
        return ptr_;
    }

    T* get() const
    {
        return ptr_;
    }

    T* release() noexcept
    {
        T* tmp = nullptr;
        std::swap(ptr_, tmp);
        return tmp;
    }

    void reset()
    {
        del_(ptr_);;
        ptr_ = nullptr;
    }

private:
    T* ptr_;
    Deleter del_;
};

template <typename T, typename ... Args>
my_unique_ptr<T> make_myunique_ptr(Args&&... args)
{
    return my_unique_ptr<T>(new T (std::forward<Args>(args)...));
}

struct Abs
{
    Abs(const std::string& st, size_t val) : str(st), count(val){
        std::cout << "Abs()" << std::endl;
    }

    Abs(const Abs& other) : str(other.str), count(other.count){
        std::cout << "Abs(const Abs& other)" << std::endl;
    }

    Abs& operator=(const Abs& other){
        str = other.str;
        count = other.count;
        std::cout << "Abs operator=(const Abs& other)" << std::endl;
        return *this;
    }

    Abs(Abs&& other) : str(std::move(other.str)), count(other.count){
        other.count = 0;
        std::cout << "Abs(Abs&& other)" << std::endl;
    }

    Abs& operator=(Abs&& other){
        str = std::move(other.str);
        count = 0;
        other.swap(*this);
        std::cout << "Abs& operator=(Abs&& other)" << std::endl;
        return *this;
    }

    void swap(Abs& other) noexcept
    {
        std::swap(str, other.str);
        std::swap(count, other.count);
    }

public:
    std::string str;
    size_t count;
};



int main()
{
    my_unique_ptr<int> prt(new int (20));

    my_unique_ptr<int> b = std::move(prt);

    my_unique_ptr<int> c(new int (12));

    //cout << *c.get() << endl;

    c = std::move(b);

    *c = 23;

    my_unique_ptr<Abs> a = make_myunique_ptr<Abs>("4fdsfdssd", 32);

    my_unique_ptr<Abs> df = make_myunique_ptr<Abs>("frffffffffffffffffff", 56);

    my_unique_ptr<Abs> cc(std::move(df));

//    std::cout << a->str << std::endl;
//    std::cout << cc->str << std::endl;
//    std::cout << df->str << std::endl;

    {
        int* fst_p = new int (221);
        my_unique_ptr<int> fst_uniq(fst_p);
        {
            my_unique_ptr<int> scnd_uniq(fst_p);
        }
        std::cout << *fst_uniq.get(); // UB
    }

    //std::cout << *b.get() << " " << *prt.get() << " " << *c.get();

    return 0;
}
