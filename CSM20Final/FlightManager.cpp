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
	std::string filename = flightFile;
	std::ifstream input;
	// TODO: have FlightManager read files and put data into trees.
	// Read flight data file and add all flights to list.
	input.open(filename);
	while (!input.good())	// input validation.
	{
		input.close();
		input.clear();
		std::cout << "Flight data file \"" << flightFile << "\" is corrupted or invalid. Please enter a valid file name: ";
		std::cin >> filename;
		input.open(filename);
	}
	readFlightsFromFile(input);

	// Read passenger data file and add all passengers to list/flights.
	filename = passengerFile;
	input.open(filename);
	while (!input.good())	// input validation.
	{
		input.close();
		input.clear();
		std::cout << "Flight data file \"" << passengerFile << "\" is corrupted or invalid. Please enter a valid file name: ";
		std::cin >> filename;
		input.open(filename);
	}
	readPassengersFromFile(input);
}	// End constructor

void FlightManager::readFlightsFromFile(std::ifstream& inputStream)
{
	std::string fieldBuffer;
	FlightData newFlight;
	while (!inputStream.eof())
	{
		std::getline(inputStream, fieldBuffer, ',');	// Flight number
		newFlight.setFlightNumber(std::strtol(fieldBuffer.c_str(), nullptr, 10));
		std::getline(inputStream, fieldBuffer, ',');	// To City
		newFlight.setToCity(fieldBuffer.c_str()[0]);
		std::getline(inputStream, fieldBuffer, ',');	// From City
		newFlight.setFromCity(fieldBuffer.c_str()[0]);
		std::getline(inputStream, fieldBuffer, ',');	// Departure Time
		newFlight.setDepartTime(std::strtol(fieldBuffer.c_str(), nullptr, 10));
		std::getline(inputStream, fieldBuffer, ',');	// Arrival Time
		newFlight.setArriveTime(std::strtol(fieldBuffer.c_str(), nullptr, 10));

		addFlight(newFlight);		// Add new flight to list.
	}
	inputStream.close();
}	// End readFlightsFromFile

void FlightManager::readPassengersFromFile(std::ifstream& inputStream)
{
	std::string fieldBuffer;
	PassengerData newPassenger;
	while (!inputStream.eof())
	{
		std::getline(inputStream, fieldBuffer, ',');	// Reservation number
		newPassenger.setReservationNum(std::strtol(fieldBuffer.c_str(), nullptr, 10));
		std::getline(inputStream, fieldBuffer, ',');	// First name
		newPassenger.setFirstName(fieldBuffer);
		std::getline(inputStream, fieldBuffer, ',');	// Last name
		newPassenger.setLastName(fieldBuffer);
		std::getline(inputStream, fieldBuffer, ',');	// Flight number
		newPassenger.setFlightNum(std::strtol(fieldBuffer.c_str(), nullptr, 10));
		std::getline(inputStream, fieldBuffer, ',');	// Membership value
		newPassenger.setMembership(std::strtol(fieldBuffer.c_str(), nullptr, 10));

		addPassenger(newPassenger);		// Add new passenger to list.
	}
	inputStream.close();
}	// End readPassengersFromFile


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
}	// End addFlight

bool FlightManager::addPassenger(const PASS_DATA_TYPE& passenger)	// Will not allow passengers to be added to list unless a matching flight number exists in the flight list.
{
	
	FLIGHT_DATA_TYPE flightBuffer;
	flightBuffer.setFlightNumber(passenger.getFlightNum());	// Create a temporary flight object using the passenger's given flight number; used for searching available flights.
	if (flightList.contains(flightBuffer))					// If the flight number exists, do the following:
	{
		passengerList.add(passenger);	// Add passenger to list.

		flightBuffer = flightList.getEntry(flightBuffer);			// Set buffer to the matching flight.
		flightList.remove(flightBuffer);							// Remove the matching flight from the flight list.

		// Put all current passengers into priority queue.
		seatQueue.setFlight(flightBuffer);
		
		// Add new passenger to queue.
		seatQueue.add(passenger);
		
		// Create new seating vector and add passengers to flight/waitlist
		seatQueue.finalizeSeating();

		// re-add flight to list
		flightList.add(flightBuffer);

		return true;
	}
	else
	{
		std::cout << "\n\nError: Passenger's flight number does not match any existing flights. Passenger not added to list.\n\n";
	}
}	// End addPassenger