//
//  FlightManager.cpp
//  CSM20Final
//
//  Created by Nick Clayton on 11/30/15.
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//
#include <string>

#include "FlightManager.h"

// Constructor
FlightManager::FlightManager()
{
	populateMap(); // Gets the map up
}

void FlightManager::calculateMileage(FLIGHT_DATA_TYPE& flight)
{
	//std::string origin = flight.getFrom();					// Get origin node.
	//std::string destination = flight.getTo();					// Get end node.

	//size_t distance = Map.shortestPath(origin,desitnation);	// Get the shortest path between the nodes.

	//flight.setMileage(distance);								// Set flight mileage to distance.
}	// End calculateMileage;

bool FlightManager::search(const PASS_DATA_TYPE& criteria)	// Accepts a Passenger object; returns true or false.
{
	passengerSearch.setSearchCriteria(criteria);	// set search criteria for passenger.
	passengerList.inorderTraverse(passengerSearch);	// Traverse flight AVL tree while searching for entered criteria
	if (passengerSearch.found())					// If any results are found, display them, clear the results vector, and return true.
	{
		passengerSearch.displayResults();
		passengerSearch.clearResults();
		return true;
	}
	else											// If no results are found, return false.
		return false;
}	// End search (passenger)

bool FlightManager::search(const FLIGHT_DATA_TYPE& criteria)	// Accepts a Flight object; returns true or false.
{
	flightSearch.setSearchCriteria(criteria);	// set search criteria for flight.
	flightList.inorderTraverse(flightSearch);	// Traverse flight AVL tree while searching for entered criteria
	if (flightSearch.found())					// If any results are found, display them, clear the results vector, and return true.
	{
		flightSearch.displayResults();
		flightSearch.clearResults();
		return true;
	} 
	else										// If no results are found, return false.
		return false;
}	// End search (flight)


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
	//temp.setFlightNumber(passenger.getFlightNumber());	// Create a temporary flight object using the passenger's given flight number; used for searching available flights.
	if (search(temp))										// If the flight exists, do the following:
	{
		passengerSearch.clearResults();						// Clear results of search
		temp = flightList.getEntry(temp);					// Set temp to the matching flight.
		flightList.remove(temp);							// Remove the matching flight from the flight list.
		// TODO: put all current passengers into priority queue, add new passenger to queue, then re-add passengers to flight.
		// Put all current passengers into priority queue.
		// Add new passenger to queue.
		// Re-add all passengers to flight.
	}
}	// End addPassenger

/* populateMap()
Will create the map by adding the vertices (cities) with edges
input: none
output: none
*/
void FlightManager::populateMap()
{
	// Hardcoded map data
	Map.add('B', 'A', 142);
	Map.add('A', 'C', 170);
	Map.add('C', 'D', 114);
	Map.add('D', 'E', 93);
	Map.add('D', 'M', 209);
	Map.add('M', 'N', 208);
	Map.add('N', 'P', 134);
	Map.add('P', 'O', 193);
	Map.add('E', 'F', 155);
	Map.add('F', 'I', 160);
	Map.add('F', 'G', 184);
	Map.add('I', 'G', 83);
	Map.add('I', 'L', 88);
	Map.add('I', 'J', 73);
}