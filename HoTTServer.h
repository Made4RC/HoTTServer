/*
 *
 * HoTT - Hopping Telemetry Transmission - Server
 * 
 * Sensor
 * The sender, that responds to a request by a server (reciever), acts as server.
 *
 *
 * Arduino Micro 5v/16mHz w/ Atmega 328
 *
 * Userful links:
 * http://www.rc-network.de/forum/showthread.php/281496-Graupner-HoTT-Telemetrie-Sensoren-Eigenbau-DIY-Telemetrie-Protokoll-entschlüsselt?p=3369807&viewfull=1#post3369807
 * https://github.com/3yc/hott-for-ardupilot/blob/master/PX4/hott-px4-code/px4-hott-module/hott_msgs.h
 * https://github.com/obayer/MultiWii-HoTT/blob/master/MultiWii_2_1/HoTTv4.ino
 *
 * How to connect the arduino with your reciever
 *
 *         TX ----------
 *                     |
 * Arduino              1k5 Ohm                              Reciever
 *                     |
 *         RX ----------------------- Telemetry signal
 *
*/


#ifndef HoTTServer_h
#define HoTTServer_h

#include "Arduino.h"
#include "SoftwareSerial.h"

// Protocoll definitions

#define HOTT_TX_DELAY     1500  	// time in us between 2 bytes in a binpacket
#define HOTT_SEND_DELAY   4500  	// HoTT line idle-protocol

// Graupner #33620 Electric Air Module (EAM)
#define HOTT_ELECTRIC_AIR_MODULE_ID					0x8E
#define HOTT_ELECTRIC_AIR_SENSOR_ID					0xE0
#define HOTT_TEXT_MODE_REQUEST_ELECTRIC_AIR			0xEF
// Graupner #33611 General Air Module (GAM)
#define HOTT_GENERAL_AIR_MODULE_ID					0x8D
#define HOTT_GENERAL_AIR_SENSOR_ID					0xD0 
#define HOTT_TEXT_MODE_REQUEST_GENERAL_AIR			0xDF 
// Graupner #33600 GPS module
#define HOTT_GPS_MODULE_ID							0x8A
#define HOTT_GPS_SENSOR_ID							0xA0
#define HOTT_TEXT_MODE_REQUEST_GPS					0xAF
// Graupner #33601 Vario Module
#define HOTT_VARIO_MODULE_ID						0x89
#define HOTT_VARIO_SENSOR_ID						0x90
#define HOTT_TEXT_MODE_REQUEST_VARIO				0x9F
//Graupner #337xx Air ESC 
#define HOTT_AIRESC_MODULE_ID						0x8C
#define HOTT_AIRESC_SENSOR_ID						0xc0 
#define HOTT_TEXT_MODE_REQUEST_AIRESC				0xCF 


// inverted characters
#define HOTT_PRIMARY_INVERTED						0
#define HOTT_SECONDARY_INVERTED						1

// ###########################################################################

// Sent, when reciever request telemetry data
#define HOTT_BINARY_MODE_REQUEST_ID					0x80
// or text (configuration) data
#define HOTT_TEXT_MODE_REQUEST_ID					0x7F 
 

// Radio keys
#define HOTT_KEY_LEFT								7
#define HOTT_KEY_SET								9
#define HOTT_KEY_DOWN								11
#define HOTT_KEY_UP									13
#define HOTT_KEY_RIGHT								14
#define HOTT_TEXT_MODE_IDLE             			0x0F 


