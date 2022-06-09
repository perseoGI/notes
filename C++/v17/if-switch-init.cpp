#include <iostream>
#include <vector>
#include <algorithm>

int main (int argc, char *argv[])
{
   std::vector<int> vec {1, 3, 4, 5};
   
   // If initialization statement
   if(const auto it = std::find(vec.begin(), vec.end(), 3);
      it != vec.end()){
      *it = 42;
   }


   // Equivalent
   {
      const auto it = std::find(vec.begin(), vec.end(), 3);
      if(it != vec.end()){
         *it = 42;
      }
   }


   // Switch initialization statement
   switch(const auto it = std::find(vec.rbegin(), vec.rend(), 1);
         *it){
      case 1:
         std::cout << "Yass\n";
         break;
      default:
         std::cout << "Whaaat?\n";
   }

   for(const auto &e : vec)
      std::cout << e << ' ';
   std::cout << '\n';

   return 0;
}
