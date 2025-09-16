#include <iostream>
int main() {
	setlocale(LC_ALL, "1251");
	int a = 0, b, ostatok, s = 0;
	std::cout << "Введите число" << std::endl;
	if (!(std::cin >> a)) {
		std::cout << "wont work";
		std::exit(1);
	}
	if (a > 9999) {
		std::cout << "number has to have 4 digits";
		std::exit(1);
	}
	b = a;
	while (b > 0) {
		ostatok = b % 10;
		b = b / 10;
		s = s * 10 + ostatok;
	}
	if (s == a) {
		std::cout << "Palindrom!";
	}

	else {
		std::cout << "just a number:(";
	}
	return 0;
}


