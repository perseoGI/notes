#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

// Limited to only two lambdas...
template <typename Lambda1, typename Lambda2>
struct Merged : Lambda1, Lambda2 {
    Merged(Lambda1 l1, Lambda2 l2)
        : Lambda1{std::move(l1)}
        , Lambda2{std::move(l2)}
    {
    }

    using Lambda1::operator();
    using Lambda2::operator();
};

// Variadic using
template <typename... Lambda>
struct MergedVariadic : Lambda... {
    MergedVariadic(Lambda &&... l)
        : Lambda{std::forward<Lambda>(l)}...
    {
    }

    using Lambda::operator()...;
};


int main(int argc, char *argv[])
{
    auto merged = Merged([](int num) { return num + 1; }, [](const std::string &str) { std::cout << str << std::endl; });
    std::cout << merged(10) << std::endl;
    merged("hola");

    auto mergedVariadic = MergedVariadic([](int num) { return num + 1; }, [](const std::string &str) { std::cout << str << std::endl; },
                                         [](char c){std::cout << c + 1 << std::endl;});

    mergedVariadic('A');


    int sumInt{};
    double sumDouble{};
    auto visitor = MergedVariadic([&sumInt](int num) {sumInt += num;}, [&sumDouble](double num){sumDouble += num;});
    std::vector<std::variant<int,double>> vec {1, 256.3, 34, 6433.3};

    std::for_each(vec.begin(), vec.end(), [&visitor](auto num){std::visit(visitor, num);});

    std::cout << sumInt << " " << sumDouble << std::endl;

    return 0;
}
