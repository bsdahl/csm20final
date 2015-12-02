#ifndef _SeatingQueue
#define _SeatingQueue

#include <vector>
#include <queue>

#include "PassengerData.h"
#include "FlightData.h"
#include "AVLTree.h"


class SeatingQueue
{
private:
	/////////////////////////////
	// Private Utility Classes //
	/////////////////////////////
	class compareMembership	// should sort memberships from lowest number to highest number
	{
	public:
		bool operator()(const PassengerData& passenger1, const PassengerData& passenger2) { return passenger1.getMembership() > passenger2.getMembership(); }
	};

	//////////////////////////
	// Private Data Members //
	//////////////////////////
	static const size_t MAX_PILOT_CLASS = 3;
	static const size_t MAX_FIRST_CLASS = 5;
	static const size_t MAX_BUSI_CLASS = 5;
	static const size_t MAX_ECON_CLASS = 27;
	static const size_t MAX_BOUNCED = 10;
	static const size_t MAX_SEATS = 40;
	static const size_t PILOT_CLASS = 1;
	static const size_t FIRST_CLASS = 2;
	static const size_t BUSI_CLASS = 3;

	std::priority_queue<PassengerData, std::vector<PassengerData>, compareMembership > seatQueue;
	AVLTree<PassengerData>* waitListPtr;	// A pointer to the AVL tree used to store waitlisted passengers
	FlightData* flightPtr;		// A pointer to the FlightData object that passengers are to be added to.

	///////////////////////////////
	// Private Utility Functions //
	///////////////////////////////

public:
	////////////////////////////
	// Constructor/Destructor //
	////////////////////////////
	SeatingQueue(AVLTree<PassengerData>& waitList) : waitListPtr(&waitList), flightPtr(nullptr) { }	// requires an AVL tree of passengers in which to store excess passengers

	////////////////////////////////
	// Public Interface Functions //
	////////////////////////////////
	bool push(const PassengerData& newPassenger);
	void pop() { seatQueue.pop(); }
	void setFlight(FlightData& aFlight);
	void queueCurrentPassengers();
	bool empty() { return seatQueue.empty(); }
	bool isFull() { return seatQueue.size() > MAX_SEATS; }
	void inputFlight(const FlightData& aFlight);
	void clear();
	std::vector<PassengerData> finalizeSeating();
};



#endif