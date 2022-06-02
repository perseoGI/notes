#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Base case variadic template recursion
template <typename T> void print(T type) { std::cout << type << std::endl; }

template <typename T1, typename... T> void print(T1 val, T... args) {
    std::cout << val << std::endl;
    print(args...);
}

template <typename T> void non_recursive_impl(const T &t) {
    std::cout << t << '\n';
}

template <typename... Args> void non_recursive_print(const Args &...args) {
    // Coma operator returns 0 to the initializer initializer_list
    // (void) cast let compiler optimize to not create temporal array
    // (initializer_list) Coma operator and initializer_list ensures left to
    // right execution order

    // (void)std::initializer_list<int>{(non_recursive_impl(args), 0)...};

    // Version with no need of implementation
    (void)std::initializer_list<int>{(std::cout << args << '\n', 0)...};
}

template <typename T> std::string to_string_impl(const T &t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template <typename... Args>
std::vector<std::string> to_string(const Args &...args) {
    // return {to_string_impl(args)...};

    // Or
    // std::vector<std::string> vec;
    // std::stringstream ss;
    // (void)std::initializer_list<int>{
    //    (ss.str(""),
    //    ss << args,
    //    vec.push_back(ss.str()),
    //    0) ...
    // };
    // return vec;
    
    std::stringstream ss;
    return {(ss.str(""), ss << args, ss.str())...};
}

int main(int argc, char *argv[]) {
    int x = 120;
    print(12, 2, "value", x, 'c', true);
    non_recursive_print(12, 2, "value", x, 'c', true);
    auto strings = to_string(12, 2, "value", x, 'c', true);
    for (auto &s : strings)
        std::cout << s << ',';
    std::cout << std::endl;
    return 0;
}
