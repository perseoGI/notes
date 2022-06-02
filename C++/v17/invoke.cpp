#include <iostream>
#include <functional>
#include <string>

int foo (const int a){
   return a * 2;
}

struct S {
   
   std::string str {"hello world"};
   int bar(const std::string &s, const int i){
      return i + s.size();
   }
};

int main (int argc, char *argv[])
{
   
   std::cout << std::invoke(&foo, 3) << '\n';
   S s;
   
   // Call method
   std::cout << std::invoke(&S::bar, s, "hi", 2) << '\n';

   // Access struct member
   std::cout << std::invoke(&S::str, s) << '\n';


   // Old way: function pointers 
   
   int (S::*fun)(const std::string&, const int) = &S::bar;
   std::cout << (s.*fun)("old", 1) << '\n';

   auto fun_easy = &S::bar;
   std::cout << (s.*fun_easy)("not that old", 2) << '\n';

   return 0;
}   
