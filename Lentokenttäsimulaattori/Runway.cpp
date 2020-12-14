#include <iostream>
using namespace std;

#include "Runway.h"

Runway::Runway(int limit)
/*
Post:  The Runway data members are initialized to record no
       prior Runway use and to record the limit on queue sizes.
*/

{
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = num_crashes = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
}


Error_code Runway::can_land(const Plane& current, int runway_mode)
/*
Post:  If possible, the Plane current is added to the
       landing Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (landing.size() < queue_limit && current.get_fuel() == 1 && runway_mode < 2)
        result = landing.append_front(current);
    else if (landing.size() < queue_limit)
        result = landing.append(current);
    else
        result = fail;
    num_land_requests++;

    if (result != success)
        num_land_refused++;
    else
        num_land_accepted++;

    return result;
}


Error_code Runway::can_depart(const Plane& current)
/*
Post:  If possible, the Plane current is added to the
       takeoff Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (takeoff.size() < queue_limit)
        result = takeoff.append(current);
    else
        result = fail;
    num_takeoff_requests++;
    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;

    return result;
}


Runway_activity Runway::activity(int time, Plane& moving, int runway_mode)
/*
Post:  If the landing Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  land is returned. Otherwise,
       if the takeoff Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  takeoff is returned. Otherwise,
       idle is returned. Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Runway_activity in_progress;
    if (!landing.empty() && (runway_mode == 1 || runway_mode == 2)) {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        if (runway_mode < 2 && moving.fuel_empty(time - moving.started())) num_crashes++;
        else num_landings++;
        in_progress = land;
        landing.serve();
    }

    else if (!takeoff.empty() && (runway_mode == 1 || runway_mode == 3)) {
        takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = takeoff_;
        takeoff.serve();
    }

    else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

void Runway::shut_down(int time, int runway_mode) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "Simulation has concluded after " << time << " time units." << endl
        << "Total number of planes processed "
        << (num_land_requests + num_takeoff_requests) << endl
        << "Total number of planes asking to land "
        << num_land_requests << endl
        << "Total number of planes asking to take off "
        << num_takeoff_requests << endl
        << "Total number of planes accepted for landing "
        << num_land_accepted << endl
        << "Total number of planes accepted for takeoff "
        << num_takeoff_accepted << endl
        << "Total number of planes refused for landing "
        << num_land_refused << endl
        << "Total number of planes refused for takeoff "
        << num_takeoff_refused << endl
        << "Total number of planes that landed "
        << num_landings << endl
        << "Total number of planes that took off "
        << num_takeoffs << endl;
        if (runway_mode < 2) {
            cout << "Total number of planes that crashed "
                << num_crashes << endl;
        }
        cout << "Total number of planes left in landing queue "
        << landing.size() << endl
        << "Total number of planes left in takeoff queue "
        << takeoff.size() << endl;
    if (runway_mode < 2) {
        cout << "Percentage of time runway idle "
            << 100.0 * ((float)idle_time) / ((float)time) << "%" << endl;
    }
    else if (runway_mode < 4) {
        cout << "Percentage of time runway idle "
            << 100.0 * ((float)idle_time) / ((float)time) / 2 << "%" << endl;
    }
    else {
        cout << "Percentage of time runway idle "
            << 100.0 * ((float)idle_time) / ((float)time) / 3 << "%" << endl;
    }
    cout << "Average wait in landing queue "
        << ((float)land_wait) / ((float)num_landings) << " time units";
    cout << endl << "Average wait in takeoff queue "
        << ((float)takeoff_wait) / ((float)num_takeoffs)
        << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
        << ((float)num_land_requests) / ((float)time)
        << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
        << ((float)num_takeoff_requests) / ((float)time)
        << " per time unit" << endl;
}

int Runway::landing_size() const
{
    return landing.size();
}

int Runway::takeoff_size() const
{
    return takeoff.size();
}

void Runway::crash()
{
    num_crashes++;
}
