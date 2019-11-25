//=============================================================================================================
//Programmers: Ryan Appel, Haeri Kyoung
//Course: Computational Problem Solving 2
//Date: 11/20/2017
//Description: Create a reservation system that allows the user te enter up to 5 drivers, edit their data, and then
//begin taking reservations. The user will ask for a time and vehicle until they are met with a driver who meets those
//qualifications. When done they will be given a reservation code and the reservation will be set. These reservations
//can be deleted or displayed as well as the drivers overall schedule. When done output the drivers passenger schedule
//showing the times they are in use.
//=============================================================================================================

#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>
#include "reservations.h"

using namespace std;

class driver{ //Class for all driver information
public:
    
    //The 5 values needed for the drivers
    string name;
    char ID, vehicle;
    int startHour, endHour;
    
    //Functions used to set driver data
    int numberOfDrivers();
    void driverData();
    void driverTable();
    
};

int driver::numberOfDrivers() { //When called, askes for the number of drivers and makes sure its between 1 and 5
    bool invalid = true;
    int numDrivers;
    do{
        cout << "\nEnter the number of drivers: ";
        cin >> numDrivers;
        if(numDrivers <= 5 && numDrivers >= 1) {invalid = false;}
        else cout << "\nDrivers must be between 1 and 5!" << endl;}
    while(invalid == true);
    //A HUD to display general knowledge to the user
    cout<<"--------------------------------------------------------------------"<<endl;
    cout<<"Shuttle  service runs daily b/w 800 (8:00a.m.) and 1700 (5:00p.m.)\n";
    cout<<"Types of vehicle: Motorcycle, Car, Van\n";
    cout<<"--------------------------------------------------------------------"<<endl;
    return numDrivers;
}

void driver::driverData() {
    bool check = true;
    //enter the driver name
    cout<<"\nEnter the details for driver! "<< endl;
    cout<<"Enter driver name: ";
    cin>>name;
    
    //enter the driver ID
    cout<<"Enter driver ID: ";
    cin>>ID;
    
    //Enter the start time and check if it is between 8 and 17
    do
    {
        cout<<"Enter driver starting hour (i.e. 800 for 8:00): ";
        cin>>startHour;
        if (startHour >= 800 && startHour <= 1630)
        {check = false;}
        else {cout << "Must Start and End Between 8:00 and 17:00" << endl;}
    }
    while (check == true);
    
    //Same as the start date but it has to be lower than the start date
    check = true;
    do
    {
        cout<<"Enter driver ending hour (i.e. 1700 for 5:00): ";
        cin>>endHour;
        if (endHour >= 800 && endHour <= 1700 && endHour > startHour)
        {check = false;}
        else {cout << "Must Start and End Between 8:00 and 17:00" << endl;}
    }
    while (check == true);
    
    check = true;
    
    //Enter a vehicle and it must be a car motorcycle or van
    do
    {
        cout<<"Enter driver vehicle (i.e. m for motorcycle): ";
        cin>>vehicle;
        if (vehicle == 'M' || vehicle == 'm' || vehicle == 'C' || vehicle == 'c' || vehicle == 'V' || vehicle == 'v')
        {check = false;}
        else {cout << "Must Be A Motorcycle(M), Car(C), or Van(V)" << endl;}
    }
    while (check == true);
    
}

void driver::driverTable () { //Output all the data that was input for that driver
    
    cout<<"\nName\tID\tStart\tEnd\tVehicle\n";
    
    cout<<fixed<<setw(8)<<left<<name;
    cout<<fixed<<setw(8)<<left<<ID;
    cout<<fixed<<setw(8)<<left<<startHour;
    cout<<fixed<<setw(8)<<left<<endHour;
    cout<<vehicle<<endl;
}

