//
//  FlightManager.cpp
//  CSM20Final
//
//  Created by Nick Clayton on 11/30/15.
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//
#include <string>

#include "FlightManager.h"

FlightManager::FlightManager(const std::string& passengerFile, const std::string& flightFile)
: seatQueue(waitList)
{
	// TODO: have FlightManager read files and put data into trees.
}


void FlightManager::calculateMileage(FLIGHT_DATA_TYPE& flight)
{
	//std::string origin = flight.getFrom();					// Get origin node.
	//std::string destination = flight.getTo();					// Get end node.

	//size_t distance = Map.shortestPath(origin,desitnation);	// Get the shortest path between the nodes.

	//flight.setMileage(distance);								// Set flight mileage to distance.
}	// End calculateMileage;

void FlightManager::addFlight(FLIGHT_DATA_TYPE& flight)
{
	calculateMileage(flight);	// calculate and set the mileage of the new flight.
	flightList.add(flight);		// add new flight to AVL tree.

	// TODO: have flight manager search existing passengers to see if they are on new flight, then add them according to flight queue
	
}	// End addFlight

void FlightManager::addPassenger(const PASS_DATA_TYPE& passenger)
{
	passengerList.add(passenger);	// Add passenger to list.
	
	FLIGHT_DATA_TYPE temp;
	temp.setFlightNumber(passenger.getFlightNum());	// Create a temporary flight object using the passenger's given flight number; used for searching available flights.
	if (flightList.contains(temp))										// If the flight exists, do the following:
	{
		temp = flightList.getEntry(temp);					// Set temp to the matching flight.
		flightList.remove(temp);							// Remove the matching flight from the flight list.
		// TODO: put all current passengers into priority queue, add new passenger to queue, then re-add passengers to flight.
		// Put all current passengers into priority queue.
		std::vector<PassengerData> seatVector = temp.getSeatMap();
		std::reverse(seatVector.begin(), seatVector.end());
		while (!seatVector.empty())
		{
			seatQueue.push(seatVector.back());
			seatVector.pop_back();
		}
		// Add new passenger to queue.
		seatQueue.push(passenger);
		// Create new seating vector
		seatVector = seatQueue.finalizeSeating();
		// Re-add all passengers to flight.
	}
}	// End addPassenger