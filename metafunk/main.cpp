#include <iostream>
#include <vector>
#include <type_traits>
#include <assert.h>

//using namespace std;

//template <typename IterarratorFst, typename IterarratorScnd>
//int distantion(IterarratorFst it1, IterarratorScnd it2)
//{
//    if constexpr(is_same<IterarratorFst,IterarratorScnd>::value)
//    {
//        std::cout << "same";
//        return 0;
//    }
//    std::cout << "not the same";
//}


//class A
//{
//public:
//    class B
//    {
//        int x = 10;
//    public:
//        void getx()
//        {std::cout << x;}
//    };

//    class C
//    {
//        int x = 20;
//    public:
//        void getx()
//        {std::cout << x;}
//    };

//public:
//    A() = default;

//    using iter = B;
//    using constiter = C;
//};
//------------------------------
template <int ... Other>
struct IntList;

template <int First, int ... Other>
struct IntList <First, Other...>
{
    static int const Head = First;
    using Tail = IntList<Other...>;
};

template <>
struct IntList<>
{
};

//------------------------------

template <typename IntList>
struct Length
{
    static constexpr int value = 1 + Length<typename IntList::Tail>::value;
};

template <>
struct Length<IntList<>>
{
    static constexpr int value = 0;
};


//------------------------------

template <int Element, typename IL>
struct IntCons
{};

template <int Element, int ... List>
struct IntCons<Element, IntList<List...>>
{
    using type = IntList<Element, List...>;
};

//------------------------------

template <int Element, typename IL>
struct ConsInt
{};

template <int Element, int ... List>
struct ConsInt<Element, IntList<List...>>
{
    using type = IntList<List..., Element>;
};

//------------------------------

template <int N, typename IL = IntList<>>
struct Generate;

template <int N, int ... Types >
struct Generate<N, IntList<Types...>>
{
    using type = typename ConsInt<N-1, typename Generate<N - 1, IntList<Types...>>::type>::type;
};

template <>
struct Generate<0>
{
    using type = IntList<>;
};

//------------------------------

template<typename FirstList, typename SecondList, template <int, int> class Func>
struct Zip {};

template< int ... FstListTypes, int ... ScndListTypes, template <int, int> class Func>
struct Zip<IntList<FstListTypes ...>, IntList<ScndListTypes ...> , Func>
{
    // первый аргумент - новый элемент, второй - прошлая итерация листа
    using type = typename IntCons<Func <IntList<FstListTypes ...>::Head, IntList<ScndListTypes ...>::Head>::value,
                typename Zip<typename IntList<FstListTypes ...>::Tail, typename IntList<ScndListTypes ...>::Tail, Func >::type>::type;
};

template<template <int, int> class Func>
struct Zip<IntList<>, IntList<>, Func>
{
};

//............

//template <typename FirstList, typename SecondList, template <int, int> class Func>
//struct Zip;

//template <int ...FstListTypes, int ...ScndListTypes, template <int, int> class Op>
//struct Zip<IntList<FstListTypes...>, IntList<ScndListTypes...>, Op>
//{
//    using type = IntList<Op<FstListTypes, ScndListTypes>::value...>;
//};

int main()
{
//    using a = IntList<3,24,6,7,4>;
//    int b = a::Head;
//    using type = a::Tail;
//    std::cout << b;
    using a = IntCons<23,IntList<4,6,87,2>>;
    //std::cout << a::type::Head;
    constexpr int x = 4;
    using b = Generate<x>;
    using c = IntList<2,1,0>;
    //static_assert( std::is_same<c, y>::value );
    //assert(std::is_same_v<c,b>);

    //std::cout << b::type::Head;
    int arr[20]{0};
    std::cout << *(arr+10);
    return 0;
}
