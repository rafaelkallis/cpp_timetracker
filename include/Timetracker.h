/*
 * Timetracker.h
 *
 *  Created on: Oct 28, 2015
 *      Author: rafael
 */

#ifndef TIMETRACKER_H_
#define TIMETRACKER_H_

#include <sys/time.h>
#include <time.h>

class timetracker {
public:
	timetracker();
	~timetracker();

	void start  ();
	long stop   ();
	long check  ();
	void reset  ();

protected:
	timeval tracker_time;
	timeval diff;
	bool isRunning;
};

#endif /* TIMETRACKER_H_ */
