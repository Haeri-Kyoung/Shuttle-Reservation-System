#ifndef RESERVATIONS_H_
#define RESERVATIONS_H_

double requestTime();
char requestVehicle();
int driverSeats(char vehicle);
int driverScheduleCreate(double startHour, double endHour, int seats, int j);
int checkAvailability(char vehicle, int schedule, char infoVehicle, int driverNumber, int tally, int count);
int reservationDelete(int reservations);
char reservationLoop();
char reservationStart();
int driverTally(int driverNumber, int i, int tally);
int driverTallyD(int driverNumber, int i, int tally);

#endif /* RESERVATIONS_H_ */
