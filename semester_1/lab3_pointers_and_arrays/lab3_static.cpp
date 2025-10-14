#include <iostream>
#include<cmath>
#include<random>
void inputnumberwithcheck(int&length) {
    std::cout << "enter the length of the array";
    if (!(std::cin >> length)||length<=0) {
        std::cout<< "no chepuha please.enter whole numbers";
        std::exit(1);
    }
}
void checkiflengthexceeded(int& length,const int&maxlength) {
    if (length > maxlength) {
        std::cout << "exceeded size limit.Please enter a size less than 100";
        std::exit(1);
    }
}
void boundariesinputwithcheck(int& a,int& b,int*arr) {
    std::cout << "enter two whole numbers that will be boundaries of generation" << std::endl;
    if (!(std::cin >> a >> b)) {
        std::cout << "no chepuha please.enter whole numbers";
        std::exit(1);
    }
}
void inputwithcheckchoice(int& forrand,int*arr) {
    std::cout << "for random numebrs type 67,for manual input type anything else" << std::endl;
    if (!(std::cin >> forrand)) {
        std::cout << "no chepuha please.enter normal numbers";
        std::exit(1);
    }
}
void genrandomforarraywithboundaries(int& length, int* arr,int&a,int&b) {
    std::cout << "enter two whole numbers that will be boundaries of generation" << std::endl;
    if (!(std::cin >> a >> b)) {
        std::cout << "no chepuha please.enter whole numbers";
        std::exit(1);
    }
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist(std::min(a, b), std::max(a, b));
    for (int i = 0; i < length; ++i) {
        arr[i] = dist(gen);
    }
}
void printarray(int& length, int* arr) {
    for (int i = 0; i < length; ++i) {
        std::cout << arr[i] << " ";
    }
}
void manualinputingwithcheck(int& length,int*arr) {
    std::cout << "enter the elements of the array" << std::endl;
    for (int i = 0; i < length; ++i) {
        if (!(std::cin >> arr[i])) {
            std::cout << "no chepuha please.enter whole numbers";
            std::exit(1);
        }
    }
}
void findingthebiggestandsmallestnumbers(int& min, int& max,int*arr,int&length) {
    for (int i = 1; i < length; ++i) {
        if (arr[i] < arr[min]) {
            min = i;
        }
        if (arr[i] > arr[max]) {
            max = i;
        }
    }
}
void swap(int& min, int& max,int*arr) {
    arr[min] ^= (arr[max] ^= (arr[min] ^= arr[max]));
}
int thesmalestabsolute(int& absmin, int& length, int* arr) {
    for (int i = 1; i < length; ++i) {
        if (std::abs(arr[i]) < std::abs(arr[absmin])) {
            absmin = i;
        }
    }
    return absmin;
}
void summaryofelements(int& sum, int& length, int* arr, int& absmin) {
    for (int k = absmin + 1; k < length; ++k) {
        sum += arr[k];
    }
}
void negativetosquares(int& length, int* arr) {
    for (int i = 0; i < length; ++i) {
        if (arr[i] < 0) {
            arr[i] *= arr[i];
        }
    }
}
void bubblesorting(int& length, int* arr) {
    int temp;
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
int main()
{
    int length = 0;
    const int maxlength = 100;
    inputnumberwithcheck(length);
    checkiflengthexceeded(length,maxlength);
    int arr[maxlength];
    int forrand = 0;
    inputwithcheckchoice(forrand,arr);
    int a = 0;
    int b = 0;
    if (forrand == 67) {
        genrandomforarraywithboundaries(length, arr, a, b);
        std::cout << "our array:";
        printarray(length, arr);
    }
    else {
        manualinputingwithcheck(length, arr);
    }
    int min = 0;
    int max = 0;
    findingthebiggestandsmallestnumbers(min, max, arr, length);
    swap(min, max, arr);
    std::cout << "sorted array:";
    printarray(length, arr);
    swap(min, max, arr);
    int absmin = 0;
    thesmalestabsolute(absmin, length, arr);
    int sum = 0;
    summaryofelements(sum, length, arr, absmin);
    std::cout << "summary of the unsorted array's numbers is:" << sum << std::endl;
    negativetosquares(length, arr);
    bubblesorting(length, arr);
    std::cout << "our array but with squares instead of negative numbers:";
    printarray(length, arr);
    std::cout << ":)";
    return 0;
}
