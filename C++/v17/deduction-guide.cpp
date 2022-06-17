#include <iostream>
#include <typeinfo>

template<typename T, typename U>
struct Collection{
    T first{};
    U second{};
};


// Deduction guide
// Collection objects initialized with arguments of type T and U should be
// deduce to Collection<T,U>
template<typename T, typename U>
Collection(T,U) -> Collection<T,U>;

int main (int argc, char *argv[])
{
    Collection<int,double> c1 {1, 2.3};
    Collection c2 {3, 4};  // type deduction
    std::cout << typeid(c2).name() << '\n';
    return 0;
}
