#include <functional>
#include <iostream>
#include <string>
#include <algorithm>

int main (int argc, char *argv[]) {
    
    std::string str{"hello world folks!"};
    std::string pattern{"lo "};

    auto res = std::search(str.begin(), str.end(), pattern.begin(), pattern.end());

    // More efficient search algorithm
    auto res1 = std::search(str.begin(), str.end(), std::boyer_moore_searcher(pattern.begin(), pattern.end()));

    std::cout << std::distance(str.begin(), res) << " " << res1.base() << std::endl;

    return 0;
}
