#include <atomic>
#include <iostream>

int main()
{
    std::atomic<int> var;
    int spinlock = 0;
    std::cout << "Value of spinlock before modification: " << spinlock << std::endl;

    spinlock = var.exchange(1);
    std::cout << "Value of spinlock (line 11): " << spinlock << std::endl;

    spinlock = var.exchange(2);
    std::cout << "Value of spinlock (line 14): " << spinlock << std::endl;

    return 0;
}