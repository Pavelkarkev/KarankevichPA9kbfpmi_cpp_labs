#include<iostream>


int main() {
	setlocale(LC_ALL, "1251");
	int n = 0;
	int sumodd = 0;
	int lesszero = 0;
	std::cout << "Введите число" << std::endl;
	if (!(std::cin >> n)) {
		std::cout << "wont work";
		std::exit(1);
	}
	 if (n >= 0) {
		sumodd = n * n;//Формула суммы первых n нечетных чисел
		std::cout << "Cумма нечетных чисел равна:" << sumodd;
	 }
	   else {
		  lesszero = n * n * -1;
		  std::cout << "Cумма нечетных чисел равна:" << lesszero;
	   }
	 return 0;
	
}
	





