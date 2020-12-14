#include <iostream>
using namespace std;

void initialize(int& end_time, int& queue_limit,
    double& arrival_rate, double& departure_rate)
    /*
    Pre:  The user specifies the number of time units in the simulation,
          the maximal queue sizes permitted,
          and the expected arrival and departure rates for the airport.
    Post: The program prints instructions and initializes the parameters
          end_time, queue_limit, arrival_rate, and departure_rate to
          the specified values.
    Uses: utility function user_says_yes
    */

{
    cout << "This program simulates an airport with an amount of runways chosen by user." << endl
        << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void run_idle(int time)
/*
Post: The specified time is printed with a message that the runway is idle.
*/
{
    cout << time << ": Runway is idle." << endl;
}