//
//  timetracker.cpp
//  Development
//
//  Created by Rafael Kallis on 18/10/15.
//  Copyright © 2015 Rafael Kallis. All rights reserved.
//

#include "timetracker.hpp"

std::unordered_map<std::string ,timetracker::timeslot> timetracker::static_time;

void timetracker::start(){
    if (!local_time.isRunning) {
        gettimeofday(&local_time.time, NULL);
        local_time.isRunning = true;
    }
}

long timetracker::stop(){
    if (local_time.isRunning) {
        timeval current_time;
        gettimeofday(&current_time, NULL);
        
        local_time.diff.tv_sec  += current_time.tv_sec  - local_time.time.tv_sec;
        local_time.diff.tv_usec += current_time.tv_usec - local_time.time.tv_usec;
        
        local_time.isRunning = false;
    }
    
    return (1000*(local_time.diff.tv_sec) + (local_time.diff.tv_usec)/1000);
}

long timetracker::check(){
    if (local_time.isRunning) {
        timeval current_time;
        gettimeofday(&current_time, NULL);
        
        local_time.diff.tv_sec  += current_time.tv_sec  - local_time.time.tv_sec;
        local_time.diff.tv_usec += current_time.tv_usec - local_time.time.tv_usec;
    }
    
    return (1000*(local_time.diff.tv_sec) + (local_time.diff.tv_usec)/1000);
}

void timetracker::reset(){
    local_time.init();
}

// Static Functions

void timetracker::start(const std::string& name){
    std::unordered_map<std::string,timeslot>::iterator it = timetracker::static_time.find(name);
    if (it == timetracker::static_time.end() || it->second.isRunning) {
        return;
    }
    gettimeofday(&it->second.time,NULL);
    it->second.isRunning=true;
}

long timetracker::stop(const std::string& name){
    std::unordered_map<std::string,timeslot>::iterator it = timetracker::static_time.find(name);
    if (it == static_time.end()) {
        return 0;
    }else if(it->second.isRunning){
        timeval current_time;
        gettimeofday(&current_time, NULL);
        
        it->second.diff.tv_sec  += current_time.tv_sec  - it->second.time.tv_sec;
        it->second.diff.tv_usec += current_time.tv_usec - it->second.time.tv_usec;
        
        it->second.isRunning = false;
    }

    return (1000*(it->second.diff.tv_sec) + (it->second.diff.tv_usec)/1000);
//    timeval current_time;
//    timeval diff;
//    gettimeofday(&current_time, NULL);
//    
//    diff.tv_sec  = (current_time.tv_sec  - it->second.time.tv_sec)  + it->second.diff.tv_sec;
//    diff.tv_usec = (current_time.tv_usec - it->second.time.tv_usec) + it->second.diff.tv_usec;
//    
//    timetracker::static_time.erase(it);
//    
//    return 1000*(diff.tv_sec) + (diff.tv_usec)/1000;
}

long timetracker::check(const std::string &name){
    std::unordered_map<std::string,timeslot>::iterator it = timetracker::static_time.find(name);
    if (it == static_time.end()) {
        return 0;
    }else if(it->second.isRunning){
        timeval current_time;
        gettimeofday(&current_time, NULL);
        
        it->second.diff.tv_sec  += current_time.tv_sec  - it->second.time.tv_sec;
        it->second.diff.tv_usec += current_time.tv_usec - it->second.time.tv_usec;
    }
    
    return (1000*(it->second.diff.tv_sec) + (it->second.diff.tv_usec)/1000);
//    std::unordered_map<std::string,timeslot>::iterator it = timetracker::static_time.find(name);
//    if (it == timetracker::static_time.end() || !it->second.isRunning) {
//        return 0;
//    }
//    timeval current_time;
//    gettimeofday(&current_time, NULL);
//    
//    return (1000*(current_time.tv_sec - it->second.time.tv_sec) + (current_time.tv_usec - it->second.time.tv_usec)/1000);
}

void timetracker::reset(const std::string& name){
    std::unordered_map<std::string,timeslot>::iterator it = timetracker::static_time.find(name);
    if (it != timetracker::static_time.end()) {
        it->second.init();
    }
}
