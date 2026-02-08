#include <iostream>
#include<vector>
#include<map>
#include<algorithm>
#include <string>
#include <fstream>
#include<set>
bool isEmpty(std::ifstream& in) {
    return in.peek() == std::ifstream::traits_type::eof();
}
struct Mark {
    std::string subject;
    size_t mark=-1;
};
struct StudentData {
    std::string name;
    size_t number=-1;
    std::vector<Mark> marks;
    double average_score=0;
    double sum = 0;
};
std::map<size_t, StudentData> CreateMap(const std::string& StudentDataFile) {
    std::ifstream in(StudentDataFile);
    if (!in.is_open()) {
        throw std::runtime_error("Could not open the file");
    }
    if (isEmpty(in)) {
        throw std::runtime_error("File is empty!");
    }
    std::map<size_t, StudentData> studmap;
    Mark mrk;
    size_t studentNumber;
    std::string studentName;
    while (in >> mrk.subject >> mrk.mark >> studentNumber) {
        std::getline(in >> std::ws, studentName);
        std::map<size_t, StudentData>::iterator it = studmap.find(studentNumber);
        if (it != studmap.end()) {
            it->second.marks.push_back(mrk);
        }
        else {
            StudentData newData;
            newData.name = studentName;
            newData.number = studentNumber;
            newData.marks.push_back(mrk);
            studmap[studentNumber] = newData;
        }
    }
    in.close();
    return studmap;
}
std::set<std::string> getsubjects(std::map<size_t, StudentData>& studmap) {
    std::map<size_t, StudentData>::iterator it;
    std::set<std::string>subjects;
    for (it = studmap.begin(); it != studmap.end(); ++it) {
        for_each(it->second.marks.begin(), it->second.marks.end(), [&subjects](const Mark& x) {
            subjects.emplace(x.subject);
        });
    }
    return subjects;
}
void InfoOut(StudentData& x) {
    std::cout << x.name << " " << x.number << std::endl;
}
void OutById(std::map<size_t, StudentData>& studmap) {
    std::map<size_t, StudentData>::iterator it;
    for (it = studmap.begin(); it != studmap.end(); ++it) {
        std::cout << it->first <<" ";
        std::cout << it->second.name << std::endl;
    }
}
void CalculateAverage(std::map<size_t, StudentData>& studmap) {
    std::map<size_t, StudentData>::iterator it;
    for (it = studmap.begin(); it != studmap.end(); ++it) {
        try {
            std::vector<Mark>::iterator Vit;
            double sum = 0;
            double counter = 0;
            if (it->second.marks.empty()) {
                throw std::invalid_argument("Student has no marks,his average score will remain 0");
            }
            else {
            for (Vit = it->second.marks.begin(); Vit != it->second.marks.end(); Vit++) {
                sum = sum + Vit->mark;
                counter++;
            }
                it->second.average_score = sum / counter;
                it->second.sum = sum;
            }
        }
        catch (std::invalid_argument& e) {
            std::cerr << e.what();
            continue;
        }
    }
}
void OutByNames(std::map<size_t, StudentData>& studmap) {
    std::map<size_t, StudentData>::iterator it;
    std::vector<StudentData> tmp;
    for (it = studmap.begin(); it != studmap.end(); ++it) {
        tmp.push_back(it->second);
    }
    std::sort(tmp.begin(), tmp.end(), [](const StudentData& a, const StudentData& b) {
        if (a.name != b.name) {
            return a.name < b.name;
        }
        return a.average_score > b.average_score;
    });
    int counter = 1;
    for_each(tmp.begin(), tmp.end(), [&counter](const StudentData& x){
        std::cout << counter << " " << x.name << " " << x.number << " " << x.average_score << std::endl;
        counter++;
    });
}
void OutInRange(std::map<size_t, StudentData>& studmap) {
    std::map<size_t, StudentData>::iterator it;
    std::vector<StudentData> tmp;
    std::cout << "Please enter search boundaries";
    double lwr;
    double uppr;
    bool found = false;
    if (!(std::cin >> lwr>>uppr)) {
        throw std::invalid_argument("Please enter positive numbers");
    }
    for (it = studmap.begin(); it != studmap.end(); ++it) {
        tmp.push_back(it->second);
    } 
    std::sort(tmp.begin(), tmp.end(), [](const StudentData& a, const StudentData& b) {
        return a.average_score < b.average_score;
    });
    for_each(tmp.begin(), tmp.end(), [lwr, uppr,&found](const StudentData& x) {
        if (x.average_score >= std::min(lwr,uppr) && x.average_score <= std::max(lwr,uppr)) {
            std::cout << x.name << std::endl;
            found = true;
        }
    });
    if (!found) {
        std::cout << "No students in given range" << std::endl;
    }
}
void FindMatches(std::map<size_t, StudentData>& studmap, const std::string& subj,bool outType) {
    std::map<size_t, StudentData>::iterator it;
    int counter = 0;
    for (it = studmap.begin(); it != studmap.end(); ++it) {
        bool matchfound = false;
        for_each(it->second.marks.begin(), it->second.marks.end(), [subj,&counter, &matchfound](const Mark& m){
            if (subj == m.subject) {
                matchfound = true;
                ++counter;
            }
            });
        if (outType) {
            if (matchfound) {
                InfoOut(it->second);
            }
        }
        
    }
    if(!outType) {
        std::cout << "Number of students that took " << subj << ":" << counter << std::endl;
    }
    if (counter == 0) {
        std::cout << "No correlations were found" << std::endl;
    }
    
}
void SubjectMapAdd(std::map<size_t, StudentData>& studmap, const std::string& subj, std::map<double, std::string>& subjWithAvg) {
    std::map<size_t, StudentData>::iterator it;
    double sum = 0;
    double counter = 0;
    for (it = studmap.begin(); it != studmap.end(); ++it) {
        for_each(it->second.marks.begin(), it->second.marks.end(), [subj, &sum,&counter](const Mark& m) {
            if (subj == m.subject) {
                sum = sum + m.mark;
                counter++;
            }
        });
    }
    if (counter != 0) {
        double averageOnSubj = sum / counter;
        subjWithAvg.emplace(averageOnSubj, subj);
    }else{
        std::cout << "No students took this exam,therfore average score couldnt be calculated" << std::endl;
    }
}
void StudentsThatTookExam(std::map<size_t, StudentData>& studmap){
    std::string subj;
    std::cout << "Please enter the subject." << std::endl;
    std::cin >> subj;
    FindMatches(studmap,subj,{true});
}
void NumberOfTimesSubjectTaken(std::map<size_t, StudentData>& studmap,std::set<std::string>& subjects) {
    std::set<std::string>::iterator Sit;
    for (Sit = subjects.begin(); Sit != subjects.end(); Sit++) {
        FindMatches(studmap, *Sit, { false });
    }
}
void OutAverageOnSubj(std::map<size_t, StudentData>& studmap, std::set<std::string>& subjects) {
    std::set<std::string>::iterator Sit;
    std::map<double, std::string> subjWithAvg;
    std::map<double, std::string>::reverse_iterator Mit;
    for (Sit = subjects.begin(); Sit != subjects.end(); Sit++) {
        SubjectMapAdd(studmap,*Sit,subjWithAvg);
    }
    for (Mit = subjWithAvg.rbegin(); Mit != subjWithAvg.rend(); Mit++) {
        std::cout << Mit->second << " average score: " << Mit->first<<std::endl;
    }
}
void OutEveryMaxStudent(std::map<size_t, StudentData>& studmap) {
    std::map<size_t, StudentData>::iterator it;
    std::multimap<double, StudentData> sumMap;
    for (it = studmap.begin(); it != studmap.end(); it++) {
       
        sumMap.emplace(it->second.sum, it->second);
    }
    std::multimap<double, StudentData>::reverse_iterator rit;
    rit = sumMap.rbegin();
    double max = rit->first;
    std::multimap<double, StudentData>::reverse_iterator it2;
    for (it2 = sumMap.rbegin(); it2 != sumMap.rend(); it2++) {
        if (it2->first == max) {
            InfoOut(it2->second);
        }
        else {
            break;
        }
    }
}
void StudentsWithBadGrades(std::map<size_t, StudentData>& studmap) {
    std::map<size_t, StudentData>::iterator it;
    for (it = studmap.begin(); it != studmap.end(); it++) {
        bool badgradefound = false;
        for_each(it->second.marks.begin(), it->second.marks.end(), [&badgradefound](const Mark& m) {
            if (m.mark<=3) {
                badgradefound = true;
            }
        });
        if (badgradefound) {
            InfoOut(it->second);
        }
    }
}
int main(){
     const std::string StudentInputFile = "Data.txt";
     try {

         std::map<size_t, StudentData> studmap = CreateMap(StudentInputFile);
         std::set<std::string> subjects = getsubjects(studmap);
         std::cout << "Sorted by ID" << std::endl;
         OutById(studmap);
      
         CalculateAverage(studmap);
         std::cout << "Sorted by names and average score" << std::endl;
         OutByNames(studmap);
         std::cout << "Students in average score range" << std::endl;
         OutInRange(studmap);
         std::cout << "Students that took specific subject" << std::endl;
         StudentsThatTookExam(studmap);
         std::cout << "Number of students for each subject" << std::endl;
         NumberOfTimesSubjectTaken(studmap, subjects);
         std::cout << "Average score for each subject" << std::endl;
         OutAverageOnSubj(studmap, subjects);
         std::cout << "Students with maximum total sum" << std::endl;
         OutEveryMaxStudent(studmap);
         std::cout << "Students with bad grades" << std::endl;
         StudentsWithBadGrades(studmap); 
     }
     catch (const std::runtime_error& e) {
         std::cerr << e.what() << std::endl;
     }
     catch (const std::invalid_argument& e) {
         std::cerr << e.what() << std::endl;
     }
        
}
