#include "SeatingQueue.h"

std::vector<PassengerData> SeatingQueue::finalizeSeating()
{
	std::vector<PassengerData> seating;

	while (!seatQueue.empty() && (seating.size() < MAX_SEATS))
	{
		size_t pilotC = 0;
		size_t firstC = 0;
		size_t busiC = 0;
		size_t econC = 0;
		size_t bounced = 0;
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
				bounced++;												// If passenger is of higher class, increment bounced counter.
			firstC++;
			seating.push_back(seatQueue.top());
			seatQueue.pop();
		}
		else if (topSeat <= BUSI_CLASS && busiC < MAX_BUSI_CLASS)	// If passenger is business class or better, and business class seats are not full,
		{															//  increment business class counter and add passenger to flight.
			if (topSeat < BUSI_CLASS)
				bounced++;											// If passenger is of higher class, increment bounced counter.
			busiC++;
			seating.push_back(seatQueue.top());
		}
		else if (econC < MAX_ECON_CLASS && seating.size() < MAX_SEATS)	// If passenger is economy class, or is overflow, and flight is not full,
		{																//  add passenger to flight.
			if (topSeat <= BUSI_CLASS && bounced >= MAX_BOUNCED)		// If passenger is from a higher class, and the maximum number of passengers has been
			{															//  bounced, send passenger to the wait list.
				waitListPtr->add(seatQueue.top());
			}
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

	return seating;
}