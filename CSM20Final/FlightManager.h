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

private:
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