#include <iostream>
#include <type_traits>

template <typename... T> 
auto add(const T &...t) {
    // Old way
    typename std::common_type<T...>::type acc{};
    std::initializer_list{(acc += t, 0)...};
    return acc;
}

template <typename... T>
auto mul(const T &...t) {
    // Fold expression 
    return (t + ...);
}

int main(int argc, char *argv[]) {

    std::cout << add(23, 3.3, 19.3f) << '\n';
    std::cout << mul(2, 3.5, true) << '\n';
    return 0;
}