// Alarms
typedef enum { 
    HOTT_ALARM_NONE = 0x00, 
    HOTT_ALARM_SENSOR1_TEMP_MIN = 0x06, 
    HOTT_ALARM_SENSOR1_TEMP_MAX = 0x08, 
    HOTT_ALARM_SENSOR2_TEMP_MIN = 0x07, 
    HOTT_ALARM_SENSOR2_TEMP_MAX = 0x09, 
    HOTT_ALARM_SENSOR1_VOLTAGE_MIN = 0x12, 
    HOTT_ALARM_SENSOR1_VOLTAGE_MAX = 0x0a, 
    HOTT_ALARM_SENSOR2_VOLTAGE_MIN = 0x13, 
    HOTT_ALARM_SENSOR2_VOLTAGE_MAX = 0x0b, 
    HOTT_ALARM_CELL_VOLTAGE_MIN = 0x11, 
    HOTT_ALARM_CAPACITY_MAX = 0x16, 
    HOTT_ALARM_CURRENT_MAX = 0x17, 
    HOTT_ALARM_POWER_MIN = 0x10, 
    HOTT_ALARM_POWER_MAX = 0x18, 
    HOTT_ALARM_RPM_MIN = 0x14, 
    HOTT_ALARM_RPM_MAX = 0x19, 
    HOTT_ALARM_ALTITUDE_MIN = 0x0f, 
    HOTT_ALARM_ALTITUDE_MAX = 0x1a, 
    HOTT_ALARM_DESCENT_LOW = 0x02, 
    HOTT_ALARM_DESCENT_HIGH = 0x03, 
    HOTT_ALARM_CLIMB_LOW = 0x0d, 
    HOTT_ALARM_CLIMB_HIGH = 0x0e, 
    HOTT_ALARM_SPEED_MIN = 0x01, 
    HOTT_ALARM_SPEED_MAX = 0x0c, 
    HOTT_ALARM_DISTANCE_MAX = 0x04, 
    HOTT_ALARM_UNKNOWN_1 = 0x05,
    HOTT_ALARM_UNKNOWN_2 = 0x15
} HOTTAlarm_e; 

// show inverted
typedef enum { 
	HOTT_INVERT_CELL_VOLTAGE = 0x00,
	HOTT_INVERT_BATTERY_1 = 0x01,
	HOTT_INVERT_BATTERY_2 = 0x02,
	HOTT_INVERT_TEMPERATURE_1 = 0x03,
	HOTT_INVERT_TEMPERATURE_2 = 0x04,
	HOTT_INVERT_FUEL = 0x05,
	HOTT_INVERT_CAPACITY = 0x06,
	HOTT_INVERT_ALTITUDE = 0x07,
	HOTT_INVERT_MAIN_CURRENT = 0x00,
	HOTT_INVERT_MAIN_VOLTAGE = 0x01,
	HOTT_INVERT_CLIMB_1s = 0x03,
	HOTT_INVERT_CLIMB_3s = 0x04,
	HOTT_INVERT_NO_GPS = 0x01
} HOTTInvert_e;

// Voltage sensors
typedef enum {
	HOTT_PRIMARY_VOLTAGE = 0,
	HOTT_SECONDARY_VOLTAGE = 1,
	HOTT_MAIN_VOLTAGE = 2,
	HOTT_BEC_VOLTAGE = 3
} HOTTVoltage_e;

// current sensors
typedef enum {
	HOTT_MAIN_CURRENT = 0,
	HOTT_BEC_CURRENT = 1,
	HOTT_MAX_MOTOR_CURRENT = 2
} HOTTCurrent_e;

// Climb rat's
typedef enum {
	HOTT_CLIMBRATE_1S = 0,
	HOTT_CLIMBRATE_3S = 1,
	HOTT_CLIMBRATE_10S = 2
} HOTTClimbRate_e;

// temperatures
typedef enum {
	HOTT_PRIMARY_TEMPERATURE = 0,
	HOTT_SECONDARY_TEMPERATURE = 1,
	HOTT_ESC_TEMPERATURE = 2,
	HOTT_BEC_TEMPERATURE = 3,
	HOTT_MOTOR_TEMPERATURE = 4
} HOTTTemperature_e;

// rpm's
typedef enum {
	HOTT_PRIMARY_RPM = 0,
	HOTT_SECONDARY_RPM = 1,
	HOTT_MOTOR_RPM = 2
} HOTTRPM_e;

// axis'
typedef enum {
	HOTT_X_AXIS = 0,
	HOTT_Y_AXIS = 1,
	HOTT_Z_AXIS = 2
} HOTTAxis_e;

