#include "palindrome.h"

int main() {
    std::string x;
    std::cin >> x;
    if (x.empty()) {
        std::cout << "empty string"<<std::endl;
    }
    else {
        if (palindrome(x) == 1) {
            std::cout << "palindrome string" << std::endl;
        }
        else {
            std::cout << "string not palindrome" << std::endl;
        }
    }
    return 0;
}