#pragma once

#include <string>
#include "time_utility.h"
#include<fstream>
#include<iostream>

using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};


class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train(TrainId id, TrainType type, std::string destination, std::time_t dispatch,
          std::time_t travel)
        : id_(id),
          type_(type),
          destination_(destination),
          dispatch_time_(dispatch),
          travelling_time_(travel) {
    }
    std::time_t GetDispatchTime() {
        return dispatch_time_;
    }
    std::string GetTypeString() const {
        switch (type_) {
            case TrainType::PASSENGER:
                return "Passenger";
            case TrainType::FREIGHT:
                return "Freight";
            case TrainType::HIGH_SPEED:
                return "High Speed";
            case TrainType::SUBWAY:
                return "Subway";
            case TrainType::SPECIALIZED:
                return "Specialized";
            default:
                return "Unknown";
        }
    }
    void InfoOut() {
        std::cout << (*this).id_ << " " << (*this).GetTypeString() << " " << (*this).destination_
                  << " ";
        PrintTime((*this).dispatch_time_);
        std::cout<< " " << (*this).travelling_time_ << std::endl;
    }
    std::string GetDestination() {
        return destination_;
    }
    std::time_t GetTravelTime() {
        return travelling_time_;
    }
};


