#include "Arduino.h"
#include "HoTTServer.h"

HoTTServer::HoTTServer() {
	setWarning(HOTT_ALARM_NONE);

    Serial.begin(19200);
}

void HoTTServer::_sendData(uint8_t *data, uint8_t size) {
	// Checksum berechnen
	uint8_t sum = 0;
	for(int i = 0; i < size-1; i++){
		sum += data[i];
	}
	data[44] = sum;

	// Daten senden
	for(int j = 0; j < size; j++){
		Serial.write(data[j]);
		delay(2);
		Serial.read();
	}
}

void HoTTServer::processRequest() {
	if (Serial.available() >= 2) {
		uint8_t requestMode = Serial.read();
		switch (requestMode) {
			case HOTT_TEXT_MODE_REQUEST_ID:
			{
				uint8_t requestID = Serial.read();
				switch (requestID & 0x0f) { 
						case HOTT_TEXT_MODE_IDLE: 
							break; 
						case HOTT_KEY_RIGHT: 
							break; 
						case HOTT_KEY_LEFT: 
							break; 
						case HOTT_KEY_UP: 
							break; 
						case HOTT_KEY_DOWN: 
							break; 
						case HOTT_KEY_SET: 
							break; 
				}
				
				// Text mode msgs type 
				uint8_t textData[] = {  
					0x7B, 										/*   0									start */
					0x00,										/*   1                           		fill byte */
					0x00,										/*   2									warning */
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*   3,   4,   5,   6,   7,   8,   9	ASCII - Line 1 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  10,  11,  12,  13,  14,  15,  16	ASCII - Line 1 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  17,  18,  19,  20,  21,  22,  23	ASCII - Line 1 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  24,  25,  26,  27,  28,  29,  30	ASCII - Line 2 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  31,  32,  33,  34,  35,  36,  37	ASCII - Line 2 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  38,  39,  40,  41,  42,  43,  44	ASCII - Line 2 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  45,  46,  47,  48,  49,  50,  51	ASCII - Line 3 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  52,  53,  54,  55,  56,  57,  58	ASCII - Line 3 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  59,  60,  61,  62,  63,  64,  65	ASCII - Line 3 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  66,  67,  68,  69,  70,  71,  72	ASCII - Line 4 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  73,  74,  75,  76,  77,  78,  79	ASCII - Line 4 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  80,  81,  82,  83,  84,  85,  86	ASCII - Line 4 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  87,  88,  89,  90,  91,  92,  93	ASCII - Line 5 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  94,  95,  96,  97,  98,  99, 100	ASCII - Line 5 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 101, 102, 103, 104, 105, 106, 107	ASCII - Line 5 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 108, 109, 110, 111, 112, 113, 114	ASCII - Line 6 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 115, 116, 117, 118, 119, 120, 121	ASCII - Line 6 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 122, 123, 124, 125, 126, 127, 128	ASCII - Line 6 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 129, 130, 131, 132, 133, 134, 135	ASCII - Line 7 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 136, 137, 138, 139, 140, 141, 142	ASCII - Line 7 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 143, 144, 145, 146, 147, 148, 149	ASCII - Line 7 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 150, 151, 152, 153, 154, 155, 156	ASCII - Line 8 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 157, 158, 159, 160, 161, 162, 163	ASCII - Line 8 */ 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 164, 165, 166, 167, 168, 169, 170	ASCII - Line 8 */ 							
					0x7D,										/* 171									End sign */ 
					0x00										/* 172									Checksum */ 
				}; 

				textData[2] = _warningID;

				// Textmeldung Zeile 1
				for (uint8_t i = 0; i < 21; i++) {
					textData[3+i] = _message[i];
				}

				_sendData(textData, 173);
			}
			break;
			case HOTT_BINARY_MODE_REQUEST_ID:
			{
				uint8_t  requestID = Serial.read();
/*
    Serial.print("requestMode: '0x");
    Serial.print(requestMode, HEX);
    Serial.print("', requestID: '0x");
    Serial.print(requestID, HEX);
    Serial.println("'");
*/
				switch (requestID) {
#ifdef HOTT_ELECTRIC_AIR_MODULE
				case HOTT_ELECTRIC_AIR_MODULE_ID:
						uint8_t telemetryData[] = {  
							0x7C, 
							HOTT_ELECTRIC_AIR_MODULE_ID,  
							0x00,										/* 2							Alarm */ 
							HOTT_ELECTRIC_AIR_SENSOR_ID, 
							0x00, 0x00,									/* 4, 5							Inverted Value 1 and 2 */ 
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*  6,  7,  8,  9, 10, 11, 12	Cell Voltage 1-7, LSB, in [2mV]/step */ 
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 13, 14, 15, 16, 17, 18, 19	Cell Voltage 1-7, MSB, in [2mV]/step */ 
							0x00, 0x00,									/* 20, 21						Battetry 1, LSB/MSB, in [100mV]/step, 50 == 5V */ 
							0x00, 0x00,									/* 22, 23						Battetry 2, LSB/MSB, in [100mV]/step, 50 == 5V */ 
							0x14,										/* 24							Temp 1, Offset -20, 20 == 0, in [°C] */  
							0x14,										/* 25							Temp 2, Offset -20, 20 == 0, in [°C] */ 
							0xF4, 0x01,									/* 26, 27						Altitude, Offset -500, 500 == 0, in [m] */ 
							0x00, 0x00,									/* 28, 29						Current, LSB/MSB in [100mA]/step, 1 = 0.1A */ 
							0x00, 0x00,									/* 30, 31						Drive Voltage, LSB/MSB */ 
							0x00, 0x00,									/* 32, 33						Capacity, LSB/MSB, in [mAh] */ 
							0x48, 0x00,									/* 34, 35						FIXME climbrate ? m2s */  
							0x78,										/* 36							FIXME climbrate ? m3s */ 
							0x00, 0x00,									/* 37, 38						RPM, LSB/MSB, [10rev]/step, 300 == 3000rpm */ 
							0x00,										/* 39							Electric minutes */ 
							0x00,										/* 40							Electric seconds */ 
							0x00,										/* 41							Speed, in [km/h] */ 
							0x00,										/* 42							Version Number */ 
							0x7D,										/* 43							End sign */ 
							0x00										/* 44							Checksum */ 
						}; 

						telemetryData[2] = _warningID;
						telemetryData[4] = _inverted1;
						telemetryData[5] = _inverted2;

						// battery voltages
						telemetryData[20] = lowByte((uint16_t)(_voltage1*10));
						telemetryData[21] = highByte((uint16_t)(_voltage1*10));
						telemetryData[22] = lowByte((uint16_t)(_voltage2*10));
						telemetryData[23] = highByte((uint16_t)(_voltage2*10));

						// temperatures
						telemetryData[24] = 20+_temperature1;
						telemetryData[25] = 20+_temperature2;

						// altitude
						telemetryData[26] = lowByte(_altitude+500);
						telemetryData[27] = highByte(_altitude+500);

						// current
						telemetryData[28] = lowByte((uint16_t)(_current*10));
						telemetryData[29] = highByte((uint16_t)(_current*10));

						// main voltage
						telemetryData[30] = lowByte((uint16_t)(_mainVoltage*10));
						telemetryData[31] = highByte((uint16_t)(_mainVoltage*10));
						
						// capacity
						telemetryData[32] = lowByte((uint16_t)(_capacity/10));
						telemetryData[33] = highByte((uint16_t)(_capacity/10));

						_sendData(telemetryData, 45);

						break;
#endif
#ifdef HOTT_GENERAL_AIR_MODULE
					case HOTT_GENERAL_AIR_MODULE_ID:
						uint8_t telemetryData[] = {  
							0x7C, 
							HOTT_GENERAL_AIR_MODULE_ID,  
							0x00,										/* 2							Alarm */ 
							HOTT_GENERAL_AIR_SENSOR_ID, 
							0x00, 0x00,									/*  4,  5						Inverted Value 1 and 2 */ 
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00,			/*  6,  7,  8,  9, 10, 11		Voltage Cell 1-6, in [2mV]/step */ 
							0x00, 0x00,									/* 12, 13						Battetry 1, LSB/MSB, in [100mV]/step, 50 == 5V */ 
							0x00, 0x00,									/* 14, 15						Battetry 2, LSB/MSB, in [100mV]/step, 50 == 5V */ 
							0x14,										/* 16							Temp 1, Offset -20, in [°C] */  
							0x14,										/* 17							Temp 2, Offset -20, in [°C] */ 
							0x00,										/* 18							Fuel percentage */ 
							0x00, 0x00,									/* 19, 20						Fuel, LSB/MSB, in  [mL] (milliliter) */ 
							0x00, 0x00,									/* 21, 22						RPM, LSB/MSB, [10rev]/step, 300 == 3000rpm */
							0xF4, 0x01,									/* 23, 24						Altitude, LSB/MSB, Offset -500, 500 = 0m */ 
							0x00, 0x00,									/* 25, 26						Climb rate, FIXME, in m/1s */  
							0x00,										/* 27							Climb rate, FIXME, in m/3s */ 
							0x00, 0x00,									/* 28, 29						Current, LSB/MSB in 100mA steps, 1 = 0.1A */
							0x00, 0x00,									/* 30, 31						Main voltage, LSB/MSB */
							0x00, 0x00,									/* 32, 33						Capacity, LSB/MSB, in [mAh] */
							0x00, 0x00,									/* 34, 35						Speed, in [km/h] */ 
							0x00,										/* 36							min. cell voltage */
							0x00,										/* 37							Cell number with min. voltage */
							0x00, 0x00,									/* 38, 39						RPM2, LSB/MSB, [10rev]/step, 300 == 3000rpm */
							0x00,										/* 40							General error number */
							0x00,										/* 41							Pressure */
							0x00,										/* 42							Version Number */ 
							0x7D,										/* 43							End sign */ 
							0x00										/* 44							Checksum */ 
						}; 

						telemetryData[2] = _warningID;

						// show inverted
						telemetryData[4] = _inverted1;
						telemetryData[5] = _inverted1;
						
						// cell voltages
						telemetryData[6] = _cellVoltage1 * 100 / 2;
						telemetryData[7] = _cellVoltage2 * 100 / 2;
						telemetryData[8] = _cellVoltage3 * 100 / 2;
						telemetryData[9] = _cellVoltage4 * 100 / 2;
						telemetryData[10] = _cellVoltage5 * 100 / 2;
						telemetryData[11] = _cellVoltage6 * 100 / 2;

						// battery voltages
						telemetryData[12] = lowByte((uint16_t)(_voltage1*10));
						telemetryData[13] = highByte((uint16_t)(_voltage1*10));
						telemetryData[14] = lowByte((uint16_t)(_voltage2*10));
						telemetryData[15] = highByte((uint16_t)(_voltage2*10));

						// temperatures
						telemetryData[16] = 20+_temperature1;
						telemetryData[17] = 20+_temperature2;

						// fuel percentage
						telemetryData[18] = _fuelPercentage;

						// fuel
						telemetryData[19] = lowByte(_fuel);
						telemetryData[20] = highByte(_fuel);

						// RPM1
						telemetryData[21] = lowByte((uint16_t)(_rpm1/10));
						telemetryData[22] = highByte((uint16_t)(_rpm1/10));

						// altitude
						telemetryData[23] = lowByte(_altitude+500);
						telemetryData[24] = highByte(_altitude+500);

						// climb rate m/s
						//höherwertiges Byte zum Bezugswert 117 (ca. 0 Meter) berechnen 
						uint8_t OFFSET_STEIGRATE = 117;
						int steigrate_meter = _climbRate1s / 2.560+OFFSET_STEIGRATE;
						//Rest berechnen, um das niederwertige Byte zu bestimmen    
						float rest = _climbRate1s-(2.560*(steigrate_meter-OFFSET_STEIGRATE));
						//Bezugswert ist 40, denn Byte24=117 + Byte23=40 entsprechen 0.0 Metern)
						int OFFSET_DEZIMETER = 40;
						if(_climbRate1s > 0) OFFSET_DEZIMETER = 50;
						int steigrate_dezimeter = OFFSET_DEZIMETER+rest*100;
						//da beim oben stehenden Algorithmus (echte "int"-Werte!) 
						//im niederwertigen Byte23 auch Werte über 255 auftreten könnten,
						//muss hier geprüft werden
						if(steigrate_dezimeter > 0xff){
							steigrate_dezimeter = steigrate_dezimeter -0xff;
							steigrate_meter = steigrate_meter+1;
						}
						telemetryData[25] = steigrate_dezimeter;
						telemetryData[26] = steigrate_meter;

						// climb rate m/3s
						telemetryData[27] = 120 + (uint8_t)_climbRate3s;
						
						// current
						telemetryData[28] = lowByte((uint16_t)(_current*10));
						telemetryData[29] = highByte((uint16_t)(_current*10));
						
						// main voltage
						telemetryData[30] = lowByte((uint16_t)(_mainVoltage*10));
						telemetryData[31] = highByte((uint16_t)(_mainVoltage*10));
						
						// capacity
						telemetryData[32] = lowByte((uint16_t)(_capacity/10));
						telemetryData[33] = highByte((uint16_t)(_capacity/10));
						
						// speed
						telemetryData[34] = lowByte(_speed);
						telemetryData[35] = highByte(_speed);

						// min. cell voltage and id
						telemetryData[36] = _minCellVoltage*100/2;
						telemetryData[37] = _minCellVoltageCell;

						// RPM2
						telemetryData[38] = lowByte((uint16_t)(_rpm2/10));
						telemetryData[39] = highByte((uint16_t)(_rpm2/10));

						// pressure
						telemetryData[41] = _pressure*10;

						_sendData(telemetryData, 45);

						break;
#endif
#ifdef HOTT_GPS_MODULE
					case HOTT_GPS_MODULE_ID:
						uint8_t telemetryData[] = {  
							0x7C, 
							HOTT_GPS_MODULE_ID,  
							0x00,										/* 2							Alarm */ 
							HOTT_GPS_SENSOR_ID, 
							0x00, 0x00,									/*  4,  5						Inverted Value 1 and 2 */ 
							0x00,										/*  6							Flight direction */  
							0x00, 0x00,									/*  7,  8						Ground speed, LSB/MSB */  
							0x00, 0x00, 0x00, 0x00, 0x00,				/*  9, 10, 11, 12, 13			Latitude */ 
							0x00, 0x00, 0x00, 0x00, 0x00,				/* 14, 15, 16, 17, 18			Longitude */ 
							0x00, 0x00,									/* 19, 20						Distance, LSB/MSB, in [m] */ 
							0xF4, 0x01,									/* 21, 22						Altitude, Offset -500, 500 == 0, in [m] */ 
							0x78, 0x00,									/* 23, 24						Climb rate, in [m/s], 1 = 0.01m/s */  
							0x78,										/* 25							Climb rate, in [m/3s], 120 = 0 */ 
							0x00,										/* 26							Number of satelites */  
							0x00,										/* 27							GPS fix character */ 
							0x00,										/* 28							Home direction */ 
							0x00,										/* 29							angle x-direction */ 
							0x00,										/* 30							angle y-direction */ 
							0x00,										/* 31							angle z-direction */ 
							0x00, 0x00,									/* 32, 33						gyro x */ 
							0x00, 0x00,									/* 34, 35						gyro y */  
							0x00, 0x00,									/* 36, 37						gyro z */ 
							0x00,										/* 38							Vibrations */ 
							0x00,										/* 39							ASCII Free Character 4 */ 
							0x00,										/* 40							ASCII Free Character 5 */ 
							0x00,										/* 41							ASCII Free Character 6 */ 
							0x00,										/* 42							Version Number */ 
							0x7D,										/* 43							End sign */ 
							0x00										/* 44							Checksum */ 
						}; 

						telemetryData[2] = _warningID;

						// show inverted
						telemetryData[4] = _inverted1;
						telemetryData[5] = _inverted1;
						
						// Flight direction
						telemetryData[6] = _flightDirection / 2;
						
						// speed
						telemetryData[7] = lowByte(_speed);
						telemetryData[8] = highByte(_speed);
						
						// distance
						telemetryData[19] = lowByte(_distance);
						telemetryData[20] = highByte(_distance);
						
						// altitude
						telemetryData[21] = lowByte(_altitude+500);
						telemetryData[22] = highByte(_altitude+500);

						_sendData(telemetryData, 45);
						
						break;
#endif
#ifdef HOTT_VARIO_MODULE
					case HOTT_VARIO_MODULE_ID:
						uint8_t telemetryData[] = {  
							0x7C, 
							HOTT_VARIO_MODULE_ID,  
							0x00,										/* 2							Alarm */ 
							HOTT_VARIO_SENSOR_ID, 
							0x00, 0x00,									/*  4							Inverted Value 1 */ 
							0xF4, 0x01,									/*  5,  6  						Altitude, Offset -500, 500 == 0, in [m] */
							0xF4, 0x01,									/*  7,  8						Max. altitude, Offset -500, 500 == 0, in [m] */
							0xF4, 0x01,									/*  9, 10						Min. altitude, Offset -500, 500 == 0, in [m] */
							0x30, 0x75,									/* 11, 12						Climb rate, in [m/s] */ 
							0x30, 0x75,									/* 13, 14						Climb rate, in [m/3s] */ 
							0x30, 0x75,									/* 15, 16						Climb rate, in [m/10s] */  
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 17, 18, 19, 20, 21, 22, 23	ASCII */ 
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 24, 25, 26, 27, 28, 29, 30	ASCII */ 
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00,	/* 31, 32, 33, 34, 35, 36, 37	ASCII */ 
							0x00, 0x00, 0x00, 0x00,						/* 38, 39, 40, 41				free */ 
							0x00,										/* 42							Version Number */ 
							0x7D,										/* 43							End sign */ 
							0x00										/* 44							Checksum */ 
						}; 

						// Warnings
						telemetryData[2] = _warningID;

						// show inverted
						telemetryData[4] = _inverted1;
						
						// altitude
						telemetryData[5] = lowByte(_altitude+500);
						telemetryData[6] = highByte(_altitude+500);
						
						// max. altitude
						telemetryData[7] = lowByte(_max_altitude+500);
						telemetryData[8] = highByte(_max_altitude+500);
						
						// min. altitude
						telemetryData[9] = lowByte(_min_altitude+500);
						telemetryData[10] = highByte(_min_altitude+500);

						// climb m/1s							
						//höherwertiges Byte zum Bezugswert 117 (ca. 0 Meter) berechnen 
						uint8_t OFFSET_STEIGRATE = 117;
						int steigrate_meter = _climbRate1s / 2.560+OFFSET_STEIGRATE;
						//Rest berechnen, um das niederwertige Byte zu bestimmen    
						float rest = _climbRate1s-(2.560*(steigrate_meter-OFFSET_STEIGRATE));
						//Bezugswert ist 40, denn Byte24=117 + Byte23=40 entsprechen 0.0 Metern)
						int OFFSET_DEZIMETER = 40;
						if(_climbRate1s > 0) OFFSET_DEZIMETER = 50;
						int steigrate_dezimeter = OFFSET_DEZIMETER+rest*100;
						//da beim oben stehenden Algorithmus (echte "int"-Werte!) 
						//im niederwertigen Byte23 auch Werte über 255 auftreten könnten,
						//muss hier geprüft werden
						if(steigrate_dezimeter > 0xff){
							steigrate_dezimeter = steigrate_dezimeter -0xff;
							steigrate_meter = steigrate_meter+1;
						}
						telemetryData[11] = steigrate_dezimeter;
						telemetryData[12] = steigrate_meter;

						// climb m/3s							
						//höherwertiges Byte zum Bezugswert 117 (ca. 0 Meter) berechnen 
						steigrate_meter = _climbRate3s / 2.560+OFFSET_STEIGRATE;
						//Rest berechnen, um das niederwertige Byte zu bestimmen    
						rest = _climbRate3s-(2.560*(steigrate_meter-OFFSET_STEIGRATE));
						//Bezugswert ist 40, denn Byte24=117 + Byte23=40 entsprechen 0.0 Metern)
						OFFSET_DEZIMETER = 40;
						if(_climbRate3s > 0) OFFSET_DEZIMETER = 50;
						steigrate_dezimeter = OFFSET_DEZIMETER+rest*100;
						//da beim oben stehenden Algorithmus (echte "int"-Werte!) 
						//im niederwertigen Byte23 auch Werte über 255 auftreten könnten,
						//muss hier geprüft werden
						if(steigrate_dezimeter > 0xff){
							steigrate_dezimeter = steigrate_dezimeter -0xff;
							steigrate_meter = steigrate_meter+1;
						}
						telemetryData[13] = steigrate_dezimeter;
						telemetryData[14] = steigrate_meter;

						// climb m/10s							
						//höherwertiges Byte zum Bezugswert 117 (ca. 0 Meter) berechnen 
						steigrate_meter = _climbRate10s / 2.560+OFFSET_STEIGRATE;
						//Rest berechnen, um das niederwertige Byte zu bestimmen    
						rest = _climbRate10s-(2.560*(steigrate_meter-OFFSET_STEIGRATE));
						//Bezugswert ist 40, denn Byte24=117 + Byte23=40 entsprechen 0.0 Metern)
						OFFSET_DEZIMETER = 40;
						if(_climbRate10s > 0) OFFSET_DEZIMETER = 50;
						steigrate_dezimeter = OFFSET_DEZIMETER+rest*100;
						//da beim oben stehenden Algorithmus (echte "int"-Werte!) 
						//im niederwertigen Byte23 auch Werte über 255 auftreten könnten,
						//muss hier geprüft werden
						if(steigrate_dezimeter > 0xff){
							steigrate_dezimeter = steigrate_dezimeter -0xff;
							steigrate_meter = steigrate_meter+1;
						}
						telemetryData[15] = steigrate_dezimeter;
						telemetryData[16] = steigrate_meter;

						// Textmeldung
						for (uint8_t i = 0; i < 21; i++) {
							telemetryData[17+i] = _message[i];
						}

						_sendData(telemetryData, 45);
							
						break;
#endif
#ifdef HOTT_AIRESC_MODULE
					case HOTT_AIRESC_MODULE_ID:
						uint8_t telemetryData[] = {  
							0x7C, 
							HOTT_AIRESC_MODULE_ID,  
							0x00,										/* 2							Alarm */ 
							HOTT_AIRESC_SENSOR_ID, 
							0x00, 0x00,									/*  4,  5						Inverted Value 1 and 2 */ 
							0x00, 0x00,									/*  6,  7						Input voltage, LSB/MSB, in [100mV]/step, 50 == 5V */
							0x00, 0x00,									/*  8,  9						min. input voltage, LSB/MSB, in [100mV]/step, 50 == 5V */  
							0x00, 0x00,									/* 10, 11						Capacity, LSB/MSB, in [mAh] */
							0x00,										/* 12							ESC temperature, in [°C] */
							0x00,										/* 13							ESC max. temperature, in [°C] */
							0x30, 0x75,									/* 14, 15						Current, LSB/MSB in [100mA]/step, 1 = 0.1A */ 
							0x30, 0x75,									/* 16, 17						max. current, LSB/MSB in [100mA]/step, 1 = 0.1A */ 
							0x00, 0x00,									/* 18, 19						RPM, LSB/MSB, [10rev]/step, 300 == 3000rpm */ 
							0x00, 0x00,									/* 20, 21						max. RPM, LSB/MSB, [10rev]/step, 300 == 3000rpm */ 
							0x00,										/* 22							Throttle, in [%] */
							0x00, 0x00,									/* 23, 24						Speed, in [km/h] */ 
							0x00, 0x00,									/* 25, 26						max. Speed, in [km/h] */ 
							0x00,										/* 27							BEC voltage */
							0x00,										/* 28							BEC min. voltage */
							0x00,										/* 29							BEC current */ 
							0x00, 0x00,									/* 30, 31						BEC max. current */
							0x00,										/* 32							PWM */
							0x00,										/* 33							BEC temperature */ 
							0x00,										/* 34							BEC max. temperature */
							0x00,										/* 35							motor temperature */
							0x00,										/* 36							motor max. temperature */
							0x00, 0x00,									/* 37, 38						Motor RPM, LSB/MSB, [10rev]/step, 300 == 3000rpm */ 
							0x00,										/* 39							motor timing */
							0x00,										/* 40							motor timing advanced */
							0x00,										/* 41							motor highest current */
							0x00,										/* 42							Version Number */ 
							0x7D,										/* 43							End sign */ 
							0x00										/* 44							Checksum */ 
						}; 

						
						// main voltage
						telemetryData[6] = lowByte((uint16_t)(_mainVoltage*10));
						telemetryData[7] = highByte((uint16_t)(_mainVoltage*10));
						
						// min. main voltage
						telemetryData[8] = lowByte((uint16_t)(_minMainVoltage*10));
						telemetryData[9] = highByte((uint16_t)(_minMainVoltage*10));
						
						// capacity
						telemetryData[10] = lowByte((uint16_t)(_capacity/10));
						telemetryData[11] = highByte((uint16_t)(_capacity/10));

						telemetryData[12] = _ESCTemperature;
						telemetryData[13] = _maxESCTemperature;
						
						// current
						telemetryData[14] = lowByte((uint16_t)(_current*10));
						telemetryData[15] = highByte((uint16_t)(_current*10));

						// max. current
						telemetryData[16] = lowByte((uint16_t)(_maxCurrent*10));
						telemetryData[17] = highByte((uint16_t)(_maxCurrent*10));

						// RPM1
						telemetryData[18] = lowByte((uint16_t)(_rpm1/10));
						telemetryData[19] = highByte((uint16_t)(_rpm1/10));

						telemetryData[20] = _throttle;

						// speed
						telemetryData[21] = lowByte(_speed);
						telemetryData[22] = highByte(_speed);

						// max speed
						telemetryData[23] = lowByte(_maxSpeed);
						telemetryData[24] = highByte(_maxSpeed);

						telemetryData[25] = (uint8_t)(_BECVoltage*10);
						telemetryData[26] = (uint8_t)(_minBECVoltage*10);

						// BEC current
						telemetryData[27] = _BECCurrent*10;
						telemetryData[28] = lowByte((uint16_t)(_maxBECCurrent*10));
						telemetryData[29] = highByte((uint16_t)(_maxBECCurrent*10));
						
						telemetryData[30] = _PWM;
						
						telemetryData[30] = _BECTemperature;
						telemetryData[31] = _maxBECTemperature;
						
						telemetryData[32] = _motorTemperature;
						telemetryData[33] = _maxMotorTemperature;
						
						// Motor RPM
						telemetryData[34] = lowByte((uint16_t)(_motorRpm/10));
						telemetryData[35] = highByte((uint16_t)(_motorRpm/10));

						telemetryData[36] = _motorTiming;
						telemetryData[37] = _motorAdvancedTiming;

						_sendData(telemetryData, 45);

						break;
#endif
				}
			}
			break;				
		}			
	}
}

