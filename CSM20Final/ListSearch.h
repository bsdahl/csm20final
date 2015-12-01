//
//  ListSearch.h
//  CSM20Final
//
//  Created by Nick Clayton on 11/30/15.
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//

#ifndef _ListSearch
#define _ListSearch


template<class Type>
class ListSearch
{
public:
	/////////////////////////////
	// Constructors/Destructor //
	/////////////////////////////
	ListSearch() : criteria() {};	// Default constructor sets criteria to default object of template type.
	~ListSearch() {};

	////////////////////////////////
	// Public Interface Functions //
	////////////////////////////////
	void displayResults();
	void setSearchCriteria(const Type& search) { criteria = search; }	// Set search criteria
	bool found() { return (!results.empty()); }
	void clearResults() { results.clear(); }

	////////////////////////
	// Operator Overloads //
	////////////////////////
	void operator()(const Type&);

private:
	//////////////////////////
	// Private Data Members //
	//////////////////////////
	std::vector<Type> results;
	Type criteria;
};

template<class Type>
void ListSearch<Type>::displayResults()		// Outputs all elements of results vector. Displays an error if results vector is empty.
{
	if (!results.empty)
	{
		for (int i = 0; i < results.size(); i++)
			std::cout << results[i] << std::endl;
	}
	else
		std::cout << "No results found." << std::endl;
}		// End displayResults


template<class Type>
void ListSearch<Type>::operator()(const Type& search)	// Function object useage:
{														// Used as an argument for an AVL tree traversal.
	if (search == criteria)								// Examines node item for matching criteria; if matched, adds item to the results vector.
		results.push_back(search);
}	// End operator()

#endif