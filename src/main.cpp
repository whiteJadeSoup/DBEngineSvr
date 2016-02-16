#include <iostream>
#include "Server.hpp"

using namespace std;

int main()
{
    io_service io;
    Server server (io, 11000);
    io.run();
    return 0;
}
