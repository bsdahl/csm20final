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
    cout << "D. Delete a Passenger.\n";
    cout << "Q. Quit.\n";
    cout << "Enter your selection: ";
    
	cin.ignore(cin.rdbuf()->in_avail());
	option = getCharInput("menu item");
    cout << endl;
    
    switch (option)
    {
        {case '1':
            displayAllPassengers();
            break;}
            
        {case '2':
			cout << "Enter Destination City: ";
			char city = getCharInput("menu item");
            displayPassengersTo(city);
            break;}
            
        {case '3':
			cout << "Enter Origin City: ";
			char city = getCharInput("menu item");
            displayPassengersFrom(city);
            break;}
            
        {case '4':
			cout << "Enter a Flight Number: ";
			size_t flight = getNumericInput("flight number");
            displayPassengersOnFlt(flight);
            break;}
            
        {case '5':
			cout << "Enter a Flight Number: ";
			size_t flight = getNumericInput("flight number");
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
			cout << "Choose an option.\n"
				<< "1. Search by Name\n"
				<< "2. Search by Reservation Number\n"
				<< "Enter your selection: ";

			cin.ignore(cin.rdbuf()->in_avail());
			option = getCharInput("menu item");
			cout << endl;

			switch (option)
			{
				{case '1':
					string firstName ,lastName;
					cout << "Enter the First Name: ";
					cin >> firstName;
					cout << "Enter the Last Name: ";
					cin >> lastName;
					searchPassenger(firstName, lastName);
					break; }
				{case '2':
					cout << "Enter the Reservation Number: ";
					size_t reservationNum = getNumericInput("reservation number");
					searchPassenger(reservationNum);
					break; }
				{default:
					cout << option << " is not a valid menu item.\n\n";
					break; }
			}

            break;}
            
        {case '0':
			cout << "Enter a Flight Number: ";
			size_t flight = getNumericInput("flight number");
            searchFlight(flight);
            break;}
            
        {case 'D':
            cout << "WARNING: This will permenently delete the passenger from the Reservation System. This action cannot be undone.\n";
            cout << "Choose an option.\n"
            << "1. Search by Name\n"
            << "2. Search by Reservation Number\n"
            << "Enter your selection: ";
            
            cin.ignore(cin.rdbuf()->in_avail());
            option = getCharInput("menu item");
            cout << endl;
            
            switch (option)
            {
                {case '1':
                    string firstName ,lastName;
                    cout << "Enter the First Name: ";
                    cin >> firstName;
                    cout << "Enter the Last Name: ";
                    cin >> lastName;
                    removePassenger(firstName, lastName);
                    break; }
                {case '2':
                    cout << "Enter the Reservation Number: ";
                    size_t reservationNum = getNumericInput("reservation number");
                    removePassenger(reservationNum);
                    break; }
                {default:
                    cout << option << " is not a valid menu item.\n\n";
                    break; }
            }
            
            break;}
            
        {case 'Q':
            return false;
            break;}
            
        {default:
            cout << option << " is not a valid menu item.\n\n";
            break;}
    }
    
    return true;
}

bool AirlineInterface::displayAllPassengers()
{
	passengerSearch.clearKeys();

	data.traversePassenger(passengerSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::displayPassengersTo(char city)
{
	flightSearch.clearKeys();
	flightSearch.setToCity(city);

	data.traverseFlight(flightSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::displayPassengersFrom(char city)
{
	flightSearch.clearKeys();
	flightSearch.setFromCity(city);

	data.traverseFlight(flightSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::displayPassengersOnFlt(size_t flight)
{
	flightSearch.clearKeys();
	flightSearch.setFlightNum(flight);

	data.traverseFlight(flightSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::displayWaitFlight(size_t flight)
{
	passengerSearch.clearKeys();
	passengerSearch.setFightNumKey(flight);

	data.traverseWait(passengerSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::displayWaitAll()
{
	passengerSearch.clearKeys();

	data.traverseWait(passengerSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::displayAllFlights()
{
	flightSearch.clearKeys();
	flightSearch.setDisplayPassengers(false);

	data.traverseFlight(flightSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::displayAllFlightsPassengers()
{
	flightSearch.clearKeys();
	
	data.traverseFlight(flightSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::searchPassenger(string firstName, string lastName)
{
	passengerSearch.clearKeys();
	passengerSearch.setFirstNameKey(firstName);
	passengerSearch.setLastNameKey(lastName);

	data.traversePassenger(passengerSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::searchPassenger(size_t reservationNum)
{
	passengerSearch.clearKeys();
	passengerSearch.setReservationNumKey(reservationNum);

	data.traversePassenger(passengerSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::searchFlight(size_t flight)
{
	flightSearch.clearKeys();
	flightSearch.setFlightNum(flight);

	data.traverseFlight(flightSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::removePassenger(string firstName, string lastName)
{
    passengerSearch.clearKeys();
    passengerSearch.setFirstNameKey(firstName);
    passengerSearch.setLastNameKey(lastName);
    passengerSearch.setRemovePassengerKey(true);
    passengerSearch.setfmPtr(&data);
    
    data.traversePassenger(passengerSearch);
    
    enterToContinue();
    return true;
}

bool AirlineInterface::removePassenger(size_t reservationNum)
{
    passengerSearch.clearKeys();
    passengerSearch.setReservationNumKey(reservationNum);
    passengerSearch.setRemovePassengerKey(true);
    passengerSearch.setfmPtr(&data);
    
    data.traversePassenger(passengerSearch);
    
    passengerSearch.removeMarkedPassenger();
    
    enterToContinue();
    return true;
}

char AirlineInterface::getCharInput(string field)
{
	string selection;

	do
	{
		cin >> selection;

		if (selection.length() > 1)
			cout << "That is not a valid format for a " << field << ".\n"
				<< "Please enter a single character: ";
	} while (selection.length() > 1);

	cout << endl;

	selection[0] = toupper(selection[0]);

	return selection[0];
}

size_t AirlineInterface::getNumericInput(string field)
{
	string line;
	size_t num;
	bool successful;
	char c;

	do 
	{
		successful = true; //set flag to true to prevent infinite loop
		cin >> line;

		stringstream input(line);

		if (!(input >> num)) //input is not of type size_t
			successful = false;
		else if (num == 0) //0 is used to signify that flightNumber should not be compared in SearchFlightData class
			successful = false;

		if (input >> c) //if input was valid, but input remains in the stringstream
			successful = false; //then reject all input and ask user to reenter flight num

		if (!successful)
			cout << "That is not a valid format for a " << field << ".\n"
			<< "Please enter only one non-zero, non-negative integer number: ";
	} while (!successful);

	return num;
}

void AirlineInterface::enterToContinue()
{
    cin.ignore( cin.rdbuf()->in_avail() );
    cout << "\n\n********************* Press Enter to continue  -->  ";
    cin.ignore();
    cout << endl;
}
