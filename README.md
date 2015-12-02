#CSM20 Final Group Project

This is the Design Document for the CSM20 Final Group Project for the right group. The goal of the assignment was to create an Airline Reservations System in C++. 

##Design Strategies

We all worked together to create a design plan for the application. Strategies included simplifying tasks to specific classes, optimizing code size by relying on containers, and focusing on the requirements of the assignment. We started by outlining what classes we would need, including PassengerData.h, and FlightData.h classes. We then discussed separating the data from the interface by creating two classes: AirlineInterface.h would handle the program output and interface, and FlightManager.h would handle the creation, storage, and calculation of the data. We tried to focus on how an actual Airline Reservations System might work. 

##Project Architecture

###AirlineInterface.h

AirlineInterface.h is the main interface class for the program. Its responsibilities are to hold the FlightManager data member, and provide input/output interface for the program. displayMenu() is designed to be used in main inside a while loop. It returns false when the user wishes to quit. 

<table>
	<tr>
		<td>AirlineInterface.h</td>
	<tr>
		<td>data : FlightManager</td>
	</tr>
	<tr>
		<td>displayMenu()</td>
	</tr>
</table>

###FlightManager.h

FlightManager.h is the main data class. It is responsible for holding AVL trees of PassengerData objects and FlightData objects. It's constructor reads the input files and fills the trees. The constructor also calculates the distances between airports and calculates the seatmaps for each flight and the waitlist. FlightManager.h also provides traversal functions to the AirlineInterface.h class for the private data members.

<table>
	<tr>
		<td>AirlineInterface.h</td>
	<tr>
		<td>passengerList : AVLTree&lt;PassengerData&gt;<br>
		flightList : AVLTree&lt;FlightData&gt;<br>
		waitList : AVLTree&lt;PassengerData&gt;<br>
		flightMap : FlightMap</td>
	</tr>
	<tr>
		<td>FlightManager()<br>
		</td>
	</tr>
</table>

###FlightData.h

<table>
	<tr>
		<td>FlightData.h</td>
	<tr>
		<td></td>
	</tr>
	<tr>
		<td></td>
	</tr>
</table>

###PassengerData.h

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