#define HoTTServerGAM	0
#define HoTTServerEAM	1
#define HoTTServerVario	2
#define HoTTServerGPS	3
#define HoTTServerESC	4

class HoTTServer {

private:

	SoftwareSerial _serialPort;

	HOTTAlarm_e _warningID;
	uint8_t	_inverted1;
	uint8_t	_inverted2;

	uint16_t _capacity;
	float _current;
	float _maxCurrent;
	float _voltage1;
	float _voltage2;
	float _mainVoltage;
	float _minMainVoltage;
	float _BECVoltage;
	float _minBECVoltage;
	float _cellVoltage1;
	float _cellVoltage2;
	float _cellVoltage3;
	float _cellVoltage4;
	float _cellVoltage5;
	float _cellVoltage6;
	float _cellVoltage7;
	float _minCellVoltage;
	uint8_t _minCellVoltageCell;
	int16_t _altitude;
	int16_t _min_altitude;
	int16_t _max_altitude;
	float _climbRate1s;
	float _climbRate3s;
	float _climbRate10s;
	uint8_t _fuelPercentage;
	uint16_t _fuel;
	uint8_t _temperature1;
	uint8_t _temperature2;
	uint8_t _ESCTemperature;
	uint8_t _maxESCTemperature;
	uint8_t _BECTemperature;
	uint8_t _maxBECTemperature;
	uint8_t _motorTemperature;
	uint8_t _maxMotorTemperature;
	uint16_t _rpm1;
	uint16_t _maxRpm1;
	uint16_t _rpm2;
	uint16_t _maxRpm2;
	uint16_t _motorRpm;
	uint16_t _speed;
	uint16_t _maxSpeed;
	float _pressure;
	uint16_t _distance;
	uint8_t _flightDirection;
	char _message[22];
	uint8_t _throttle;
	uint8_t _BECCurrent;
	uint8_t _maxBECCurrent;
	uint8_t _PWM;
	uint8_t _motorTiming;
	uint8_t _motorAdvancedTiming;
	uint8_t _maxMotorCurrent;
	uint8_t _satelites;
	uint8_t _angleX;
	uint8_t _angleY;
	uint8_t _angleZ;
	uint8_t _gyroX;
	uint8_t _gyroY;
	uint8_t _gyroZ;
	uint8_t _homeDirection;
	
	uint8_t _registeredModules;
	
	void _sendData(uint8_t *data, uint8_t size);
	bool _isModuleRegistered(uint8_t module);

public:
	HoTTServer(uint8_t rxPin, uint8_t txPin);
	
	void registerModule(uint8_t module);
	void start();
	bool processRequest();
	
	void setWarning(HOTTAlarm_e warningID);
	void setInverted(uint8_t invertedID, uint8_t inverted);
	void setCapacity(uint16_t capacity);
	void setCurrent(HOTTCurrent_e sensorID, float current);
	void setVoltage(HOTTVoltage_e sensorID, float voltage);
	void setCellVoltage(uint8_t cellNumber, float voltage);
	void setAltitude(int16_t altitude);
	void setClimbRate(HOTTClimbRate_e climbRateID, float climbRate);
	void setFuelPercentage(uint8_t percent);
	void setFuel(uint16_t fuel);
	void setTemperature(HOTTTemperature_e temperatureID, int8_t temperature);
	void setRPM(HOTTRPM_e rpmID, uint16_t rpm);
	void setSpeed(uint16_t speed);
	void setPressure(float pressure);
	void setDistance(uint16_t distance);
	void setFlightDirection(uint8_t direction);
	void setMessage(char message[], uint8_t length);
	void setThrottle(uint8_t throttle);
	void setPWM(uint8_t PWM);
	void setMotorTimimg(uint8_t timing);
	void setMotorAdvancedTimimg(uint8_t timing);
	void setAngle(HOTTAxis_e axisID, uint8_t angle);
	void setGyro(HOTTAxis_e axisID, uint8_t gyro);
};
#endif /* HoTTServer_h */
