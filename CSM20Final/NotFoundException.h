/****************************************************
	Not Found Exception Class

	Topic D Project

	CS M20
*****************************************************/

#ifndef _NOT_FOUND_EXCEP
#define _NOT_FOUND_EXCEP

#include <stdexcept>
#include <string>

using namespace std;

class NotFoundException : public logic_error
{
public:
	NotFoundException(const string& message = ""): logic_error("Not Found Exception: " + message) {}
}; // end NotFoundExcep

#endif