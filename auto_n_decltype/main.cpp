#include <iostream>

using namespace std;

template <typename T>
struct Debug
{
    Debug(T) = delete;
};

template<typename T>
void f(T& x){}

template <typename Container>
void funk(Container&& cont)
{
    for(auto&& value : cont)
        ;// ...
}

template <typename T>
auto funk_return(T var)
{
    if constexpr (var > 0) // OK
        return ++var;
    else {
        return 1u;
    }
}

template <auto N>
void funk_num(){}

template<typename Container>
auto funk(Container& cont, size_t index)
    -> decltype(cont[index])
{
    return cont[index];
}

template<typename Container>
decltype(auto) funk(Container& cont, size_t index)
{
    return cont[index];
}


int main()
{
    auto&& x = funk_return(21); // UB, var - hanging ref

    {
        auto x = 3;
        //auto& a = 2; //CE try to rval lref

        auto&& lva = a;  //int&
        lva = 12;
        auto&& rva = 12; //int&&
        rva = 16;

        std::cout << a << lva << rva; // 16 16 16
    }

    {
        auto a = 0;
        decltype(std::move(a))& b = a; // int&& + & = int&
        b += 2;
        std::cout << a << b; // 0 2
    }

    {
        auto a = 2;
        decltype((a)) b = a; // (a) - exprassion lvalue -> int&
        ++b;
        std::cout << a << b; // 3 3
    }

    {
        auto a = 23;            //int
        auto& b = a;            //int&
        decltype(b) c = a;      //int&
        decltype(b)& z = a;     //int& ref collap
        decltype(z)&& j = a;    //int& ref collap
        ++a;
        std::cout << a << b << c << z; // 24

        Debug<decltype(j)> a;
    }

    {
        std::string s = "Compiler";

        auto sz = s.size();              // ulonglong
        auto c1 = s[0];                  // char
        decltype(s[0]) c2 = s[7];        // char&
        decltype(s[0] + s[7]) c3 = s[1]; // int
        decltype(s) sa = s;              // std::string
        decltype((s)) sb = s;            // basic_string<char>&

        Debug<decltype()> a;
    }

    return 0;
}
