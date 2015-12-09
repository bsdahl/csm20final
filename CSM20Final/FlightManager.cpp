//
//  FlightManager.cpp
//  CSM20Final
//
//  Created by Nick Clayton on 11/30/15.
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//
#include <string>

#include "FlightManager.h"

//FlightManager::FlightManager(const std::string& passengerFile, const std::string& flightFile)
FlightManager::FlightManager()
: seatQueue(waitList)
{
	populateMap();  // Gets the map up

	std::string filename = "flightdata.txt";
	std::ifstream input;
	// TODO: have FlightManager read files and put data into trees.
	// Read flight data file and add all flights to list.
	input.open(filename);
	while (!input.good())	// input validation.
	{
		input.close();
		input.clear();
		std::cout << "Flight data file \"" << filename << "\" is corrupted or invalid. Please enter a valid file name: ";
		std::cin >> filename;
		input.open(filename);
	}
	readFlightsFromFile(input);

	// Read passenger data file and add all passengers to list/flights.
	filename = "passengerdata.txt";
	input.open(filename);
	while (!input.good())	// input validation.
	{
		input.close();
		input.clear();
		std::cout << "Passenger data file \"" << filename << "\" is corrupted or invalid. Please enter a valid file name: ";
		std::cin >> filename;
		input.open(filename);
	}
	readPassengersFromFile(input);

}	// End constructor

void FlightManager::readFlightsFromFile(std::ifstream& inputStream)
{
	std::string fieldBuffer, line;
	FlightData newFlight;
	while (!inputStream.eof())
	{
        std::getline(inputStream,line);
        std::stringstream lineStream(line);
        
		std::getline(lineStream, fieldBuffer, ',');	// Flight number
		newFlight.setFlightNumber(std::strtol(fieldBuffer.c_str(), nullptr, 10));
		std::getline(lineStream, fieldBuffer, ',');	// To City
		newFlight.setToCity(fieldBuffer.c_str()[0]);
		std::getline(lineStream, fieldBuffer, ',');	// From City
		newFlight.setFromCity(fieldBuffer.c_str()[0]);
		std::getline(lineStream, fieldBuffer, ',');	// Departure Time
		newFlight.setDepartTime(std::strtol(fieldBuffer.c_str(), nullptr, 10));
		std::getline(lineStream, fieldBuffer, ',');	// Arrival Time
		newFlight.setArriveTime(std::strtol(fieldBuffer.c_str(), nullptr, 10));

		addFlight(newFlight);		// Add new flight to list.
	}
	inputStream.close();
}	// End readFlightsFromFile

void FlightManager::readPassengersFromFile(std::ifstream& inputStream)
{
	std::string fieldBuffer, line;
	PassengerData newPassenger;
	while (!inputStream.eof())
	{
        std::getline(inputStream,line);
        std::stringstream lineStream(line);
        
		std::getline(lineStream, fieldBuffer, ',');	// Reservation number
		newPassenger.setReservationNum(std::strtol(fieldBuffer.c_str(), nullptr, 10));
		std::getline(lineStream, fieldBuffer, ',');	// First name
		newPassenger.setFirstName(fieldBuffer);
		std::getline(lineStream, fieldBuffer, ',');	// Last name
		newPassenger.setLastName(fieldBuffer);
		std::getline(lineStream, fieldBuffer, ',');	// Flight number
		newPassenger.setFlightNum(std::strtol(fieldBuffer.c_str(), nullptr, 10));
		std::getline(lineStream, fieldBuffer, ',');	// Membership value
		newPassenger.setMembership(std::strtol(fieldBuffer.c_str(), nullptr, 10));

		addPassenger(newPassenger);		// Add new passenger to list.
	}
	inputStream.close();
}	// End readPassengersFromFile


void FlightManager::calculateMileage(FLIGHT_DATA_TYPE& flight)
{
	// Gets from-and-to cities and determines the shortest path using shortestPath (from flightMap)
	flight.setMileage(Map.shortestPath(flight.getFromCity(), flight.getToCity()));

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
		return false;
	}
}	// End addPassenger

PASS_DATA_TYPE FlightManager::removePassenger(const PASS_DATA_TYPE& aPassenger)	throw (NotFoundException)
{
	if (passengerList.contains(aPassenger))
	{
		PassengerData removedPassenger = passengerList.getEntry(aPassenger);
		size_t flightNumber = removedPassenger.getFlightNum();
		FlightData flightBuffer;
		flightBuffer.setFlightNumber(flightNumber);

		if (waitList.contains(removedPassenger))	// If passenger is waitlisted, remove them from the waitlist.
		{
			waitList.remove(removedPassenger);
		}
		else if (flightList.contains(flightBuffer))	// If passenger is not on waitlist, temporarily remove flight containing the passenger from list.
		{
			flightBuffer = flightList.getEntry(flightBuffer);
			flightList.remove(flightBuffer);

			flightBuffer.removePassenger(aPassenger);		// remove passenger from flight.

			// If there is a passenger waitlisted for the flight, add them to the flight.
			if (!waitList.isEmpty())
			{
				nextFromWaitlist next(flightNumber);
				waitList.inorderTraverse(next);		// Find next passenger.
				if (next.found())	// Check if a passenger was found.
				{
					// Add waitlisted passenger to flight and requeue passengers.
					if (flightBuffer.getBounceCount() > 0)
						flightBuffer.decBounceCount();	// If there have been any bounced passengers, decrement the bounced count for the flight.
					seatQueue.setFlight(flightBuffer);
					seatQueue.add(next.get());
					seatQueue.finalizeSeating();
					waitList.remove(next.get());
				}
			}
			// re-add flight to list.
			flightList.add(flightBuffer);
		}
		else
			throw NotFoundException("\n\nPassenger's flight does not exist. Cannot remove passenger.\n\n");

		// Remove specified passenger from list of passengers.
		passengerList.remove(removedPassenger);

		return removedPassenger;
	}
	else
	{
		throw NotFoundException("\n\nPassenger does not exist. Cannot remove passenger.\n\n");
	}
}	// End removePassenger

/* populateMap()
Will create the map by adding the vertices (cities) with
edges
input: none
output: none
*/
void FlightManager::populateMap()
{
	// parameters are: the two vertices and the edge weight
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

}  // end populateMap()