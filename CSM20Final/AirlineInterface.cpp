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

bool AirlineInterface::displayAllPassengers()
{
    return true;
}

bool AirlineInterface::displayPassengersTo(string city)
{
    return true;
}

bool AirlineInterface::displayPassengersFrom(string city)
{
    return true;
}

bool AirlineInterface::displayPassengersOnFlt(size_t flight)
{
    return true;
}

bool AirlineInterface::displayWaitFlight(size_t flight)
{
    return true;
}

bool AirlineInterface::displayWaitAll()
{
    return true;
}

bool AirlineInterface::displayAllFlights()
{
    return true;
}

bool AirlineInterface::displayAllFlightsPassengers()
{
    return true;
}

bool AirlineInterface::searchPassenger(string passenger)
{
    return true;
}

bool AirlineInterface::searchFlight(size_t flight)
{
    return true;
}
