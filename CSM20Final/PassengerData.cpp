//
//	PassengerData.h
//	CSM20 Final
//
//	Created by Jake Lyon on 11/27/2015
//	Copyright © 2015 CSM20Final. All rights reserved.
//

#include <string>

using namespace std;

#include "PassengerData.h"

PassengerData::PassengerData( string first, string last, size_t Membership,
							  size_t reservation, size_t flight )
{
	setFirstName(first);
	setLastName(last);
	setMembership(Membership);
	setReservationNum(reservation);
	setFlightNum(flight);
}

void PassengerData::setFirstName(string first)
{
	if (nameCheck(first))
	{
		firstName = first;
	}
	else
	{
		throw PrecondViolatedExcep("Invalid Name: Name must consist of alphabetic characters.");
	}
}

void PassengerData::setLastName(string last)
{
	if (nameCheck(last))
	{
		lastName = last;
	}
	else
	{
		throw PrecondViolatedExcep("Invalid Name: Name must consist of alphabetic characters.");
	}
}

void PassengerData::setMembership(const size_t seatClass)
{
	if (seatClass > 4 || seatClass == 0)
		throw PrecondViolatedExcep("Invalid seating: Seating class is represented by a value of 1-4");

	this->seatClass = seatClass;
}

void PassengerData::setReservationNum(const size_t reservation)
{
	if (reservation == 0)
		throw PrecondViolatedExcep("Invalid reservation number: Reservation number must be greater than 0");

	reservationNum = reservation;
}

void PassengerData::setFlightNum(const size_t flight)
{
	if (flightNum == 0)
		throw PrecondViolatedExcep("Invalid Flight Number: Flight number must be greater than 0");

	flightNum = flight;
}

const bool PassengerData::operator ==(const PassengerData& rhs)
{
	return (getReservationNum() == rhs.getReservationNum());
}

const bool PassengerData::operator >(const PassengerData& rhs)
{
	return (getReservationNum() > rhs.getReservationNum());
}

const bool PassengerData::operator <(const PassengerData& rhs)
{
	return (getReservationNum() < rhs.getReservationNum());
}

bool PassengerData::nameCheck(string name)
{
	bool nameOK = true;
	while (nameOK)
	{
		for (char ch : name)
			nameOK = isalpha(ch);
	}

	return nameOK;
}

istream & operator >> (istream &in, PassengerData &val)
{
	string buf;
	int iBuf;

	getline(in, buf, ',');
	val.setReservationNum(stol(buf));

	getline(in, buf, ',');
	val.setFirstName(buf);

	getline(in, buf, ',');
	val.setLastName(buf);

	getline(in, buf, ',');
	val.setFlightNum(stol(buf));

	getline(in, buf, ',');
	val.setMembership(stol(buf));
}

ostream &operator << (ostream & out, const PassengerData & val)
{
	out << val.getFirstName() << " " << val.getLastName << ", " << val.getReservationNum() << ", "
		<< val.getMembership() << ", " << val.getFlightNum();
}
