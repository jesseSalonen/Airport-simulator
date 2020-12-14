#include <iostream>
#include "functions.h"
#include "Random.h"
#include "Runway.h"
using namespace std;

void main_1(Runway& small_airport, int current_time, Plane& moving_plane, int runway_mode);
void main_2(Runway& small_airport, int current_time, Plane& moving_plane, int runway_mode);

int main()     //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/

{
    int runway_mode = 0;
    int runway_mode_temp = 0;
    char runways;
    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;

    cout << "amount of runways? 1/2/3:";
    cin >> runways;
    if (runways == '2') runway_mode = 2;
    else if (runways == '3') runway_mode = 4;
    runway_mode_temp = runway_mode;

    initialize(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway small_airport(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            runway_mode = runway_mode_temp;
            Plane current_plane(flight_number++, current_time, arriving, variable.random_integer(1, 5)); //jokaisella koneella maksimissaan 5 aikakierrosta polttoainetta
            if (small_airport.can_land(current_plane, runway_mode) != success) {
                if (current_plane.refuse(runway_mode)) small_airport.crash();      //check if fuel empty
                runway_mode++;
            }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing, 10);
            if (small_airport.can_depart(current_plane) != success) {
                current_plane.refuse(runway_mode);
            }
        }

        Plane moving_plane;

        if (runway_mode >= 2 && runway_mode < 4) {
            main_1(small_airport, current_time, moving_plane, runway_mode);
        }
        else if (runway_mode >= 4) {
            main_2(small_airport, current_time, moving_plane, runway_mode);
        }
        else {
            switch (small_airport.activity(current_time, moving_plane, 1)) {
                //  Let at most one Plane onto the Runway at current_time.
            case land:
                moving_plane.land(current_time, runway_mode);
                break;
            case takeoff_:
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
            }
        }
    }
    small_airport.shut_down(end_time, runway_mode);
}


void main_1(Runway &small_airport, int current_time, Plane &moving_plane, int runway_mode) {
    bool runway1_idle = false;
    bool runway2_idle = false;
    switch (small_airport.activity(current_time, moving_plane, 2)) {
        //  Let at most one Plane onto the Runway at current_time.
    case land:
        moving_plane.land(current_time, runway_mode);
        break;
    case idle:
        run_idle(current_time);
        runway1_idle = true;
    }

    if (runway_mode != 3) {
        switch (small_airport.activity(current_time, moving_plane, 3)) {
            //  Let at most one Plane onto the Runway at current_time.
        case takeoff_:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
            runway2_idle = true;
        }
    }

    if (runway1_idle && small_airport.takeoff_size() > 0) {
        cout << current_time << ": Using idle runway for takeoffs." << endl;
        switch (small_airport.activity(current_time, moving_plane, 3)) {
            //  Let at most one Plane onto the Runway at current_time.
        case takeoff_:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
    }
    if ((runway2_idle && small_airport.landing_size() > 0) || runway_mode == 3) {
        cout << current_time << ": Using idle runway for landings." << endl;
        switch (small_airport.activity(current_time, moving_plane, 2)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time, runway_mode);
            break;
        case idle:
            run_idle(current_time);
        }
    }

    return;
}

void main_2(Runway& small_airport, int current_time, Plane& moving_plane, int runway_mode)
{
    bool runway1_idle = false;
    switch (small_airport.activity(current_time, moving_plane, 2)) {
        //  Let at most one Plane onto the Runway at current_time.
    case land:
        moving_plane.land(current_time, runway_mode);
        break;
    case idle:
        run_idle(current_time);
        runway1_idle = true;
    }

    
    switch (small_airport.activity(current_time, moving_plane, 3)) {
        //  Let at most one Plane onto the Runway at current_time.
    case takeoff_:
        moving_plane.fly(current_time);
        break;
    case idle:
        run_idle(current_time);
    }
    


    if (small_airport.landing_size() == 0 && small_airport.takeoff_size() > 0) {
        cout << current_time << ": Using idle runway for takeoffs." << endl;
        switch (small_airport.activity(current_time, moving_plane, 3)) {
            //  Let at most one Plane onto the Runway at current_time.
        case takeoff_:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
    }
    else {
        switch (small_airport.activity(current_time, moving_plane, 2)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time, runway_mode);
            break;
        case idle:
            run_idle(current_time);
        }
    }


    return;
}
