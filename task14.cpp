#include <iostream>

int main() {
	int a = 0;
	int sum = 0;
	setlocale(LC_ALL, "1251");
	std::cout << "Введите число" << std::endl;
	if (!(std::cin >> a)) {
		std::cout << "wont work";
		std::exit(1);
	}
	int b = a;
	if (a < 0) {
		std::cout << "число меньше 0";
		std::exit(1);
	}
	while (b > 0) {
		int ostatok = b % 10;
		b = b / 10;
		sum = sum + ostatok;
	}
	std::cout << sum;
	return 0;
}
		 
