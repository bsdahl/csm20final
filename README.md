#CSM20 Final Group Project

This is the Design Topic for the CSM20 Final Group Project for the right group. The goal of the assignment was to create an Airline Reservations System in C++. 

##Design Strategies

We all worked together to create a design plan for the application. Strategies included simplifying tasks to specific classes, optimizing code size by relying on containers, and focusing on the requirements of the assignment. We started by outlining what classes we would need, including PassengerData.h, and FlightData.h classes. We then discussed separating the data from the interface by creating two classes: AirlineInterface.h would handle the program output and interface, and FlightManager.h would handle the creation, storage, and calculation of the data. We tried to focus on how an actual Airline Reservations System might work. 

##Project Architecture

###ArlineInterface.h

###FlightManager.h

###FlightData.h

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
