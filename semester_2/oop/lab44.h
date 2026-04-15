#pragma once
#pragma once
#include<iostream>
#include<string>
class Lesson {
protected:
	size_t auditorynumber_;
	std::string subject_;
	std::string lecturername_;
	std::string dayofweek_;
	size_t duration_;
	const size_t uid_ = 0;
	static size_t counter;
public:
	Lesson(size_t auditorynumber, std::string& subject, std::string& lecturername, std::string& dayofweek, size_t duration);
	virtual ~Lesson() = default;
	Lesson(const Lesson& cop);
	virtual void DisplayInfo();
	virtual std::string GetType() = 0;
	std::string Getname();
	size_t GetTime();
	std::string GetDay();
	Lesson(Lesson&& other) noexcept;
	Lesson& operator=(const Lesson& other);
	Lesson& operator=(Lesson&& other) noexcept;
};
class Lab :public Lesson {
public:
	using Lesson::Lesson;
	void DisplayInfo() override;
	std::string GetType() override;
};
class Lecture :public Lesson {
public:
	using Lesson::Lesson;
	void DisplayInfo() override;
	std::string GetType() override;
};
class Seminar :public Lesson {
public:
	using Lesson::Lesson;
	void DisplayInfo() override;
	std::string GetType() override;
};