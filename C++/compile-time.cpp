#include <iostream>
#include <array>

template<int N>
struct Factorial{
   static const unsigned long long val = N * Factorial<N - 1>::val;
};

template<>
struct Factorial<0>{
   static const unsigned long long val = 1;
};

template<>
struct Factorial<1>{
   static const unsigned long long val = 1;
};

// Compile time generation of factorial numbers
template<size_t ... N>
const unsigned long long factorial_impl(std::index_sequence<N ...>, const int n){
   std::array<unsigned long long, sizeof...(N)> precalculated = {Factorial<N>::val ...};
   return precalculated[n];
}

const unsigned long long factorial(const int n){
   return factorial_impl(std::make_index_sequence<66>(), n);
}

int main (int argc, char *argv[])
{
   // 0s runtime
   std::cout << Factorial<65>::val << '\n';

   if (argc > 1){
      // 0s runtime
      std::cout << factorial(atoi(argv[1])) << '\n';
   }
   return 0;
}
