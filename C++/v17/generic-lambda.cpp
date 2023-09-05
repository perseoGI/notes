#include <algorithm>
#include <iostream>
#include <variant>
#include <vector>

int main (int argc, char *argv[]) {
    
    std::vector<std::variant<int,double>> vec {1, 256.3, 34, 6433.3};
    int sumInt{};
    double sumDouble{};

    std::common_type_t<decltype(sumInt),decltype(sumDouble)> totalSum{};
    auto genericLambda = [&sumInt, &sumDouble, &totalSum](const auto num){
        totalSum += num;
        if constexpr(std::is_same_v<double, std::decay_t<decltype(num)>>){ 
            sumDouble += num;
        }
        else sumInt += num;
    };
    std::for_each(vec.begin(), vec.end(), [&genericLambda](const auto num){std::visit(genericLambda, num);});

    std::cout << sumInt << " " << sumDouble << " " << totalSum << std::endl;
}
