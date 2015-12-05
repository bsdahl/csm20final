//
//  AirlineInterface.h
//  CSM20Final
//
//  Created by user on 11/28/15.
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//


#ifndef _AirlineInterface
#define _AirlineInterface

#include <iostream>
#include <stdio.h>
#include <string>
#include "FlightManager.h"
#include "PassengerData.h"
#include "FlightData.h"

using namespace std;

class AirlineInterface
{
public:
    bool displayMenu();
    
private:
	class SearchForPassenger
	{
	public:
		SearchForPassenger()					{ clearKeys();			   }

		void setFirstNameKey	 (string key)	{ firstNameKey		= key; }
		void setLastNameKey		 (string key)	{ lastNameKey		= key; }
		void setReservationNumKey(size_t key)	{ reservationNumKey = key; }
		void setFightNumKey		 (size_t key)	{ flightNumKey		= key; }

		void clearKeys()						{ firstNameKey		= "";
												  lastNameKey		= "";
					   							  reservationNumKey = 0; 
												  flightNumKey		= 0;   }

		void operator()(PassengerData data)
		{
			bool match = true;
			if (firstNameKey != "")
				match = match && (firstNameKey		== data.getFirstName());
			if (lastNameKey != "")
				match = match && (lastNameKey		== data.getLastName());
			if (reservationNumKey != 0)
				match = match && (reservationNumKey == data.getReservationNum());
			if (flightNumKey != 0)
				match = match && (flightNumKey		== data.getFlightNum());
			if (match)
				cout << data;
		}

	private:
		string firstNameKey;
		string lastNameKey;
		size_t reservationNumKey;
		size_t flightNumKey;
	};

	class SearchForFlight
	{
	public:
		SearchForFlight()						{ clearKeys();			   }
		void setToCity(char key)				{ toCity			= key; }
		void setFromCity(char key)				{ fromCity			= key; }
		void setFlightNum(size_t key)			{ flightNum			= key; }
		void setDisplayPassengers(bool key)		{ displayPassengers = key; }

		void clearKeys()						{ toCity			= 0;
												  fromCity			= 0;
												  flightNum			= 0;   
												  displayPassengers = true;}

		void operator()(FlightData data) 
		{
			bool match = true;
			if (toCity != 0)
				match = match && (toCity			== data.getToCity());
			if (fromCity != 0)
				match = match && (fromCity			== data.getFromCity());
			if (flightNum != 0)
				match = match && (flightNum			== data.getFlightNumber());
			if (match)
			{
				cout << data;
				if (displayPassengers)
				{
					cout << "Placeholder";
				}
			}
		}
	private:
		char toCity;
		char fromCity;
		size_t flightNum;
		bool displayPassengers;
	};

    FlightManager data;
	SearchForPassenger passengerSearch;
	SearchForFlight flightSearch;
    
    bool displayAllPassengers();
    bool displayPassengersTo(char);
    bool displayPassengersFrom(char);

    bool displayPassengersOnFlt(size_t);
    bool displayWaitFlight(size_t);
    bool displayWaitAll();
    
    bool displayAllFlights();
    bool displayAllFlightsPassengers();
    
    bool searchPassenger(string, string);
	bool searchPassenger(size_t);
    bool searchFlight(size_t);

	char getCityInput();
	size_t getNumericInput();
};

#endif
