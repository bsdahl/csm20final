#include "FlightData.h"

bool FlightData::addPassenger(const PassengerData& pd) {
	if (seatMap.size() >= MAX_PASSENGERS) return false;
	seatMap.push_back(pd);
	return true;
}

bool FlightData::findPassenger(const PassengerData& pd) {
	for (size_t i = 0; i < seatMap.size(); ++i)
		if (seatMap[i] == pd)
			return true;
	return false;
}

PassengerData FlightData::removePassenger(const PassengerData& pd) {
	size_t i;
	PassengerData pdRemoved;
	for (i = 0; i < seatMap.size(); ++i) {
		if (seatMap[i] == pd) {
			pdRemoved = seatMap[i];
			seatMap.erase(seatMap.begin() + i);
			break;
		}
	}
	return pdRemoved;
}

std::ostream& operator<<(std::ostream & out, const FlightData& fd) {
	char prev(' ');

	out << "  " << std::right << std::setw(4) << std::setfill('0')
		<< fd.flightNumber << "  " << std::setfill(' ')
		<< std::setw(12) << std::left << fd.fromCity << "  "
		<< std::setw(12) << fd.toCity << "  " << std::right
		<< std::setw(2) << std::setfill('0') << fd.departTime / 100
		<< ':' << std::setw(2) << fd.departTime % 100 << "  "
		<< std::setw(2) << fd.arriveTime/ 100
		<< ':' << std::setw(2) << fd.arriveTime % 100
		<< "  " << std::setw(4) << fd.mileage << '\n';
	cout.fill(prev);  // to reset setfill()
	return out;
}
