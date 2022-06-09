#include<iostream>

constexpr int greater(int x, int y){
   return (x > y ? x : y);
}


consteval int lesser(int x, int y){
   return (x < y ? x : y);
}


int main (int argc, char *argv[])
{
   constexpr int a {10}; 
   constexpr int b {20}; 

   int c {2};
   constexpr int res1 = greater(a, b);   // compile time
   constexpr int res2 = greater(1, 3);   // compile time
   int res3 = greater(c, 3);   // execution time: constexpr function allow runtime execution!

   constexpr int res4 = lesser(a, b);
   // constexpr int res5 = lesser(c, b); // compile time error: consteval force compile time execution

   std::cout << res1 << '\n';
   std::cout << res2 << '\n';
   std::cout << res3 << '\n';
   std::cout << res4 << '\n';
   std::cout << greater(32,3) << '\n';   // undetermined: cout is a runtime expression, thus, compiler could or could not optime greater call

   return 0;
}
