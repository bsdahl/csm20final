#pragma once

#include <vector>		//For seatMap
#include <iostream>		//For cout
#include <iomanip>		//For setw, setfill
#include "PassengerData.h"

class FlightData {
private:

	//Max number of passengers in a flight
	static const size_t MAX_PASSENGERS = 40;

	//Unique flight number 
	size_t flightNumber;

	//Departure and arrival time, format: HHMM
	size_t departTime, arriveTime;

	//Keep track of number of passengers bounced from flight
	size_t bounced = 0;

	//Shortest path mileage
	size_t mileage;

	//Characters to represent the cities
	char toCity, fromCity;

	//List of passengers on the flight
	std::vector<PassengerData> seatMap;

public:

	//Constructor
	FlightData(size_t fn = 0, size_t miles = 0, size_t departTime = 0,
		size_t arriveTime = 0, char toc = '0', char frc = '0')
		: flightNumber(fn), mileage(miles), departTime(departTime),
		arriveTime(arriveTime), toCity(toc), fromCity(frc) { }

	//Operator overloads
	bool operator==(const FlightData& right) const {
		return flightNumber == right.flightNumber;
	}
	bool operator>(const FlightData& right) const {
		return flightNumber > right.flightNumber;
	}
	bool operator<(const FlightData& right) const {
		return flightNumber < right.flightNumber;
	}
	friend std::ostream& operator<<(std::ostream& out, const FlightData& fd);

	//Set functions
	void setFlightNumber(size_t fn) { flightNumber = fn; }
	void setMileage(size_t miles) { mileage = miles; }
	void setDepartTime(size_t time) { departTime = time; }
	void setArriveTime(size_t time) { arriveTime = time; }
	void setToCity(char city) { toCity = city; }
	void setFromCity(char city) { fromCity = city; }
	void setSeatMap(const std::vector<PassengerData>& sm) { seatMap = sm; }

	//Get functions
	size_t getMaxPassengers() { return MAX_PASSENGERS; }
	size_t getFlightNumber() { return flightNumber; }
	size_t getMileage() { return mileage; }
	size_t departureTime() { return departTime; }
	size_t arrivalTime() { return arriveTime; }
	size_t fullSeats() { return seatMap.size(); }
	size_t freeSeats() { return MAX_PASSENGERS - seatMap.size(); }
	size_t getBounceCount() { return bounced; }
	char getToCity() { return toCity; }
	char getFromCity() { return fromCity; }
	std::vector<PassengerData> getSeatMap() { return seatMap; }

	//Bounce count
	void incBounceCount() { bounced++; }
	void decBounceCount() { bounced--; }

	//Passenger list modify
	bool addPassenger(const PassengerData& pd);
	bool findPassenger(const PassengerData& pd);
	PassengerData removePassenger(const PassengerData& pd);

};
