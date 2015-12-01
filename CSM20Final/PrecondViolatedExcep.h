// PrecondViolatedExcep.h
// Right group
// CS M20
// Final Project

#ifndef PRECONDVIOLATEDEXCEP_H
#define PRECONDVIOLATEDEXCEP_H

#include <stdexcept>
#include <string>

using namespace std;

// Class to handle our exceptions

class PrecondViolatedExcep : public logic_error
{
public:
	PrecondViolatedExcep(const string & message = "")
		: logic_error("Precondition Violated Excpetion: " + message)
	{}

};

#endif
