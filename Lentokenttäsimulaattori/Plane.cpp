#include <iostream>
#include "Random.h"
using namespace std;

#include "Plane.h"
Plane::Plane(int flt, int time, Plane_status status, int fuel)
/*
Post:  The Plane data members flt_num, clock_start,
       and state are set to the values of the parameters flt,
       time and status, respectively.
*/

{
    flt_num = flt;
    clock_start = time;
    state = status;
    fuel_left = fuel;
    cout << "Plane number " << flt << " ready to ";
    if (status == arriving) {
        cout << "land with " << fuel_left << " time units of fuel left." << endl;
    }
    else
        cout << "take off." << endl;
}

int Plane::get_fuel() const
{
    return fuel_left;
}


Plane::Plane()
/*
Post:  The Plane data members flt_num, clock_start,
       state are set to illegal default values.
*/
{
    flt_num = -1;
    clock_start = -1;
    state = null;
    fuel_left = -1;
}


bool Plane::refuse(int runway_mode) const
/*
Post: Processes a Plane wanting to use Runway, when
      the Queue is full.
*/

{
    cout << "Plane number " << flt_num;
    if (state == arriving) {
        cout << " directed to another airport" << endl;
        if (fuel_left < 5 && runway_mode < 2) {
            cout << "Fuel ran out on the way to another airport," << endl
                << "plane crashed!" << endl;
            return true;
        }
    }
    else
        cout << " told to try to takeoff again later" << endl;
    return false;
}


void Plane::land(int time, int runway_mode)
/*
Post: Processes a Plane that is landing at the specified time.
*/

{
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " landed after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the landing queue." << endl;
    if (runway_mode < 2 && get_fuel() < 1) cout << "Landing was faster than expected! Fuel ran out!" << endl;
}


void Plane::fly(int time) const
/*
Post: Process a Plane that is taking off at the specified time.
*/

{
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " took off after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the takeoff queue." << endl;
}


int Plane::started() const
/*
Post: Return the time that the Plane entered the airport system.
*/
{
    return clock_start;
}

bool Plane::fuel_empty(int wait)
{
    fuel_left -= wait;
    if (fuel_left < 1) return true;
    else return false;
}
