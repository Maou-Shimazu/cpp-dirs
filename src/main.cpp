#include <iostream>
#include "cpp-dirs.hpp"

int main() {
    std::cout << dirs::hostname << std::endl;
    std::cout << dirs::username << std::endl;
    return 0;
}