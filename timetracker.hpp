//
//  timetracker.hpp
//  Development
//
//  Created by Rafael Kallis on 18/10/15.
//  Copyright © 2015 Rafael Kallis. All rights reserved.
//

#ifndef timetracker_hpp
#define timetracker_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <String>
#include <ctime>
#include <sys/time.h>

class timetracker{
public:
    timetracker(){local_time.init();}
    ~timetracker(){}
    
    void start  ();
    long stop   ();
    long check  ();
    void reset  ();
    
    static void start   (const std::string& name);
    static long stop    (const std::string& name);
    static long check   (const std::string& name);
    static void reset   (const std::string& name);
    
private:
    typedef struct{
        timeval time;
        timeval diff;
        bool isRunning;
        void init(){time.tv_sec=time.tv_usec=diff.tv_sec=diff.tv_usec=0,isRunning=false;}
    } timeslot;
    
    timeslot local_time;
    static std::unordered_map<std::string, timetracker::timeslot> static_time;
};

#endif /* timetracker_hpp */
