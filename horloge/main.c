/*********************************************************************
 *               carte horloge :
 *  3 servos sur K1, K2, K3
 *********************************************************************/
#define BOARD Versa1
#include <fruit.h>
#include <servo.h>
#include <switch.h>
t_delay mainDelay;


//----------- Setup ----------------
void setup(void) {	
	fruitInit();			

	servoInit();        // init servo module
	servoSelect(0,K1); // assign connector K1 to servo channel 0
	servoSelect(1,K2); // assign connector K2 to servo channel 1
	servoSelect(2,K3); // assign connector K3 to servo channel 2

	switchInit();        // init switch module
	switchSelect(0, K4);

	delayStart(mainDelay, 5000); 	// init the mainDelay to 5 ms
}

// ---------- Main loop ------------
void loop() {
	fraiseService();// listen to Fraise events
	servoService();	// servo management routine
	switchService();

	if(delayFinished(mainDelay)) // when mainDelay triggers :
	{
		delayStart(mainDelay, 5000); 	// re-init mainDelay
		//analogSend();		// send analog channels that changed
		switchSend();
	}
}

// ---------- Interrupts ------------
void highInterrupts()
{
	servoHighInterrupt();
}

// ---------- Receiving ------------
void fraiseReceive() // receive raw bytes
{
	unsigned char c=fraiseGetChar();
	if(c==20) servoReceive(); // if first byte is 20, then call servo receive function.
}

