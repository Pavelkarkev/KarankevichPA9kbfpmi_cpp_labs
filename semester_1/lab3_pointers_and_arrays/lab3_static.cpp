#include <iostream>
#include<cmath>
#include<random>

int main()
{
    int n;
    const int maxlength = 100;

    std::cout << "enter the length of the array" << std::endl;
    if (!(std::cin >> n) || (n < 0)) {
        std::cout << "please enter natural numbers";
        std::exit(1);
    }

    if (n > maxlength) {
        std::cout << "exceeded size limit.Please enter a size less than 100";
        std::exit(1);
    }

    int* p = new int[n];
    int forrand = 0;
    std::cout << "for random numebrs type 67" << std::endl;
    std::cin >> forrand;
        int a = 0;
        int b = 0;
        std::cout << "enter two whole numbers that will be boundaries of generation" << std::endl;
        if (!(std::cin >> a >> b)) {
            std::cout << "no chepuha please.Enter whole numbers";
            delete[] p;
            std::exit(1);
        }
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist(std::min(a, b), std::max(a, b));
        for (int i = 0; i < n; ++i) {
            p[i] = dist(gen);
        }
    }
    else {
        std::cout << "enter the elements of the array" << std::endl;
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> p[i])) {
                std::cout << "no chepuha please.Enter whole numbers";
                delete[] p;
                std::exit(1);
            }

        }
    }
    std::cout << "our array :";
    for (int i = 0; i < n;i++) {
        std::cout << p[i]<<" ";
    }
    int min = 0;
    int max = 0;
    for (int i = 1; i < n; ++i) {

        if (p[i] < p[min]) {
            min = i;
        }
        if (p[i] > p[max]) {
            max = i;
        }
    }
    p[min] ^= (p[max] ^= (p[min] ^= p[max]));
    std::cout << "swapped array :";
    for (int i = 0; i < n; ++i) {
        std::cout << p[i] << " ";
    }
    p[min] ^= (p[max] ^= (p[min] ^= p[max]));
    int absmin = 0;
    for (int i = 1; i < n; ++i) {
        if (std::abs(p[i]) < std::abs(p[absmin])) {
            absmin = i;
        }
    }
    int sum = 0;
    for (int k = absmin + 1; k < n; ++k) {
        sum += p[k];
    }
    std::cout << "summary of the numbers is:" << sum << std::endl;
    for (int i = 0; i < n; ++i) {
        if (p[i] < 0) {
            p[i] *= p[i];
        }
    }
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j] > p[j + 1]) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    std::cout << "our array but with squares instead of negative numbers:";
    for (int i = 0; i < n; i++) {
        std::cout << p[i] << " ";
    }
    delete[] p;
    std::cout << ":)";
    return 0;
}

