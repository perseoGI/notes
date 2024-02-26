#include <array>
#include <charconv>
#include <iostream>
#include <string_view>
#include <system_error>
 
void show_to_chars(auto... format_args)
{
    std::array<char, 10> str;
 
#if __cpp_lib_to_chars >= 202306L
    // use C++26 operator bool() for error checking
    if (auto res = std::to_chars(str.data(), str.data() + str.size(), format_args...))
        std::cout << std::string_view(str.data(), res.ptr) << '\n';
    else
        std::cout << std::make_error_code(res.ec).message() << '\n';
#else
    if (auto [ptr, ec]
            = std::to_chars(str.data(), str.data() + str.size(), format_args...);
        ec == std::errc())
        std::cout << std::string_view(str.data(), ptr) << '\n';
    else
        std::cout << std::make_error_code(ec).message() << '\n';
#endif
}
 
int main()
{
    show_to_chars(42);
    show_to_chars(+3.14159F);
    show_to_chars(-3.14159, std::chars_format::fixed);
    show_to_chars(-3.14159, std::chars_format::scientific, 3);
    show_to_chars(3.1415926535, std::chars_format::fixed, 10);
}
