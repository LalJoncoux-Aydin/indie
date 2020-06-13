#include "indie.hpp"

int main(int ac, char **argv)
{  
    try {
        indie();
    } catch (std::string error) {
        std::cerr << error << std::endl;
    }
    if (ac > 2 && strcmp(argv[1], "-h") == 0) {
        std::cout << HELP << std::endl;
        return 0;
    }
    return 0;
}
