#include<iostream>
#include<vector>
#include<istream>
#include<algorithm>
#include <numeric>
#include <functional>
#include<string>
#include <stdexcept>  
#include<cstdint>
#include <limits>
#include<cmath>

void PrintVector(const std::vector<int>& numbers) {
	for (size_t i = 0; i < numbers.size(); ++i) {
		std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;
}

std::vector<int> NumbersToVector() {
	std::cout << "Enter numbers,type a letter if you want to end the input" << std::endl;
	std::vector<int> numbers;
	int x;
	while (std::cin >> x) {
		numbers.push_back(x);
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return numbers;
}

int countEqualNumbers(const std::vector<int>& numbers) {
	int x;
	std::cout << "enter the number you want to be counted";
	if (!(std::cin >> x)) {
		throw std::invalid_argument("Only numbers should be written");
	}
	return std::count(numbers.begin(), numbers.end(), x);
}

int countWhatUserSays(const std::vector<int>& numbers) {
	std::cout << "Now,please type the condition you want to be done.If you want to find numbers greater than some numbers,type the word greater,if you want less than some number,type the word less " << std::endl;
	std::string condition;
	std::cin >> condition;
	std::cout << "now type a number you want to compare" << std::endl;
	int x;
	if (!(std::cin >> x)) {
		throw std::invalid_argument("Next time enter an integer");
	}
	if (condition == "greater") {
		return std::count_if(numbers.begin(), numbers.end(), [x](int vecvar) {return vecvar > x;});
	}
	if (condition == "less") {
		return std::count_if(numbers.begin(), numbers.end(), [x](int vecvar) {return vecvar < x;});
	}
	else {
		throw std::invalid_argument("Next time enter greater or less");
	}
}

void allZerosToMiddleNumber(std::vector<int>& numbers) {
	int middle = std::accumulate(numbers.begin(), numbers.end(), 0) / numbers.size();
	std::replace(numbers.begin(), numbers.end(), 0, middle);
}

void AddSumFromIntersval(std::vector<int>& numbers) {
	std::cout << "please enter 2 numbers that will be the places of integers that will be boundaries of the interval";
	int a;
	int b;
	if (!(std::cin >> a >> b)) {
		throw std::invalid_argument("Next time enter integers");
	}
	int lower = std::min((a - 1), b - 1);
	int upper = std::max((a - 1), b - 1);
	if (lower < 0 || upper >= numbers.size()) {
		throw std::invalid_argument("Incorrect boundaries");
	}
	int temp = std::accumulate(numbers.begin() + lower, numbers.begin() + upper + 1, 0);
	for (size_t i = 0; i < numbers.size(); ++i) {
		numbers[i] = numbers[i] + temp;
	}
}

void replaceEveryEvenAbs(std::vector<int>& numbers) {
	int maxEl = *std::max_element(numbers.begin(), numbers.end());
	int minElem = *std::min_element(numbers.begin(), numbers.end());
	int difference = maxEl - minElem;
	std::replace_if(numbers.begin(), numbers.end(), [](int x) {
		if (std::abs(x) % 2 == 0) { return true; }
		return false;
		}, difference);
}

void deleteEveryEqualabs(std::vector<int>& numbers) {
	std::vector<int> tempval;
	for (size_t i = 0; i < numbers.size(); ++i) {
		int curVal = numbers[i];
		bool isMet = false;
		for (size_t j = 0; j < tempval.size(); ++j) {
			if (std::abs(curVal) == std::abs(tempval[j])) {
				isMet = true;
				break;
			}
		}
		if (isMet == false) {
			tempval.push_back(curVal);
		}
	}
	numbers = tempval;
}
int main() {
	std::vector<int> numbers = NumbersToVector();
	if (numbers.size() == 0) {
		std::cerr << "Please ebter at least 1 number";
		return 1;
	}

	std::cout << "sum of vector elements" << std::endl << std::accumulate(numbers.begin(), numbers.end(), 0) << std::endl;
	std::cout << "quantity of numbers in vector" << std::endl << numbers.size() << std::endl;

	try {
		int tempnum3 = countEqualNumbers(numbers);
		std::cout << "quantity of equal numbers is" << std::endl << tempnum3 << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	try {
		int tempnum = countWhatUserSays(numbers);
		std::cout << "quantity of numbers that are gretaer/less than entered number is" << std::endl << tempnum << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	allZerosToMiddleNumber(numbers);
	std::cout << "our vector after every zero was replaced with middle sum of numbers" << std::endl;
	PrintVector(numbers);

	try {
		AddSumFromIntersval(numbers);
		std::cout << "vector after sum from entered interval was added to every element" << std::endl;
		PrintVector(numbers);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	try {
		replaceEveryEvenAbs(numbers);
		std::cout << "vector after every even absolute number was replaced with the differnce between max and min element" << std::endl;
		PrintVector(numbers);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	deleteEveryEqualabs(numbers);
	std::cout << "our vector after every equal absolute number was removed" << std::endl;
	PrintVector(numbers);

	return 0;
}
