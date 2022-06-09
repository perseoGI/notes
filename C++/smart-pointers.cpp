#include<iostream>
#include<memory>
#include<array>
#include<vector>

void memory_leak(){
   auto *ptr = new std::array<int, 1024>;
}

void unique_ptr_example(){
   std::unique_ptr<int> ptr(new int(42));
   std::unique_ptr<std::array<int, 1024>> arrayPtr(new std::array<int, 1024>);
   // Pointer should be freed
}

void shared_ptr_example(){
   std::shared_ptr<std::vector<int>> vectorPtr(new std::vector<int>);
   // TODO improve example
}


int main (int argc, char *argv[])
{
   while(true){
      // memory_leak();
      unique_ptr_example();
   }
   // 
   switch(x){
      case 1:
         std::cout << "1\n";
         [[fallthrough]];
      case 2: 
         std::cout << "2\n";
         break;
   }


   return 0;
}
