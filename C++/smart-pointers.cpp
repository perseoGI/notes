#include<iostream>
#include<memory>
#include<array>

void memory_leak(){
   auto *ptr = new std::array<int, 1024>;
}

void unique_ptr_example(){
   std::unique_ptr<int> ptr(new int(42));
   std::unique_ptr<std::array<int, 1024>> arrayPtr(new std::array<int, 1024>);
   // Pointer should be freed
}

void shared_ptr_example(){

}


int main (int argc, char *argv[])
{
   while(true){
      // memory_leak();
      unique_ptr_example();
   }

   return 0;
}
