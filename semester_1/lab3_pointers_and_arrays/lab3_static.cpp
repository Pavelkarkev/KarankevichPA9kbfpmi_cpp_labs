#include <iostream>
#include<cmath>
#include<random>
void inputNumberWithCheck(int& length) {
    std::cout << "enter the length of the array" << std::endl;
    if (!(std::cin >> length) || length <= 0) {
        std::cout << "no chepuha please.enter whole numbers";
        std::exit(1);
    }
}
void checkIfLengthExceeded(int length, const int maxlength) {
    if (length > maxlength) {
        std::cout << "exceeded size limit.Please enter a size less than 100";
        std::exit(1);
    }
}
void inputWithCheckChoice(int& forrand, double* arr) {
    std::cout << "for random numebrs type 67,for manual input type anything else" << std::endl;
    if (!(std::cin >> forrand)) {
        std::cout << "no chepuha please.enter normal numbers";
        std::exit(1);
    }
}
void genRandomForArrayWithBoundaries(int length, double *arr, double& a, double& b,std::mt19937& gen) {
    std::cout << "enter two whole numbers that will be boundaries of generation" << std::endl;
    if (!(std::cin >> a >> b)) {
        std::cout << "no chepuha please.enter whole numbers";
        std::exit(1);
    }
    std::uniform_real_distribution<double> dist(std::min(a, b), std::max(a, b));
    for (int i = 0; i < length; ++i) {
        arr[i] = dist(gen);
    }
}
void printarray(int length, double* arr) {
    for (int i = 0; i < length; ++i) {
        std::cout << arr[i] << " ";
    }
}
void manualInputingWithCheck(int length, double* arr) {
    std::cout << "enter the elements of the array" << std::endl;
    for (int i = 0; i < length; ++i) {
        if (!(std::cin >> arr[i])) {
            std::cout << "no chepuha please.enter whole numbers";
            std::exit(1);
        }
    }
}
void findingTheBiggestAndSmallestNumbers(int& min, int& max, double* arr, int length) {
    if (length == 1) {
        std::cerr << "There is only 1 element of the array" << std::endl;
        return;
    }
    for (int i = 1; i < length; ++i) {
        if (arr[i] < arr[min]) {
            min = i;
        }
        if (arr[i] > arr[max]) {
            max = i;
        }
    }
}
void theSmallestAbsolute(int& absmin, int length, double* arr) {
    for (int i = 1; i < length; ++i) {
        if (std::abs(arr[i]) < std::abs(arr[absmin])) {
            absmin = i;
        }
    }
}
void summaryOfElements(double& sum, int length, double* arr, int absmin) {
    if (absmin == length - 1) {
        std::cerr << "No elements after the smallest absolute of number" << std::endl;
        return;
    }
    for (int k = absmin + 1; k < length; ++k) {
        sum += arr[k];
    }
    std::cout << "summary of numbers after the smallest absolute of number is:" << sum << std::endl;
}
void negativeToSquares(int length, double* arr) {
    for (int i = 0; i < length; ++i) {
        if (arr[i] < 0) {
            arr[i] *= arr[i];
        }
    }
}
void bubblesorting(int length, double* arr) {
    double temp;
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void swap(int& min, int& max,double* arr) {
    double temp = arr[max];
    arr[max] = arr[min];
    arr[min] = temp;
}
int main()
{
    int length = 0;
    const int maxlength = 100;
    inputNumberWithCheck(length);
    checkIfLengthExceeded(length, maxlength);
    double arr[maxlength];
    int forrand = 0;
    inputWithCheckChoice(forrand, arr);
    double a = 0;
    double b = 0;
    if (forrand == 67) {
        std::mt19937 gen;
        genRandomForArrayWithBoundaries(length, arr, a, b,gen);
        std::cout << "our array:";
        printarray(length, arr);
    }
    else {
        manualInputingWithCheck(length, arr);
    }
    int min = 0;
    int max = 0;
    findingTheBiggestAndSmallestNumbers(min, max, arr, length);
    swap(min, max,arr);
    std::cout << "sorted array:";
    printarray(length, arr);
    swap(min, max,arr);
    int absmin = 0;
    theSmallestAbsolute(absmin, length, arr);
    double sum = 0;
    summaryOfElements(sum, length, arr, absmin);
    negativeToSquares(length, arr);
    bubblesorting(length, arr);
    std::cout << "our array but with squares instead of negative numbers:";
    printarray(length, arr);
    std::cout << ":)";
    return 0;
}
