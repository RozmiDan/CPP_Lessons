#include <iostream>
#include <mystringclass.h>

using namespace std;

class A
{
public:
    void af() const
    {
        cout << "2";
    }
};

void funk(const char* arr)
{
    int af = std::strlen(arr);
    cout << af;
    for(int i = 0; i < af; i++)
    {
        cout << arr[i];
    }
    cout << endl;
}

int main()
{
    A f;
    f.af();
//    MyStringClass a("sdfdsfd");
//    funk("sdtrtbvcv");
//    cout << endl;
    return 0;
}
