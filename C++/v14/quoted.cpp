#include <iomanip>
#include <iostream>

int main(int argc, char *argv[])
{
    auto quoted = std::quoted("SELECT \"*\" FROM \"users\";");
    std::cout << "Quoted statement: " << quoted << std::endl;

    return 0;
}