void HoTTServer::setWarning(HOTTAlarm_e warningID) {
	_warningID = warningID;
}	
void HoTTServer::setInverted(uint8_t invertedID, uint8_t inverted) {
	invertedID = constrain(invertedID, 0, 1);
	
	switch (invertedID) {
		case HOTT_PRIMARY_INVERTED:
			_inverted1 = inverted;
			break;
		case HOTT_SECONDARY_INVERTED:
			_inverted2 = inverted;
			break;
	}
}
	
void HoTTServer::setCapacity(uint16_t capacity) {
#ifdef HOTT_ELECTRIC_AIR_MODULE || HOTT_GENERAL_AIR_MODULE || HOTT_AIRESC_MODULE
	_capacity = capacity;
#endif
}
void HoTTServer::setCurrent(HOTTCurrent_e sensorID, float current) {
	switch (sensorID) {
#ifdef HOTT_ELECTRIC_AIR_MODULE || HOTT_GENERAL_AIR_MODULE || HOTT_AIRESC_MODULE
		case HOTT_MAIN_CURRENT:
			current = constrain(current, 0.0, 999.9);
			
			_current = current;
			_maxCurrent = max(_maxCurrent, current);
			break;
#endif
#ifdef HOTT_AIRESC_MODULE
		case HOTT_BEC_CURRENT:
			current = constrain(current, 0.0, 25.5);
			
			_BECCurrent = current;
			_maxBECCurrent = max(_maxBECCurrent, current);
			break;
		case HOTT_MAX_MOTOR_CURRENT:
			current = constrain(current, 0.0, 25.5);
			
			_maxMotorCurrent = (uint8_t)current;
			break;
#endif
	}
}
void HoTTServer::setVoltage(HOTTVoltage_e sensorID, float voltage) {
	switch (sensorID) {
		case HOTT_PRIMARY_VOLTAGE:
			_voltage1 = voltage;
			break;
		case HOTT_SECONDARY_VOLTAGE:
			_voltage2 = voltage;
			break;
		case HOTT_MAIN_VOLTAGE:
			_mainVoltage = voltage;
			_minMainVoltage = min(_minMainVoltage, voltage);
			break;
		case HOTT_BEC_VOLTAGE:
			_BECVoltage = voltage;
			_minBECVoltage = min(_minMainVoltage, voltage);
			break;
	}
}
void HoTTServer::setCellVoltage(uint8_t cellNumber, float voltage) {
	voltage = constrain(voltage, 0.0, 5.1);
	
	switch (cellNumber) {
		case 1:
			_cellVoltage1 = voltage;
			break;
		case 2:
			_cellVoltage2 = voltage;
			break;
		case 3:
			_cellVoltage3 = voltage;
			break;
		case 4:
			_cellVoltage4 = voltage;
			break;
		case 5:
			_cellVoltage5 = voltage;
			break;
		case 6:
			_cellVoltage6 = voltage;
			break;
	}
	
	if (_minCellVoltage==0.0) {
		_minCellVoltage = voltage;
		_minCellVoltageCell = cellNumber;
	}
	if (voltage < _minCellVoltage) {
		_minCellVoltage = voltage;
		_minCellVoltageCell = cellNumber;
	}
}
void HoTTServer::setAltitude(int16_t altitude) {
	_altitude = constrain(altitude, -500, 9999);
	
	_min_altitude = min(_altitude, _min_altitude);
	_max_altitude = max(_altitude, _max_altitude);
}
void HoTTServer::setClimbRate(HOTTClimbRate_e climbRateID, float climbRate) {
	climbRate = constrain(climbRate, -296.9, 327.5);

	switch (climbRateID) {
		case HOTT_CLIMBRATE_1S:
			_climbRate1s = climbRate;
			break;
		case HOTT_CLIMBRATE_3S:
			_climbRate3s = climbRate;
			break;
		case HOTT_CLIMBRATE_10S:
			_climbRate10s = climbRate;
			break;
	}
}
void HoTTServer::setFuelPercentage(uint8_t percent) {
	percent = constrain(percent, 0, 100);
	
	_fuelPercentage = percent;
}
void HoTTServer::setFuel(uint16_t fuel) {
	_fuel = fuel;
}
void HoTTServer::setTemperature(HOTTTemperature_e temperatureID, int8_t temperature) {
	temperature = constrain(temperature, -20, 235);
	
	switch (temperatureID) {
		case HOTT_PRIMARY_TEMPERATURE:
			_temperature1 = temperature;
			break;
		case HOTT_SECONDARY_TEMPERATURE:
			_temperature2 = temperature;
			break;
		case HOTT_ESC_TEMPERATURE:
			_ESCTemperature = temperature;
			_maxESCTemperature = max(_maxESCTemperature, temperature);
			break;
		case HOTT_BEC_TEMPERATURE:
			_BECTemperature = temperature;
			_maxBECTemperature = max(_maxBECTemperature, temperature);
			break;
		case HOTT_MOTOR_TEMPERATURE:
			_motorTemperature = temperature;
			_maxMotorTemperature = max(_maxMotorTemperature, temperature);
			break;
	}
}
void HoTTServer::setRPM(HOTTRPM_e rpmID, uint16_t rpm) {
	rpm = constrain(rpm, 0, 65535);
	
	switch (rpmID) {
		case HOTT_PRIMARY_RPM:
			_rpm1 = rpm;
			_maxRpm1 = max(_maxRpm1, rpm);
			break;
		case HOTT_SECONDARY_RPM:
			_rpm2 = rpm;
			_maxRpm2 = max(_maxRpm2, rpm);
			break;
		case HOTT_MOTOR_RPM:
			_motorRpm = rpm;
			break;
	}
}
void HoTTServer::setSpeed(uint16_t speed) {
	_speed = speed;
	_maxSpeed = max(_maxSpeed, speed);
}
void HoTTServer::setPressure(float pressure) {
	pressure = constrain(pressure, 0, 25.5);
	
	_pressure = pressure;
}
void HoTTServer::setDistance(uint16_t distance) {
	_distance = distance;
}
void HoTTServer::setFlightDirection(uint8_t direction) {
	_flightDirection = constrain(_flightDirection,0,360);

	_flightDirection = direction;
}
void HoTTServer::setMessage(char message[], uint8_t length) {
	length = constrain(length, 0, 21);

	for (uint8_t i = 0; i < length; i++) {
		_message[i] = message[i];
	}
	for (uint8_t i = length; i < 21; i++) {
		_message[i] = 0;
	}
}
void HoTTServer::setThrottle(uint8_t throttle) {
	throttle = constrain(throttle, 0, 100);
	
	_throttle = throttle;
}
void HoTTServer::setPWM(uint8_t PWM) {
	_PWM = PWM;
}
void HoTTServer::setMotorTimimg(uint8_t timing) {
	_motorTiming = timing;
}
void HoTTServer::setMotorAdvancedTimimg(uint8_t timing) {
	_motorAdvancedTiming = timing;
}
void HoTTServer::setAngle(HOTTAxis_e axisID, uint8_t angle) {
	angle = constrain(angle, 0, 360);
	
	switch (axisID) {
		case HOTT_X_AXIS:
			_angleX = angle;
			break;
		case HOTT_Y_AXIS:
			_angleY = angle;
			break;
		case HOTT_Z_AXIS:
			_angleZ = angle;
			break;
	}
}
void HoTTServer::setGyro(HOTTAxis_e axisID, uint8_t gyro) {
	gyro = constrain(gyro, 0, 360);
	
	switch (axisID) {
		case HOTT_X_AXIS:
			_gyroX = gyro;
			break;
		case HOTT_Y_AXIS:
			_gyroY = gyro;
			break;
		case HOTT_Z_AXIS:
			_gyroZ = gyro;
			break;
	}	
}

