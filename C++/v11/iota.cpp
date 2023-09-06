#include <algorithm>
#include <numeric>
#include <iostream>
#include <array>

int main(int argc, char *argv[])
{
    std::array<int, 10> arr;
    auto print = [&arr]() {
        for (const auto e : arr)
            std::cout << e << " ";
        std::cout << std::endl;
    };

    std::iota(arr.begin(), arr.end(), 4);
    print();

    // C++98 std::generate -> much powerful than iota
    std::generate(arr.begin(), arr.end(), [i = 1]() mutable { return i += i; });
    print();

    return 0;
}
