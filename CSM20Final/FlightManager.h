//
//  FlightManager.h
//  CSM20Final
//
//  Created by Nick Clayton on 11/30/15.
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//

#ifndef _FlightManager
#define _FlightManager


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>

#include "AVLTree.h"
#include "flightMap.h"
#include "PassengerData.h"
#include "FlightData.h"
#include "SeatingQueue.h"
#include "NotFoundException.h"

#define PASS_DATA_TYPE PassengerData		// TODO: change placeholder type to passenger data type when available
#define FLIGHT_DATA_TYPE FlightData		// TODO: change placeholder type to flight data type when available


class FlightManager
{
public:
	/////////////////////////////
	// Constructors/Destructor //
	/////////////////////////////
	//FlightManager() : seatQueue(waitList) {}
	//FlightManager(const std::string& passengerFile, const std::string& flightFile);
	FlightManager();  // Added default constructor
	~FlightManager() {}

	////////////////////////////////
	// Public Interface Functions //
	////////////////////////////////
	template<class Function>
	void traversePassenger(Function& fxn) { passengerList.inorderTraverse(fxn); }
	template<class Function>
	void traverseFlight(Function& fxn) { flightList.inorderTraverse(fxn); }
	template<class Function>
	void traverseWait(Function& fxn) { waitList.inorderTraverse(fxn); }

	bool addPassenger(const PASS_DATA_TYPE&);
	void addFlight(FLIGHT_DATA_TYPE& flight);
	PASS_DATA_TYPE removePassenger(const PASS_DATA_TYPE&) throw (NotFoundException);


private:
	/////////////////////////////
	// Private Utility Classes //
	/////////////////////////////
	class nextFromWaitlist		// used for finding the next, highest membership, waitlisted passenger for a specified flight.
	{
	private:
		size_t flightNum;
		PASS_DATA_TYPE* nextPassenger;
	public:
		nextFromWaitlist(const size_t& flightNumber) : flightNum(flightNumber), nextPassenger(nullptr) {}
		~nextFromWaitlist() { delete nextPassenger; nextPassenger = nullptr; }
		void operator()(const PASS_DATA_TYPE& aPassenger)
		{
			if (aPassenger.getFlightNum() == flightNum)
			{
				if (nextPassenger == nullptr)
					nextPassenger = new PassengerData(aPassenger);
				if (aPassenger.getMembership() < nextPassenger->getMembership())
				{
					*nextPassenger = aPassenger;
				}
			}
		}
		PASS_DATA_TYPE get() { return *nextPassenger; }
		bool found() { return nextPassenger != nullptr;  }
	};

	//////////////////////////
	// Private Data Members //
	//////////////////////////
	AVLTree<PASS_DATA_TYPE> passengerList;
	AVLTree<FLIGHT_DATA_TYPE> flightList;
	AVLTree<PASS_DATA_TYPE> waitList;
	flightMap<char> Map;
	SeatingQueue seatQueue;


	///////////////////////////////
	// Private Utility Functions //
	///////////////////////////////
	void calculateMileage(FLIGHT_DATA_TYPE&);
	void readFlightsFromFile(std::ifstream&);
	void readPassengersFromFile(std::ifstream&);
	void populateMap();

};


#endif