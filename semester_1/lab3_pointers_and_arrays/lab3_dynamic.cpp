#include <iostream>
#include<cmath>
#include<random>
int* allocatingmemory(int& length) {
    return new int[length];
}
void genrandomforarraywithboundaries(int& length, int* arr, int& a, int& b) {
    std::cout << "enter two whole numbers that will be boundaries of generation" << std::endl;
    if (!(std::cin >> a >> b)) {
        std::cout << "no chepuha please.enter whole numbers";
        delete[] arr;
        std::exit(1);
    }
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist(std::min(a, b), std::max(a, b));
    for (int i = 0; i < length; ++i) {
        arr[i] = dist(gen);
    }
}
void inputnumberwithcheck(int& length) {
    std::cout << "enter the length of the array"<<std::endl;
    if (!(std::cin >> length) || length <= 0) {
        std::cout << "no chepuha please.enter whole numbers";
        std::exit(1);
    }
}
void inputwithcheckchoice(int& forrand, int* arr) {
    std::cout << "for random numebrs type 67,for manual input type anything else" << std::endl;
    if (!(std::cin >> forrand)) {
        std::cout << "no chepuha please.enter normal numbers";
        delete[] arr;
        std::exit(1);
    }
}
void manualinputingwithcheck(int& length, int* arr) {
    std::cout << "enter the elements of the array" << std::endl;
    for (int i = 0; i < length; ++i) {
        if (!(std::cin >> arr[i])) {
            std::cout << "no chepuha please.enter whole numbers";
            delete[] arr;
            std::exit(1);
        }
    }
}
void multyplying(int& length, int* arr,int&mod) {
    for (int i = 0; i < length; ++i) {
        if (i % 2 == 0) {
            mod *= arr[i];
        }
    }
}
void findingthebiggestandsmallestpositive(int& length, int* arr, int& maxpos, int& minpos) {
    for (int i = 0; i < length; ++i) {
        if (arr[i] > 0) {
            minpos = i;
            maxpos = i;
            break;
        }
    }
    if (minpos != -1) {
        for (int i = minpos + 1; i < length; ++i) {
            if (arr[i] > 0) {
                if (arr[i] < arr[minpos]) {
                    minpos = i;
                }
                if (arr[i] > arr[maxpos]) {
                    maxpos = i;
                }
            }
        }
    }
}
void summarybetween(int* arr, int& maxpos, int& minpos,int&sumpos) {
    if (maxpos > minpos) {
        for (int i = minpos + 1; i < maxpos; ++i) {
            sumpos += arr[i];
        }
    }
    if (maxpos < minpos) {
        for (int i = maxpos + 1; i < minpos; ++i) {
            sumpos += arr[i];
        }
    }
}
void modifiedbubblesort(int& length, int* arr) {
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
void printarray(int& length, int* arr) {
    for (int i = 0; i < length; ++i) {
        std::cout << arr[i] << " ";
    }
}
int main() {
    int length=0;
    inputnumberwithcheck(length);
    int* arr = allocatingmemory(length);
    int forrand = 0;
    inputwithcheckchoice(forrand, arr);
    if (forrand == 67) {
        int a = 0;
        int b = 0;
        genrandomforarraywithboundaries(length, arr, a, b);
        std::cout << "our array:"<<" ";
        printarray(length, arr);
    }
    else {
        manualinputingwithcheck(length, arr);
    }
    int mod=1;
    multyplying(length, arr, mod);
    std::cout << "product of numbers with the even index is:"<<mod<<std::endl;
    int minpos = -1;
    int maxpos = -1;
    findingthebiggestandsmallestpositive(length, arr, maxpos, minpos);
    int sumpos=0;
    summarybetween(arr, maxpos, minpos, sumpos);
        std::cout << "summary of numbers between the smallest and the biggest positive numbers is:" << sumpos << std::endl;
        modifiedbubblesort(length, arr);
        std::cout<<"sorted array:";
        printarray(length, arr);
        delete[] arr;
        return 0;
    
}
