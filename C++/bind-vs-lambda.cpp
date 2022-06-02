#include <iostream>
#include <functional>


template<typename T>
void concat(const T &t1, const T &t2){
   std::cout << t1 << ' ' << t2 << '\n';
}

int main (int argc, char *argv[])
{
   const auto fun1 = std::bind(&concat<int>, 3, std::placeholders::_1);
   fun1(1);

   int val = 0;
   // Can pass references, and can reorder parameters!
   const auto fun2 = std::bind(&concat<int>, std::placeholders::_1, std::ref(val)) ;
   fun2(99);
   val = 42;
   // will swallow rest of arguments
   fun2(99, 1, 2, 3, 4);

   std::function<void (int)> preCpp11(fun2);
   preCpp11(23);


   // Lambda version
   // Much better, allows auto detect templates
   // 20% more efficient on compile time and run time
   const auto lambda1 = [](const auto &arg1, const auto &arg2){
      concat(arg1, arg2);
   };
   lambda1(2, 7);

   float f = 23.32;
   const auto lambda2 = [&](const auto &arg1){
      concat(f, arg1);
   };
   lambda2(7.23f);

   return 0;
}
