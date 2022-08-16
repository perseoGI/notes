#include <iostream>

struct Foo{
   int a;
   char b;
};

struct Bar: Foo{
   float c;
   double d;
};


int main (int argc, char *argv[])
{
   Bar b {{1, 'a'}, 32.2, 12.32};
   return 0;
}
