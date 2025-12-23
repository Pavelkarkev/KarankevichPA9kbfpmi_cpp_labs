#include "pch.h"
#include "Library.h"
#include <fstream>
bool isEmpty(std::ifstream& in) {
    return in.peek() == std::ifstream::traits_type::eof();
}

void GetAuthors(std::ifstream& in, std::set<Author>& AllAuth) {
    int count;
    if (!(in >> count)) return;
    int i;
    for (i = 0; i < count; ++i) {
        std::string ln, n, s;
        if (in >> ln >> n >> s) {
            AllAuth.insert(Author(ln, n, s));
        }
    }
}

std::set<Book> FromFileToSet(const std::string& s) {
    std::ifstream in{ s };
    if (!in.is_open()) throw std::invalid_argument("Couldnt open");
    if (isEmpty(in)) throw std::invalid_argument("Empty file");

    unsigned long id;
    std::string BkName;
    int Year;
    std::set<Book> Books;

    while (in >> id >> BkName >> Year) {
        std::set<Author> AllAuth;
        GetAuthors(in, AllAuth);
        Books.insert(Book(id, AllAuth, BkName, Year));
    }
    in.close();
    return Books;
}

void FindBook(const std::set<Book>& books, const std::string& BkName) {
    bool found = false;
    std::set<Book>::iterator it;
    for (it = books.begin(); it != books.end(); ++it) {
        if (it->GetBkName() == BkName) {
            it->GetInfo();
            found = true;
        }
    }
    if (!found) std::cout << "No books found" << std::endl;
}

void PopBook(const std::string& bkname, std::set<Book>& books) {
    std::set<Book>::iterator it;
    for (it = books.begin(); it != books.end(); ++it) {
        if (it->GetBkName() == bkname) {
            books.erase(it);
            return;
        }
    }
    std::cout << "Nothing to erase" << std::endl;
}

void PushAuthor(const Author& au, std::set<Book>& books, const std::string& bkname) {
    std::set<Book>::iterator it;
    for (it = books.begin(); it != books.end(); ++it) {
        if (it->GetBkName() == bkname) {
            Book temp = *it;
            temp.SetAuthors(au);
            books.erase(it);
            books.insert(temp);
            return;
        }
    }
}
void SearchBooksByAuthor(const std::set<Book>& library, const std::string& lastName) {
    std::set<Book>::iterator it;
    bool foundGlobal = false;

    for (it = library.begin(); it != library.end(); ++it) {
        const std::set<Author>& authors = it->GetAuthors();
        std::set<Author>::iterator authIt;

        for (authIt = authors.begin(); authIt != authors.end(); ++authIt) {
            if (authIt->GetLastName() == lastName) {
                it->GetInfo();
                foundGlobal = true;
                break;
            }
        }
    }

    if (!foundGlobal) {
        std::cout << "No books found for author: " << lastName << std::endl;
    }
}
void RemoveAuthorFromBook(std::set<Book>& library, const std::string& bookTitle, const std::string& authorLastName) {
    std::set<Book>::iterator it;
    for (it = library.begin(); it != library.end(); ++it) {
        if (it->GetBkName() == bookTitle) {
            Book temp = *it;
            std::set<Author>& authors = temp.GetAuthors();
            std::set<Author>::iterator authIt;
            bool found = false;

            for (authIt = authors.begin(); authIt != authors.end(); ++authIt) {
                if (authIt->GetLastName() == authorLastName) {
                    authors.erase(authIt);
                    found = true;
                    break;
                }
            }

            if (found) {
                library.erase(it);
                library.insert(temp);
            }
            else {
                std::cout << "Author not found in this book" << std::endl;
            }
            return;
        }
    }
    std::cout << "Book not found" << std::endl;
}
int main() {

    return 0;
}
