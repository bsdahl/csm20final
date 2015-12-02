#include "SeatingQueue.h"

void SeatingQueue::setFlight(FlightData& aFlight)
{
	clear();
	flightPtr = &aFlight;
	queueCurrentPassengers();
}	// End setFlight

void SeatingQueue::queueCurrentPassengers()
{
	if (flightPtr != nullptr)
	{
		std::vector<PassengerData> seatVector = flightPtr->getSeatMap();
		std::reverse(seatVector.begin(), seatVector.end());
		while (!seatVector.empty())
		{
			seatQueue.push(seatVector.back());
			seatVector.pop_back();
		}
	}
}	// End queueCurrentPassengers

void SeatingQueue::clear()
{
	while (!seatQueue.empty())
		seatQueue.pop();
	flightPtr = nullptr;
}	// End clear

bool SeatingQueue::push(const PassengerData& newPassenger)
{
	if (flightPtr == nullptr)
	{
		std::cout << "\n\nError: Seating queue does not have a flight to populate. Please set a flight to populate.\n\n";
		return false;
	}

	seatQueue.push(newPassenger);	// enqueue the new passenger
	return true;
}	// End push

void SeatingQueue::finalizeSeating()
{
	std::vector<PassengerData> seating;

	// Reseat all passengers.
	while (!seatQueue.empty() && (seating.size() < MAX_SEATS))
	{
		size_t pilotC = 0;
		size_t firstC = 0;
		size_t busiC = 0;
		size_t econC = 0;
		size_t topSeat = seatQueue.top().getMembership();
		if (topSeat == PILOT_CLASS && pilotC < MAX_PILOT_CLASS)	// If passenger is pilot class, and pilot class seats are not full,
		{														//  increment pilot class counter and add passenger to flight.
			pilotC++;
			seating.push_back(seatQueue.top());
			seatQueue.pop();
		}
		else if (topSeat <= FIRST_CLASS && firstC < MAX_FIRST_CLASS)	// If passenger is pilot or first class, and first class seats are not full, 
		{																//  increment first class counter and add passenger to flight.
			if (topSeat < FIRST_CLASS)
			if (flightPtr != nullptr)
				flightPtr->incBounceCount();									// If passenger is of higher class, increment bounced counter.
			firstC++;
			seating.push_back(seatQueue.top());
			seatQueue.pop();
		}
		else if (topSeat <= BUSI_CLASS && busiC < MAX_BUSI_CLASS)	// If passenger is business class or better, and business class seats are not full,
		{															//  increment business class counter and add passenger to flight.
			if (topSeat < BUSI_CLASS)
			if (flightPtr != nullptr)
				flightPtr->incBounceCount();								// If passenger is of higher class, increment bounced counter.
			busiC++;
			seating.push_back(seatQueue.top());
		}
		else if (econC < MAX_ECON_CLASS && seating.size() < MAX_SEATS)	// If passenger is economy class, or is overflow, and flight is not full,
		{																//  add passenger to flight.
			if (flightPtr != nullptr)
			if (topSeat <= BUSI_CLASS && flightPtr->getBounceCount() >= MAX_BOUNCED)		// If passenger is from a higher class, and the maximum number of passengers has been
				waitListPtr->add(seatQueue.top());											//  bounced, send passenger to the wait list.
			else
				seating.push_back(seatQueue.top());
			seatQueue.pop();
		}
		else		// If passenger matches none of the above criteria, add to waitlist.
		{
			waitListPtr->add(seatQueue.top());
			seatQueue.pop();
		}
	}

	flightPtr->setSeatMap(seating);
}	// End finalizeSeating