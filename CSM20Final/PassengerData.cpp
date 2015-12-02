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

PassengerData::PassengerData( size_t reservation, string first, string last,
							  size_t seatClass, size_t flight )
{
	setFirstName(first);
	setLastName(last);
	setMembership(seatClass);
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
	bool check = false;
	if (reservationNum == 0 && rhs.reservationNum == 0)
	{
		if ((firstName != "" && rhs.firstName != "") && (firstName == rhs.firstName))
			check = true;
		if ((lastName != "" && rhs.lastName != "") && (lastName == rhs.lastName))
			check = true;
		if ((seatClass != 0 && rhs.seatClass != 0) && (seatClass == rhs.seatClass))
			check = true;
		if ((flightNum != 0 && rhs.flightNum != 0) && (flightNum == rhs.flightNum))
			check = true;
	}
	else if (reservationNum == rhs.reservationNum)
		check = true;
	else
		check = false;

	return check;
}

const bool PassengerData::operator >(const PassengerData& rhs)
{
	bool check = false;
	if (reservationNum == 0 && rhs.reservationNum == 0)
	{
		if ((firstName != "" && rhs.firstName != "") && (firstName > rhs.firstName))
			check = true;
		if ((lastName != "" && rhs.lastName != "") && (lastName > rhs.lastName))
			check = true;
		if ((seatClass != 0 && rhs.seatClass != 0) && (seatClass > rhs.seatClass))
			check = true;
		if ((flightNum != 0 && rhs.flightNum != 0) && (flightNum > rhs.flightNum))
			check = true;
	}
	else if (reservationNum > rhs.reservationNum)
		check = true;
	else
		check = false;

	return check;
}

const bool PassengerData::operator <(const PassengerData& rhs)
{
	bool check = false;
	if (reservationNum == 0 && rhs.reservationNum == 0)
	{
		if ((firstName != "" && rhs.firstName != "") && (firstName < rhs.firstName))
			check = true;
		if ((lastName != "" && rhs.lastName != "") && (lastName < rhs.lastName))
			check = true;
		if ((seatClass != 0 && rhs.seatClass != 0) && (seatClass < rhs.seatClass))
			check = true;
		if ((flightNum != 0 && rhs.flightNum != 0) && (flightNum < rhs.flightNum))
			check = true;
	}
	else if (reservationNum < rhs.reservationNum)
		check = true;
	else
		check = false;

	return check;
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

	return in;
}

ostream &operator << (ostream & out, const PassengerData & val)
{
	size_t membership = val.getMembership();

	out << val.getFirstName() << " " << val.getLastName() << ", " << val.getReservationNum() << ", ";
	switch (membership)
	{
	case 1:
		out << "Pilot Club";
		break;
	case 2:
		out << "First Class";
		break;
	case 3:
		out << "Business Class";
		break;
	case 4:
		out << "Economy Class";
		break;
	default:
		break;
	}

	out << ", " << val.getFlightNum(); 

	return out;
}
