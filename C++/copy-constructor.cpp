#include <iostream>
#include <string>


struct S{
   int a;
   std::string b;

   // Default constructor
   S(): a(42), b("Hello World!"){
      std::cout << "S::default-constructor\n";
   }

   // Parametrized constructor
   S(const int a, const std::string &b): a(a), b(b){
      std::cout << "S::parmetrized-constructor\n";
   }
   
   // Copy constructor
   S(const S &s){
      this->a = s.a;
      b = s.b;
      std::cout << "S::copy-constructor\n";
   }

   // Assignment operator
   S& operator=(const S &s){
      a = s.a;
      b = s.b;
      std::cout << "S::assignment-operator\n";
      return *this;
   }

};


int main (int argc, char *argv[])
{
   S a;
   S b = a;
   S c(3, "Hi!");
   c = a;
   return 0;
}
