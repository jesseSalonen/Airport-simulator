#pragma once
#include "Utility.h"
#include "Extended_queue.h"
#include "Plane.h"
enum Runway_activity { idle, land, takeoff_ };

class Runway {
public:
	Runway(int limit);
	Error_code can_land(const Plane& current, int runway_mode);
	Error_code can_depart(const Plane& current);
	Runway_activity activity(int time, Plane& moving, int runway_mode);
	void shut_down(int time, int runway_mode) const;
	int landing_size() const;
	int takeoff_size() const;
	void crash();

private:
	Extended_queue landing;
	Extended_queue takeoff;
	int queue_limit;
	int num_land_requests;        //  number of planes asking to land
	int num_takeoff_requests;     //  number of planes asking to take off
	int num_landings;             //  number of planes that have landed
	int num_takeoffs;             //  number of planes that have taken off
	int num_land_accepted;        //  number of planes queued to land
	int num_takeoff_accepted;     //  number of planes queued to take off
	int num_land_refused;         //  number of landing planes refused
	int num_takeoff_refused;      //  number of departing planes refused
	int land_wait;                //  total time of planes waiting to land
	int takeoff_wait;             //  total time of planes waiting to take off
	int idle_time;                //  total time runway is idle
	int num_crashes;			  //  number of planes that have crashed
};

