#pragma once

#include <vector>
#include "PassengerData.h"

class FlightData {
private:
	const size_t MAX_PASSENGERS = 40;
	size_t flightNumber, mileage, departTime, arriveTime;
	char toCity, fromCity;
	std::vector<PassengerData> seatMap;
	FlightData(const FlightData& other) { }
public:
	FlightData(size_t fn, size_t miles, size_t departTime,
		size_t arriveTime, char toc, char frc)
		: flightNumber(fn), mileage(miles),	departTime(departTime),
		arriveTime(arriveTime), toCity(toc), fromCity(frc) { }
	void setFlightNumber(size_t fn) { flightNumber = fn; }
	void setMileage(size_t miles) { mileage = miles; }
	void setDepartTime(size_t time) { departTime = time; }
	void setArriveTime(size_t time) { arriveTime = time; }
	void setToCity(char city) { toCity = city; }
	void setFromCity(char city) { fromCity = city; }
	size_t getMaxPassengers() { return MAX_PASSENGERS; }
	size_t getFlightNumber() { return flightNumber; }
	size_t mileage() { return mileage; }
	size_t departureTime() { return departTime; }
	size_t arrivalTime() { return arriveTime; }
	char getToCity() { return toCity; }
	char getFromCity() { return fromCity; }
	size_t fullSeats() { return seatMap.size(); }
	size_t freeSeats() { return MAX_PASSENGERS - seatMap.size(); }
	bool operator==(const FlightData& right) const {
		return flightNumber == right.flightNumber;
	}
	bool operator>(const FlightData& right) const {
		return flightNumber > right.flightNumber;
	}
	bool operator<(const FlightData& right) const {
		return flightNumber < right.flightNumber;
	}
	bool addPassenger(const PassengerData& pd);
	bool findPassenger(const PassengerData& pd);
	PassengerData& removePassenger(const PassengerData& pd);

};