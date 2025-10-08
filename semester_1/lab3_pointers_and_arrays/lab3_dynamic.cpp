#include <iostream>
#include<cmath>
#include<random>

int main() {
    int n;
    std::cout << "enter the length of the array" << std::endl;
    if (!(std::cin >> n) || (n < 0)) {
        std::cout << "please enter natural numbers";
        std::exit(1);

    }
    int* p = new int[n];
    int forrand = 0;
    std::cout << "for random numebrs type 67" << std::endl;
    std::cin >> forrand;
    if (forrand == 67) {
        std::cout << "SIX SEVEEEEN" << std::endl;
        int a = 0;
        int b = 0;
        std::cout << "enter two whole numbers that will be boundaries of generation" << std::endl;
        if (!(std::cin >> a >> b)) {
            std::cout << "no chepuha please.Enter whole numbers";
            std::exit(1);
            delete[] p;
        }
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist(std::min(a, b), std::max(a, b));
        std::cout << "our array:";
        for (int i = 0; i < n; ++i) {
            p[i] = dist(gen);
            std::cout << p[i] << " ";
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
    int mod = 1;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            mod *= p[i];
        }
    }
    std::cout << "product of numbers with the even index is:" << mod << std::endl;
    int minpos = -1;
    int maxpos = -1;
    for (int i = 0; i < n; ++i) {
        if (p[i] > 0) {
            minpos = i;
            maxpos = i;
            break;
        }
    }


    if (minpos != -1) {
        for (int i = minpos + 1; i < n; ++i) {
            if (p[i] > 0) {
                if (p[i] < p[minpos]) {
                    minpos = i;
                }
                if (p[i] > p[maxpos]) {
                    maxpos = i;
                }
            }
        }
    }
    int sumpos = 0;
    if (maxpos > minpos) {
        for (int i = minpos + 1; i < maxpos; ++i) {
            sumpos += p[i];
        }
    }
    if (maxpos < minpos) {
        for (int i = maxpos + 1; i < minpos; ++i) {
            sumpos += p[i];
        }
    }
    std::cout << "summary of numbers between the smallest and the biggest positive numbers is:" << sumpos << std::endl;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (p[j] >= 0 && p[j + 1] < 0) {
                int temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << p[i] << " ";
    }

    delete[] p;
    return 0;

}
