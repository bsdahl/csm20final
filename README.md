#CSM20 Final Group Project

This is the Design Document for the CSM20 Final Group Project for the right group. The goal of the assignment was to create an Airline Reservations System in C++. 

Github repository:
`https://github.com/radiofreq10/csm20final`

##Design Strategies

We all worked together to create a design plan for the application. Strategies included simplifying tasks to specific classes, optimizing code size by relying on containers, and focusing on the requirements of the assignment. We started by outlining what classes we would need, including PassengerData.h, and FlightData.h classes. We then discussed separating the data from the interface by creating two classes: AirlineInterface.h would handle the program output and interface, and FlightManager.h would handle the creation, storage, and calculation of the data. We tried to focus on how an actual Airline Reservations System might work. 

###Credit

- Nicholas Clayton
  - FlightManager Class
  - SeatingQueue Class
- Benjamin Dahl
  - Airline Interface Class
- Jeff Grammer
  - FlightData Class 
- Robbie Jordan
  - Input Files
- Alex Latouf
  - Airline Interface Class
- Beto Lopez
  - Graph Class and Flightmap Clas
- Jake Lyon
  - Passenger Data Class

##Project Architecture

###AirlineInterface.h

AirlineInterface.h is the main interface class for the program. Its responsibilities are to hold the FlightManager data member, and provide input/output interface for the program. displayMenu() is designed to be used in main inside a while loop. It returns false when the user wishes to quit. 

The AirlineInterface main menu.
```
Welcome to CSM20 Airlines. Choose an option.
1. Display all passengers.
2. Display passengers going to a city.
3. Display passengers leaving a city.
4. Display passengers on a flight.
5. Display wait list for a flight.
6. Display global wait list.
7. Display all flights.
8. Display all flights including passengers.
9. Search for a passenger.
0. Search for a flight.
D. Delete a Passenger.
Q. Quit.
Enter your selection:
```

AirlineInterface.h also contains a couple nested classes including SearchForPassenger class, and SearchForFlight class. These classes are utility classes that have the operator() overloaded. They are used as a function object for the AVL Tree traversal functions. 

*Notes:* It is important to recognize that the output of displaying passengers on a flight shows the original seatclass of the passenger's reservation rather than the seat class they are currently in. The list of passengers on a flight is in order of the seatmap. The first 3 seats are for Pilot Club, the next 5 seats are First Class, the next 5 seats are Business Class, and the remaining 27 seats are economy. If there was not room for a passenger in their seating class they were bounced into a lower seat rather than putting them on a waitlist. The bounce was in order of reservation number. Consideration was made to be sure that no more than 10 bounced seats occur on a given flight.

<table>
	<tr>		
		<td>AirlineInterface.h</td>
	</tr>
	<tr>
		<td>-data : FlightManager</td>
	</tr>
	<tr>
		<td>+displayMenu() : boolean<br>
		-displayAllPassengers() : boolean<br>
		-displayPassengersTo( city : char ) : boolean<br>
		-displayPassengersFrom( city : char ) : boolean<br>
		-displayPassengersOnFlt( flight : size_t ) : boolean<br>
		-displayWaitFlight( flight : size_t) : boolean<br>
		-displayWaitAll() : boolean<br>
		-displayAllFlights() : boolean<br>
		-displayAllFlightsPassengers() : boolean<br>
		-searchPassenger( passenger : string ) : boolean<br>
		-searchFlight( flight : size_t ) : boolean<br>
		-getCharInput( field : string ) : char<br>
		-getNumericInput( field : string ) : size_t<br>
		-enterToContinue() : void</td>
	</tr>
</table>

<table>
	<tr>		
		<td>SearchForPassenger</td>
	</tr>
	<tr>
		<td>-displayCount : int<br>
		-firstNameKey : string<br>
		-lastNameKey : string<br>
		-reservationNumkey : size_t<br>
		-flightNumKey : size_t<br>
		-removePassenger : bool<br>
		-firstPass : bool<br>
		-fmPtr : FlightManager*<br>
		-markedForRemoval : PassengerData* = nullptr</td>
	</tr>
	<tr>
		<td>+SearchForPassenger()<br>
		+~SearchForPassenger()<br>
		+setFirstNameKey( key : string ) : void<br>
		+setLastNameKey( key : string ) : void<br>
		+setReservationNumKey( key : size_t ) : void<br>
		+setFightNumKey( key : size_t ) : void<br>
		+setRemovePassengerKey( key : bool ) : void<br>
		+setfmPtr( key : FlightManager* ) : void<br>
		+clearKeys() : void<br>
		+operator()(passenger : PassengerData ) : void<br>
		+removeMarkedPassenger() : bool</td>
	</tr>
</table>

