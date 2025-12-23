#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class Author {
private:
    std::string Lstname_;
    std::string Name_;
    std::string Patronymic_;
public:
    Author(std::string Lstname, std::string Name, std::string Patronymic) :
        Lstname_(Lstname), Name_(Name), Patronymic_(Patronymic) {
    }

    bool operator<(const Author& other) const {
        if (Lstname_ != other.Lstname_) return Lstname_ < other.Lstname_;
        if (Name_ != other.Name_) return Name_ < other.Name_;
        return Patronymic_ < other.Patronymic_;
    }

    void GetAuth() const {
        std::cout << Lstname_ << " " << Name_ << " " << Patronymic_;
    }

    std::string GetLastName() const { return Lstname_; }
};

class Book {
private:
    unsigned long Id_;
    std::set<Author> AllAuth_;
    std::string BkName_;
    int Year_;
public:
    Book(unsigned long Id, std::set<Author> AllAuth, std::string Bkname, int Year) :
        Id_(Id), AllAuth_(AllAuth), BkName_(Bkname), Year_(Year) {
    }

    bool operator<(const Book& other) const {
        return BkName_ < other.BkName_;
    }

    void GetInfo() const {
        std::cout << Id_ << " " << BkName_ << " " << Year_ << " ";
        std::set<Author>::iterator it;
        for (it = AllAuth_.begin(); it != AllAuth_.end(); ++it) {
            it->GetAuth();
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    std::string GetBkName() const { return BkName_; }
    std::set<Author>& GetAuthors() { return AllAuth_; }
    const std::set<Author>& GetAuthors() const { return AllAuth_; }

    void SetAuthors(const Author& au) {
        AllAuth_.insert(au);
    }
};
