#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int driverSeats(char vehicle)
{
	//Checks vehicle type for number of seats
	int seats;
	if (vehicle == 'V' || vehicle == 'v')
	{seats = 4;}
	else if (vehicle == 'C' || vehicle == 'c')
	{seats = 2;}
	else if (vehicle == 'M' || vehicle == 'm')
	{seats = 1;}

	//Does not need to be error checked, it was done before.
	return seats;
}

double requestTime() //Ask for the reservation time
{
	int time, timeSlot;
	bool loop = true;

	do
	{
       cout << "What Time for the Reservation: ";
	cin >> time;

		//return the time slot for the reservation
	if (time == 800){timeSlot=0;
	loop = false;}
	else if (time == 830){timeSlot=1;
	loop = false;}
	else if (time == 900){timeSlot=2;
	loop = false;}
	else if (time == 930){timeSlot=3;
	loop = false;}
	else if (time == 1000){timeSlot=4;
	loop = false;}
	else if (time == 1030){timeSlot=5;
	loop = false;}
	else if (time == 1000){timeSlot=6;
	loop = false;}
	else if (time == 1130){timeSlot=7;
	loop = false;}
	else if (time == 1100){timeSlot=8;
	loop = false;}
	else if (time == 1230){timeSlot=9;
	loop = false;}
	else if (time == 1200){timeSlot=10;
	loop = false;}
	else if (time == 1330){timeSlot=11;
	loop = false;}
	else if (time == 1300){timeSlot=12;
	loop = false;}
	else if (time == 1430){timeSlot=13;
	loop = false;}
	else if (time == 1400){timeSlot=14;
	loop = false;}
	else if (time == 1530){timeSlot=15;
	loop = false;}
	else if (time == 1500){timeSlot=16;
	loop = false;}
	else if (time == 1630){timeSlot=17;
	loop = false;}
	else { cout << "Invalid Time!" << endl;}
	}
	while(loop == true);

	return timeSlot;
}

char requestVehicle()//The vehicle for the reservation
{
	char vehicle;
	bool loop = true;

	do
	{
        cout << "What Vehicle for the Reservation: ";
        cin >> vehicle;

      //return what the vehicle was entered
	if (vehicle == 'V' || vehicle == 'v')
	{return vehicle;
	loop = false;}
	else if (vehicle == 'C' || vehicle == 'c')
	{return vehicle;
	loop = false;}
	else if (vehicle == 'M' || vehicle == 'm')
	{return vehicle;
	loop = false;}
	else {cout << "Invalid Vehicle!" << endl;}
	}
	//Make sure it is valid of the 3
	while(loop == true);
    return 0;
}

int driverScheduleCreate(double startHour, double endHour, int seats, int j)
{
	//From start hour to end hour, enter the amount of seats into the schedule for each timeslot for the selected vehicle
	//I.E A car adds 2 openings for each time slot from start to end
	if (startHour <= 800 && endHour >= 800 && j == 0){return seats;}
	else if (startHour <= 830 && endHour >= 830 && j == 1){return seats;}
	else if (startHour <= 900 && endHour >= 900 && j == 2){return seats;}
	else if (startHour <= 930 && endHour >= 930 && j == 3){return seats;}
	else if (startHour <= 1000 && endHour >= 1000 && j == 4){return seats;}
	else if (startHour <= 1030 && endHour >= 1030 && j == 5){return seats;}
	else if (startHour <= 1100 && endHour >= 1100 && j == 6){return seats;}
	else if (startHour <= 1130 && endHour >= 1130 && j == 7){return seats;}
	else if (startHour <= 1200 && endHour >= 1200 && j == 8){return seats;}
	else if (startHour <= 1230 && endHour >= 1230 && j == 9){return seats;}
	else if (startHour <= 1300 && endHour >= 1300 && j == 10){return seats;}
	else if (startHour <= 1330 && endHour >= 1330 && j == 11){return seats;}
	else if (startHour <= 1400 && endHour >= 1400 && j == 12){return seats;}
	else if (startHour <= 1430 && endHour >= 1430 && j == 13){return seats;}
	else if (startHour <= 1500 && endHour >= 1500 && j == 14){return seats;}
	else if (startHour <= 1530 && endHour >= 1530 && j == 15){return seats;}
	else if (startHour <= 1600 && endHour >= 1600 && j == 16){return seats;}
	else if (startHour <= 1630 && endHour >= 1630 && j == 17){return seats;}
    else if (startHour <= 1700 && endHour >= 1700 && j == 18){return seats;}
	else {return 0;}
}

int checkAvailability(char vehicle, int schedule, char infoVehicle, int driverNumber, int tally, int count)
{
	//Check if the spot has an opening, this is looped for every driver seeded by least passengers
	driverNumber++;
	if (schedule > 0 && vehicle == infoVehicle && tally == count)
	{return driverNumber;}
	else {return 0;}
}

int reservationDelete(int reservations)
{
	int reservation;
	bool loop = true;

	do
	{
        cout << "Enter Reservation Number:" << endl;
        cin >> reservation; //Input reservation number

	if (reservation > reservations || reservation < 0)
	{
		cout << "Invalid Reservation Number!" << endl; //If it does not exists, say so
	}
	else {loop = false;}
	}
	while (loop == true);

	//Return the given input
	return reservation;

}

char reservationLoop() //The main loop
{
	char reservation;
	bool loop = true;

	do //The Hud that displays inputs
	{
        cout << "\nEnter Another Reservation (R)";
        cout << "\nDelete a Reservation (D)";
        cout << "\nDisplay a Reservation (S)";
        cout << "\nDisplay Driver Schedules (P)";
        cout << "\nFinish (F)";
        cin >> reservation;

	if (reservation == 'R' || reservation == 'r' || reservation == 'D' || reservation == 'd' || reservation == 'F' || reservation == 'f' || reservation == 'S' || reservation == 's' || reservation == 'P' || reservation == 'p')
	{loop = false;}
	else {cout << "Invalid Command!" << endl;}
	}
	//When valid, return
	while (loop == true);

	return reservation;
}

char reservationStart() //First loop of the code allowing driver edits
{
	char start;
	bool loop = true;

	do
	{
        cout << "\nEdit a Driver or Start Reservations? (D or R): ";
	cin >> start; //Edit the driver or start reservations

	if (start == 'R' || start == 'r' || start == 'D' || start == 'd')
	{loop = false;}
	else {cout << "Invalid Command! " << endl;}
	}
	//When valid, return
	while (loop == true);

	return start;
}

int driverTally(int driverNumber, int i, int tally)
{
	//Simply count up whenever a passenger is added to a driver
	if (i == driverNumber)
	{tally = tally + 1;
	return tally;}
	else {return tally;}
}

int driverTallyD(int driverNumber, int i, int tally)
{
	//As done before, but subtract from the tally if a reservation for that driver is deleted.
	if (i == driverNumber)
	{tally = tally - 1;
	return tally;}
	else {return tally;}
}