<table>
	<tr>		
		<td>SearchForFlight</td>
	</tr>
	<tr>
		<td>-displayCount : int<br>
		-toCity : char<br>
		-fromCity : char<br>
		-flightNum : size_t<br>
		-displayPassengers : bool<br>
		-firstPass : bool</td>
	</tr>
	<tr>
		<td>+SearchForFlight()<br>
		+setToCity( key : char ) : void<br>
		+setFromCity( key : char ) : void<br>
		+setFlightNum( key : size_t ) : void<br>
		+setDisplayPassengers( key : bool ) : void<br>
		+clearKeys() : void<br>
		+operator()(passenger : PassengerData ) : void<br></td>
	</tr>
</table>

###FlightManager.h

FlightManager.h is the main data class. It is responsible for holding AVL trees of PassengerData objects and FlightData objects. AVL trees were chosen as the primary data container for ease of sorting and searching based on key values.
It's constructor reads the input files and fills the trees. The constructor also calculates the distances between airports and calculates the seatmaps for each flight and the waitlist. FlightManager.h also provides traversal functions to the AirlineInterface.h class for the private data members.
addPassenger() adds a passenger to passengerList and the seating vector on their corresponding flight.
addFlight() adds a flight to flightList and calls calculateMileage using the flight as the parameter.
removePassenger() removes a passenger from all lists and their flight's corresponding seating vector.
calculateMileage() calculates the mileage of a flight using the flightMap graph.
populateMap() sets the vertices and edge length of flightMap.


<table>
	<tr>
		<td>FlightManager.h</td>
	</tr>
	<tr>
		<td>-passengerList : AVLTree&lt;PassengerData&gt;<br>
		-flightList : AVLTree&lt;FlightData&gt;<br>
		-waitList : AVLTree&lt;PassengerData&gt;<br>
		-flightMap : FlightMap<br>
		-seatQueue : SeatingQueue</td>
	</tr>
	<tr>
		<td>+FlightManager()<br>
		+traversePassenger() : void<br>
		+traverseFlight() : void<br>
		+traverseWait() : void<br>
		+addPassenger( passenger : const PassengerData&amp; ) : bool<br>
		+addFlight( flight : FlightData&amp; ) : void<br>
		+removePassenger( aPassenger : const PassengerData&amp; ) : PassengerData<br>
		-calculateMileage( flight : FlightData&amp; ) : void<br>
		-readFlightsFromFile( inputStream : ifstream&amp; ) : void<br>
		-readPassengersFromFile( inputStream : ifstream&amp; ) : void<br>
		-populateMap() : void</td>
	</tr>
</table>

###nextFromWaitList

nextFromWaitList is a private utility class within FlightManager. It is called as a function object parameter for an AVL tree traversal. It will determine the next highest membership passenger waitlisted for a given flight. This passenger is stored in dynamic memory pointed to by nextPassenger, and is returned by get(). The found() function returns a bool indicating whether a passenger for the specified flight was found in the AVL tree.
get() returns *nextPassengers.
found() returns nextPassenger != nullptr.

<table>
	<tr>
		<td>nextFromWaitlist</td>
	</tr>
	<tr>
		<td>-flightNum : size_t<br>
		-nextPassenger : PassengerData*</td>
	</tr>
	<tr>
		<td>+nextFromWaitlist( flightNumber : const size_t&amp; )<br>
		+operator()( aPassenger : const PassengerData&amp; ) : void<br>
		+get() : PassengerData<br>
		+found() : bool</td>
	</tr>
</table>

###SeatingQueue.h

The SeatingQueue.h class is a functional class that extracts the PassengerData vector from a FlightData object, and enqueues the PassengerData objects in a priority queue checking for membership class. The underlying structure is a std::priority_queue; chosen for ease of sorting by clearly defined priority levels. Membership classes range from 1 to 4, with 1 being the highest class and 4 the lowest.
empty() returns seatQueue.empty().
isFull() returns seatQueue.size() &gt;= MAX_SEATS.
clear() empties seatQueue and sets flightPtr = nullptr.
finalizeSeating() inserts passengers from seatQueue into the seating vector. Handles bouncing lower class passengers and adding excess passengers to the waitlist.

<table>
	<tr>
		<td>SeatingQueue.h</td>
	</tr>
	<tr>
		<td>-MAX_PILOT_CLASS : static const size_t = 3<br>
			-MAX_FIRST_CLASS : static const size_t = 5<br>
			-MAX_BUSI_CLASS : static const size_t = 5<br>
			-MAX_ECON_CLASS : static const size_t = 27<br>
			-MAX_BOUNCED : static const size_t = 10<br>
			-MAX_SEATS : static const size_t = 40<br>
			-PILOT_CLASS : static const size_t = 1<br>
			-FIRST_CLASS : static const size_t = 2<br>
			-BUSI_CLASS : static const size_t = 3<br>
			-seatQueue : std::priority_queue&lt;PassengerData, std::vector&lt;PassengerData&gt;, compareMembership&gt;<br>
			-waitListPtr : AVLTress&lt;PassengerData&gt;*<br>
			-flightPtr : FlightData* = nullptr<td>
	</tr>
	<tr>
		<td>-queueCurrentPassengers() : void<br>
			+SeatingQueue( waitList : AVLTree&lt;PassengerData&gt;&amp; )
			+add( newPassenger : const PassengerData&amp; ) : bool<br>
			+setFlight( aFlight : FlightData&amp; ) : void<br>
			+empty() : bool<br>
			+isFull() : bool<br>
			+clear() : void<br>
			+finalizeSeating() : void
		</td>
	</tr>
