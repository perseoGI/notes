#include <iostream>
#include <limits>
#include <type_traits>

template <typename T> constexpr bool is_integer() {
    if constexpr (std::is_integral_v<T> && !std::is_same_v<bool, T>) {
        if (std::numeric_limits<T>::max() > 255) {
            return true;
        }
    }
    return false;
}

// Allow evaluate expressions at compile time
template <typename T> auto get_type_info(const T &t) {

    auto is_integer_lambda = [&]() constexpr->bool {
        if constexpr (std::is_integral_v<T> && !std::is_same_v<bool, T>) {
            if (std::numeric_limits<T>::max() > 255) {
                return true;
            }
        }
        return false;
    };

    // if constexpr(is_integer<T>()){
    if constexpr (is_integer_lambda()) {
        return t * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return t + 0.00001;
    } else {
        return t;
    }
}

int main(int argc, char *argv[]) {
    std::cout << get_type_info(32) << '\n';
    std::cout << get_type_info(1.3) << '\n';
    std::cout << get_type_info(char(3)) << '\n';
}
