#include <iostream>
#include <cmath>

int main() {
    int a;
    int b;
    int counter = 0;
    std::cout << "enter boundaries a b" << std::endl;
    if (!(std::cin >> a >> b)) {
        std::cout << "wont work";
        std::exit(1);
    }
    if (a < 0) {
        a = 1;
    }
    if (a && b < 0) {
        std::cout << "numbers should be positive";
        std::exit(0);
    }
    for (int i = std::min(a, b); i <= std::max(a, b); i++) {
        
        int powerof2 = pow(2, counter);
        if ((i + 1) % powerof2 == 0) {
            std::cout << i<<" ";
            counter++;
        }
        
    }

}


