/*
 Name:		H2DataLogger.ino
 Created:	5/5/2023 3:25:38 PM
 Author:	eugen
*/

// the setup function runs once when you press reset or power the board

#include "DTLogger.h"
#include <_Teensy.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

DTLogger DTlog;

void setup() {

	Serial.begin(9600);
	while (!Serial); // wait until Arduino Serial Monitor opens
	setSyncProvider(RTC.get);   // the function to get the time from the RTC
	if (timeStatus() != timeSet)
		Serial.println("Unable to sync with the RTC");
	else
		Serial.println("RTC has set the system time");
	

	DTlog.init();
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (Serial.available()) {
		time_t t = processSyncMessage();
		if (t != 0) {
			RTC.set(t);   // set the RTC and the system time to the received value
			setTime(t);
		}
	}
	
	//create the state object
	subSystemState_t state;
	state.logTime = String(hour()) + ":" + String(minute()) + ":" + String(second()) + " " + String(day()) + "/" + String(month()) + "/" + String(year());
	state.depth = 55.00;
	state.xPos = 22.00;

	//log to sdcard and retrieve the logged string
	String strLogLine = DTlog.logState(&state, LOG_DEPTH + LOG_POSITION + LOG_ATT);
	Serial.println(strLogLine);

	delay(1000);
  
}





/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
	unsigned long pctime = 0L;
	const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

	if (Serial.find(TIME_HEADER)) {
		pctime = Serial.parseInt();
		return pctime;
		if (pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
			pctime = 0L; // return 0 to indicate that the time is not valid
		}
	}
	return pctime;
}
