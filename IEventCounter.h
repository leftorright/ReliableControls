//
// Created by Stephanie on 2018-02-11.
//

#ifndef RELIABLECONTROLS_IEVENTCOUNTER_H
#define RELIABLECONTROLS_IEVENTCOUNTER_H
#endif //RELIABLECONTROLS_IEVENTCOUNTER_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <atomic>
#include <boost/config.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


class IEventCounter {
    std::unordered_map<std::string, std::atomic<int> > counters;

public:
    void ParseEvents(const char* deviceId, const char* logName) {
        std::ifstream reader(logName, std::ios::in);
        if(!reader.is_open()) {
            std::cout << "Failed to open " << logName << "\n";
            return;
        }
        std::string date, time, stage;
        int counter = 0;
        while(GetNextLine(&date, &time, &stage, &reader)) {
            if (stage == "3") {
                std::string n_date, n_time, n_stage;
                int length = 0;
                while (GetNextLine(&n_date, &n_time, &n_stage, &reader)) {
                    length += StageLength(n_date, n_time, date, time);
                    if (length >= 5) {
                        // need to check for event
                        if (n_stage == "2") {
                            while ((stage == "3" && n_stage == "2") || (stage == "2" && n_stage == "3")) {
                                date = n_date;
                                time = n_time;
                                stage = n_stage;
                                if (!GetNextLine(&n_date, &n_time, &n_stage, &reader)) {
                                    RegisterCounter(deviceId, counter);
                                    return;
                                }
                            }
                            if (n_stage == "0") {
                                counter++;
                                break;
                            }
                        }
                    } else if (n_stage != "3") {
                        break;
                    } else {
                        date = n_date;
                        time = n_time;
                        stage= n_stage;
                    }
                }
            }
        }
        RegisterCounter(deviceId, counter);
    }
    int GetEventCount(const char* deviceId) {
        int value = 0;
        auto counter = counters.find(deviceId);
        if (counter == counters.end()) {
            // counter associated with deviceId not found
            // registers new counter with this deviceId
            RegisterCounter(deviceId, 0);
        } else {
            value = counter->second.load(std::memory_order_relaxed);
        }

        return value;
    }
private:
    void RegisterCounter(const char* deviceId, int value) {
        counters[deviceId].store(value, std::memory_order_relaxed);
    }
    int StageLength(std::string n_date, std::string n_time, std::string date, std::string time) {
        boost::posix_time::ptime t1(boost::posix_time::time_from_string(date + " " + time));
        boost::posix_time::ptime t2(boost::posix_time::time_from_string(n_date + " " + n_time));
        boost::posix_time::time_duration td = t2 - t1;
        std::string time_difference = boost::posix_time::to_simple_string(td);
        int hours, minutes, seconds;
        std::sscanf(time_difference.std::string::c_str(), "%d:%d:%d", &hours, &minutes, &seconds);

        return (hours * 60) + minutes + (seconds / 60);
    }
    bool GetNextLine(std::string *date,std::string *time, std::string *stage, std::ifstream *reader) {
        std::string line;
        if (std::getline(*reader, line)) {
            std::istringstream iss(line);
            iss >> *date;
            iss >> *time;
            iss >> *stage;
            return true;
        }
        return false;
    }
};


