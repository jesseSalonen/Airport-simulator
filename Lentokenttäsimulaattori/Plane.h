#pragma once
enum Plane_status { null, arriving, departing };

class Plane {
public:
	Plane();
	Plane(int flt, int time, Plane_status status, int fuel);
	int get_fuel() const;
	bool refuse(int runway_mode) const;
	void land(int time, int runway_mode);
	void fly(int time) const;
	int started() const;
	bool fuel_empty(int wait);

private:
	int flt_num;
	int clock_start;
	Plane_status state;
	int fuel_left;
};

