#define _CRT_SECURE_NO_WARNINGS
#include "time_utility.h"
#include "train.h"
#include <iostream>
bool isEmpty(std::ifstream& in) {
    return in.peek() == std::ifstream::traits_type::eof();
}
std::vector<Train> FromFileToVector(const std::string& s) {
    std::ifstream in{s};
    if (!in.is_open()) {
        throw std::invalid_argument("Couldnt open the file");
    }
    if (isEmpty(in)) {
        throw std::invalid_argument("File is empty");
    }
    std::vector<Train> AllTrains;
    size_t id, type_id, hour, min;
    std::string dest;
    std::time_t travel_time;
    while (in >> id >> type_id >> dest>> hour >> min >> travel_time) {
        std::time_t dispatch = time_utility::SetTime(hour, min);
        TrainType type = static_cast<TrainType>( type_id);
        Train dedf{id, type, dest,dispatch, travel_time};
        AllTrains.push_back(dedf);
    }
    in.close();
    return AllTrains;
}
void SortByDispatch(std::vector<Train>&vec) {
    std::sort(vec.begin(), vec.end(), []( Train& a,  Train& b) {
        if (a.GetDispatchTime() > b.GetDispatchTime()) {
            return true;
        }
        return false;
    });
}
void GetInfoTime(const std::time_t& lower, const std::time_t& upper,  std::vector<Train>& vec) {
    bool wereout = false;
    if (lower > upper) {
        throw std::invalid_argument("Lower shoudnt be greater than upper");
    }
    for_each(vec.begin(), vec.end(), [&lower, &upper,&wereout](Train& a)mutable {
        if (a.GetDispatchTime() >= lower && a.GetDispatchTime() <= upper) {
            a.InfoOut();
            wereout = true;
        }
    });
    if (wereout == false) {
        std::cout << "No trains in given boundaries" << std::endl;
    }
}
void GetInfoDest(const std::string& destname,  std::vector<Train>& vec) {
    bool wereout = false;
    for_each(vec.begin(), vec.end(), [destname,&wereout](Train& a)mutable {
        if (a.GetDestination() == destname) {
            a.InfoOut();
            wereout = true;
        }
    });
    if (wereout == false) {
        std::cout << "No trains in given destination" << std::endl;
    }
}
void GetInfoSpecDest(const std::string& specality,  const std::string& destname,
     std::vector<Train>& vec) {
    bool werefound = false;
    for_each(vec.begin(), vec.end(), [specality,destname,&werefound](Train& a) mutable{
        if (a.GetDestination() == destname && a.GetTypeString() == specality) {
            a.InfoOut();
            werefound = true;
        }
    });
    if (werefound == false) {
        std::cout << "No trains in given destination" << std::endl;
    }
}
std::time_t GetFastestTime(const std::string& destname,std::vector<Train>& vec) {
    if (vec.size() == 0) {
        throw std::runtime_error("This vector is empty");
    }
    std::vector<Train> temp;
    for (int j = 0; j < vec.size(); ++j) {
        if (vec[j].GetDestination() == destname) {
            temp.push_back(vec[j]);
        }
    }
    std::time_t min = temp[0].GetTravelTime();
    for (int i = 1; i < temp.size(); ++i) {
        if (temp[i].GetTravelTime() < min) {
            min = temp[i].GetTravelTime();
        }
    }
    return min;
}

void FindTheFastestTrain(const std::string& destname,  std::vector<Train>& vec) {
    int temp = GetFastestTime(destname, vec);
    for_each(vec.begin(), vec.end(), [destname,&vec,temp](Train& a) {
        if (a.GetDestination() == destname) {
            if (a.GetTravelTime() == temp) {
                a.InfoOut();
            }
        }
    });
    
}
void PrintVector( std::vector<Train>& vec) {
    for_each(vec.begin(), vec.end(), [](Train& a) { a.InfoOut(); });
    std::cout << std::endl;
}

int main() {

    using namespace time_utility;
    const std::string inpit_file="input.txt";
    std::cout << "If you want to change something in the input file be sure to form data for one "
                 "train in a format(id,type,destination,hours,minutes,travel time in seconds)"
              << std::endl;
    std::cout
        << "Warning:when you type in destination be sure to type it in accordance with register"
        << std::endl;
    std::vector<Train>AllTrains=FromFileToVector(inpit_file);
    SortByDispatch(AllTrains);
    std::cout << "Sorted vector" << std::endl;
    PrintVector(AllTrains);
    std::cout << "Please enter hours an lower value of time and the upper one " << std::endl;
        try {
        std::time_t h1, m1, h2, m2;
        if (!(std::cin >> h1 >> m1 >> h2 >> m2)) {
            throw std::exception("Please enter valid time values");
        }
            std::time_t t1 = SetTime(h1, m1);
            std::time_t t2 = SetTime(h2, m2);
            GetInfoTime(t1, t2, AllTrains);
        } catch (const std::out_of_range& err) {
            std::cerr << err.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        } catch (const std::exception& n) {
            std::cerr << n.what() << std::endl;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter destination" << std::endl;
    std::string dest;
    if (!getline(std::cin,dest)) {
        std::cout << "Please enter valid destionation name";
    }
    GetInfoDest(dest, AllTrains);
    std::cout << "Please enter  destination for specifying info" << std::endl;
    std::string sdest;
    if (!getline(std::cin, sdest)) {
        std::cout << "Please enter valid destionation name";
    }
    std::cout << "Please enter train type" << std::endl;
    std::string tpid;
    if (!getline(std::cin, tpid)) {
        std::cout << "Please enter valid train type name";
    }
    GetInfoSpecDest(tpid, sdest, AllTrains);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    try {
        std::cout << "Please enter destination for fastest trains" << std::endl;
        std::string fdest;
        if (!getline(std::cin, fdest)) {
            std::cout << "Please enter valid destionation name";
        }
        std::cout << " The fastest train info" << std::endl;
        FindTheFastestTrain(fdest,AllTrains);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
    


    

}

