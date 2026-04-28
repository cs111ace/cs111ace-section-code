#include <iostream>

int foo() {
    std::cout << "hello from foo" << std::endl;
    int y = 42;
    return y;
}


int *cooked()
{
    int x = 10;
    return &x;
}

int main()
{
    int *x = cooked();
    auto y = foo();
    std::cout << *x << std::endl;
    return 0;
}