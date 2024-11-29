#include "HoTTServer.h"

HoTTServer server(10,11);;

void setup() {
	server.registerModule(HoTTServerVario);
	server.start();
}

void loop() {
	// server.setCellVoltage(1,4.2);
	// server.setCellVoltage(2,3.1);
	// server.setCellVoltage(3,2.0);
	// server.setCellVoltage(4,1.3);
	// server.setCellVoltage(5,5.7);
	// server.setCellVoltage(6,1.9);
	// server.setVoltage(HOTT_PRIMARY_VOLTAGE, 5.5);
	// server.setVoltage(HOTT_SECONDARY_VOLTAGE, 35.5);
	// server.setTemperature(HOTT_PRIMARY_TEMPERATURE, -10);
	// server.setTemperature(HOTT_SECONDARY_TEMPERATURE, 35);
	// server.setFuelPercentage(23);
	// server.setFuel(500);
	// server.setRPM(HOTT_PRIMARY_RPM,18500);
	server.setAltitude(123);
	server.setClimbRate(HOTT_CLIMBRATE_1S, 6.7);
	server.setClimbRate(HOTT_CLIMBRATE_3S, -45.7);
	server.setClimbRate(HOTT_CLIMBRATE_10S, 7.6);
	// server.setVoltage(HOTT_MAIN_VOLTAGE, 42.56);
	// server.setCurrent(HOTT_MAIN_CURRENT, 9.1);
	// server.setCurrent(HOTT_BEC_CURRENT, 0.9);
	// server.setCapacity(1860);
	// server.setSpeed(184);
	// server.setRPM(HOTT_SECONDARY_RPM,17400);
	// server.setPressure(25.5);
	// server.setFlightDirection(120);
	// server.setMessage("Test v0.1", 9);
	// server.setThrottle(75);
	// server.setPWM(150);
	// server.setMotorTimimg(234);
	// server.setMotorAdvancedTimimg(135);
	// server.setAngle(HOTT_X_AXIS, 5);
	// server.setAngle(HOTT_Y_AXIS, 10);
	// server.setAngle(HOTT_Z_AXIS, 15);
	// server.setGyro(HOTT_X_AXIS, 25);
	// server.setGyro(HOTT_Y_AXIS, 30);
	// server.setGyro(HOTT_Z_AXIS, 35);
	
	server.processRequest();
	
	delay(100);  
}
