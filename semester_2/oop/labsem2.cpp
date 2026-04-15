#include"lab44.h"
#include<vector>
#include<fstream>
#include<sstream>
#include<functional>
#include<map>
#include<algorithm>
#include<utility>
size_t Lesson::counter = 0;
bool IsEmpty(std::ifstream& in) {
	return in.peek() == std::ifstream::traits_type::eof();
}
Lesson::Lesson(size_t auditorynumber, std::string& subject, std::string& lecturername, std::string& dayofweek, size_t duration) :
	auditorynumber_(auditorynumber), subject_(subject), lecturername_(lecturername), dayofweek_(dayofweek), duration_(duration), uid_(counter) {
	++counter;
}
Lesson::Lesson(const Lesson& cop) :uid_(counter), auditorynumber_(cop.auditorynumber_), subject_(cop.subject_), lecturername_(cop.lecturername_), dayofweek_(cop.dayofweek_), duration_(cop.duration_) {
	++counter;
}
std::string Lesson::Getname() {
	return lecturername_;
}
size_t Lesson::GetTime() {
	return duration_;
}
std::string Lesson::GetDay() {
	return dayofweek_;
}
void Lesson::DisplayInfo() {
	std::cout << subject_ << ' ' << lecturername_ << ' ' << dayofweek_ << ' ' << duration_ << ' ' << uid_ << ' ';
}
std::string Lab::GetType() {
	std::string str = "Lab";
	return str;
}
void Lab::DisplayInfo() {
	Lesson::DisplayInfo();
	Lab::GetType();
}
std::string Seminar::GetType() {
	std::string str = "Seminar";
	return str;
}
void Seminar::DisplayInfo() {
	Lesson::DisplayInfo();
	Seminar::GetType();
}
std::string Lecture::GetType() {
	std::string str = "Lecture";
	return str;
}
void Lecture::DisplayInfo() {
	Lesson::DisplayInfo();
	Lecture::GetType();
}
Lesson::Lesson(Lesson&& other) noexcept :
	auditorynumber_(std::exchange(other.auditorynumber_, 0)),
	subject_(std::move(other.subject_)),
	lecturername_(std::move(other.lecturername_)),
	dayofweek_(std::move(other.dayofweek_)),
	duration_(std::exchange(other.duration_, 0)),
	uid_(counter) {
	++counter;
}
Lesson& Lesson::operator=(const Lesson& other) {
	if (this != &other) {
		auditorynumber_ = other.auditorynumber_;
		subject_ = other.subject_;
		lecturername_ = other.lecturername_;
		dayofweek_ = other.dayofweek_;
		duration_ = other.duration_;
	}
	return *this;
}
Lesson& Lesson::operator=(Lesson&& other) noexcept {
	if (this != &other) {
		auditorynumber_ = std::exchange(other.auditorynumber_, 0);
		subject_ = std::move(other.subject_);
		lecturername_ = std::move(other.lecturername_);
		dayofweek_ = std::move(other.dayofweek_);
		duration_ = std::exchange(other.duration_, 0);
	}
	return *this;
}
std::vector<std::unique_ptr<Lesson>> ReadFromFile(const std::string& classes_file) {
	std::ifstream in{ classes_file };
	if (!(in.is_open())) {
		throw std::runtime_error("Error opening the file");
	}
	if (IsEmpty(in)) {
		throw std::runtime_error("File is empty");
	}
	std::vector<std::unique_ptr<Lesson>> lessons;
	std::string line;
	std::string type, roomStr, subject, teacher, day, durationStr;
	while (getline(in, line)) {
		if (!line.empty()) {
			std::stringstream s_in{ line };
			getline(s_in, type, ';');
			getline(s_in, roomStr, ';');
			getline(s_in, subject, ';');
			getline(s_in, teacher, ';');
			getline(s_in, day, ';');
			getline(s_in, durationStr, ';');
			try {
				size_t duration = std::stoull(durationStr);
				size_t room = std::stoull(roomStr);
				if (type == "Lecture") {
					lessons.emplace_back(std::make_unique<Lecture>(room, subject, teacher, day, duration));
				}
				else if (type == "Seminar") {
					lessons.emplace_back(std::make_unique<Seminar>(room, subject, teacher, day, duration));
				}
				else if (type == "Lab") {
					lessons.emplace_back(std::make_unique<Lab>(room, subject, teacher, day, duration));
				}
			}
			catch (const std::exception& e) {
				std::cerr << "Error parsing line: " << line << e.what() << std::endl;
				continue;
			}
		}

	}
	return lessons;
}
void InfoOut(std::vector<std::unique_ptr<Lesson>>& lessons) {
	for (const auto& lesson_ptr : lessons) {
		if (lesson_ptr != nullptr) {
			lesson_ptr->DisplayInfo();
			std::cout << std::endl;
		}
	}
}
void countEverySubj(std::vector<std::unique_ptr<Lesson>>& lessons) {
	std::map<std::string, int> stats;
	for (const auto& lesson : lessons) {
		if (lesson.get()->GetType() == "Lecture") {
			stats["Lecture"]++;
		}
		else if (lesson.get()->GetType() == "Seminar") {
			stats["Seminar"]++;
		}
		else if (lesson.get()->GetType() == "Lab") {
			stats["Lab"]++;
		}
	}
	for (const auto& pair : stats) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
	
}
void InfoByLecturer(std::vector<std::unique_ptr<Lesson>>& lessons) {
	std::string name;
	std::cout << "Please enter the name of the lecturer" << std::endl;
	std::cin >> name;
	bool werefound = false;
	for (const auto& lesson : lessons) {
		if (name == lesson.get()->Getname()) {
			lesson.get()->DisplayInfo();
			std::cout << std::endl;
			werefound = true;
		}
	}
	if (!werefound) {
		std::cout << "No matches" << std::endl;
	}
}
void CalculateTime(std::vector<std::unique_ptr<Lesson>>& lessons) {
	std::map<std::string, size_t> stats;
	for (const auto& lesson : lessons) {
		if (lesson.get()->GetType() == "Lecture") {
			stats["Lecture"] = stats["Lecture"] + lesson.get()->GetTime();
		}
		else if (lesson.get()->GetType() == "Seminar") {
			stats["Seminar"]=stats["Seminar"] + lesson.get()->GetTime();
		}
		else if (lesson.get()->GetType() == "Lab") {
			stats["Lab"] = stats["Lab"] + lesson.get()->GetTime();
		}
	}
	for (const auto& pair : stats) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
	
}
void OutByDay(std::vector<std::unique_ptr<Lesson>>& lessons) {
	std::string day;
	std::cout << "Please enter the day" <<std::endl;
	std::cin >> day;
	bool werefound = false;
	for (const auto& lesson : lessons) {
		if (day == lesson.get()->GetDay()) {
			lesson.get()->DisplayInfo();
			std::cout << std::endl;
			werefound = true;
		}
	}
	if (!werefound) {
		std::cout << "No matches" << std::endl;
	}
}
int main() {
	const std::string classes_file = "classes.txt";
	try {
		std::vector<std::unique_ptr<Lesson>> lessons = ReadFromFile(classes_file);
		bool endprogram = false;
		int n;
		while (endprogram==false) {
			std::cout << "Please enter the number of inquire you want to be executed" << std::endl;
			if (!(std::cin >> n)) {
				throw std::runtime_error("Please enter number from 1-5");
			}
			if (n < 1 || n>5) {
				throw std::runtime_error("Please enter number from 1-5");
			}
			switch (n) {
			case 1:
				InfoOut(lessons);
				break;
			case 2:
				countEverySubj(lessons);
				break;
			case 3:
				InfoByLecturer(lessons);
				break;
			case 4:
				CalculateTime(lessons);
				break;
			case 5:
				OutByDay(lessons);
				break;
			}
			
			std::cout << "Do you want to quit? 0/1" << std::endl;
			if (!(std::cin >> endprogram)){
				throw std::runtime_error("enter 0/1");
			}
		}

	}
		catch (std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
		}
	
}
