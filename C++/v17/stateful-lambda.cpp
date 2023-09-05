#include <iostream>
#include <utility>

auto fib = [a = 0, b = 1]() mutable {
    a = std::exchange(b, b + a);
    return a;
};

auto fibInjectable = [a = 0, b = 1]() mutable {
    struct Results {
        int &a;
        int &b;
        Results next(int num = 1)
        {
            while (num > 0) {
                a = std::exchange(b, b + a);
                --num;
            }
            return *this;
        }
        operator int() { return a; }
    };
    return Results{a, b}.next();
};

int main()
{
    std::cout << fib() << std::endl;
    std::cout << fib() << std::endl;
    std::cout << fib() << std::endl;
    std::cout << fib() << std::endl;

    std::cout << fibInjectable().next().next().next(4) << std::endl;
}
