//
//	PassengerData.h
//	CSM20 Final
//
//	Created by Jake Lyon on 11/27/2015
//	Copyright © 2015 CSM20Final. All rights reserved.
//

#ifndef PASSENGER_DATA_H
#define PASSENGER_DATA_H

#include <iostream>

#include "PrecondViolatedExcep.h"

class PassengerData
{
public:
	////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////
	PassengerData( size_t reservation = 0, std::string first = "", std::string last = "",
				   size_t seatClass = 0, size_t flight = 0);

	////////////////////////////////////////////
	// Public Interface Functions
	////////////////////////////////////////////
	void setFirstName	  ( const std::string first )
								throw(PrecondViolatedExcep);
	void setLastName	  ( const std::string last )
								throw(PrecondViolatedExcep);
	void setMembership	  ( const size_t seatClass );
	void setReservationNum( const size_t reservation );
	void setFlightNum	  ( const size_t flight );

	const std::string	getFirstName()		const { return firstName; }
	const std::string	getLastName()		const { return lastName;  }
	const size_t		getMembership()		const { return seatClass; }
	const size_t		getReservationNum() const { return reservationNum; }
	const size_t		getFlightNum()		const { return flightNum; }

	///////////////////////////////////////////
	// Overloaded operators
	///////////////////////////////////////////
	const bool operator == (const PassengerData & rhs);
	const bool operator >  (const PassengerData & rhs);
	const bool operator <  (const PassengerData & rhs);

private:
	///////////////////////////////////////////
	// Copy constructor and assignment operator
	// Set to private to prevent copies
	///////////////////////////////////////////
	PassengerData ( const PassengerData & ) {}
	PassengerData & operator = ( const PassengerData & rhs ) {}

	///////////////////////////////////////////
	// Helper function and class data members
	///////////////////////////////////////////
	bool nameCheck ( std::string name );

	std::string firstName;
	std::string lastName;
	size_t		seatClass;
	size_t		reservationNum;
	size_t		flightNum;
};

///////////////////////////////////////////////
// Overloaded Input/Output operators
///////////////////////////////////////////////
std::istream & operator >>( istream & in,  PassengerData & val );
std::ostream & operator <<( ostream & out, const PassengerData & val );

#endif