int main(){
    
    driver info[5], driver; //an array to hold driver data
    int schedule[18][5]; //An 18 by 5 array to hold all the time slots for the schedule (80 to 1700)
    int scheduleTaken[18][5]; //The spaces taken up by passengers
    int tally[5] = {0, 0, 0, 0, 0}; //The amount of passengers per driver total
    int driverEdit, seats, time, driverNumber, resDelete, resSel;
    //Variables to hold general data about the driver. These variables are used to find the proper location in the array for the driver and their times
    char start, vehicle; //Two inputs one for the main loop the other for vehicle type
    int reservationNumber[100], reservationTime[100], reservationDriverNumber[100];
    char reservationDriver[100];
    //These 4 arrays are used to hold the reservation data up to 100 reservations
    int reservation = 0; //Reservation count
    bool loop = true;
    bool check = true;
    
    int numDrivers;
    numDrivers = driver.numberOfDrivers(); //Input number of drivers
    
    for(int i=0; i< numDrivers;i++) //Output the driver data for each driver used
    {info[i].driverData();}
    for(int i=0; i< numDrivers;i++)
    {info[i].driverTable();}
    
    do
    {
        start = reservationStart(); //Ask to edit drivers or start reservations.
        
        if (start == 'D' || start == 'd'){
            do
            {
                cout << "Which Driver to Edit? (1 for first driver): ";
                cin >> driverEdit; //Input driver number
                
                //Make sure the driver exists
                if(driverEdit > numDrivers)
                {cout << "Driver does not exist" << endl;}
                else {check = false;}
            }
            while (check == true);
            info[(driverEdit - 1)].driverData();
            for(int i=0; i< numDrivers;i++)
            {info[i].driverTable();}
            loop = true;}
        
        //start reservations
        else if(start == 'R' || start == 'r')
        {
            //Output the driver schedules
            for(int i=0; i< numDrivers;i++)
            {
                cout << "\nAvailable Time and Spots for Driver " << info[i].name << " (ID: " << info[i].ID << ", Vehicle: " << info[i].vehicle <<")"<<endl;
                cout << "|0800|0830|0900|0930|1000|1030|1100|1130|1200|1230|1300|1330|1400|1430|1500|1530|1600|1630|1700|" << endl;
                seats = driverSeats(info[i].vehicle);
                for (int j=0; j<19;j++)
                {
                    schedule[j][i] = driverScheduleCreate(info[i].startHour, info[i].endHour, seats, j);
                    scheduleTaken[j][i] =0;
                    cout << "|" << fixed << setw(4) << schedule[j][i];
                }
                cout << "|" << endl;
            }
            //----------------------------------------------------------------------------------------------------------
            do
            {
                if (start == 'R' || start == 'r')
                {
                    reservation++; //Number of reservations
                    int  count = 0; //a counter used to sort from lowest seed to highest
                    check = true;
                    bool check2;
                    
                    do
                    {
                        check2 = true;
                        count = 0;
                        cout << "\nRequest a Time and Vehicle!"<< endl;
                        time = requestTime(); //Input time
                        vehicle = requestVehicle(); //Input vehicle
                        
                        do
                        {
                            for(int i=0; i< numDrivers;i++) //For each driver
                            {
                                driverNumber = checkAvailability(vehicle, schedule[time][i], info[i].vehicle, i, tally[i], count);
                                //Check if a time is open
                                if (driverNumber > 0) //Save it
                                {i = numDrivers;
                                    check = false;
                                    check2 = false;}
                            }
                            //If not try next seed
                            if (driverNumber == 0) {count++;}
                            if (driverNumber == 0 && count == 100) //If never say it does not exist
                            {cout << "Not Available, Try Again" << endl;
                                check2 = false;}
                        }
                        while (check2 == true);
                    }
                    while (check == true);
                    
                    //These arrays hold the reservation data as tagged
                    reservationNumber[reservation] = reservation;
                    reservationTime[reservation] = time;
                    reservationDriver[reservation] = info[(driverNumber-1)].ID;
                    reservationDriverNumber[reservation] = driverNumber-1;
                    
                    //output the code and fix the schedules
                    cout << "Reservation code: " << reservationDriver[reservation] << reservationNumber[reservation] << " made!" << endl;
                    schedule[time][(driverNumber-1)]--;
                    scheduleTaken[time][(driverNumber-1)]++;
                    
                    //Mark up the passengers for that driver
                    for(int i=0; i< numDrivers;i++)
                    {tally[i] =  driverTally(reservationDriverNumber[reservation], i, tally[i]);}
                    
                    //ask for next mode
                    start = reservationLoop();
                }
                //----------------------------------------------------------------------------------------------------------
                else if (start == 'D' || start == 'd')
                {
                    
                    //Mark the reservation number, output the code and then fix the schedules
                    resDelete = reservationDelete(reservation);
                    cout << "Reservation: " << reservationDriver[resDelete] << reservationNumber[resDelete] << " deleted!" << endl;
                    schedule[reservationTime[resDelete]][reservationDriverNumber[resDelete]]++;
                    scheduleTaken[reservationTime[resDelete]][reservationDriverNumber[resDelete]]--;
                    
                    //Subtract a passenger from their total
                    for(int i=0; i< numDrivers;i++)
                    {tally[i] =  driverTallyD(reservationDriverNumber[resDelete], i, tally[i]);}
                    
                    //These arrays set the dats to a set value to describe it as removed
                    reservationNumber[resDelete] = 100;
                    reservationTime[resDelete] = 100;
                    reservationDriver[resDelete] = 'X';
                    reservationDriverNumber[resDelete] = 5;
                    
                    //ask for next mode
                    start = reservationLoop();
                    
                }
                //----------------------------------------------------------------------------------------------------------
                else if (start == 'F' || start == 'f') //End the code
                {
                    loop = false;
                    
                    //Output total passenger data for each driver
                    for(int i=0; i< numDrivers;i++)
                    {
                        
                        cout << "\nSchedule for Driver " << info[i].name << " (ID: " << info[i].ID << ", Vehicle: " << info[i].vehicle <<")"<<endl;
                        cout << "|0800|0830|0900|0930|1000|1030|1100|1130|1200|1230|1300|1330|1400|1430|1500|1530|1600|1630|1700|" << endl;
                        for (int j=0; j< 19;j++)
                        {
                            cout << "|" << fixed << setw(4) << scheduleTaken[j][i];
                        }
                        cout << "|" << endl;
                        cout << "Total Passengers is: " << tally[i] << endl; //Final tally of passengers
                    }
                }
                //----------------------------------------------------------------------------------------------------------
                else if (start == 'S' || start == 's')
                {
                    check = true;
                    do
                    {
                        resSel = reservationDelete(reservation); //Select a reservation number
                        
                        if (reservationDriver[resSel] == 'X')
                        {cout << "This Reservation Was Deleted" << endl;} //If it does not exist, say so
                        else {check = false;}
                    }
                    while (check == true);
                    
                    //Output the reservation data
                    cout << "Reservation: " << reservationDriver[resSel] << reservationNumber[resSel] << endl;
                    cout << "Driver ID " << reservationDriver[resSel] << endl;
                    cout << "Driver Name " << info[reservationDriverNumber[resSel]].name << endl;
                    cout << "Seats Left Available " << schedule[reservationTime[resSel]][reservationDriverNumber[resSel]] << endl;
                    
                    //ask for next mode
                    start = reservationLoop();
                }
                //----------------------------------------------------------------------------------------------------------
                else if (start == 'P' || start == 'p') //Print the current schedules
                {
                    for(int i=0; i< numDrivers;i++)
                    {
                        cout << "\nAvailable Time and Spots for Driver " << info[i].name << " (ID: " << info[i].ID << ", Vehicle: " << info[i].vehicle <<")"<<endl;
                        cout << "|0800|0830|0900|0930|1000|1030|1100|1130|1200|1230|1300|1330|1400|1430|1500|1530|1600|1630|1700|" << endl;
                        for (int j=0; j<19;j++)
                        {
                            cout << "|" << fixed << setw(4) << schedule[j][i];
                        }
                        cout << "|" << endl;
                    }
                    
                    //ask for next mode
                    start = reservationLoop();
                }
            }
            while(loop == true);
        }
        else {cout << "Invalid Input" << endl;}
    }
    while(loop == true);
    
}
