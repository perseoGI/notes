#include <iostream>

class Foo
{
public:
    int a, b, c{42};

    int getA()
    {
        std::cout << "Normal member\n";
        return a;
    }
    int getB() &
    {
        std::cout << "Accessing from lvalue ref\n";
        return b;
    }

    int getB() &&
    {
        std::cout << "Accessing from rvalue ref\n";
        return b;
    }

    int getC() &
    {
        std::cout << "Accessing C only from lvalue ref\n";
        return c;
    }
};

Foo getTmp()
{
    return Foo{2, 3};
}

int main(int argc, char *argv[])
{
    Foo f{1, 2};
    std::cout << f.getA() << std::endl;
    std::cout << f.getB() << std::endl;
    std::cout << getTmp().getB() << std::endl;
    std::cout << f.getC() << std::endl;
    // std::cout << getTmp().getC() << std::endl; // This cannot work! force only be accesible from lvalue
    return 0;
}
