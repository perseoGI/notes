#include <iostream>
#include <utility>
#include <thread>
#include <future>

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

auto fun = [n = 0]() mutable { return ++n; };
auto funStatic = []() {
    static auto n{0};
    return ++n;
};

auto funThreadSafe = []() {
    thread_local auto n{0};
    return ++n;
};


int main()
{
    std::cout << fib() << std::endl;
    std::cout << fib() << std::endl;
    std::cout << fib() << std::endl;
    std::cout << fib() << std::endl;

    std::cout << fibInjectable().next().next().next(4) << std::endl;
    auto funCopyMutable = fun;
    funCopyMutable(); // this wont affect local lambda -> stateful lambdas dont share values
    std::cout << fun() << std::endl;
    auto funCopy = funStatic;
    funStatic();
    funCopy(); // share the same static member
    
    auto res = std::async(std::launch::async, funStatic);
    res.get(); // will increment the static variable

    auto funCopySafe = funThreadSafe;
    funCopySafe();

    auto resSafe = std::async(std::launch::async, funThreadSafe);
    resSafe.get(); // will not increment static variable as it is thread_local

    std::cout << funStatic() << std::endl;
    std::cout << funThreadSafe() << std::endl;
}
