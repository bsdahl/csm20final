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
    
	cin.ignore(cin.rdbuf()->in_avail());
    cin >> option;
    cout << endl;
    
    switch (option)
    {
        {case '1':
            displayAllPassengers();
            break;}
            
        {case '2':
			char city = getCityInput();
            displayPassengersTo(city);
            break;}
            
        {case '3':
			char city = getCityInput();
            displayPassengersFrom(city);
            break;}
            
        {case '4':
			size_t flight = getFlightInput();
            displayPassengersOnFlt(flight);
            break;}
            
        {case '5':
			size_t flight = getFlightInput();
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
			size_t flight = getFlightInput();
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

bool AirlineInterface::displayPassengersTo(char city)
{
    return true;
}

bool AirlineInterface::displayPassengersFrom(char city)
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

char AirlineInterface::getCityInput()
{
	string city;

	do
	{
		cout << "Enter Destination City: ";
		cin >> city;

		if(city.length() > 1)
			cout << "That is not a valid format for a city.\n"
				<< "Please enter a single character city name.\n";
	} while (city.length() > 1);

	return city[0];
}

size_t AirlineInterface::getFlightInput()
{
	string line;
	size_t flight;
	bool successful;
	char c;

	do {
		successful = true; //set flag to true to prevent infinite loop

		cout << "Enter Flight Number: ";
		cin >> line;

		stringstream input(line);

		if (!(input >> flight)) //input is not of type size_t
			successful = false;
		else if (flight == 0) //0 is used to signify that flightNumber should not be compared in SearchFlightData class
			successful = false;

		if (input >> c) //if input was valid, but input remains in the stringstream
			successful = false; //then reject all input and ask user to reenter flight num

		if (!successful)
			cout << "That is not a valid format for a flight number.\n"
			<< "Please enter only one non-zero, non-negative integer number.\n";
	} while (!successful);

	return flight;
}
