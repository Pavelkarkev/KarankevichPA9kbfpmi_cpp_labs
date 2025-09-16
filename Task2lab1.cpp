#include <iostream>
int main() {
	setlocale(LC_ALL, "1251");

	int n = 0;
	int sum = 0;
	int modif = 1;
	std::cout << "Введите границу отрезка n" << std::endl;
	if (!(std::cin >> n)) {
		std::cout << "No chepuha please";
		std::exit(1);
	}
	if (n <= 1) {
		std::cout << "n должен быть больше 1";
	}
	else {
		for (int i = 1; i <= n; i++) {
			if (i % 2 == 0) {

				sum += i;
			}
			else {

				modif *= i;
			}
		}
		std::cout << "Сумма четных:" << sum << std::endl;
		std::cout << "Произведение нечетных:" << modif;

	}
	return 0;
}
		
			


	
	