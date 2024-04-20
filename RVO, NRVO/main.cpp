#include <iostream>

using namespace std;

class Optional
{
public:
    Optional() {std::cout << "constructed" << endl;}

    Optional(const Optional&) {std::cout << "copyed" << endl;}

    Optional(Optional&&) {std::cout << "moved" << endl;}

    ~Optional() {std::cout << "destroyed" << endl;}
};

Optional funk(Optional&& a)
{
    return std::move(a);
}

int main()
{
    Optional a;
    Optional b = funk(std::move(a)); // copy elision
    return 0;
}
