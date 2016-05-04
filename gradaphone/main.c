/*********************************************************************
 *               analog example for Versa1.0
 *	Analog capture on connectors K1, K2, K3 and K5. 
 *********************************************************************/

#define BOARD 8X2A

#include <fruit.h>
//#include <analog.h>
#include <dcmotor.h>
#include <dimmer.h>
#include <switch.h>

t_delay mainDelay;

DCMOTOR_DECLARE(C);
DCMOTOR_DECLARE(D);

void setup(void) {	
//----------- Setup ----------------
	fruitInit();
			
	//pinModeDigitalOut(LED); 	// set the LED pin mode to digital out
	//digitalClear(LED);		// clear the LED
	delayStart(mainDelay, 5000); 	// init the mainDelay to 5 ms

//----------- Analog setup ----------------
	//analogInit();		// init analog module
	/*analogSelect(0,K2);	// assign connector K1 to analog channel 0
	analogSelect(1,K3);
	analogSelect(2,K4);
	analogSelect(3,K5);*/
	switchInit();        // init switch module
	switchSelect(0, PHONE_SW);
	switchSelect(1, PRESENCE_SW);
	
	dimmerInit();        // init dimmer module

//----------- dcmotor setup ----------------
    dcmotorInit(C);
    dcmotorInit(D);
}


void loop() {
// ---------- Main loop ------------
	fraiseService();	// listen to Fraise events
	//analogService();	// analog management routine
	switchService();
	dimmerService();	// dimmer management routine

	if(delayFinished(mainDelay)) // when mainDelay triggers :
	{
		delayStart(mainDelay, 5000); 	// re-init mainDelay
		//analogSend();		// send analog channels that changed
		switchSend();
		DCMOTOR_COMPUTE(C,SYM);
		DCMOTOR_COMPUTE(D,SYM);
	}
}

// Receiving

void fraiseReceiveChar() // receive text
{
	unsigned char c;
	
	c=fraiseGetChar();
	if(c=='L'){		//switch LED on/off 
		c=fraiseGetChar();
		//digitalWrite(LED, c!='0');		
	}
	else if(c=='E') { 	// echo text (send it back to host)
		printf("C");
		c = fraiseGetLen(); 			// get length of current packet
		while(c--) printf("%c",fraiseGetChar());// send each received byte
		putchar('\n');				// end of line
	}	
}


void fraiseReceive() // receive raw
{
	unsigned char c;
	c=fraiseGetChar();
	
	if(c==40) dimmerReceive(); // if first byte is 40, then call dimmer receive function.
	else switch(c) {
	    case 120 : DCMOTOR_INPUT(C) ; break;
	    case 121 : DCMOTOR_INPUT(D) ; break;
	}
}

// ---------- Interrupts ------------
void highInterrupts()
{
	dimmerHighInterrupt();
}