</table>

###compareMembership

compareMembership is a private utility class of SeatingQueue.h. It is used as a function object for use in an std::priority_queue to compare the membership values of the enqueued PassengerData objects. Low membership values have higher priority than higher values.
<table>
	<tr>
		<td>compareMembership</td>
	</tr>
	<tr>
		<td>+operator()( passenger1 : const PassengerData&amp;, passenger2 : const PassengerData&amp;) : bool</td>
	</tr>
</table>

###PassengerData.h

PassengerData.h class is a data class that holds all the data fields associated with a Passenger.

The default constructor is written such that it will either validate the input via set functions, or set the data members to default values.

All set functions check the data being passed to them and throw PrecondViolatedExcep for invalid data entry. SetFirstName() and SetLastName() use a helper function, nameCheck(string), to validate name data.

All get functions return constant data. No validation is conducted, assumes data has been checked via set functions.

NameCheck(string) is the only helper function. It checks each character in the string using the function isalpha(char);

Overloaded comparison operators check the reservation numbers first. If both reservation numbers are set to default values, the rest of the data members are compared instead. If all data is default, the operator returns false.

Copy constructor and overloaded assignment operator originally made private to prevent implicit copies. Copies turned out to be extremely valuable in the implementation of other classes that use PassengerData, thus the copy constructor is back in.

Overloaded stream extraction operator (>>) inserts data in the order of reservation number, first name, last name, flight number, and membership class. It is assumed the class inputting the data knows this. Only one (string) buffer is used; an int buffer was considered, but the idea was dropped as getline() will not accept an int argument. Instead, the String function stol(string) was used to input numerical data. All input validation is done through the set functions.

Overloaded stream insertion operator (<<) outputs data in the order of Reservation number, first name, last name, membership class, and flight number. Here, the number used to represent membership is used in a switch/case to output a string stating the passenger's seating class.

<table>
	<tr>
		<td>PassengerData.h</td>
	<tr>
		<td>-firstName : string<br>
		-lastName : string<br>
		-seatClass : size_t<br>
		-reservationNumber : size_t<br>
		-flightNum : size_t<br>
		-nameCheck(name : string) : bool<br></td>
	</tr>
	<tr>
		<td>+PassengerData( reservation : size_t, first : string, last : string, seatClass : size_t, flight : size_t)<br>
		+setFirstName(first : string) : void<br>
		+setLastName(last : string) : void<br>
		+setMembership(seatClass : membership) : void<br>
		+setReservationNum(reservation : size_t) : void<br>
		+setFlightNum(flight : size_t) : void<br>
		+getFirstName() : string<br>
		+getLastName() : string<br>
		+getMembership() : size_t<br>
		+getReservationNum() : size_t<br>
		+getFlightNum() : size_t <br>
		+operator ==<br>
		+operator ><br>
		+operator <</td>
	</tr>
</table>

###Graph.h

*Graph* class is a weighted, undirected and connected graph, implemented as an adjacency list. The class is responsible 
for representing the flight map, where the vertices will represent the cities, and the edges will represent the distance between the cities. Class is base class for *flightMap* class

<table>
	<tr>
		<td>Graph.h</td>
	<tr>
		<td>-numVertices : int<br>
		-numEdges : int<br>
		-adjList : map&lt;ItemType, map&lt;ItemType, int&gt;&gt;<br>
		-iter : map&lt;ItemType, int&gt::const_iterator<br>
		-iter2 : map&lt;ItemType, map&lt;ItemType, int&gt;&gt;::const_iterator</td>
	</tr>
	<tr>
		<td>+getNumVertices() const : int<br>
		+getNumEdges() const : int<br>
		+getVertex(vertex : ItemType) : ItemType<br>
		+getWeight(startVertex : ItemType, endVertex: ItemType) : int<br>
		+add(startVertex : ItemType, endVertex : Itemtype, weight : int) : bool<br>
		+remove(startVertex : ItemType, endVertex : ItemType) : bool<br>
		+isEmpty() : bool<br>
		+breadthFirstTraversal(startVertex : Itemtype, visit(vertex : Itemtype) : void) : void<br>
	</tr>
</table>

###flightMap.h

*flightMap* class inherits from *Graph* class. The class was created to implement Dijkstra's algorithm to find the
shortest path between two vertices(cities) whilst maintaining data independence of the class *Graph*.   

<table>
	<tr>
		<td>flightMap.h</td>

	<tr>
		<td>+shortestPath(startVertex : ItemType, endVertex : ItemType) : size_t<br>
	
	</tr>
</table>
