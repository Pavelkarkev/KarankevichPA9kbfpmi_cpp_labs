#include <iostream>
#include<cmath>
#include<random>
int* allocatingmemory(int length) {
    return new int[length];
}
void genRandomForArrayWithBoundaries(int length, int* arr, int a, int b, std::mt19937& gen) {
    std::cout << "enter two whole numbers that will be boundaries of generation" << std::endl;
    if (!(std::cin >> a >> b)) {
        std::cout << "no chepuha please.enter whole numbers";
        delete[] arr;
        std::exit(1);
    }
    std::uniform_int_distribution<int> dist(std::min(a, b), std::max(a, b));
    for (int i = 0; i < length; ++i) {
        arr[i] = dist(gen);
    }
}
void inputNumberWithCheck(int& length) {
    std::cout << "enter the length of the array" << std::endl;
    if (!(std::cin >> length) || length <= 0) {
        std::cout << "no chepuha please.enter whole numbers";
        std::exit(1);
    }
}
void inputWithCheckChoice(int& forrand, int* arr) {
    std::cout << "for random numebrs type 67,for manual input type anything else" << std::endl;
    if (!(std::cin >> forrand)) {
        std::cout << "no chepuha please.enter normal numbers";
        delete[] arr;
        std::exit(1);
    }
}
void manualinputingwithcheck(int length, int* arr) {
    std::cout << "enter the elements of the array" << std::endl;
    for (int i = 0; i < length; ++i) {
        if (!(std::cin >> arr[i])) {
            std::cout << "no chepuha please.enter whole numbers";
            delete[] arr;
            std::exit(1);
        }
    }
}
void multyplying(int length, int* arr, int& mod) {
    if (length == 1) {
        std::cerr << "Coudnt calculate the product" << std::endl;
        return;
    }
    for (int i = 0; i < length; ++i) {
        if (i % 2 != 0) {
            mod *= arr[i];
        }
    }
    std::cout << "product of numbers with the even numbers is:" << mod << std::endl;
}
void findIndexOfPositives(int length, int* arr, int& maxpos, int& minpos) {
        for (int i = 0; i < length; ++i) {
            if ((arr[i] > 0)) {
                minpos = i;
                break;
            }
        }
        for (int i = length - 1; i > +0; --i) {
            if ((arr[i] > 0)) {
                maxpos = i;
                break;
            }
        }
}
void summaryBetween(int* arr, int maxpos, int minpos, int& sumpos) { 
    if ((minpos == -1) && (maxpos == -1)) {
        std::cerr << "No positives" << std::endl;
        return;
    }
    if (minpos == maxpos) {
        std::cerr << "Only 1 positive integer" << std::endl;
        return;
    }
   
    for (int i = minpos + 1; i < maxpos; ++i) {
        sumpos += arr[i];
    }
    std::cout << "Summary of numbers between the first and the last positive numbers is:" << sumpos << std::endl;
}
void modifiedBubbleSort(int length, int* arr) {
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - i - 1; ++j) {
            if (arr[j] >= 0 && arr[j + 1] < 0) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void printArray(int length, int* arr) {
    for (int i = 0; i < length; ++i) {
        std::cout << arr[i] << " ";
    }
}
int main() {
        int length = 0;
        inputNumberWithCheck(length);
        int* arr = allocatingmemory(length);
        int forrand = 0;
        inputWithCheckChoice(forrand, arr);
        if (forrand == 67) {
            int a = 0;
            int b = 0;
            std::mt19937 gen;
            genRandomForArrayWithBoundaries(length, arr, a, b, gen);
            std::cout << "our array:" << " ";
            printArray(length, arr);
        }
        else {
            manualinputingwithcheck(length, arr);
        }
        int mod = 1;
        multyplying(length, arr, mod);
        int minpos = -1;
        int maxpos = -1;
        findIndexOfPositives(length, arr, maxpos, minpos);
        int sumpos = 0;
        summaryBetween(arr, maxpos, minpos, sumpos);
        modifiedBubbleSort(length, arr);
        std::cout << "sorted array:";
        printArray(length, arr);
        delete[] arr;
        return 0;
}
