#include <iostream>
#include<random>
void genrandomforarrayonly01(int row, int** matrix, int col,std::mt19937& gen) {
    std::uniform_int_distribution<int> dist(0, 1);
    for (int i = 0; i < row; ++i) {
        matrix[i] = new int[col];
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = dist(gen);
        }
    }
}
void matrixprint(int row, int** matrix, int col) {
    std::cout << "Our matrix:" << std::endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            std::cout << matrix[i][j] << "  ";
        std::cout << std::endl;
    }
}
void manualinput(int** matrix, int row, int col) {
    for (int i = 0; i < row; ++i) {
        matrix[i] = new int[col];
    }
    std::cout << "Only 0 or 1." << std::endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << "Input the element with the index[" << i << "][" << j << "]=";
            if (!(std::cin >> matrix[i][j]) || (matrix[i][j] < 0) || (matrix[i][j] > 1)) {
                std::cout << "Please read the requirements.";
                for (int i = 0; i < row; ++i) {
                    delete[]matrix[i];
                }
                delete[]matrix;
                std::exit(1);
            }
        }
    }
}
void inputrowscolumns(int& row, int& col) {
    std::cout << "Enter the number of rows,then the number of columns.Enter whole numbers,no negative or zeros,or letters." << std::endl;
    if (!(std::cin >> row >> col) || row == 0 || col == 0 || (row < 0) || col < 0) {
        std::cout << "Please read the requirements.";
        std::exit(1);
    }
}
void choosingpath(int& choose) {
    std::cout << "Enter 1 for manual input,2-for random." << std::endl;
    if (!(std::cin >> choose) || (choose < 1) || (choose > 2)) {
        std::cout << "Only 1 or 2";
        std::exit(1);
    }
}
void findingTheMost1(int row, int col, int** matrix) {
    int max1 = 0;
    bool isThere1 = false;
    int comparison1 = 0;
    int comparison2 = 0;
    for (int k = 0; k < row; ++k) {
        for (int m = 0; m < col; ++m) {
            int count1 = 0;
            for (int m = 0; m < col; ++m) {
                if (matrix[k][m] == 1) {
                    count1++;
                    isThere1=true;
                }
            }
            if (comparison1 < count1) {
                comparison1 = count1;
            }
        }
        if (comparison1 > comparison2) {
            max1 = k;
            comparison2 = comparison1;
        }
    }
    if (isThere1) {
        std::cout << "Row with the most 1 is:" << (max1 + 1) << std::endl;
    }
    else {
        std::cerr << "No ones here" << std::endl;
    }
}
void findingsimmilarrows(int row, int col, int** matrix) {
    bool numOfCouts = false;
    for (int k = 0; k < row; ++k) {
        for (int j = k + 1; j < row; j++) {
            bool isEqual = false;
            int initCount = 0;
            for (int ifcounter = 0; ifcounter < col; ++ifcounter) {
                bool CurrIsequal = true;
                for (int m = 0; m < col; ++m) {
                    if (matrix[k][m] != matrix[j][m]) {
                        CurrIsequal = false;
                        break;
                    }
                }
                if (CurrIsequal == true) {
                    isEqual = true;
                    break;
                }
                if (ifcounter < col - 1) {
                    int last = matrix[j][col - 1];
                    for (int a = col - 1; a > 0; a--) {
                        matrix[j][a] = matrix[j][a - 1];
                    }
                    matrix[j][0] = last;
                    initCount++;
                }
            }
            for (int b = 0; b < initCount; ++b) {
                int first = matrix[j][0];
                for (int a = 0; a < col - 1; a++) {
                    matrix[j][a] = matrix[j][a + 1];
                }
                matrix[j][col - 1] = first;
            }
            if (isEqual == true) {
                std::cout << "Row " << (k + 1) << " is equal to row " << (j + 1) << " through " << initCount << " shifts to the left " << std::endl;
                numOfCouts = true;
            }
        }
    }
    if (numOfCouts == false) {
        std::cerr << "No equal rows here" << std::endl;
    }
}
void deletingmatrix(int** matrix, int row) {
    for (int i = 0; i < row; ++i) {
        delete[]matrix[i];
    }
    delete[]matrix;
}
int main() {
    int row = 0;
    int col = 0;
    inputrowscolumns(row, col);
    int choose = 0;
    choosingpath(choose);
    int** matrix = new int* [row];
    if (choose == 1) {
        manualinput(matrix, row, col);
    }
    else {
        std::mt19937 gen;
        genrandomforarrayonly01(row, matrix, col,gen);
    }
    matrixprint(row, matrix, col);
    findingsimmilarrows(row, col, matrix);
    findingTheMost1(row, col, matrix);
    matrixprint(row, matrix, col);
    deletingmatrix(matrix, row);
    std::cout << ":)";
    return 0;
}

