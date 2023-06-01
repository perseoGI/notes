#include <iostream>
#include <vector>

template <typename T> class Printer {
  T *pData;

public:
  Printer(T *data) : pData{data} {}
  void print() { std::cout << '{' << *pData << "}\n"; }
  T *data() { return pData; }
};

// Class explicit specialization
template<>
class Printer<char*> {
  char *pData;

public:
  Printer(char *data) : pData{data} {}
  void print() { std::cout << '{' << pData << "}\n"; }
  char *data() { return pData; }
};

// Method explicit specialization
template<>
void Printer<std::vector<int>>::print(){
    std::cout << "[ ";
    for(const auto &elem : *pData){
        std::cout << elem << ' ';
    }
    std::cout << "]\n";
}

template<>
void Printer<std::vector<std::vector<int>>>::print(){
    std::cout << "{\n";
    auto vecIdx{0};
    for(const auto &vec : *pData){
        std::cout << "\t{";
        for(auto i{0}; i < vec.size(); ++i){
            std::cout << vec[i];
            if(i < vec.size() - 1) std::cout << ',';
        }
        std::cout << "}" << (vecIdx++ < pData->size() - 1? "," : "") << '\n';
    }
    std::cout << "}\n";
}



int main(int argc, char *argv[]) {
  int num{42};
  Printer p1(&num);
  p1.print();

  char *str{"hello"};
  Printer<char*> p2(str);
  const char *res{p2.data()};
  std::cout << res << std::endl;
  p2.print();

  std::vector<int> vec{1, 2, 3, 4};
  Printer p3(&vec);
  p3.print();

  std::vector<std::vector<int>> vec2{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Printer p4(&vec2);
  p4.print();
}
