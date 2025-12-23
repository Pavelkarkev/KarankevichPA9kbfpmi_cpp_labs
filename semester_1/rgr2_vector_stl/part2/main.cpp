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
    while (in >> id >> type_id >> hour >> min >> dest >> travel_time) {
        std::time_t dispatch = time_utility::SetTime(hour, min);
        TrainType type = static_cast<TrainType>( type_id);
        Train dedf{id, type, dest,dispatch, travel_time};
        AllTrains.push_back(dedf);
    }
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
    for_each(vec.begin(), vec.end(), [&lower, &upper](Train& a) {
        if (a.GetDispatchTime() >= lower && a.GetDispatchTime() <= upper) {
            a.InfoOut();
        }
    });
}
void GetInfoDest(const std::string& destname,  std::vector<Train>& vec) {
    for_each(vec.begin(), vec.end(), [destname](Train& a) {
        if (a.GetDestination() == destname) {
            a.InfoOut();
        }
    });
}
void GetInfoSpecDest(const std::string& specality,  const std::string& destname,
     std::vector<Train>& vec) {
    for_each(vec.begin(), vec.end(), [specality,destname](Train& a) {
        if (a.GetDestination() == destname && a.GetTypeString() == specality) {
            a.InfoOut();
        }
    });
}
std::time_t GetFastestTime(std::vector<Train>& vec) {
    if (vec.size() == 0) {
        throw std::runtime_error("This vector is empty");
    }
    std::time_t min = vec[0].GetTravelTime();
    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i].GetTravelTime() < min) {
            min = vec[i].GetTravelTime();
        }
    }
    return min;
}

void FindTheFastestTrain(const std::string& destname,  std::vector<Train>& vec) {
    for_each(vec.begin(), vec.end(), [destname,&vec](Train& a) {
        if (a.GetDestination() == destname) {
            if (a.GetTravelTime() == GetFastestTime(vec)) {
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
                 "train in a format(id,type,destination,dispatch time,travel time)"
              << std::endl;
    std::vector<Train>AllTrains=FromFileToVector(inpit_file);
    SortByDispatch(AllTrains);
    std::cout << "Sorted vector" << std::endl;
    PrintVector(AllTrains);

    

}
