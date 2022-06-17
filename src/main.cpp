#include <iostream>
#include "cpp-dirs.hpp"

int main() {
    dirs config = dirs("Maou Corporation", "cppm");
    std::cout << config.get_joint() << std::endl;
    config.home_dir().create();
    std::cout << config.hostname << std::endl;
    std::cout << config.username << std::endl;
    std::cout << dirs::home() << std::endl;
    std::cout << dirs::cache() << std::endl;
    std::cout << dirs::data_dir() << std::endl;
    std::cout << dirs::data_local_dir() << std::endl;
    std::cout << dirs::video() << std::endl;
    std::cout << dirs::documents() << std::endl;
    std::cout << dirs::pictures() << std::endl;
    std::cout << dirs::downloads() << std::endl;
    std::cout << dirs::desktop() << std::endl;
    std::cout << dirs::public_dir() << std::endl;
    std::cout << dirs::audio() << std::endl;
    return 0;
}