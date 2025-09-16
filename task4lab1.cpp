#include <iostream>
#include<cmath>

int main() {
	setlocale(LC_ALL, "1251");
	int a = 0;
	int modifeven = 1;
	int modifodd = 1;
	std::cout << "Введите число" << std::endl;

	if (!(std::cin >> a)) {
		std::cout << "wont work";
		std::exit(1);
	}
	if (a < 0) {
		std::cout << "number less than zero";
		std::exit(1);
	}
	if (a % 2 == 0) {
		for (int i = 1; i <= a; i++) {
			if (i % 2 == 0) {
				modifeven *= i;
			}
		}
		std::cout << "Двойной факториал равен:" << modifeven;
	}
	if (a % 2 != 0) {
		for (int i = 1; i <= a; i++) {
			if (i % 2 != 0) {
				modifodd *= i;
			}
		}
		std::cout << "Двойной факториал равен:" << modifodd;
	}
	return 0;
}


