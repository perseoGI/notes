#include <iostream>
#include <numeric>
#include <utility>
#include <vector>


struct Bar {
    void doThings(){};
};

// void receiveBar(Bar &bar){
//     bar.doThings();
// }

void receiveBar(const Bar &bar){
    std::cout << "const\n";
}

template <typename Invocable>
void foo(const Invocable &invocable){
    Bar bar;
    bar.doThings();
    invocable(std::as_const(bar));  // ensure const method is called
}

int main(int argc, char *argv[])
{
    std::vector<int> vec{1000};
    std::iota(vec.begin(), vec.end(), 1);

    // Even though the elem variable is const& the container is not const so the for loop would use non-const
    // begin()/end() and cause a potentially expensive detach (container copy).
    for (const auto &elem : std::as_const(vec)) {
    }

    foo(receiveBar);
    
    return 0;
}
