#include <initializer_list>
#include <iostream>
#include <type_traits>

template <typename T>
void print(std::initializer_list<T> args)
{
    for (const auto &elem : args)
        std::cout << elem << ' ';
    std::cout << std::endl;
}

// Base case function
// Function parameter packc
void printVariadic()
{
    std::cout << std::endl;
}

// Template parameter pack
template <typename T, typename... Args>
// Function parameter packc
void printVariadic(const T &first, const Args &...args)
{
    std::cout << first;
    if (sizeof...(args) > 0)
        std::cout << ", ";
    printVariadic(args...);
}

template <typename T, typename... Args>
void printVariadicPerfectForwarding(T &&first, Args &&...args)
{
    std::cout << first;
    if (sizeof...(args) > 0)
        std::cout << ", ";
    printVariadic(std::forward<Args>(args)...);
}

struct Number {
    Number()
        : p_num{new int(0)}
    {
    }
    Number(int value)
        : p_num{new int(value)}
    {
        std::cout << "Constructor\n";
    }
    Number(const Number &num)
        : p_num{new int(*num.p_num)}
    {
        std::cout << "Copy constructor\n";
    }
    Number(Number &&num)
        : p_num{new int(*num.p_num)}
    {
        std::cout << "Move constructor\n";
    }

    Number &operator=(const Number &num)
    {
        std::cout << "Copy assign operator\n";
        this->p_num = num.p_num;
        return *this;
    }

    Number &operator=(Number &&num)
    {
        std::cout << "Move assign operator\n";
        this->p_num = std::move(num.p_num);
        return *this;
    }

    ~Number() { delete p_num; }
    friend std::ostream &operator<<(std::ostream &os, const Number &num) { return os << *num.p_num; }

private:
    int *p_num;
};

template <typename N1, typename N2>
decltype(auto) min(N1 n1, N2 n2)
{
    return std::min(n1, n2);
}

template <typename First, typename Second, typename... Rest>
decltype(auto) min(First first, Second second, Rest... rest)
{
    return min(std::min(first, second), rest...);
}

// Other solution

template <typename First, typename... Rest>
decltype(auto) min_better(const First &&first, const Rest &&...rest)
{
    using Common = typename std::common_type<Rest...>::type;
    Common minimum = first;
    ((minimum = std::min(minimum, static_cast<Common>(rest))), ...);
    return minimum;
}

template <typename First, typename... Rest>
decltype(auto) min_better_(const First &first, const Rest &...rest)
{
    using Common = typename std::common_type<Rest...>::type;
    const Common *minimum = std::addressof(first);
    ((minimum = &std::min(*minimum, rest)), ...);
    return *minimum;
}

int main(int argc, char *argv[])
{
    print({1, 2, 3});
    // print({1,2,3.3});  // This cannot compile because the template argument
    // deduction will fail
    printVariadic(1, 2, 3, 3.3, 'a', Number{42});
    printVariadicPerfectForwarding(1, 2, 3, 3.3, 'a', Number{42});

    std::cout << min(10, 20, 0, 23, -1, -10, 1, -100) << std::endl;
    std::cout << min_better(10, 20, 0, 23, -1, -10, 1, -100) << std::endl;
    std::cout << min_better(10, 20, 0, 23, -1, -10, 1, -100, -100.1) << std::endl;
    return 0;
}
