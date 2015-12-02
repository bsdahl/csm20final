//
//  AirlineInterface.cpp
//  CSM20Final
//
//  Created by user on 11/28/15.
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//

#include "AirlineInterface.h"

bool AirlineInterface::displayMenu()
{
    char option;
    
    cout << "Welcome to CSM20 Airlines. Choose an option.\n";
    cout << "1. Display all passengers.\n";
    cout << "2. Display passengers going to a city.\n";
    cout << "3. Display passengers leaving a city.\n";
    cout << "4. Display passengers on a flight.\n";
    cout << "5. Display wait list for a flight.\n";
    cout << "6. Display global wait list.\n";
    cout << "7. Display all flights.\n";
    cout << "8. Display all flights including passengers.\n";
    cout << "9. Search for a passenger.\n";
    cout << "0. Search for a flight.\n";
    cout << "Q. Quit.\n";
    cout << "Enter your selection: ";
    
    cin >> option;
    cout << endl;
    
    switch (option)
    {
        {case '1':
            displayAllPassengers();
            break;}
            
        {case '2':
            string city;
            cout << "Enter Destination City: ";
            cin >> city;
            displayPassengersTo(city);
            break;}
            
        {case '3':
            string city;
            cout << "Enter Origin City: ";
            cin >> city;
            displayPassengersFrom(city);
            break;}
            
        {case '4':
            size_t flight;
            cout << "Enter Flight Number: ";
            cin >> flight;
            displayPassengersOnFlt(flight);
            break;}
            
        {case '5':
            size_t flight;
            cout << "Enter Flight Number: ";
            cin >> flight;
            displayWaitFlight(flight);
            break;}
            
        {case '6':
            displayWaitAll();
            break;}
            
        {case '7':
            displayAllFlights();
            break;}
            
        {case '8':
            displayAllFlightsPassengers();
            break;}
            
        {case '9':
            string passenger;
            cout << "Enter a Reservation number or name: ";
            cin >> passenger;
            searchPassenger(passenger);
            break;}
            
        {case '0':
            size_t flight;
            cout << "Enter Flight Number: ";
            cin >> flight;
            searchFlight(flight);
            break;}
            
        {case 'Q':
            return false;
            break;}
            
        {default:
            cout << option << " is not a valid menu item.\n";
            break;}
    }
    
    return true;
}

// Traverses the Passenger Tree and outputs all passengers
bool AirlineInterface::displayAllPassengers()
{
    return true;
}

// Traversals the Passenger tree, gets the flightreservation number
// traversals the FlightData tree to retrieve that flight, checks the From
// city. It match, output the passenger. This is an expensive operation,
// but it expected of a relationship database design where a lookup
// requires a join of two tables.
bool AirlineInterface::displayPassengersTo(string city)
{
    return true;
}

// Traversals the Passenger tree, gets the flightreservation number
// traversals the FlightData tree to retrieve that flight, checks the From
// city. It match, output the passenger. This is an expensive operation,
// but it expected of a relationship database design where a lookup
// requires a join of two tables.
bool AirlineInterface::displayPassengersFrom(string city)
{
    return true;
}

// Traversals the flight tree, selects matching flight, and outputs
// the SeatMap vector
bool AirlineInterface::displayPassengersOnFlt(size_t flight)
{
    return true;
}

// Traversals the WaitList tree and outputs each passenger that
// matches the flight number.
bool AirlineInterface::displayWaitFlight(size_t flight)
{
    return true;
}

// Traversals the WaitList tree and outputs all passengers
bool AirlineInterface::displayWaitAll()
{
    return true;
}

// Traversals Flight Tree and outputs each flight
bool AirlineInterface::displayAllFlights()
{
    return true;
}

// Traversals Flight Tree and outputs each flight followed
// by its Passenger List
bool AirlineInterface::displayAllFlightsPassengers()
{
    return true;
}

// Accepts a string, determines whether the string is a
// ReservationNumber or a Name. Whether that name is one
// word or two words. It then searches the PassengerTree
// for match against the ReservationNumber OR both FirstName
// and LastName OR one name is either FirstName or LastName
bool AirlineInterface::searchPassenger(string passenger)
{
    return true;
}

// Accepts size_t, searches flight tree for matching flightNumber
bool AirlineInterface::searchFlight(size_t flight)
{
    return true;
}
