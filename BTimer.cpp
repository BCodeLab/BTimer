#include "Arduino.h"

#include "BTimer.h"
#include "limits.h"

BTimer::BTimer() {
    this->enabled = false;
    this->tMillisOverflow = false;
    this->realOverflow = false;
    this->lastMillis = millis();
    this->callback = 0;
}

BTimer::BTimer(int interval, void (*f)()) {
    this->enabled = false;
    this->tInterval = interval;
    this->callback = f;
    this->tMillisOverflow = false;
    this->realOverflow = false;
    this->lastMillis = millis();
}

void BTimer::setInterval(int interval) {
    this->tInterval = interval;
}

void BTimer::setCallback(void (*f)()) {
    this->callback = f;
    this->extHandler = 0;
}

void BTimer::setCallback (BTimerHandler* extHandler) {
    this->callback = 0;
    this->extHandler = extHandler;
}

void BTimer::start() {
    this->enabled = true;
    this->reset();
}

void BTimer::stop() {
    this->enabled = false;
}

void BTimer::reset() {
    unsigned long cMillis = millis();

    if (ULONG_MAX - this->tInterval > cMillis) {
        this->targetMillis = cMillis + this->tInterval;
    } else {
        this->tMillisOverflow = true;
        this->targetMillis = this->tInterval - (ULONG_MAX - cMillis);
    }
}

void BTimer::check() {
    if(!this->enabled){
        return;
    }
    
    unsigned long cMillis = millis();
    if (this->lastMillis > cMillis) {
        this->realOverflow = true;
    }

    if (!this->tMillisOverflow && cMillis > this->targetMillis) {

        this->launchCallback();
        this->reset();
    }
    if ((this->tMillisOverflow && this->realOverflow) && cMillis > this->targetMillis) {

        this->launchCallback();
        this->reset();

    }

    this->lastMillis = cMillis;
}

void BTimer::launchCallback(){
	if(this->callback != 0){
        this->callback();
	}
	else if(this->extHandler != 0){
		this->extHandler->timerCallback(this);
	}
}




