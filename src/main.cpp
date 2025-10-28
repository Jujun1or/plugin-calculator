#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Calculator project skeleton initialized." << std::endl;
    std::cout << "Args count: " << argc - 1 << std::endl;

    for (int i = 1; i < argc; ++i) {
        std::cout << "Arg " << i << ": " << argv[i] << std::endl;
    }

    return 0;
}
