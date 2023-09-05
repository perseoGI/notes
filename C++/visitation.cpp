#include <iostream>
#include <string>
#include <variant>
#include <numeric>

using ReturnType = std::variant<int, bool>;

struct IOperation {
    virtual ReturnType resultOf(int *begin, int *end) = 0;
    virtual ~IOperation() = default;
};

struct SumOperation : IOperation {
    ReturnType resultOf(int *begin, int *end) { return std::accumulate(begin, end, 0); }
};

struct BoolOperation : IOperation {
    virtual ReturnType resultOf(int *begin, int *end)
    { /* return bool */
        return true;
    }
};

// helper type for the visitor
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

void operate(IOperation *op)
{
    int arr[4]{1, 2, 3, 4};
    auto result = op->resultOf(std::begin(arr), std::end(arr));
    // Use visitation for type safe access

    std::visit(overloaded{
                   [](int result) { std::cout << "Integer: " << result << '\n'; },
                   [](bool result) { std::cout << "Boolean: " << std::boolalpha << result << '\n'; },
               },
               result);
}

int main(int argc, char *argv[])
{
    SumOperation sumOp;
    BoolOperation booleanOp;
    operate(&booleanOp);
    operate(&sumOp);
    return 0;
}
