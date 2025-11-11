#include <iostream>
#include <string>
#include<vector>
bool isPunctuation(char c) {
	const std::string punctuation = ".,!;:-—' ";
	return punctuation.find(c) != std::string::npos;
}
void EnterDelimeters(std::string& delimeters){
	std::cout << "Enter delimeters of the text" <<std::endl;
	getline(std::cin, delimeters);
	for (char c : delimeters) {
		if (!isPunctuation(c)) {
			throw std::invalid_argument("Not a delimeter");
		}
	}
}
void EnterString(std::string& text) {
	std::cout << "Please enter your text, divided by previous delimeters.Enter english text." << std::endl;
	if (!(getline(std::cin, text))) {
		throw 2;
	}
}
size_t CountWords(const std::string& text,const std::string& delimeters) {
	size_t words_amount = 0;
	std::string::size_type beg_index = 0;
	std::string::size_type end_index = text.find_first_of(delimeters, beg_index);

	while (beg_index != std::string::npos) {

		std::string word = text.substr(beg_index, end_index - beg_index);
		if (!word.empty()) {
			++words_amount;
		}

		beg_index = text.find_first_not_of(delimeters, end_index);
		end_index = text.find_first_of(delimeters, end_index + 1);
	}
	if (words_amount == 0) {
		throw 1;
	}
	return words_amount;
}
std::vector<std::string> SplitText(const std::string& text,
	const std::string& delimeters) {

	std::vector<std::string> words;

	std::string::size_type beg_index = 0;
	std::string::size_type end_index = text.find_first_of(delimeters, beg_index);

	while (beg_index != std::string::npos) {

		std::string word = text.substr(beg_index, end_index - beg_index);
		if (!word.empty()) {
			words.push_back(word);
		}

		beg_index = text.find_first_not_of(delimeters, end_index);
		end_index = text.find_first_of(delimeters, end_index + 1);
	}

	return words;
}
std::vector<std::string> deleteallequalsymbols(const std::vector<std::string>& words,
	size_t words_amount) {
	std::vector<std::string> unequalWords;
	for (size_t i = 0; i < words_amount; ++i) {
		std::string word = words[i]; 
		if (word.empty()) {
			unequalWords.push_back(""); 
			continue;
		}
		for (size_t a = 0; a < word.length(); ++a) {
			for (size_t r = a + 1; r < word.length(); ) {
				if (word[a] == word[r]) {
					word.erase(r, 1); 
				}
				else {
					++r; 
				}
			}
		}

		unequalWords.push_back(word);
	}

	return unequalWords;
}
int getMaxLength(const std::vector<std::string>& unequalWords, size_t words_amount) {
	int maxLength = 0;
	for (int i = 0; i < words_amount; ++i) {
		std::string tempUnEqualWord = unequalWords[i];
		if (tempUnEqualWord.length() > maxLength) {
			maxLength = tempUnEqualWord.length();
		}
	}
	return maxLength;
}
void printNeededWords(const std::vector<std::string>& unequalWords, const std::vector<std::string>& words,
	size_t words_amount,int maxLength){
	std::cout << "Words with the most unequal symbols are ";
	for (int i = 0; i < words_amount; ++i) {
		std::string tempUnEqualWord = unequalWords[i];
		if (tempUnEqualWord.length() == maxLength) {
			std::cout << words[i] << " ";
		}
	}
}
int main() {
	std::string delimeters;
	try {
		EnterDelimeters(delimeters);
	}
	catch (const std::invalid_argument&) {
		std::cerr << "please enter only delimeters(., ! ; : - —')";
		return -1;
	}
	std::string text;
	try {
		EnterString(text);
		CountWords(text, delimeters);
	}
	catch (int value) {
		switch (value) {
		case 1:
			std::cerr << "This text has no words,nothing to work with";
			return 1;
			
		case 2:
			std::cerr << "Unknown error";
			return 2;
			
		}
	}
	size_t words_amount = CountWords(text, delimeters);
	std::vector<std::string> words = SplitText(text, delimeters);
	std::vector<std::string> unequalWords = deleteallequalsymbols(words, words_amount);
	int maxLength = getMaxLength(unequalWords, words_amount);
	printNeededWords(unequalWords,words,words_amount,maxLength);
	return 0;
}



	















