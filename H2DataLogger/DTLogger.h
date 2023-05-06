// DTLogger.h
// digital twin logger that writes to SDCard storage
// uses format as specified by the DM4DT v1
// metadata_ids as defined in dt_data_config 

#ifndef _DTLOGGER_h
#define _DTLOGGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define LOG_MOTOR 0x40 // (1<<6)
#define LOG_SURFACES 0x20 // (1<<5)
#define LOG_BALLAST 0x10 // (1<<4)
#define LOG_POSITION 0x8 // (1<<3)
#define LOG_DEPTH  0x04 // (1<<2)
#define LOG_ATT 0x02 // (1<<1)
#define LOG_ACC  0x01 // (1<<0)

typedef struct {
	String logTime;

	float acc[3];
	float att[3];
	float depth;
	float xPos;

	float balPos[2];

	float dpPos;
	float tailPos[4];

	float motorTh;
	float mototRPM;
	float motorVolt;
	float motorCurr;
} subSystemState_t;

class DTLogger{

	public:

		DTLogger();

		void init();

		String logState(subSystemState_t* state, int8_t logFlags);
   
	private:
		
};

#endif

