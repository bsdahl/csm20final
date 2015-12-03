#CSM20 Final Group Project

This is the Design Document for the CSM20 Final Group Project for the right group. The goal of the assignment was to create an Airline Reservations System in C++. 

##Design Strategies

We all worked together to create a design plan for the application. Strategies included simplifying tasks to specific classes, optimizing code size by relying on containers, and focusing on the requirements of the assignment. We started by outlining what classes we would need, including PassengerData.h, and FlightData.h classes. We then discussed separating the data from the interface by creating two classes: AirlineInterface.h would handle the program output and interface, and FlightManager.h would handle the creation, storage, and calculation of the data. We tried to focus on how an actual Airline Reservations System might work. 

##Project Architecture

###AirlineInterface.h

AirlineInterface.h is the main interface class for the program. Its responsibilities are to hold the FlightManager data member, and provide input/output interface for the program. displayMenu() is designed to be used in main inside a while loop. It returns false when the user wishes to quit. 

<table>
	<tr>		<td>AirlineInterface.h</td>
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
		-getCityInput() : char<br>
		-getFlightInput() : size_t</td>
	</tr>
</table>

###FlightManager.h

FlightManager.h is the main data class. It is responsible for holding AVL trees of PassengerData objects and FlightData objects. It's constructor reads the input files and fills the trees. The constructor also calculates the distances between airports and calculates the seatmaps for each flight and the waitlist. FlightManager.h also provides traversal functions to the AirlineInterface.h class for the private data members.

<table>
	<tr>
		<td>FlightManager.h</td>
	<tr>
		<td>-passengerList : AVLTree&lt;PassengerData&gt;<br>
		-flightList : AVLTree&lt;FlightData&gt;<br>
		-waitList : AVLTree&lt;PassengerData&gt;<br>
		-flightMap : FlightMap</td>
	</tr>
	<tr>
		<td>+FlightManager()
		+traversePassenger() : void<br>
		+traverseFlight() : void<br>
		+traverseWait() : void<br>
		-readInput() : void<br>
		</td>
	</tr>
</table>

###FlightData.h

FlightData.h class is a data class that holds all the data fields associated with a Flight.

<table>
	<tr>
		<td>FlightData.h</td>
	<tr>
		<td>-MAX_PASSENGERS : const size_t = 40<br>
		-flightNumber : size_t<br>
		-mileage : size_t<br>
		-departTime : size_t<br>
		-arriveTime : size_t<br>
		-toCity : char<br>
		-fromCity : char<br>
		-seatMap : vector&lt;PassengerData&gt;</td>
	</tr>
	<tr>
		<td>+FlightData( fn : size_t = 0, miles : size_t = 0, departTime : size_t = 0, arriveTime : size_t = 0, toc : char = '0', frc : char = '0' )<br>
		+setFlightNumber( fn : size_t ) : void<br>
		+setMileage( miles : size_t ) : void<br>
		+setDepartTime( time : size_t ) : void<br>
		+setArriveTime( time : size_t ) : void<br>
		+setToCity( city : char ) : void<br>
		+setFromCity( city : char ) : void<br>
		+setFromCity( city : char ) : void<br>
		</td>
	</tr>
</table>

###PassengerData.h

PassengerData.h class is a data class that holds all the data fields associated with a Passenger.

<table>
	<tr>
		<td>PassengerData.h</td>
	<tr>
		<td>firstName : string<br>
		lastName : string<br>
		seatClass : size_t<br>
		reservationNumber : size_t<br>
		flightNum : size_t</td>
	</tr>
	<tr>
		<td>PassengerData()<br>
		setFirstName()<br>
		setLastName()<br>
		setMembership()<br>
		setReservationNum()<br>
		setFlightNum()<br>
		getFirstName()<br>
		getLastName()<br>
		getMembership()<br>
		getReservationNum()<br>
		getFlightNum()<br>
		operator ==<br>
		operator ><br>
		operator <</td>
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