#include <iostream>
#include <cmath>

int main() {
    int a;
    int b;
    int counter = 0;
    int n = std::min(a, b);
    std::cout << "enter boundaries a b" << std::endl;
    if (!(std::cin >> a >> b)) {
        std::cout << "wont work";
        std::exit(1);
    }
    if (n < 0) {
         n = 1;
    }
    if (n && std::max(a,b)< 0) {
        std::cout << "numbers should be positive";
        std::exit(0);
    }
    for (int i = n; i <= std::max(a, b); i++) {

        int powerof2 = pow(2, counter);
        if ((i + 1) % powerof2 == 0) {
            counter++;
        }
            if (powerof2>std::min(a,b) && (i + 1) % powerof2 == 0) {
                std::cout << i << " ";
            }
        
    }

}


