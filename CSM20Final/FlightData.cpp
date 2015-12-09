#include "FlightData.h"

bool FlightData::addPassenger(const PassengerData& pd) {
	//If flight is full, do not add a passenger and return false
	if (seatMap.size() >= MAX_PASSENGERS) return false;
	seatMap.push_back(pd);
	return true;
}

bool FlightData::findPassenger(const PassengerData& pd) {
	//Look through all passengers in seatMap to find a match
	for (size_t i = 0; i < seatMap.size(); ++i)
		if (seatMap[i] == pd)
			return true;
	return false; //Not found, returns false
}

PassengerData FlightData::removePassenger(const PassengerData& pd) {
	size_t i;
	PassengerData pdRemoved;
	//Search all passengers on flight till a match is found + remove
	for (i = 0; i < seatMap.size(); ++i) {
		if (seatMap[i] == pd) {
			pdRemoved = seatMap[i];
			seatMap.erase(seatMap.begin() + i);
			break;
		}
	}
	//return the removed passenger
	return pdRemoved;
}

std::ostream& operator<<(std::ostream & out, const FlightData& fd) {
	//Format the output, align values, fill with zeros, format time
	out << "  " << std::right << std::setw(4) << std::setfill('0')
		<< fd.flightNumber << "  " << std::setfill(' ')
		<< std::setw(12) << std::left << fd.fromCity << "  "
		<< std::setw(12) << fd.toCity << "  " << std::right
		<< std::setw(2) << std::setfill('0') << fd.departTime / 100
		<< ':' << std::setw(2) << fd.departTime % 100 << "  "
		<< std::setw(2) << fd.arriveTime/ 100
		<< ':' << std::setw(2) << fd.arriveTime % 100
		<< "  " << std::setw(4) << fd.mileage << '\n' << std::setfill('0');
	return out;
}
