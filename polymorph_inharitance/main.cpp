#include <iostream>

class Granny
{
    friend int main();
protected:
    int x = 0;
    void f(){std::cout << "f virt gr method";}
    ~Granny() = default;
};

class Dad:virtual Granny
{
protected:

    int z = 2;
    virtual void f() {std::cout << "f virt dad method";}
    void q(){std::cout << "q method";}
    virtual ~Dad() = default;
};

class Mom:virtual Granny
{
    friend int main();
    friend class Son;
    int y = 1;
    virtual void f();
    virtual void g() {std::cout << "g mom method";}
    //~Mom() override = default;
};

class Son:Mom
{
    friend int main();
    void f() final {std::cout << "f virt son method";}
    int j = 6;
    void g() final {std::cout << "g son method";}
    //void q() final {std::cout << "q son method";}
    //~Son() override = default;
};


using namespace std;

int main()
{
//    Mom m;
    //m.f();
    Son s;
    s.f();
    cout << endl;
    return 0;
}
