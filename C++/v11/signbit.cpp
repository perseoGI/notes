#include <cmath>
#include <ios>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << std::boolalpha << -0 << std::endl;
    std::cout << -0.0 << std::endl;  // negative 0!!!
    std::cout << 1 / -0.0 << " " << 1 / 0.0 << std::endl;
    std::cout << std::signbit(-0) << std::endl;
    std::cout << std::signbit(-0.0) << std::endl;
    std::cout << std::copysign(-1 / 0.0, 1) << std::endl;
    std::cout << std::copysign(42, -1) << std::endl;
    return 0;
}
