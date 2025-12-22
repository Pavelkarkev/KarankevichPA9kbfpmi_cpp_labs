#include<iostream>
#include<set>
#include<istream>
#include<algorithm>
#include <numeric>
#include <functional>
#include<string>
#include <stdexcept>  
#include<cstdint>
#include <limits>
#include<cmath>
#include <iterator>
void PrintSet(const std::set<int> &numbers) {
	std::set<int>::iterator temp;
	for (temp = numbers.begin();temp != numbers.end();++temp) {
		std::cout << *temp << " ";
	}
}
void EratosphenResheto(std::set<int>& numbers, int x) {
	int del = 2;

	while (del * del <= x) {
		for (int val = del * del; val <= x; val += del) {
			numbers.erase(val);
		}

		std::set<int>::iterator it2;
		it2 = numbers.upper_bound(del);

		if (it2 != numbers.end()) {
			del = *it2;
		}
		else {
			break;
		}
	}
}
int main() {
	std::set<int> numbers;
	int x;
	std::cout << "please enter an integer" << std::endl;
	if (!(std::cin >> x) ){
		std::cout<<"No letters allowed";
		return 1;
	}
	if (x <= 1) {
		std::cout << "only integers from 2 are allowed";
			return 2;
	}
	for (int i = 2;i <= x;++i) {
		numbers.insert(i);
	}
	EratosphenResheto(numbers,x);
	std::cout << "found numbers are" << std::endl;
	PrintSet(numbers);
	
}
