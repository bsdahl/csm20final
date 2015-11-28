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
//#include "FlightManager.h"

using namespace std;

class AirlineInterface
{
public:
    bool displayMenu();
    
private:
    //FlightManager data;
    
    bool displayAllPassengers();
    bool displayPassengersTo(string);
    bool displayPassengersFrom(string);

    bool displayPassengersOnFlt(size_t);
    bool displayWaitFlight(size_t);
    bool displayWaitAll();
    
    bool displayAllFlights();
    bool displayAllFlightsPassengers();
    
    bool searchPassenger(string);
    bool searchFlight(size_t);
};

#endif
