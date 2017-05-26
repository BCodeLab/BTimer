#ifndef BTimer_h
#define BTimer_h

#include "Arduino.h"

class BTimer;

/**
 * Interface for later implementation
 */
class BTimerHandler {
public:
	virtual void timerCallback(BTimer*) = 0;
};

/**
 * Here the class
 */
class BTimer {
public:

	/**
	 * Constructor
	 */
	BTimer();

	/**
	 * Constructor, set also the interval (milliseconds) and the callback function
	 */
	BTimer(int millis, void (*f)());

	/**
	 * Set the interval (milliseconds)
	 */
	void setInterval(int millis);

	/**
	 * Set the function to call  when the interval has been reached
	 */
	void setCallback(void (*f)());
	/*
	 * Set the handler to involve when the interval has been reached
	 */
	void setCallback(BTimerHandler* extHandler);

	/**
	 * Function to check if the interval has been reached.
	 * Must be included in your loop function
	 */
	void check();

	/**
	 * Stop the timer
	 */
	void stop();

	/**
	 * Start the timer
	 */
	void start();

	/**
	 * Reset elapsed time and start
	 */
	void reset();

	/**
	 * Asset function to use when the interval has been reached.
	 * Call the function or handler.
	 *
	 */
	void launchCallback();
private:
	// the interval to wait
	int tInterval;
	// when it will fire (in milliseconds)
	// last check (in milliseconds)
	unsigned long targetMillis, lastMillis;
	// if timer has to wait a millis overflow
	// if timer has reach a millis overflow altready
	// if the timer is currently enabled
	bool tMillisOverflow, realOverflow, enabled;
	// the callback function to use
	void (*callback)();
	// the handler to involve
	BTimerHandler* extHandler;
};

#endif
