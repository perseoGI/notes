#include <ctime>
#include <iostream>

class A{
   public:
   virtual void foo(){
      std::cout << "A::foo()\n";
   }
   void bar(){
      std::cout << "A::bar()\n";
   }

   virtual void derive(){
      std::cout << "A::derive()\n";
   }
};

class B: public A{
   public:
   virtual void foo(){
      std::cout << "B::foo()\n";
   }

   // void bar() override { // override force A::bar() to be virtual 
   void bar() {
      std::cout << "B::bar()\n";
   }

   void derive(){
      std::cout << "B::derive()\n";
   }
};

class C: public B{
   public:
   virtual void foo() override { // optional override keyword (allows programmer to quickly see foo is virtual on base class 
      std::cout << "C::foo()\n";
   }

   void bar(){
      std::cout << "C::bar()\n";
   }
   
   void derive(){
      std::cout << "C::derive()\n";
   }
};


int main (int argc, char *argv[])
{
   A *a = new A;
   A *b = new B;
   A *c = new C;
   
   a->foo(); // A::foo()
   b->foo(); // B::foo()
   c->foo(); // C::foo()

   a->bar(); // A::bar()
   b->bar(); // A::bar()
   c->bar(); // A::bar()

   a->derive(); // A::derive()
   b->derive(); // B::derive()
   c->derive(); // C::derive() --> deberia ser B::derive()

   return 0;
}
