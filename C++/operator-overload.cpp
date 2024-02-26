#include <iostream>


class Foo {
public:
    int a{}, b{}, c{};

    // Pre increment
    Foo operator++(){
        ++a, ++b, ++c;
        return *this;
    }

    // Post increment
    Foo operator++(int) {
        Foo tmp = *this;
        ++a, ++b, ++c;
        return tmp;
    }

    // Cast operator
    operator int(){
        return a + b + c;
    }

    friend std::ostream &operator<<(std::ostream &ss, const Foo &f){
        ss << "a: " << f.a << ", b: " << f.b << ", c: " << f.c;
        return ss;
    }

    Foo operator()(int add){
        return Foo{a + add, b + add, c + add};
    }

};

struct Bar{
    std::string s;
    Foo foo;

    // Allow bypassing
    Foo *operator->(){ 
        return &foo;
    }
};


int main (int argc, char *argv[]) {
    
    Foo f {1,2,3};
    Bar b;
    std::cout << f << std::endl;
    std::cout << ++f << std::endl;
    std::cout << f++ << std::endl;
    std::cout << static_cast<int>(f) << std::endl;
    std::cout << f(1) << std::endl;
    std::cout << f.operator()(2) << std::endl;
    std::cout << b->a << std::endl;
    return 0;
}
