//
//  FlightManager.h
//  CSM20Final
//
//  Created by Nick Clayton on 11/30/15.
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//

#ifndef _FlightManager
#define _FlightManager

#define PASS_DATA_TYPE int		// TODO: change placeholder type to passenger data type when available
#define FLIGHT_DATA_TYPE float	// TODO: change placeholder type to flight data type when available

#include <iostream>
#include <vector>
#include <fstream>

#include "AVLTree.h"
#include "ListSearch.h"
#include "flightMap.h"

class FlightManager
{
public:
	/////////////////////////////
	// Constructors/Destructor //
	/////////////////////////////
	FlightManager() {}
	~FlightManager() {}

	////////////////////////////////
	// Public Interface Functions //
	////////////////////////////////
	bool search(const PASS_DATA_TYPE&);
	bool search(const FLIGHT_DATA_TYPE&);
	void addPassenger(const PASS_DATA_TYPE& passenger);
	void addFlight(FLIGHT_DATA_TYPE& flight);

private:
	//////////////////////////
	// Private Data Members //
	//////////////////////////
	AVLTree<PASS_DATA_TYPE> passengerList;
	AVLTree<FLIGHT_DATA_TYPE> flightList;
	AVLTree<PASS_DATA_TYPE> waitList;
	//flightMap Map;
	ListSearch<PASS_DATA_TYPE> passengerSearch;
	ListSearch<FLIGHT_DATA_TYPE> flightSearch;

	///////////////////////////////
	// Private Utility Functions //
	///////////////////////////////
	void calculateMileage(FLIGHT_DATA_TYPE&);
};


#endif