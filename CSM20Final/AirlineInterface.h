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
	AirlineInterface() {}
    bool displayMenu();
    
private:
    
//
// Begin SearchForPassenger nested class.
// CSM20Final
//
// This is a utility class meant to be passed into a traversal function.
//
//
	class SearchForPassenger
	{
	public:
		SearchForPassenger()					{ clearKeys();			   }
		~SearchForPassenger()					{ clearKeys();			   }

		void setFirstNameKey	 (string key)	{ firstNameKey		= key; }
		void setLastNameKey		 (string key)	{ lastNameKey		= key; }
		void setReservationNumKey(size_t key)	{ reservationNumKey = key; }
		void setFightNumKey		 (size_t key)	{ flightNumKey		= key; }
        void setRemovePassengerKey(bool  key)   { removePassenger   = key; }
        void setfmPtr       (FlightManager* key){ fmPtr             = key; }
		void clearKeys()						{ displayCount		= 0;
												  firstNameKey		= "";
												  lastNameKey		= "";
					   							  reservationNumKey = 0; 
												  flightNumKey		= 0;   
												  firstPass			= true;
                                                  removePassenger   = false;
                                                  fmPtr             = nullptr;
                                                  if (markedForRemoval != nullptr)
                                                  {
                                                      delete markedForRemoval;
                                                      markedForRemoval = nullptr;
                                                  }}

		void operator()(PassengerData passenger)
		{
			bool match = true;
			if (firstNameKey != "")
				match = match && (firstNameKey		== passenger.getFirstName());
			if (lastNameKey != "")
				match = match && (lastNameKey		== passenger.getLastName());
			if (reservationNumKey != 0)
				match = match && (reservationNumKey == passenger.getReservationNum());
			if (flightNumKey != 0)
				match = match && (flightNumKey		== passenger.getFlightNum());
			if (firstPass)
			{
				cout << "FirstName   LastName    Rsv  Class          Flight\n";
				firstPass = false;
			}
			if (match)
			{
				if (displayCount != 0 && displayCount % 100 == 0)
				{
					cout << "Press Enter to Continue --> ";
					cin.ignore(cin.rdbuf()->in_avail());
					cin.ignore();
					cout << "FirstName   LastName    Rsv  Class          Flight\n";
				}

                cout << passenger;
                displayCount++;
                
                if (removePassenger)
                {
                    markedForRemoval = new PassengerData(passenger);
                }
			}
		}
        
        bool removeMarkedPassenger()
        {
            if (!(markedForRemoval == nullptr))
            {
                try {
                    fmPtr->removePassenger(*markedForRemoval);
                    cout << "\nSuccesfully removed.";
                    return true;
                }
                catch (NotFoundException&  error)
                {
                    cout << error.what() << endl;
                    cout << "\nRemoval failed.";
                }
            }
            else
            {
                cout << "\nRemoval failed.";
            }
            return false;
        }

	private:
		int displayCount;
		string firstNameKey;
		string lastNameKey;
		size_t reservationNumKey;
		size_t flightNumKey;
        bool removePassenger;
		bool firstPass;
        FlightManager* fmPtr;
        PassengerData* markedForRemoval = nullptr;
	};

//
// Begin SearchForFlight nested class.
// CSM20Final
//
// This is a utility class meant to be passed into a traversal function.
//
//
	class SearchForFlight
	{
	public:
		SearchForFlight()						{ clearKeys();			   }

		void setToCity(char key)				{ toCity			= key; }
		void setFromCity(char key)				{ fromCity			= key; }
		void setFlightNum(size_t key)			{ flightNum			= key; }
		void setDisplayPassengers(bool key)		{ displayPassengers = key; }

		void clearKeys()						{ displayCount		= 0;
												  toCity			= 0;
												  fromCity			= 0;
												  flightNum			= 0;   
												  displayPassengers = true;
												  firstPass			= true;}

		void operator()(FlightData data) 
		{
			bool match = true;
			if (toCity != 0)
				match = match && (toCity			== data.getToCity());
			if (fromCity != 0)
				match = match && (fromCity			== data.getFromCity());
			if (flightNum != 0)
				match = match && (flightNum			== data.getFlightNumber());
			if (firstPass)
			{
				cout << "Flight  Origin        Destination   Depart Arrive Mileage\n";
				firstPass = false;
			}
			if (match)
			{
				if (displayCount != 0 && displayCount % 2 == 0)
				{
					cout << "Press Enter to Continue --> ";
					cin.ignore(cin.rdbuf()->in_avail());
					cin.ignore();
				}
				if (displayCount != 0)            
					cout << "Flight  Origin        Destination   Depart Arrive Mileage\n";
				cout << data;

				if (displayPassengers)
				{
					cout << "FirstName   LastName    Rsv  Class          Flight\n";

					vector<PassengerData> passengers = data.getSeatMap();
					for (size_t i = 0; i < passengers.size(); i++)
						cout << passengers[i];

					displayCount++;
					cout << endl;
				}
			}
		}
	private:
		int displayCount;
		char toCity;
		char fromCity;
		size_t flightNum;
		bool displayPassengers, firstPass;
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
    
    bool removePassenger(string, string);
    bool removePassenger(size_t);

	char getCharInput(string field);
	size_t getNumericInput(string field);
    
    void enterToContinue();
};

#endif
