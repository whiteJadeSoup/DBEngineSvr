#include <iostream>
#include "Server.hpp"

using namespace std;

int main()
{
    Server server ( 11000, 12000);
    server.run();

    return 0;
}
