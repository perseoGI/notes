#include <iostream>
#include <future>
#include <random>
#include <algorithm>
#include <set>


std::set<int> generate_random_numbers(const size_t num){
   std::set<int> numbers;
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<int> dis(0, num - 1);
   std::generate_n(std::inserter(numbers, numbers.end()), num, [&](){return dis(gen);});
   std::cout << numbers.size() << '\n';
   return numbers;
}

int main (int argc, char *argv[])
{
   // Easy and secure parallelization 
   auto nums1 = std::async(std::launch::async, generate_random_numbers, 3000000);
   auto nums2 = std::async(std::launch::async, generate_random_numbers, 3000000);

   // Deferred will only execute function if get is called
   auto nums3 = std::async(std::launch::deferred, generate_random_numbers, 3000000);
   auto nums4 = std::async(std::launch::deferred, generate_random_numbers, 3000000);

   nums1.get();
   nums2.get();

   // Deferred calculation
   nums4.get();
   
   return 0;
}
