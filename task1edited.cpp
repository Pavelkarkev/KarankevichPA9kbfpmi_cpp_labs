#include <iostream>
#include <cmath>

int main() {
	setlocale(LC_ALL, "Russian");
	int a, b, d;
	
	std::cout << "Введите a,b,d" << std::endl;
	if (!(std::cin >> a >> b >> d)) {
		std::cout << "wont work";
		std::exit(1);
	}
	else {
		for (int i = std::min(a, b); i <= std::max(a, b); i += abs(d)) {
			//if (d >= 0) {
				if (i % 3 == 0) {
					std::cout << i << " ";
				}
			//}
			//if (d < 0) {
			//	if (i % 3 == 0) {
			//		std::cout << i << " ";
			//	}
			//}
		}
	}
}

			

	


